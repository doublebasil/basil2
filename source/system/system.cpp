#include "system.hpp"

#include "oled.hpp"
#include "pico/cyw43_arch.h"
#include "hardware/rtc.h"
#include "sd_card.h"
#include "ff.h"
#include "pump.hpp"
#include "hardware/watchdog.h"
#include "settings_reader.hpp"
#include "ntp.hpp"
#include "pico/time.h"
// #include "pico/util/datetime.h"

char m_text1[30];
char m_text2[30];
datetime_t m_datetime;

/* INITIALISATION MODULE SCOPE FUNCTION PROTOTYPES */
static inline void m_initialiseOled( void );
static inline void m_initialiseCyw43( void );
static inline void m_initialiseAdc( void );
static inline void m_initialisePump( void );
static inline void m_initialiseSdCardDriver( void );
static inline void m_initialiseRtc( void );
static inline void m_sdSuccessfulReadMessage( t_sdCardSettings* sdCardSettingsPtr );
static inline void m_sdFailedReadMessage( void );
/* SYSTEM UPDATE HELPER FUNCTIONS */
static void m_idleSetup( t_globalData* globalDataPtr );
static void m_idleUpdate( t_globalData* globalDataPtr );
static void m_infoSetup( t_globalData* globalDataPtr );
static void m_infoUpdate( t_globalData* globalDataPtr );
static void m_wateringSetup( t_globalData* globalDataPtr );
static void m_wateringUpdate( t_globalData* globalDataPtr );
/* OTHER */
static void m_checkInput( t_globalData* globalDataPtr );
static void m_dayOfTheWeek( char* strPrt, uint8_t strLen, uint8_t dayOfTheWeek );
static time_t m_datetimeToEpoch( datetime_t* datetimePtr );
static void m_epochToDatetime( uint64_t epoch, datetime_t* datetimePtr );
static bool m_checkRecyclingBinday( t_globalData* globalDataPtr );
static bool m_checkLandfillBinday( t_globalData* globalDataPtr );
static void m_calculateNextWateringTime( t_globalData* globalDataPtr );
static void m_propaganda( void );
static void m_calibratePump( void );

/* PUBLIC METHOD IMPLEMENTATION */
int system_initialise( t_globalData* globalDataPtr )
{
    // Initialise parts of the global data struct that haven't been set yet
    globalDataPtr->hardwareData.displayWidth = OLED_DISPLAY_WIDTH;
    globalDataPtr->hardwareData.displayHeight = OLED_DISPLAY_HEIGHT;
    // Initialise the OLED
    m_initialiseOled();
    // Initialise the WiFi driver, also needed for built-in LED
    m_initialiseCyw43();
    // Initialise ADC
    m_initialiseAdc();
    // Initialise pump
    m_initialisePump();
    // Init the SD card driver
    m_initialiseSdCardDriver();
    // Init the RTC (Real Time Clock)
    m_initialiseRtc();
    // Init the buttons
    gpio_init( INFO_BUTTON_PIN );
    gpio_set_dir( INFO_BUTTON_PIN, GPIO_IN );
    gpio_init( WATER_BUTTON_PIN );
    gpio_set_dir( WATER_BUTTON_PIN, GPIO_IN );
    // Check if the pump is being manually calibrated
    if( gpio_get( INFO_BUTTON_PIN ) && gpio_get( WATER_BUTTON_PIN ) )
        m_calibratePump();
    // Now attempt to read the SD card
    oled_terminalWrite( "" );
    oled_terminalWrite( "Reading SDC..." );
    if( settings_readFromSDCard( globalDataPtr ) != 0 )
    {
        m_sdFailedReadMessage();
        return 1;
    }
    // If sd card reading was successful:
    m_sdSuccessfulReadMessage( &(globalDataPtr->sdCardSettings) );
    sleep_ms( MESSAGE_READ_DELAY_MS );

    // Attempt to connect to WiFi
    uint8_t attempts = 0U;
    int wifiResult;
    while( attempts < MAX_WIFI_CONNECTION_ATTEMPTS )
    {
        oled_terminalWrite( "" );
        oled_terminalWrite( "Connecting to:" );
        oled_terminalWrite( globalDataPtr->sdCardSettings.wifiSsid );

        wifiResult = cyw43_arch_wifi_connect_timeout_ms( 
            globalDataPtr->sdCardSettings.wifiSsid, 
            globalDataPtr->sdCardSettings.wifiPassword, 
            CYW43_AUTH_WPA2_AES_PSK, 
            30000 );

        if( wifiResult == 0 )
            break;

        ++attempts;
        oled_terminalWrite( "Failed" );
        oled_terminalWrite( "Waiting before" );
        oled_terminalWrite( "retry..." );
        sleep_ms( WIFI_CONNECTION_RETRY_DELAY_MS );
    }
    if( wifiResult != 0 )
    {
        oled_terminalWrite( "Max connection" );
        oled_terminalWrite( "failures reached" );
        return 1;
    }

    oled_terminalWrite( "" );
    oled_terminalWrite( "Connection success" );
    sleep_ms( MESSAGE_READ_DELAY_MS );

    oled_terminalWrite( "" );
    oled_terminalWrite( "Connect to NTP" );
    if( ntp_doTheNtpStuff() != 0 )
    {
        oled_terminalWrite( "NTP process failed" );
        return 1;
    }

    m_checkLandfillBinday( globalDataPtr );
    m_checkRecyclingBinday( globalDataPtr );

    oled_terminalWrite( "" );
    oled_terminalWrite( "Sys init done" );

    sleep_ms( MESSAGE_READ_DELAY_MS );

    oled_terminalDeinit();
    oled_clear();

    globalDataPtr->currentState = e_sysState_showInfo;
    globalDataPtr->stateTimeout = make_timeout_time_ms( STATE_TIMEOUT_DELAY_MS );

    globalDataPtr->rebootTime = make_timeout_time_ms( WORKING_REBOOT_DELAY_MS );

    m_calculateNextWateringTime( globalDataPtr );

    return 0;
}

