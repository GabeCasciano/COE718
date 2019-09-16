#include "LPC17xx.H" 
#include "LED.h"

/**LED_Init
 *
 * Use to init the LEDs
 */
void LED_Init(void){
	LPC_SC->PCONP |= (1<<15);
	LPC_PINCON->PINSEL4 |= ~(0xFFC);
	LPC_GPIO2->FIOCLR = (LED_UP|LED_DOWN|LED_RIGHT|LED_LEFT|LED_SELECT);
}

/**LED_On
 *
 * Use to turn a specific LED on
 *
 * @param val -> type uint32_t -> which LED to turn on
 */
void LED_On(uint32_t val){
		LED_Clear();
    switch(val){
        case LED_UP:
            LPC_GPIO2->FIOSET |= ~LED_UP;
            break;
        case LED_RIGHT:
            LPC_GPIO2->FIOSET |= LED_RIGHT;
            break;
        case LED_DOWN:
            LPC_GPIO2->FIOSET |= LED_DOWN;
            break;
        case LED_LEFT:
            LPC_GPIO2->FIOSET |= LED_LEFT;
            break;
        case LED_SELECT:
            LPC_GPIO1->FIOSET |= LED_SELECT;
            break;
    }
}

/**LED_Off
 *
 * Use to turn a specific LED off
 *
 * @param val -> type uint32_t -> which LED to turn off
 */

void LED_Off(uint32_t val){
    switch(val){
        case LED_UP:
            LPC_GPIO2->FIOCLR |= LED_UP;
            break;
        case LED_RIGHT:
            LPC_GPIO2->FIOCLR |= LED_RIGHT;
            break;
        case LED_DOWN:
            LPC_GPIO2->FIOCLR |= LED_DOWN;
            break;
        case LED_LEFT:
            LPC_GPIO2->FIOCLR |= LED_LEFT;
            break;
        case LED_SELECT:
            LPC_GPIO1->FIOCLR |= LED_SELECT;
            break;
    }
}

/**LED_Get_On
 *
 * Use to get which LED is currently On
 *
 * @return byte for which LED is currently on
 */
uint32_t LED_Get_On(void) {
    if ((LPC_GPIO3->FIOPIN & LED_UP) == LED_UP) {
        return LED_UP;
    } else if ((LPC_GPIO3->FIOPIN & LED_RIGHT) == LED_RIGHT) {
        return LED_RIGHT;
    } else if ((LPC_GPIO3->FIOPIN & LED_DOWN) == LED_DOWN) {
        return LED_DOWN;
    } else if((LPC_GPIO2->FIOPIN & LED_LEFT) == LED_LEFT){
        return LED_DOWN;
    } else if((LPC_GPIO1->FIOPIN & LED_SELECT) == LED_SELECT){
        return LED_SELECT;
    }
		return 0;
}


/**LED_Clear
 *
 * Use to turn all of the LEDs off
 */
void LED_Clear(void){
    LPC_GPIO2->FIOCLR |= (LED_UP|LED_RIGHT|LED_DOWN|LED_LEFT);
    LPC_GPIO1->FIOCLR |= (LED_SELECT);
}

void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
}
