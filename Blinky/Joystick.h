//
// Created by gabriel on 2019-09-11.
//

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#define UP 0x1;
#define DOWN 0x2;
#define LEFT 0x3;
#define RIGHT 0x4;
#define SELECT 0X5;

extern uint32_t joyStickValue;

extern uint32_t updateJoystickValue(void);


#endif //_JOYSTICK_H