void system_reboot( void )
{
    // Reboot the board in 1 ms using the watchdog
    watchdog_enable( 1, false );
    for( ;; ) {}
}

void system_update( t_globalData* globalDataPtr )
{
    m_checkInput( globalDataPtr );
    
    switch( globalDataPtr->currentState )
    {
        case e_sysState_idle:
        {
            if( globalDataPtr->previousState != e_sysState_idle )
            {
                m_idleSetup( globalDataPtr );
                globalDataPtr->previousState = e_sysState_idle;
            }
            else
            {
                m_idleUpdate( globalDataPtr );
            }
        }
        break;
        case e_sysState_showInfo:
        {
            if( globalDataPtr->previousState != e_sysState_showInfo )
            {
                m_infoSetup( globalDataPtr );
                globalDataPtr->previousState = e_sysState_showInfo;
            }
            else
            {
                m_infoUpdate( globalDataPtr );
            }
        }
        break;
        case e_sysState_watering:
        {
            if( globalDataPtr->previousState != e_sysState_watering )
            {
                m_wateringSetup( globalDataPtr );
                globalDataPtr->previousState = e_sysState_watering;
            }
            else
            {
                m_wateringUpdate( globalDataPtr );
            }
        }
        break;
        default:
        case e_sysState_notSet:
        {
            globalDataPtr->currentState = e_sysState_idle;
            globalDataPtr->previousState = e_sysState_notSet;
        }
        break;
    }

}

/* INITIALISATION MODULE SCOPE FUNCITON IMPLEMENTATION  */
static inline void m_initialiseOled( void )
{
    if( oled_init( OLED_DATA_IN_PIN, OLED_CLOCK_PIN, OLED_CHIP_SELECT_PIN, 
        OLED_DATA_COMMAND_PIN, OLED_RESET_PIN, OLED_SPI_OUTPUT, OLED_BAUD_RATE_HZ, 
        OLED_DISPLAY_WIDTH, OLED_DISPLAY_HEIGHT ) != 0 )
    {
        for( ;; )
        {
            printf( "oled_init failed\n" );
            sleep_ms( 1000 );
        }
    }
    // Create a terminal with the OLED
    oled_terminalInit( TERMINAL_FONT_12, TERMINAL_INIT_COLOUR );
    oled_terminalWrite( "OLED initialised" );
}

static inline void m_initialiseCyw43( void )
{
    // Intialise the CYW43 driver
    oled_terminalWrite( "CYW43 initialising" );
    if( cyw43_arch_init() )
    {
        oled_terminalWrite( "Failed" );
        for( ;; )
        {
            printf( "cyw43_arch_init failed\n" );
            sleep_ms( 1000 );
        }
    }
    // Enable STA (Station) mode
    oled_terminalWrite( "Enable STA mode" );
    cyw43_arch_enable_sta_mode();
}

