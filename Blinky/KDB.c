#include "LPC17xx.h"
#include "KDB.h"
uint32_t KBD_val  = 0;     
/*----------------------------------------------------------------------------   initialize Joystick  *----------------------------------------------------------------------------*/
void KDB_Init (void) {   
	LPC_SC->PCONP     |= (1 << 15);/* enable power to GPIO & IOCON  */ /* P1.20, P1.23..26 is GPIO (Joystick) */   
	LPC_PINCON->PINSEL3 &= ~((3<< 8)|(3<<14)|(3<<16)|(3<<18)|(3<<20));   /* P1.20, P1.23..26 is input */   
	LPC_GPIO1->FIODIR   &= ~((1<<20)|(1<<23)|(1<<24)|(1<<25)|(1<<26));  
}
uint32_t KDB_get(void){
	uint32_t kdb_val;
	kdb_val = (LPC_GPIO1->FIOPIN >> 20) & KDB_MASK;
	return(kdb_val);
}

uint32_t KDB_button(void){
	uint32_t val = 0;
	val = KDB_get();
	val = (-val & KDB_MASK);
	return (val);
}
