/*----------------------------------------------------------------------------
 * Name:    Joystick.h
 * Purpose: definitions for the joystick library
 * Note(s):
 *----------------------------------------------------------------------------
 */

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#define JOYSTICK_UP "UP"
#define JOYSTICK_DOWN "DOWN"
#define JOYSTICK_LEFT "LEFT"
#define JOYSTICK_RIGHT "RIGHT"
#define JOYSTICK_SELECT "SELECT"

extern uint32_t joyStickValue;
extern void JOYSTICK_Init();
extern void getNeutral(void);
extern uint32_t JOYSTICK_Update(void);


#endif //_JOYSTICK_H