static inline void m_initialiseAdc( void )
{
    oled_terminalWrite( "Initialising ADC" );
    adc_init();
}

static inline void m_initialisePump( void )
{
    oled_terminalWrite( "Initialising pump" );
    pump_init( PUMP_CONTROL_PIN, PUMP_ADC_PIN );
}

static inline void m_initialiseSdCardDriver( void )
{
    oled_terminalWrite( "Init SDC driver" );
    if( !sd_init_driver() )
    {
        oled_terminalWrite( "Failed" );
        for( ;; )
        {
            printf( "sd_init_driver failed\n" );
            sleep_ms( 1000 );
        }
    }
}

static inline void m_initialiseRtc( void )
{
    oled_terminalWrite( "Init RTC" );
    rtc_init();
}

static inline void m_sdSuccessfulReadMessage( t_sdCardSettings* sdCardSettingsPtr )
{
    oled_terminalWrite( "Settings read" );
    oled_terminalWrite( "successfully" );
    oled_terminalWrite( "" );
    oled_terminalWrite( "Watering at:" );
    char text[20];
    int32_t secondsSinceMidnight;
    for( uint8_t index = 0U; index < MAX_NUMBER_OF_WATERING_TIMES; index++ )
    {
        secondsSinceMidnight = sdCardSettingsPtr->wateringTimes[index];
        if( secondsSinceMidnight == -1 )
            break;
        
        snprintf( text, sizeof( text ), "-> %02lld:%02lld", 
            secondsSinceMidnight / ( 60LL * 60LL ),
            ( secondsSinceMidnight % ( 60LL * 60LL ) ) / 60LL );
        
        oled_terminalWrite( text );
    }
    
    snprintf( text, sizeof( text ), "for %d ms", sdCardSettingsPtr->wateringDurationMs );
    oled_terminalWrite( text );
}

static inline void m_sdFailedReadMessage( void )
{
    oled_terminalWrite( "FAILED to read" );
    oled_terminalWrite( "settings" );
}

/* SYSTEM UPDATE HELPER FUNCTIONS */
static void m_idleSetup( t_globalData* globalDataPtr )
{
    oled_deinitAll();
    oled_clear();
    // Are there any warnings to display?
    if( globalDataPtr->tankState == e_tankState_dry )
    {
        oled_terminalInit( 20, RGB565_PURE_RED );
        oled_terminalSetLine( 2 );
        oled_terminalWrite( "Warning!" );
        oled_terminalWrite( "Dry tank" );
    }
}

static void m_idleUpdate( t_globalData* globalDataPtr )
{
    // Check button inputs
    if( globalDataPtr->waterButton == e_input_long )
    {
        globalDataPtr->currentState = e_sysState_watering;
    }
    else if( globalDataPtr->infoButton == e_input_press )
    {
        globalDataPtr->currentState = e_sysState_showInfo;
    }

    // Check if it's time to water
    if( absolute_time_diff_us( get_absolute_time(), globalDataPtr->nextWater ) < 0 )
    {
        globalDataPtr->currentState = e_sysState_watering;
    }
    
    // Check if it's time to reboot
    else if( absolute_time_diff_us( get_absolute_time(), globalDataPtr->rebootTime ) < 0 )
    {
        system_reboot();
    }
}

