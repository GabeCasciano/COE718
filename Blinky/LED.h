/*----------------------------------------------------------------------------
 * Name:    LED.h
 * Purpose: low level LED definitions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __LED_H
#define __LED_H

#include <stdint.h>

#define LED_UP (1<<2)
#define LED_DOWN (1<<4)
#define LED_LEFT (1<<5)
#define LED_RIGHT (1<<6)
#define LED_SELECT (1<<29)


/* LED Definitions */
#define LED_NUM     8                        /* Number of user LEDs          */

extern void LED_Init(void);
extern void LED_On  (uint32_t val);
extern void LED_Off (uint32_t val);
extern void LED_Clear(void);
extern uint32_t LED_Get_On(void);
//extern void LED_Out (unsigned int value);
/*
 * I could not figure out what this was to be used for,
 * so I got rid of it.
 */

#endif
