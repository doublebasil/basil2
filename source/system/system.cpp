#include "system.hpp"

#include "oled.hpp"
#include "pico/cyw43_arch.h"
#include "hardware/rtc.h"
#include "sd_card.h"
#include "ff.h"
#include "pump.hpp"
#include "hardware/watchdog.h"
#include "settings_reader.hpp"

/* INITIALISATION MODULE SCOPE FUNCTION PROTOTYPES */
static inline void m_initialiseOled( void );
static inline void m_initialiseCyw43( void );
static inline void m_initialiseAdc( void );
static inline void m_initialisePump( void );
static inline void m_initialiseSdCardDriver( void );
static inline void m_initialiseRtc( void );
static inline void m_sdSuccessfulReadMessage( t_sdCardSettings* sdCardSettingsPtr );
static inline void m_sdFailedReadMessage( void );

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
    // Now attempt to read the SD card
    oled_terminalWrite( "" );
    oled_terminalWrite( "Reading SDC..." );
    if( settings_readFromSDCard( globalDataPtr ) != 0 )
    {
        m_sdFailedReadMessage();
        return 1;
    }
    else
    {
        m_sdSuccessfulReadMessage( &(globalDataPtr->sdCardSettings) );
    }

    return 0;
}

void system_reboot( void )
{
    // Reboot the board in 1 ms using the watchdog
    watchdog_enable( 1, false );
    for( ;; ) {}
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