static void m_infoSetup( t_globalData* globalDataPtr )
{
    oled_deinitAll();
    oled_clear();

    if( m_checkLandfillBinday( globalDataPtr ) )
    {
        // Display the landfill bin image
        oled_sdWriteImage( "greenbin128.txt", 0, 0 );
        sleep_ms( IMAGE_DISPLAY_TIME_MS );
        oled_clear();
    }
    if( m_checkRecyclingBinday( globalDataPtr ) )
    {
        // Display the recycling bin image
        oled_sdWriteImage( "bluebin128.txt", 0, 0 );
        sleep_ms( IMAGE_DISPLAY_TIME_MS );
        oled_clear();
    }

    // Create a terminal 
    oled_terminalInit( 12, TERMINAL_INFO_COLOUR );

    rtc_get_datetime( &m_datetime );
    m_dayOfTheWeek( &m_text2[0], sizeof( m_text2 ), m_datetime.dotw );
    snprintf( m_text1, sizeof( m_text1 ), "%s %02d/%02d/%02d",
        m_text2, m_datetime.day, m_datetime.month, ( m_datetime.year % 100 ) );
    oled_terminalSetLine( 0 );
    oled_terminalWrite( m_text1 );

    snprintf( m_text1, sizeof( m_text1 ), "%02d:%02d:%02d",
        m_datetime.hour, m_datetime.min, m_datetime.sec );
    oled_terminalSetLine( 1 );
    oled_terminalWrite( m_text1 );

    // snprintf( m_text1, sizeof( m_text1 ), "%lld", m_datetimeToEpoch( &m_datetime ) );
    // oled_terminalSetLine( 2 );
    // oled_terminalWrite( m_text1 );

    // The bindays aren't updated in the infoUpdate function
    oled_terminalSetLine( 3 );
    oled_terminalWrite( "Next bin days:" );
    snprintf( m_text1, sizeof( m_text1 ), "Recycling %02d/%02d/%02d", globalDataPtr->currentRecycling.day, globalDataPtr->currentRecycling.month, globalDataPtr->currentRecycling.year );
    oled_terminalWrite( m_text1 );
    snprintf( m_text1, sizeof( m_text1 ), "Landfill  %02d/%02d/%02d", globalDataPtr->currentLandfill.day, globalDataPtr->currentLandfill.month, globalDataPtr->currentLandfill.year );
    oled_terminalWrite( m_text1 );

    oled_terminalSetLine( 7 );
    oled_terminalWrite( "Next watering in:" );
    oled_terminalSetLine( 8 );
    int64_t msToWatering = absolute_time_diff_us( get_absolute_time(), globalDataPtr->nextWater ) / 1000LL;
    if( msToWatering < 0 )
    {
        int64_t tempMsToWatering = msToWatering * -1;
        int64_t seconds = tempMsToWatering / 1000;
        int8_t hours = seconds / 3600;
        int8_t minutes = (seconds % 3600) / 60;
        int8_t remainingSeconds = seconds % 60;
        // int16_t remainingMilliseconds = tempMsToWatering % 1000;
        // snprintf( m_text1, sizeof( m_text1 ), "-%02u:%02u:%02u.%03u", hours, minutes, remainingSeconds, remainingMilliseconds );
        snprintf( m_text1, sizeof( m_text1 ), "-%02u:%02u:%02u", hours, minutes, remainingSeconds );
    }
    else
    {
        int64_t seconds = msToWatering / 1000;
        int8_t hours = seconds / 3600;
        int8_t minutes = (seconds % 3600) / 60;
        int8_t remainingSeconds = seconds % 60;
        // int16_t remainingMilliseconds = msToWatering % 1000;
        // snprintf( m_text1, sizeof( m_text1 ), "%02u:%02u:%02u.%03u", hours, minutes, remainingSeconds, remainingMilliseconds );
        snprintf( m_text1, sizeof( m_text1 ), "%02u:%02u:%02u", hours, minutes, remainingSeconds );
    }
    oled_terminalWrite( m_text1 );

    oled_terminalSetLine( oled_terminalGetHeightInCharacters() );
    switch( globalDataPtr->tankState )
    {
        case e_tankState_ok:
        {
            oled_terminalWriteNoScroll( "Tank is ok" );
        }
        break;
        case e_tankState_dry:
        {
            oled_terminalWriteNoScroll( "WARNING DRY TANK" );
        }
        break;
        case e_tankState_unknown:
        default:
        {
            oled_terminalWriteNoScroll( "Tank state unknown" );
        }
        break;
    }

    globalDataPtr->stateTimeout = make_timeout_time_ms( STATE_TIMEOUT_DELAY_MS );
}

