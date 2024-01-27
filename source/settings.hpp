#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

/* --- HARDWARE DEFINITIONS --- */
/* OLED */
#define OLED_DATA_IN_PIN                    ( 19 )
#define OLED_CLOCK_PIN                      ( 18 )
#define OLED_CHIP_SELECT_PIN                ( 17 )
#define OLED_DATA_COMMAND_PIN               ( 16 )
#define OLED_RESET_PIN                      ( 20 )
#define OLED_SPI_OUTPUT                     ( 0 )
#define OLED_BAUD_RATE_HZ                   ( 14000000 ) // 14 MHz
#define OLED_DISPLAY_WIDTH                  ( 128 )
#define OLED_DISPLAY_HEIGHT                 ( 128 )
/* PUMP */
#define PUMP_CONTROL_PIN                    ( 21 )
#define PUMP_ADC_PIN                        ( 26 )
/* INPUT BUTTONS */
#define WATER_BUTTON_PIN                    ( 3 )
#define INFO_BUTTON_PIN                     ( 2 )
/* SD CARD SETTINGS */
// Settings for the SD card are defined in source/no-OS-FatFS-SD-SPI-Rpi-Pico/FatFs_SPI/sd_driver/hw_config.c

/* --- OTHER DEFINITIONS --- */
#define WIFI_SSID_MAX_LEN                   ( 32 )
#define WIFI_PASSWORD_MAX_LEN               ( 32 )
#define MAX_NUMBER_OF_WATERING_TIMES        ( 5 )
#define SECONDS_PER_DAY                     ( 24LL * 60LL * 60LL )

/* --- RGB565 COLOURS --- */
#define RGB565_FOREST_GREEN                 ( 0x2444 )
#define RGB565_PURE_BLUE                    ( 0b0000000000011111 )

/* --- TERMINAL --- */
#define TERMINAL_FONT_12                    ( 12 )
#define TERMINAL_INIT_COLOUR                ( RGB565_FOREST_GREEN )
#define TERMINAL_INFO_COLOUR                ( RGB565_PURE_BLUE )

/* --- TIMING AND BEHAVIOURS --- */
#define MAIN_LOOP_TIME_PERIOD_MS            ( 50LL )
#define REBOOT_DELAY_MS                     ( 10ULL * 60ULL * 1000ULL ) // 10 minutes
#define MAX_WIFI_CONNECTION_ATTEMPTS        ( 3U )
#define WIFI_CONNECTION_RETRY_DELAY_MS      ( 30ULL * 1000ULL ) // 30 seconds
#define LONG_PRESS_TIME_MS                  ( 2000LL )
// #define MESSAGE_READ_DELAY_MS               ( 500ULL )
#define MESSAGE_READ_DELAY_MS               ( 0ULL )
#define NTP_RESEND_DELAY_US                 ( 10LL * 1000LL * 1000LL )
#define NTP_MAX_ATTEMPTS                    ( 5 )
#define DNS_MAX_ATTEMPTS                    ( 5 )
#define STATE_TIMEOUT_DELAY_MS              ( 15000ULL )
#define IMAGE_DISPLAY_TIME_MS               ( 5000ULL )
#define BINDAY_WARNING_TIME_HOURS           ( 9ULL + 12ULL ) // Number of hours before 9am on bin day that the warning should be triggered

/* --- TYPEDEFS --- */
typedef enum {
    e_tankState_unknown,
    e_tankState_ok,
    e_tankState_dry,
} t_tankState;

typedef enum {
    e_input_none,
    e_input_press,
    e_input_long,
} t_input;

/* SUB STRUCTS */
typedef struct {
    char wifiSsid[WIFI_SSID_MAX_LEN];
    char wifiPassword[WIFI_PASSWORD_MAX_LEN];
    int32_t wateringTimes[MAX_NUMBER_OF_WATERING_TIMES]; // Seconds since midnight, negative if unused, only used if RTC is set via NTP server
    uint16_t wateringDurationMs;
    // Bin days, unix time stamps for 9AM on binday
    uint8_t landfillEntries; // Size of malloc
    uint64_t* landfillUnix = NULL;
    uint8_t recyclingEntries; // Size of malloc
    uint64_t* recyclingUnix = NULL;
} t_sdCardSettings;

typedef struct {
    uint8_t displayWidth;
    uint8_t displayHeight;
} t_hardwareData;

typedef struct {
    /* WIFI */
    bool connectionSuccess = false; // Once a connection is established, reconnection should be automatic when needed
    uint8_t connectionAttempts = 0U;
    absolute_time_t reconnectionAttemptTime = nil_time;
    /* NTP */
    absolute_time_t ntpNextUpdateTime = nil_time;
    bool ntpFatal = false; // If something irrecoverable happened in the NTP process
    bool rtcSetSuccess = false;
} t_wifiData;

typedef enum {
    e_sysState_notSet,
    e_sysState_idle,
    e_sysState_showInfo,
    e_sysState_watering,
} t_sysState; // Return of the dreaded state machine

typedef struct {
    uint8_t day = 0; // 1 - 31
    uint8_t month = 0; // 1 - 12
    uint8_t year = 0;
    uint64_t unixEpoch = 0;
} t_binday;

/* GLOBAL DATA STRUCT */
typedef struct {
    /* SUB STRUCTS */
    t_sdCardSettings sdCardSettings;
    t_hardwareData hardwareData;
    t_wifiData wifiData;
    /* BUTTONS */
    t_input infoButton = e_input_none;
    t_input waterButton = e_input_none;
    /* STATE MODEL */
    t_tankState tankState = e_tankState_unknown;
    t_sysState currentState = e_sysState_notSet;
    t_sysState previousState = e_sysState_notSet;
    /* TIMESTAMPS */
    absolute_time_t stateTimeout = nil_time;
    absolute_time_t nextWater = nil_time;
    t_binday currentLandfill;
    t_binday currentRecycling;
} t_globalData;

#endif // SETTINGS_HPP
