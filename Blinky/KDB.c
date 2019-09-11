#inlcude "LPC17xx.h"
#include "KDB.h"

uint32_t KDB_val = 0;

void KDB_Init(void){
    LPC_SC->PCONP |= (1<<15); //Enable power to GPIO & IOCON

    LPC_PINCON->PINSEL3 &= ~((3<<8)|(3<<14)||(3<<16)||(3<<18)|(3<<20));//P1.20, P1.23...26 are GPIO (Joy Stick)
    LPC_GPIO->FIODIR &= ~((1<<20)|(1<<23)|(1<<24)|(1<<25)|(1<<26));//P1.20, P1.23...26 as input
}

uint32_t KDB_get(void){
    uint32_t kdb_val;

    kdb_val = (LPC_GPIO1->FIOPIN >> 20) & KDB_MASK;
    return (kdb_val);
}

uint32_t get_button(void){
    uint32_t val = 0;

    val = KDB_get(); //read state
    val = (~val & KDB_MASK);
    return (val);
}


