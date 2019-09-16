/*----------------------------------------------------------------------------
 * Name:    Joystick.c
 * Purpose: Use this class to absract the KBD reading
 * Note(s):
 *----------------------------------------------------------------------------
 */


#include <stdint.h>
#include "Joystick.h"
#include "KDB.h"

char[6] JOYSTICK_val;
uint32_t KBD_neutral = 0x0000;

/**JOYSTICK_getNeutral
 * Used to get the neutral value of KDB
 */
void JOYSTICK_getNeutral(void){
    KBD_neutral = KDB_button();
}

/**
 * Used to Init KDB, and get initial values
 */
void JOYSTICK_Init(void){
    KBD_Init();
    JOYSTICK_getNeutral();
}


/**JOYSTICK_Update
 *
 * Call this class to update the joystick and possibly get a new
 * position from kdb
 *
 * @return JOYSTICK_val -> type char -> The current value of joystick
 */
char[] JOYSTICK_Update(void){
    uint32_t temp = KDB_button() ;
    if(temp == KBD_neutral) {
        if ((temp & KDB_UP) == KDB_UP) {
            JOYSTICK_val = JOYSTICK_UP;
        } else if ((temp & KDB_DOWN) == KDB_DOWN) {
            JOYSTICK_val = JOYSTICK_DOWN;
        } else if ((temp & KDB_LEFT) == KDB_LEFT) {
            JOYSTICK_val = JOYSTICK_LEFT;
        } else if ((temp & KDB_RIGHT) == KDB_RIGHT) {
            JOYSTICK_val = JOYSTICK_RIGHT;
        } else if ((temp & KDB_SELECT) == KDB_SELECT) {
            JOYSTICK_val = JOYSTICK_SELECT;
        }
    }

    return JOYSTICK_val;
}
