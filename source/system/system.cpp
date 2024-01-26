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
static void m_infoSetup( t_globalData* globalDataPtr );
static void m_infoUpdate( t_globalData* globalDataPtr );
/* OTHER */
static void m_checkInput( t_globalData* globalDataPtr );
static void m_dayOfTheWeek( char* strPrt, uint8_t strLen, uint8_t dayOfTheWeek );
static time_t m_datetimeToEpoch( datetime_t* datetimePtr );
static bool m_checkRecyclingBinday( t_globalData* globalDataPtr );
static bool m_checkLandfillBinday( t_globalData* globalDataPtr );

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

    printf("landfill\n");
    for( uint8_t index = 0U; index < globalDataPtr->sdCardSettings.landfillEntries; index++ )
    {
        printf( "%d - %lld\n", index, globalDataPtr->sdCardSettings.landfillUnix[index] );
    }
    printf("recycling\n");
    for( uint8_t index = 0U; index < globalDataPtr->sdCardSettings.recyclingEntries; index++ )
    {
        printf( "%d - %lld\n", index, globalDataPtr->sdCardSettings.recyclingUnix[index] );
    }

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

    if( globalDataPtr->waterButton == e_input_long )
    {
        globalDataPtr->currentState = e_sysState_watering;
    }
    else if( globalDataPtr->infoButton == e_input_press )
    {
        globalDataPtr->currentState = e_sysState_showInfo;
    }
    
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
                // Do nothing
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
    // ARE THERE ANY WARNINGS TO DISPLAY?
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

    oled_terminalInit( 12, TERMINAL_INFO_COLOUR );
    oled_terminalWrite( "INFO" );

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
        // TODO show propaganda
    }

    rtc_get_datetime( &m_datetime );
    m_dayOfTheWeek( &m_text2[0], sizeof( m_text2 ), m_datetime.dotw );
    snprintf( m_text1, sizeof( m_text1 ), "%s %02d/%02d/%02d",
        m_text2, m_datetime.day, m_datetime.month, ( m_datetime.year % 100 ) );
    oled_terminalSetLine( 2 );
    oled_terminalWrite( m_text1 );

    snprintf( m_text1, sizeof( m_text1 ), "%02d:%02d:%02d",
        m_datetime.hour, m_datetime.min, m_datetime.sec );
    oled_terminalSetLine( 3 );
    oled_terminalWrite( m_text1 );

    snprintf( m_text1, sizeof( m_text1 ), "%lld", m_datetimeToEpoch( &m_datetime ) );
    oled_terminalSetLine( 5 );
    oled_terminalWrite( m_text1 );
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

static bool m_checkRecyclingBinday( t_globalData* globalDataPtr )
{
    return false; // TODO
}

static bool m_checkLandfillBinday( t_globalData* globalDataPtr )
{
    return false; // TODO
}