static void m_infoUpdate( t_globalData* globalDataPtr )
{
    // Check for timeout
    if( ( is_nil_time( globalDataPtr->stateTimeout ) == false )
        && ( absolute_time_diff_us( get_absolute_time(), globalDataPtr->stateTimeout ) < 0 ) )
    {
        // Timeout
        globalDataPtr->currentState = e_sysState_idle;
        return;
    }
    // Check for button presses
    if( globalDataPtr->waterButton == e_input_long )
    {
        // Change to watering
        globalDataPtr->currentState = e_sysState_watering;
        return;
    }
    else if( globalDataPtr->infoButton == e_input_press )
    {
        // Extend the timeout
        globalDataPtr->stateTimeout = make_timeout_time_ms( STATE_TIMEOUT_DELAY_MS );
    }
    else if( globalDataPtr->infoButton == e_input_long )
    {
        m_propaganda();
    }

    rtc_get_datetime( &m_datetime );
    m_dayOfTheWeek( &m_text2[0], sizeof( m_text2 ), m_datetime.dotw );
    snprintf( m_text1, sizeof( m_text1 ), "%s %02d/%02d/%02d",
        m_text2, m_datetime.day, m_datetime.month, ( m_datetime.year % 100 ) );
    oled_terminalSetLine( 0 );
    oled_terminalWrite( m_text1 );

    snprintf( m_text1, sizeof( m_text1 ), "%02d:%02d:%02d",
        m_datetime.hour, m_datetime.min, m_datetime.sec );
    oled_terminalSetLine( 1 );
    oled_terminalWrite( m_text1 );

    // snprintf( m_text1, sizeof( m_text1 ), "%lld", m_datetimeToEpoch( &m_datetime ) );
    // oled_terminalSetLine( 2 );
    // oled_terminalWrite( m_text1 );

    oled_terminalSetLine( 8 );
    int64_t msToWatering = absolute_time_diff_us( get_absolute_time(), globalDataPtr->nextWater ) / 1000LL;
    if( msToWatering < 0 )
    {
        int64_t tempMsToWatering = msToWatering * -1;
        int64_t seconds = tempMsToWatering / 1000;
        int8_t hours = seconds / 3600;
        int8_t minutes = (seconds % 3600) / 60;
        int8_t remainingSeconds = seconds % 60;
        // int16_t remainingMilliseconds = tempMsToWatering % 1000;
        // snprintf( m_text1, sizeof( m_text1 ), "-%02u:%02u:%02u.%03u", hours, minutes, remainingSeconds, remainingMilliseconds );
        snprintf( m_text1, sizeof( m_text1 ), "-%02u:%02u:%02u", hours, minutes, remainingSeconds );
    }
    else
    {
        int64_t seconds = msToWatering / 1000;
        int8_t hours = seconds / 3600;
        int8_t minutes = (seconds % 3600) / 60;
        int8_t remainingSeconds = seconds % 60;
        // int16_t remainingMilliseconds = msToWatering % 1000;
        // snprintf( m_text1, sizeof( m_text1 ), "%02u:%02u:%02u.%03u", hours, minutes, remainingSeconds, remainingMilliseconds );
        snprintf( m_text1, sizeof( m_text1 ), "%02u:%02u:%02u", hours, minutes, remainingSeconds );
    }
    oled_terminalWrite( m_text1 );

}

static void m_wateringSetup( t_globalData* globalDataPtr )
{
    // Clear the screen
    oled_deinitAll();
    oled_clear();

    // Run the pump (important)
    pump_run( globalDataPtr );

    // Calculate the next watering time
    m_calculateNextWateringTime( globalDataPtr );

    // Set a state timeout
    globalDataPtr->stateTimeout = make_timeout_time_ms( STATE_TIMEOUT_DELAY_MS );
}

static void m_wateringUpdate( t_globalData* globalDataPtr )
{
    // Check for button inputs
    if( globalDataPtr->infoButton == e_input_press )
    {
        printf("info button exited watering state\n");
        globalDataPtr->currentState = e_sysState_showInfo;
    }
    else if( globalDataPtr->waterButton == e_input_long )
    {
        // Extend the timeout to prevent continuous watering if the button gets stuck
        globalDataPtr->stateTimeout = make_timeout_time_ms( STATE_TIMEOUT_DELAY_MS );
    }
    // Check for timeout
    if( ( is_nil_time( globalDataPtr->stateTimeout ) == false )
        && ( absolute_time_diff_us( get_absolute_time(), globalDataPtr->stateTimeout ) < 0 ) )
    {
        // Timeout
        printf("watering state timed out\n");
        globalDataPtr->currentState = e_sysState_idle;
        return;
    }
}

