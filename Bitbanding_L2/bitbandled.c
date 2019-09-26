#include <LPC17xx.h>
#include <stdio.h>
#include "LED.h"
#include "KDB.h"
#include "GLCD.h"

#define __FI 1
#define __USE_LCD 1

#define ITM_Port8(n) (*((volatile unsigned char *) (0xE0000000+4 * n)))
#define ITM_Port16(n) (*((volatile unsigned char *) (0xE0000000+4 * n)))
#define ITM_Port32(n) (*((volatile unsigned char *) (0xE0000000+4 * n)))

#define DEMCR (*((volatile unsigned char *) (0xE000EDFC)))
#define TRCENA 0x01000000

#define DELAY_TIME 7600 //roughly 1ms

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
#define BitBand(x, y) ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

volatile unsigned long * GPIO1_LED28;
volatile unsigned long * GPIO1_LED29;
#define GPIO1_LED31 (*((volatile unsigned long *) 0x233806FC))
#define GPIO2_LED2 (*((volatile unsigned long *) 0x23380A88))//finish the address

void delay(int ms){
	int i = 0;
	int j = 0;
	for(i = 0; i < ms; i++){
		for(j = 0; j < DELAY_TIME; j++);
	}
}

int main(void){
		int r1 = 1, r2 = 1, r3 = 2;
    LED_Init();
		KDB_Init();
		GLCD_Init();
		GLCD_Clear(White);
		GLCD_SetBackColor(Blue);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString(0, 0, __FI, (unsigned char *)"r1 += r1 * 2");
		
		GPIO1_LED28 = &BitBand(&LPC_GPIO1->FIOPIN1, 28);
		GPIO1_LED29 = &BitBand(&LPC_GPIO1->FIOPIN1, 29);
		while(r1 < 20){ //invokes barrel shifting
			r1 += r1 * 2;
		}
		r1 = 2;
		while(1){
			GLCD_ClearLn(1, __FI);
			//triggers and s suffix conditional execution
			if((r1 - r2) < r3){
				LED_On(4);
				LED_On(5);
				r1 += 1;
				GLCD_DisplayString(1, 0, __FI, (unsigned char *)"1");
			}else if((r1 - r2) > r3){
				*GPIO1_LED28 = 1;
				*GPIO1_LED29 = 1;
				r1 += 2;
				GLCD_DisplayString(1, 0, __FI, (unsigned char *)"2");
			}else{
				GPIO2_LED2 = 1;
				GPIO1_LED31 = 1;
				r1 += 3;
				GLCD_DisplayString(1, 0, __FI, (unsigned char *)"3");
			}
			
			delay(2000);
			//Turn all the LEDS off for the demo
			LED_Off(3);
			LED_Off(4);
			*GPIO1_LED28 = 0;
			*GPIO1_LED29 = 0;
			GPIO1_LED31 = 0;
			GPIO2_LED2 = 0;
			
		}	
    
}

/*int main(void){
	LED_Init();
	GPIO1_LED28 = &BitBand(&LPC_GPIO1->FIOPIN1, 28);
	
	LED_On(3);
	*GPIO1_LED28 = 1;
	GPIO2_LED2 = 1;
}*/
