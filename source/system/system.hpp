#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "settings.hpp"

int system_initialise( t_globalData* globalDataPtr );

void system_reboot( void );

void system_update( t_globalData* globalDataPtr );

#endif // defined SYSTEM_HPP