/*  INCLUDES */
#include "settings.hpp"
#include "system.hpp"
#include "oled.hpp"

// Check that only the necessary parts of the oled code have been included. This saves several kB of RAM
// Parts of oled.hpp that should have been included
#if !defined(OLED_INCLUDE_FONT12) || !defined(OLED_INCLUDE_FONT20)  || !defined(OLED_INCLUDE_LOADING_CIRCLE) || !defined(OLED_INCLUDE_LOADING_BAR_HORIZONTAL) || !defined(OLED_INCLUDE_SD_IMAGES) || !defined(OLED_INCLUDE_QR_GENERATOR)
#error "A required part of oled.hpp has not been included"
// Parts of oled.hpp that should not have been included
#elif defined(OLED_INCLUDE_FONT8) || defined(OLED_INCLUDE_FONT16) || defined(OLED_INCLUDE_FONT24) || defined(OLED_INCLUDE_TEST_FUNCTION)
#error "An unnecessary part of oled.hpp has been included, this can waste lots of RAM or program space"
#endif

int main( void )
{
    // Initialise the stdio
    stdio_init_all();

    // Create the global data struct
    t_globalData globalData;

    if( system_initialise( &globalData ) != 0 )
    {
        sleep_ms( 10ULL * 60ULL * 1000ULL ); // Wait 10 minutes
        system_reboot(); // Reboot the board
    }

    return 0;
}
