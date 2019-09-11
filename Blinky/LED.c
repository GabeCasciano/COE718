#include "LPC17xx.H" 
#include "LED.h"

void LED_Init(void){
	LPC_SC->PCONP |= (1<<15);
	LPC_PINCON->PINSEL1 |= ~(3<<29);
	LPC_PINCON->PINSEL2 |= ~((3<<2)|(3<<4)|(3<<5)|(3<<6));
	
}