/* OTHER */
static void m_checkInput( t_globalData* globalDataPtr )
{
    // Input button
    static absolute_time_t infoButtonHoldStart = nil_time;
    static bool infoButtonPreviousState = false;
    // Water button
    static absolute_time_t waterButtonHoldStart = nil_time;
    static bool waterButtonPreviousState = false;

    if( gpio_get( INFO_BUTTON_PIN ) )
    {
        if( infoButtonPreviousState == true )
        {
            // Check for long press
            if( ( is_nil_time( infoButtonHoldStart ) == false )
                && ( absolute_time_diff_us( infoButtonHoldStart, get_absolute_time() ) > ( LONG_PRESS_TIME_MS * 1000LL ) ) )
            {
                globalDataPtr->infoButton = e_input_long;
            }
            else
            {
                globalDataPtr->infoButton = e_input_none;
            }
        }
        else
        {
            // Short press
            infoButtonPreviousState = true;
            globalDataPtr->infoButton = e_input_press;
            infoButtonHoldStart = get_absolute_time();
        }
    }
    else
    {
        infoButtonPreviousState = false;
        globalDataPtr->infoButton = e_input_none;
    }

    if( gpio_get( WATER_BUTTON_PIN ) )
    {
        if( waterButtonPreviousState == true )
        {
            // Check for long press
            if( ( is_nil_time( waterButtonHoldStart ) == false )
                && ( absolute_time_diff_us( waterButtonHoldStart, get_absolute_time() ) > ( LONG_PRESS_TIME_MS * 1000LL ) ) )
            {
                globalDataPtr->waterButton = e_input_long;
            }
            else
            {
                globalDataPtr->waterButton = e_input_none;
            }
        }
        else
        {
            // Short press
            waterButtonPreviousState = true;
            globalDataPtr->waterButton = e_input_press;
            waterButtonHoldStart = get_absolute_time();
        }
    }
    else
    {
        waterButtonPreviousState = false;
        globalDataPtr->waterButton = e_input_none;
    }

}

static void m_dayOfTheWeek( char* strPrt, uint8_t strLen, uint8_t dayOfTheWeek )
{
    switch( dayOfTheWeek )
    {
        case 0:
        {
            snprintf( strPrt, strLen, "Sunday" );
        }
        break;
        case 1:
        {
            snprintf( strPrt, strLen, "Monday" );
        }
        break;
        case 2:
        {
            snprintf( strPrt, strLen, "Tuesday" );
        }
        break;
        case 3:
        {
            snprintf( strPrt, strLen, "Wednesday" );
        }
        break;
        case 4:
        {
            snprintf( strPrt, strLen, "Thursday" );
        }
        break;
        case 5:
        {
            snprintf( strPrt, strLen, "Friday" );
        }
        break;
        case 6:
        {
            snprintf( strPrt, strLen, "Saturday" );
        }
        break;
        default:
        {
            snprintf( strPrt, strLen, "ERR" );
        }
    }
}

static time_t m_datetimeToEpoch( datetime_t* datetimePtr )
{
    struct tm timeinfo;

    timeinfo.tm_year = datetimePtr->year - 1900;  // years since 1900
    timeinfo.tm_mon = datetimePtr->month - 1;     // months since January [0,11]
    timeinfo.tm_mday = datetimePtr->day;          // day of the month [1,31]
    timeinfo.tm_hour = datetimePtr->hour;         // hours since midnight [0,23]
    timeinfo.tm_min = datetimePtr->min;           // minutes after the hour [0,59]
    timeinfo.tm_sec = datetimePtr->sec;

    return mktime( &timeinfo );
}

static void m_epochToDatetime( uint64_t epoch, datetime_t* datetimePtr )
{
    time_t timetEpoch = (time_t) epoch;
    struct tm *utc = gmtime( &timetEpoch );

    datetimePtr->year = utc->tm_year + 1900;
    datetimePtr->month= utc->tm_mon + 1;
    datetimePtr->day = utc->tm_mday;
    datetimePtr->hour = utc->tm_hour;
    datetimePtr->min = utc->tm_min;
    datetimePtr->sec = utc->tm_sec;
    datetimePtr->dotw = utc->tm_wday;
}

