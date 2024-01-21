/**
  ******************************************************************************
  * @file    font16.c
  * @author  MCD Application Team
  * @brief   This file provides text font16 for STM32 board's LCD driver.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2014 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef FONT_16_H
#define FONT_16_H

#include <stdint.h>

#include "fontCommon.h"

//
//  Font data for Courier New 12pt
//

const uint8_t Font16_Table[] =
{
	// @0 ' ' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @32 '!' (11 pixels wide)
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @64 '"' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1D, 0xC0, //    ### ###
	0x1D, 0xC0, //    ### ###
	0x08, 0x80, //     #   #
	0x08, 0x80, //     #   #
	0x08, 0x80, //     #   #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @96 '#' (11 pixels wide)
	0x00, 0x00, //
	0x0D, 0x80, //     ## ##
	0x0D, 0x80, //     ## ##
	0x0D, 0x80, //     ## ##
	0x0D, 0x80, //     ## ##
	0x3F, 0xC0, //   ########
	0x1B, 0x00, //    ## ##
	0x3F, 0xC0, //   ########
	0x1B, 0x00, //    ## ##
	0x1B, 0x00, //    ## ##
	0x1B, 0x00, //    ## ##
	0x1B, 0x00, //    ## ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @128 '$' (11 pixels wide)
	0x04, 0x00, //      #
	0x1F, 0x80, //    ######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x38, 0x00, //   ###
	0x1E, 0x00, //    ####
	0x0F, 0x00, //     ####
	0x03, 0x80, //       ###
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x3F, 0x00, //   ######
	0x04, 0x00, //      #
	0x04, 0x00, //      #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @160 '%' (11 pixels wide)
	0x00, 0x00, //
	0x18, 0x00, //    ##
	0x24, 0x00, //   #  #
	0x24, 0x00, //   #  #
	0x18, 0xC0, //    ##   ##
	0x07, 0x80, //      ####
	0x1E, 0x00, //    ####
	0x31, 0x80, //   ##   ##
	0x02, 0x40, //       #  #
	0x02, 0x40, //       #  #
	0x01, 0x80, //        ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @192 '&' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x0F, 0x00, //     ####
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x0C, 0x00, //     ##
	0x1D, 0x80, //    ### ##
	0x37, 0x00, //   ## ###
	0x33, 0x00, //   ##  ##
	0x1D, 0x80, //    ### ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @224 ''' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x07, 0x00, //      ###
	0x07, 0x00, //      ###
	0x02, 0x00, //       #
	0x02, 0x00, //       #
	0x02, 0x00, //       #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @256 '(' (11 pixels wide)
	0x00, 0x00, //
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x06, 0x00, //      ##
	0x0E, 0x00, //     ###
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0E, 0x00, //     ###
	0x06, 0x00, //      ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @288 ')' (11 pixels wide)
	0x00, 0x00, //
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x0C, 0x00, //     ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x1C, 0x00, //    ###
	0x18, 0x00, //    ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @320 '*' (11 pixels wide)
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x3F, 0xC0, //   ########
	0x3F, 0xC0, //   ########
	0x0F, 0x00, //     ####
	0x1F, 0x80, //    ######
	0x19, 0x80, //    ##  ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @352 '+' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x04, 0x00, //      #
	0x04, 0x00, //      #
	0x04, 0x00, //      #
	0x3F, 0x80, //   #######
	0x04, 0x00, //      #
	0x04, 0x00, //      #
	0x04, 0x00, //      #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @384 ',' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x04, 0x00, //      #
	0x0C, 0x00, //     ##
	0x08, 0x00, //     #
	0x08, 0x00, //     #
	0x00, 0x00, //
	0x00, 0x00, //

	// @416 '-' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x3F, 0x80, //   #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @448 '.' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @480 '/' (11 pixels wide)
	0x00, 0xC0, //         ##
	0x00, 0xC0, //         ##
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @512 '0' (11 pixels wide)
	0x00, 0x00, //
	0x0E, 0x00, //     ###
	0x1B, 0x00, //    ## ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x1B, 0x00, //    ## ##
	0x0E, 0x00, //     ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @544 '1' (11 pixels wide)
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x3E, 0x00, //   #####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x3F, 0xC0, //   ########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @576 '2' (11 pixels wide)
	0x00, 0x00, //
	0x0F, 0x00, //     ####
	0x19, 0x80, //    ##  ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x03, 0x00, //       ##
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x18, 0x00, //    ##
	0x30, 0x00, //   ##
	0x3F, 0x80, //   #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @608 '3' (11 pixels wide)
	0x00, 0x00, //
	0x3F, 0x00, //   ######
	0x61, 0x80, //  ##    ##
	0x01, 0x80, //        ##
	0x03, 0x00, //       ##
	0x1F, 0x00, //    #####
	0x03, 0x80, //       ###
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x61, 0x80, //  ##    ##
	0x3F, 0x00, //   ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @640 '4' (11 pixels wide)
	0x00, 0x00, //
	0x07, 0x00, //      ###
	0x07, 0x00, //      ###
	0x0F, 0x00, //     ####
	0x0B, 0x00, //     # ##
	0x1B, 0x00, //    ## ##
	0x13, 0x00, //    #  ##
	0x33, 0x00, //   ##  ##
	0x3F, 0x80, //   #######
	0x03, 0x00, //       ##
	0x0F, 0x80, //     #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @672 '5' (11 pixels wide)
	0x00, 0x00, //
	0x1F, 0x80, //    ######
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x1F, 0x00, //    #####
	0x11, 0x80, //    #   ##
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x21, 0x80, //   #    ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @704 '6' (11 pixels wide)
	0x00, 0x00, //
	0x07, 0x80, //      ####
	0x1C, 0x00, //    ###
	0x18, 0x00, //    ##
	0x30, 0x00, //   ##
	0x37, 0x00, //   ## ###
	0x39, 0x80, //   ###  ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x19, 0x80, //    ##  ##
	0x0F, 0x00, //     ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @736 '7' (11 pixels wide)
	0x00, 0x00, //
	0x7F, 0x00, //  #######
	0x43, 0x00, //  #    ##
	0x03, 0x00, //       ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @768 '8' (11 pixels wide)
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @800 '9' (11 pixels wide)
	0x00, 0x00, //
	0x1E, 0x00, //    ####
	0x33, 0x00, //   ##  ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x33, 0x80, //   ##  ###
	0x1D, 0x80, //    ### ##
	0x01, 0x80, //        ##
	0x03, 0x00, //       ##
	0x07, 0x00, //      ###
	0x3C, 0x00, //   ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @832 ':' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @864 ';' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x04, 0x00, //      #
	0x08, 0x00, //     #
	0x08, 0x00, //     #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @896 '<' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0xC0, //         ##
	0x03, 0x00, //       ##
	0x04, 0x00, //      #
	0x18, 0x00, //    ##
	0x60, 0x00, //  ##
	0x18, 0x00, //    ##
	0x04, 0x00, //      #
	0x03, 0x00, //       ##
	0x00, 0xC0, //         ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @928 '=' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0xC0, //  #########
	0x00, 0x00, //
	0x7F, 0xC0, //  #########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @960 '>' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x60, 0x00, //  ##
	0x18, 0x00, //    ##
	0x04, 0x00, //      #
	0x03, 0x00, //       ##
	0x00, 0xC0, //         ##
	0x03, 0x00, //       ##
	0x04, 0x00, //      #
	0x18, 0x00, //    ##
	0x60, 0x00, //  ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @992 '?' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x01, 0x80, //        ##
	0x07, 0x00, //      ###
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1024 '@' (11 pixels wide)
	0x00, 0x00, //
	0x0E, 0x00, //     ###
	0x11, 0x00, //    #   #
	0x21, 0x00, //   #    #
	0x21, 0x00, //   #    #
	0x27, 0x00, //   #  ###
	0x29, 0x00, //   # #  #
	0x29, 0x00, //   # #  #
	0x27, 0x00, //   #  ###
	0x20, 0x00, //   #
	0x11, 0x00, //    #   #
	0x0E, 0x00, //     ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1056 'A' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x3F, 0x00, //   ######
	0x0F, 0x00, //     ####
	0x09, 0x00, //     #  #
	0x19, 0x80, //    ##  ##
	0x19, 0x80, //    ##  ##
	0x1F, 0x80, //    ######
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x79, 0xE0, //  ####  ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1088 'B' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x00, //  #######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x3F, 0x00, //   ######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x7F, 0x00, //  #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1120 'C' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x40, //    ##### #
	0x30, 0xC0, //   ##    ##
	0x60, 0x40, //  ##      #
	0x60, 0x00, //  ##
	0x60, 0x00, //  ##
	0x60, 0x00, //  ##
	0x60, 0x40, //  ##      #
	0x30, 0x80, //   ##    #
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1152 'D' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x00, //  #######
	0x31, 0x80, //   ##   ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x31, 0x80, //   ##   ##
	0x7F, 0x00, //  #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1184 'E' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x80, //  ########
	0x30, 0x80, //   ##    #
	0x30, 0x80, //   ##    #
	0x32, 0x00, //   ##  #
	0x3E, 0x00, //   #####
	0x32, 0x00, //   ##  #
	0x30, 0x80, //   ##    #
	0x30, 0x80, //   ##    #
	0x7F, 0x80, //  ########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1216 'F' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0xC0, //  #########
	0x30, 0x40, //   ##     #
	0x30, 0x40, //   ##     #
	0x32, 0x00, //   ##  #
	0x3E, 0x00, //   #####
	0x32, 0x00, //   ##  #
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x7C, 0x00, //  #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1248 'G' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1E, 0x80, //    #### #
	0x31, 0x80, //   ##   ##
	0x60, 0x80, //  ##     #
	0x60, 0x00, //  ##
	0x60, 0x00, //  ##
	0x67, 0xC0, //  ##  #####
	0x61, 0x80, //  ##    ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1280 'H' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x3F, 0x80, //   #######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x7B, 0xC0, //  #### ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1312 'I' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x3F, 0xC0, //   ########
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x3F, 0xC0, //   ########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1344 'J' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0xC0, //    #######
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x63, 0x00, //  ##   ##
	0x63, 0x00, //  ##   ##
	0x63, 0x00, //  ##   ##
	0x3E, 0x00, //   #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1376 'K' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x31, 0x80, //   ##   ##
	0x33, 0x00, //   ##  ##
	0x36, 0x00, //   ## ##
	0x3C, 0x00, //   ####
	0x3E, 0x00, //   #####
	0x33, 0x00, //   ##  ##
	0x31, 0x80, //   ##   ##
	0x79, 0xC0, //  ####  ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1408 'L' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7E, 0x00, //  ######
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x40, //    ##    #
	0x18, 0x40, //    ##    #
	0x18, 0x40, //    ##    #
	0x7F, 0xC0, //  #########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1440 'M' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0xE0, 0xE0, // ###     ###
	0x60, 0xC0, //  ##     ##
	0x71, 0xC0, //  ###   ###
	0x7B, 0xC0, //  #### ####
	0x6A, 0xC0, //  ## # # ##
	0x6E, 0xC0, //  ## ### ##
	0x64, 0xC0, //  ##  #  ##
	0x60, 0xC0, //  ##     ##
	0xFB, 0xE0, // ##### #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1472 'N' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x73, 0xC0, //  ###  ####
	0x31, 0x80, //   ##   ##
	0x39, 0x80, //   ###  ##
	0x3D, 0x80, //   #### ##
	0x35, 0x80, //   ## # ##
	0x37, 0x80, //   ## ####
	0x33, 0x80, //   ##  ###
	0x31, 0x80, //   ##   ##
	0x79, 0x80, //  ####  ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1504 'O' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1536 'P' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x00, //  #######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x3F, 0x00, //   ######
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x7E, 0x00, //  ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1568 'Q' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x0C, 0xC0, //     ##  ##
	0x1F, 0x80, //    ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1600 'R' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x00, //  #######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x3E, 0x00, //   #####
	0x33, 0x00, //   ##  ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x7C, 0xE0, //  #####  ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1632 'S' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x80, //    ######
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x38, 0x00, //   ###
	0x1F, 0x00, //    #####
	0x03, 0x80, //       ###
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x3F, 0x00, //   ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1664 'T' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x80, //  ########
	0x4C, 0x80, //  #  ##  #
	0x4C, 0x80, //  #  ##  #
	0x4C, 0x80, //  #  ##  #
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x3F, 0x00, //   ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1696 'U' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1728 'V' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x1B, 0x00, //    ## ##
	0x1B, 0x00, //    ## ##
	0x1B, 0x00, //    ## ##
	0x0A, 0x00, //     # #
	0x0E, 0x00, //     ###
	0x0E, 0x00, //     ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1760 'W' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0xFB, 0xE0, // ##### #####
	0x60, 0xC0, //  ##     ##
	0x64, 0xC0, //  ##  #  ##
	0x6E, 0xC0, //  ## ### ##
	0x6E, 0xC0, //  ## ### ##
	0x2A, 0x80, //   # # # #
	0x3B, 0x80, //   ### ###
	0x3B, 0x80, //   ### ###
	0x31, 0x80, //   ##   ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1792 'X' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x31, 0x80, //   ##   ##
	0x1B, 0x00, //    ## ##
	0x0E, 0x00, //     ###
	0x0E, 0x00, //     ###
	0x0E, 0x00, //     ###
	0x1B, 0x00, //    ## ##
	0x31, 0x80, //   ##   ##
	0x7B, 0xC0, //  #### ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1824 'Y' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x79, 0xE0, //  ####  ####
	0x30, 0xC0, //   ##    ##
	0x19, 0x80, //    ##  ##
	0x0F, 0x00, //     ####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x1F, 0x80, //    ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1856 'Z' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x3F, 0x80, //   #######
	0x21, 0x80, //   #    ##
	0x23, 0x00, //   #   ##
	0x06, 0x00, //      ##
	0x04, 0x00, //      #
	0x0C, 0x00, //     ##
	0x18, 0x80, //    ##   #
	0x30, 0x80, //   ##    #
	0x3F, 0x80, //   #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1888 '[' (11 pixels wide)
	0x00, 0x00, //
	0x07, 0x80, //      ####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x07, 0x80, //      ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1920 '\' (11 pixels wide)
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x06, 0x00, //      ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x00, 0xC0, //         ##
	0x00, 0xC0, //         ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1952 ']' (11 pixels wide)
	0x00, 0x00, //
	0x1E, 0x00, //    ####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x1E, 0x00, //    ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @1984 '^' (11 pixels wide)
	0x04, 0x00, //      #
	0x0A, 0x00, //     # #
	0x0A, 0x00, //     # #
	0x11, 0x00, //    #   #
	0x20, 0x80, //   #     #
	0x20, 0x80, //   #     #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2016 '_' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0xFF, 0xE0, // ###########

	// @2048 '`' (11 pixels wide)
	0x08, 0x00, //     #
	0x04, 0x00, //      #
	0x02, 0x00, //       #
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2080 'a' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x1F, 0x80, //    ######
	0x31, 0x80, //   ##   ##
	0x33, 0x80, //   ##  ###
	0x1D, 0xC0, //    ### ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2112 'b' (11 pixels wide)
	0x00, 0x00, //
	0x70, 0x00, //  ###
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x37, 0x00, //   ## ###
	0x39, 0x80, //   ###  ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x39, 0x80, //   ###  ##
	0x77, 0x00, //  ### ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2144 'c' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1E, 0x80, //    #### #
	0x31, 0x80, //   ##   ##
	0x60, 0x80, //  ##     #
	0x60, 0x00, //  ##
	0x60, 0x80, //  ##     #
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2176 'd' (11 pixels wide)
	0x00, 0x00, //
	0x03, 0x80, //       ###
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x1D, 0x80, //    ### ##
	0x33, 0x80, //   ##  ###
	0x61, 0x80, //  ##    ##
	0x61, 0x80, //  ##    ##
	0x61, 0x80, //  ##    ##
	0x33, 0x80, //   ##  ###
	0x1D, 0xC0, //    ### ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2208 'e' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x60, 0xC0, //  ##     ##
	0x7F, 0xC0, //  #########
	0x60, 0x00, //  ##
	0x30, 0xC0, //   ##    ##
	0x1F, 0x80, //    ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2240 'f' (11 pixels wide)
	0x00, 0x00, //
	0x07, 0xE0, //      ######
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x3F, 0x80, //   #######
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x3F, 0x80, //   #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2272 'g' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1D, 0xC0, //    ### ###
	0x33, 0x80, //   ##  ###
	0x61, 0x80, //  ##    ##
	0x61, 0x80, //  ##    ##
	0x61, 0x80, //  ##    ##
	0x33, 0x80, //   ##  ###
	0x1D, 0x80, //    ### ##
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //

	// @2304 'h' (11 pixels wide)
	0x00, 0x00, //
	0x70, 0x00, //  ###
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x37, 0x00, //   ## ###
	0x39, 0x80, //   ###  ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x7B, 0xC0, //  #### ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2336 'i' (11 pixels wide)
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x00, 0x00, //
	0x1E, 0x00, //    ####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x3F, 0xC0, //   ########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2368 'j' (11 pixels wide)
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x00, 0x00, //
	0x3F, 0x00, //   ######
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x03, 0x00, //       ##
	0x3E, 0x00, //   #####
	0x00, 0x00, //
	0x00, 0x00, //

	// @2400 'k' (11 pixels wide)
	0x00, 0x00, //
	0x70, 0x00, //  ###
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x37, 0x80, //   ## ####
	0x36, 0x00, //   ## ##
	0x3C, 0x00, //   ####
	0x3C, 0x00, //   ####
	0x36, 0x00, //   ## ##
	0x33, 0x00, //   ##  ##
	0x77, 0xC0, //  ### #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2432 'l' (11 pixels wide)
	0x00, 0x00, //
	0x1E, 0x00, //    ####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x3F, 0xC0, //   ########
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2464 'm' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x7F, 0x80, //  ########
	0x36, 0xC0, //   ## ## ##
	0x36, 0xC0, //   ## ## ##
	0x36, 0xC0, //   ## ## ##
	0x36, 0xC0, //   ## ## ##
	0x36, 0xC0, //   ## ## ##
	0x76, 0xE0, //  ### ## ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2496 'n' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x77, 0x00, //  ### ###
	0x39, 0x80, //   ###  ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x7B, 0xC0, //  #### ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2528 'o' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x00, //    #####
	0x31, 0x80, //   ##   ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x60, 0xC0, //  ##     ##
	0x31, 0x80, //   ##   ##
	0x1F, 0x00, //    #####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2560 'p' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x77, 0x00, //  ### ###
	0x39, 0x80, //   ###  ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x30, 0xC0, //   ##    ##
	0x39, 0x80, //   ###  ##
	0x37, 0x00, //   ## ###
	0x30, 0x00, //   ##
	0x30, 0x00, //   ##
	0x7C, 0x00, //  #####
	0x00, 0x00, //
	0x00, 0x00, //

	// @2592 'q' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1D, 0xC0, //    ### ###
	0x33, 0x80, //   ##  ###
	0x61, 0x80, //  ##    ##
	0x61, 0x80, //  ##    ##
	0x61, 0x80, //  ##    ##
	0x33, 0x80, //   ##  ###
	0x1D, 0x80, //    ### ##
	0x01, 0x80, //        ##
	0x01, 0x80, //        ##
	0x07, 0xC0, //      #####
	0x00, 0x00, //
	0x00, 0x00, //

	// @2624 'r' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0x80, //  #### ###
	0x1C, 0xC0, //    ###  ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x7F, 0x00, //  #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2656 's' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x1F, 0x80, //    ######
	0x31, 0x80, //   ##   ##
	0x3C, 0x00, //   ####
	0x1F, 0x00, //    #####
	0x03, 0x80, //       ###
	0x31, 0x80, //   ##   ##
	0x3F, 0x00, //   ######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2688 't' (11 pixels wide)
	0x00, 0x00, //
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x7F, 0x00, //  #######
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x00, //    ##
	0x18, 0x80, //    ##   #
	0x0F, 0x00, //     ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2720 'u' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x73, 0x80, //  ###  ###
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x33, 0x80, //   ##  ###
	0x1D, 0xC0, //    ### ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2752 'v' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x31, 0x80, //   ##   ##
	0x31, 0x80, //   ##   ##
	0x1B, 0x00, //    ## ##
	0x1B, 0x00, //    ## ##
	0x0E, 0x00, //     ###
	0x0E, 0x00, //     ###
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2784 'w' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0xF1, 0xE0, // ####   ####
	0x60, 0xC0, //  ##     ##
	0x64, 0xC0, //  ##  #  ##
	0x6E, 0xC0, //  ## ### ##
	0x3B, 0x80, //   ### ###
	0x3B, 0x80, //   ### ###
	0x31, 0x80, //   ##   ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2816 'x' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x7B, 0xC0, //  #### ####
	0x1B, 0x00, //    ## ##
	0x0E, 0x00, //     ###
	0x0E, 0x00, //     ###
	0x0E, 0x00, //     ###
	0x1B, 0x00, //    ## ##
	0x7B, 0xC0, //  #### ####
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2848 'y' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x79, 0xE0, //  ####  ####
	0x30, 0xC0, //   ##    ##
	0x19, 0x80, //    ##  ##
	0x19, 0x80, //    ##  ##
	0x0B, 0x00, //     # ##
	0x0F, 0x00, //     ####
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x3E, 0x00, //   #####
	0x00, 0x00, //
	0x00, 0x00, //

	// @2880 'z' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x3F, 0x80, //   #######
	0x21, 0x80, //   #    ##
	0x03, 0x00, //       ##
	0x0E, 0x00, //     ###
	0x18, 0x00, //    ##
	0x30, 0x80, //   ##    #
	0x3F, 0x80, //   #######
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2912 '{' (11 pixels wide)
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x18, 0x00, //    ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x0C, 0x00, //     ##
	0x06, 0x00, //      ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2944 '|' (11 pixels wide)
	0x00, 0x00, //
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @2976 '}' (11 pixels wide)
	0x00, 0x00, //
	0x0C, 0x00, //     ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x03, 0x00, //       ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x06, 0x00, //      ##
	0x0C, 0x00, //     ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //

	// @3008 '~' (11 pixels wide)
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x18, 0x00, //    ##
	0x24, 0x80, //   #  #  #
	0x03, 0x00, //       ##
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
	0x00, 0x00, //
};

tFontTable Font16 = {
  Font16_Table,
  11, /* Width */
  16, /* Height */
};

#endif /* FONT_16_H */
