#include "LPCxx.h"
#include <stdio.h>
#include "LED.h"

#define ITM_Port8(n) (*((volatile unsigned char *) (0xE0000000+4 * n)))
#define ITM_Port16(n) (*((volatile unsigned char *) (0xE0000000+4 * n)))
#define ITM_Port32(n) (*((volatile unsigned char *) (0xE0000000+4 * n)))

#define DEMCR (*((volatile unsigned char *) (0xE000EDFC)))
#define TRCENA 0x01000000

struct __FILE { int handle; };
FILE __stdout;
FILE __stdin;

int fputc( int ch, FILE *f){
    if(DEMCR & TRCENA){
        while(ITM_Port32(0) == 0);
        ITM_Port8(0) = ch;
    }
    return(ch);
}

//Bit Banding Macros
#define ADDRESS(x) (*((volatile unsigned long *)(x)))
#define BitBand(x, y) ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000)|(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

volatile unsidgned long * bit;
#define GPIO2_LED2 (*((volatile unsigned long *) 0x042))//finish the address

int main(void){
    LED_Init();
    LED_On(LED_UP);
    printf("LED On");
    
}
