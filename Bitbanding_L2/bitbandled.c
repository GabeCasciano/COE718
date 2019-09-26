//Gabriel Casciano, 500744076
#include <LPC17xx.h>
#include <stdio.h>
#include "LED.h"
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


//Delay (int ms)
//use this function to create a delay.
//The inner for loops for DELAY_TIME iterations and then how ever
//many ms have been entered. (iterations = ms * DELAY_TIME) 
void delay(int ms){
	int i = 0;
	int j = 0;
	for(i = 0; i < ms; i++){
		for(j = 0; j < DELAY_TIME; j++);
	}
}

int main(void){
		int r1 = 1, r2 = 1, r3 = 2;
		LED_Init();//Init the LEDs for masking capabilities
		GLCD_Init();//Init the LCD for displaying Barrel Shifting
		GLCD_Clear(White);//clear screen
		GLCD_SetBackColor(Blue);//blue background behind text
		GLCD_SetTextColor(White);//White text
		GLCD_DisplayString(0, 0, __FI, (unsigned char *)"r1 += r1 * 2");//Display the Barrel shifting equation
		
		GPIO1_LED28 = &BitBand(&LPC_GPIO1->FIOPIN1, 28);//assign the create bit band address of LPC_GPIO10>FIOPIN1 (0x2009C034) to the bit;
		GPIO1_LED29 = &BitBand(&LPC_GPIO1->FIOPIN1, 29);//same as that^^
		while(r1 < 20){ //invokes barrel shifting
			r1 += r1 * 2;
		}
		r1 = 2;
		while(1){
			GLCD_ClearLn(1, __FI);//clear the first row of text every loop
			//triggers and s suffix conditional execution

			//These next series of If, Else If, and Else is mostly useless
			//it serves no actual purpose other than triggering a conditional 
			//execution statement.
		
			if((r1 - r2) < r3){
				LED_On(4);//LED P2.3 ON using masking
				LED_On(5);//LED P2.4 ON using masking
				r1 += 1; //math for conditional execution
				GLCD_DisplayString(1, 0, __FI, (unsigned char *)"1");//display 1 on LCD to represent masking mode
			}else if((r1 - r2) > r3){
				*GPIO1_LED28 = 1;//LED P1.28 ON using function
				*GPIO1_LED29 = 1;//LED P1.29 ON using function
				r1 += 2;
				GLCD_DisplayString(1, 0, __FI, (unsigned char *)"2");//display 2 on LCD for function mode
			}else{
				GPIO2_LED2 = 1;//LED P2.2 ON using BB
				GPIO1_LED31 = 1;//LED P1.31 ON using BB
				r1 += 3;
				GLCD_DisplayString(1, 0, __FI, (unsigned char *)"3");//display 3 on LCD for BB mode
			}
			
			//The next sequence is so the demo works, i.e. turning the lights off and delay so we can determine the state of the mcu
			delay(2000);//refer to delay function for explination
			//We delay and then turn the lights off so it appears that the lights seamlessy switched from one set on to the other set on
			LED_Off(4);
			LED_Off(5);
			*GPIO1_LED28 = 0;
			*GPIO1_LED29 = 0;
			GPIO1_LED31 = 0;
			GPIO2_LED2 = 0;
			
		}	
    
}

//Uncomment this main methoh and comment the other for speed testing
//Put a break point on each line, take the sums (LED_Init + LED_On) and (GPIO1_LED28 = &... + GPIO1_LDE28 = 1)
/*int main(void){
	LED_Init();
	GPIO1_LED28 = &BitBand(&LPC_GPIO1->FIOPIN1, 28);
	
	LED_On(3);
	*GPIO1_LED28 = 1;
	GPIO2_LED2 = 1;
}*/