static bool m_checkRecyclingBinday( t_globalData* globalDataPtr )
{
    // Ensure m_datetime is up to date
    rtc_get_datetime( &m_datetime );
    // Convert m_datetime into an epoch
    uint64_t epoch = (uint64_t) m_datetimeToEpoch( &m_datetime );

    // Check if we need to calculate bin day. unixEpoch has default value 0 so this works first time round too
    if( epoch > globalDataPtr->currentRecycling.unixEpoch )
    {
        bool set = false;

        for( uint16_t index = 0U; index < globalDataPtr->sdCardSettings.recyclingEntries; index ++ )
        {
            if( epoch < globalDataPtr->sdCardSettings.recyclingUnix[index] )
            {
                globalDataPtr->currentRecycling.unixEpoch = globalDataPtr->sdCardSettings.recyclingUnix[index];
                set = true;
                break;
            }
        }

        if( set == false )
        {
            printf( "Ran out of bin day dates!\n" );
            globalDataPtr->currentRecycling.unixEpoch = 0;
            globalDataPtr->currentRecycling.day = 0;
            globalDataPtr->currentRecycling.month = 0;
            globalDataPtr->currentRecycling.year = 0;
            return false;
        }
        else // if set == true
        {
            // Calculate the day, month and year for this epoch
            datetime_t datetime;
            m_epochToDatetime( globalDataPtr->currentRecycling.unixEpoch, &datetime );
            globalDataPtr->currentRecycling.day = datetime.day;
            globalDataPtr->currentRecycling.month = datetime.month;
            globalDataPtr->currentRecycling.year = datetime.year;
        }
    }

    // Check if bin day is soon
    if( epoch > ( globalDataPtr->currentRecycling.unixEpoch - ( BINDAY_WARNING_TIME_HOURS * 60ULL * 60ULL ) ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool m_checkLandfillBinday( t_globalData* globalDataPtr )
{
    // Ensure m_datetime is up to date
    rtc_get_datetime( &m_datetime );
    // Convert m_datetime into an epoch
    uint64_t epoch = (uint64_t) m_datetimeToEpoch( &m_datetime );

    // Check if we need to calculate bin day. unixEpoch has default value 0 so this works first time round too
    if( epoch > globalDataPtr->currentLandfill.unixEpoch )
    {
        bool set = false;

        for( uint16_t index = 0U; index < globalDataPtr->sdCardSettings.landfillEntries; index ++ )
        {
            if( epoch < globalDataPtr->sdCardSettings.landfillUnix[index] )
            {
                globalDataPtr->currentLandfill.unixEpoch = globalDataPtr->sdCardSettings.landfillUnix[index];
                set = true;
                break;
            }
        }

        if( set == false )
        {
            printf( "Ran out of bin day dates!\n" );
            globalDataPtr->currentLandfill.unixEpoch = 0;
            globalDataPtr->currentLandfill.day = 0;
            globalDataPtr->currentLandfill.month = 0;
            globalDataPtr->currentLandfill.year = 0;
            return false;
        }
        else // if set == true
        {
            // Calculate the day, month and year for this epoch
            datetime_t datetime;
            m_epochToDatetime( globalDataPtr->currentLandfill.unixEpoch, &datetime );
            globalDataPtr->currentLandfill.day = datetime.day;
            globalDataPtr->currentLandfill.month = datetime.month;
            globalDataPtr->currentLandfill.year = datetime.year;
        }
    }

    // Check if bin day is soon
    if( epoch > ( globalDataPtr->currentLandfill.unixEpoch - ( BINDAY_WARNING_TIME_HOURS * 60ULL * 60ULL ) ) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

static void m_calculateNextWateringTime( t_globalData* globalDataPtr )
{
    // Get the current time
    rtc_get_datetime( &m_datetime );
    // Calculate the number of seconds since midnight
    int64_t secondsSinceMidnight = m_datetime.sec + ( (int64_t) m_datetime.min * 60LL ) + ( (int64_t) m_datetime.hour * 60LL * 60LL );
    // Calculate the next watering time
    bool set = false;
    for( uint8_t wateringIndex = 0U; wateringIndex < MAX_NUMBER_OF_WATERING_TIMES; wateringIndex++ )
    {
        if( secondsSinceMidnight < globalDataPtr->sdCardSettings.wateringTimes[wateringIndex] )
        {
            globalDataPtr->nextWater = make_timeout_time_ms( ( (int64_t) globalDataPtr->sdCardSettings.wateringTimes[wateringIndex] - secondsSinceMidnight ) * 1000LL );
            set = true;
            break;
        }
    }
    // If set == false, then set to the first watering time tomorrow
    if( set == false )
    {
        int64_t secondsToMidnight = SECONDS_PER_DAY - secondsSinceMidnight;
        globalDataPtr->nextWater = make_timeout_time_ms( ( (int64_t) globalDataPtr->sdCardSettings.wateringTimes[0] + secondsToMidnight ) * 1000LL );
    }
}

static void m_propaganda( void )
{
    switch( to_ms_since_boot( get_absolute_time() ) % 6 )
    {
        case 0:
        {
            oled_sdWriteImage( "p1.txt", 0, 0 );
        }
        break;
        case 1:
        {
            oled_sdWriteImage( "p2.txt", 0, 0 );
        }
        break;
        case 2:
        {
            oled_sdWriteImage( "p3.txt", 0, 0 );
        }
        break;
        case 3:
        {
            oled_sdWriteImage( "p4.txt", 0, 0 );
        }
        break;
        case 4:
        {
            oled_sdWriteImage( "p5.txt", 0, 0 );
        }
        break;
        case 5:
        {
            oled_sdWriteImage( "p6.txt", 0, 0 );
        }
        break;
    }
    sleep_ms( IMAGE_DISPLAY_TIME_MS );
    oled_clear();
    oled_terminalSetNewColour( 0x0000 );
    oled_terminalSetNewColour( TERMINAL_INFO_COLOUR );
}

static void m_calibratePump( void )
{
    oled_deinitAll();
    oled_clear();
    oled_terminalInit( 12, 0xFFFFU );
    oled_terminalWrite( "CALIBRATING PUMP" );
    sleep_ms( 1000 );
    printf( "---PUMP CALIBRATION---\n" );
    gpio_put( PUMP_CONTROL_PIN, 1 );
    sleep_ms( 500 );
    const uint16_t runTime = 500;
    const uint16_t samplingPeriod = 50;
    uint16_t* adcReadings = (uint16_t*) malloc( sizeof(uint16_t) * ( runTime / samplingPeriod ) );
    if( adcReadings == NULL )
    {
        oled_terminalWrite( "MEM ALLOC FAIL" );
        for( ;; )
            sleep_ms( 10000 );
    }
    if( PUMP_ADC_PIN == 26 )
        adc_select_input( 0 );
    else if( PUMP_ADC_PIN == 27 )
        adc_select_input( 1 );
    else if( PUMP_ADC_PIN == 28 )
        adc_select_input( 2 );
    else
    {
        oled_terminalWrite( "ADC SELECT FAILED" );
        for( ;; )
            sleep_ms( 10000 );
    }

    absolute_time_t loopEndTime;
    for( uint16_t reading = 0U; reading < ( runTime / samplingPeriod ); reading++ )
    {
        loopEndTime = make_timeout_time_ms( samplingPeriod );
        adcReadings[reading] = adc_read();
        if( ( adcReadings[reading] > ADC_THRESHOLD_MAX ) || ( adcReadings[reading] < ADC_THRESHOLD_MIN ) )
        {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        }
        printf( "l:%d @ %lu\n", reading, to_ms_since_boot( get_absolute_time() ) );
        sleep_until( loopEndTime );
    }
    printf( "Turning off pump" );
    gpio_put( PUMP_CONTROL_PIN, 0 );

    // Do some statistics
    uint16_t minimum = 0xFFFF;
    uint16_t maximum = 0x0000;
    uint64_t sum = 0;
    for( uint16_t reading = 0U; reading < ( runTime / samplingPeriod ); reading++ )
    {
        if( minimum > adcReadings[reading] )
            minimum = adcReadings[reading];

        if( maximum < adcReadings[reading] )
            maximum = adcReadings[reading];

        sum += adcReadings[reading];
    }
    uint64_t mean = sum / ( runTime / samplingPeriod );
    char text[30];
    snprintf( text, sizeof(text), "MAX : %u", maximum );
    oled_terminalWrite( text );
    snprintf( text, sizeof(text), "MEAN: %llu", mean );
    oled_terminalWrite( text );
    snprintf( text, sizeof(text), "MIN : %u", minimum );
    oled_terminalWrite( text );

    oled_terminalWrite( "" );
    oled_terminalWrite( "WAITING FOR REBOOT" );

    for( ;; )
        sleep_ms( 10000 );
}
