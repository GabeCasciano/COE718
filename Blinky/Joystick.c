//
// Created by gabriel on 2019-09-11.
//

#include <stdint.h>
#include "Joystick.h"
#include "KDB.h"

uint32_t joyStickValue = 0;

uint32_t updateJoyStickValue(void){
    uint32_t temp = KDB_button() ;

    if((temp & KDB_UP) == KDB_UP){
        joyStickValue = UP;
		}
    else if((temp & KDB_DOWN) == KDB_DOWN){
        joyStickValue = DOWN;
		}
    else if((temp & KDB_LEFT) == KDB_LEFT){
        joyStickValue = LEFT;
		}
    else if((temp & KDB_RIGHT) == KDB_RIGHT){
        joyStickValue = RIGHT;
		}
    else if((temp & KDB_SELECT) == KDB_SELECT){
        joyStickValue = SELECT;
		}
		return (joyStickValue);
}
