/*----------------------------------------------------------------------------
 * Name:    Blinky.c
 * Purpose: LED Flasher
 * Note(s): __USE_LCD   - enable Output on LCD, uncomment #define in code to use
 *  				for demo (NOT for analysis purposes)
 *----------------------------------------------------------------------------
 * Copyright (c) 2008-2011 Keil - An ARM Company.
 * Name: Anita Tino
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "LPC17xx.H"                       
#include "GLCD.h"
#include "LED.h"
#include "ADC.h"
#include "KDB.h"
#include "Joystick.h"

#define __FI        1                      /* Font index 16x24               */
#define __USE_LCD   1										/* Uncomment to use the LCD */

//ITM Stimulus Port definitions for printf //////////////////
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

struct __FILE { int handle;  };
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f) {
  if (DEMCR & TRCENA) {
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
  }
  return(ch);
}
/////////////////////////////////////////////////////////

char adc_value[16];
char string[20];
char joystick_value[10];

const unsigned long led_mask1[] = { 1UL<<28, 1UL<<29, 1UL<<31, 1UL<< 2,

                                   1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6 };

//Use to trace the pot values in Debug
uint16_t ADC_Dbg;

/* Import external variables from IRQ.c file                                  */
extern uint8_t  clock_ms;


/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  uint32_t ad_avg = 0;
  uint16_t ad_val = 0, ad_val_ = 0xFFFF;

  LED_Init();                                /* LED Initialization            */
  ADC_Init();                                /* ADC Initialization            */
  KDB_Init();																 /* KDB Initialization						*/
	JOYSTICK_Init();                           /* JOYSTICK Initialization       */
	

#ifdef __USE_LCD
  GLCD_Init();                               /* Initialize graphical LCD (if enabled */

  GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, (unsigned char *)"     COE718 Demo    ");
	GLCD_SetTextColor(White);
  GLCD_DisplayString(1, 0, __FI, (unsigned char *)"       Blinky.c     ");
  GLCD_DisplayString(2, 0, __FI, (unsigned char *)"       Something    ");
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);

#endif

  SysTick_Config(SystemCoreClock/100);       /* Generate interrupt each 10 ms */

  while (1) {                                /* Loop forever                  */

    /* AD converter input                                                     */
    if (AD_done) {                           /* If conversion has finished    */
      AD_done = 0;

      ad_avg += AD_last << 8;                /* Add AD value to averaging     */
      ad_avg ++;
      if ((ad_avg & 0xFF) == 0x10) {         /* average over 16 values        */
        ad_val = (ad_avg >> 8) >> 4;         /* average devided by 16         */
        ad_avg = 0;
      }
    }
    
		ADC_Dbg = ad_val;
		
    if (ad_val ^ ad_val_) {                  /* AD value changed              */
        ad_val_ = ad_val;

        sprintf(adc_value, "0x%04X", ad_val);       /* format text for print out     */
    }
		strcpy(string, "ADC: ");
		strcat(string, adc_value);
    GLCD_DisplayString(6, 0, __FI, (unsigned char*)string);
    /* Print message with AD value every 10 ms                               */
    if (clock_ms) {
      clock_ms = 0;
			
      printf("AD value: %s\r\n", adc_value);
    }
       /* Update Joystick value and displays*/
		
    strcpy(joystick_value, JOYSTICK_Update());
    strcpy(string, "Joy Value: ");
	if(strcmp(joystick_value, JOYSTICK_UP)){
		LED_Out(0);
	}else if(strcmp(joystick_value, JOYSTICK_DOWN)){
		LED_Out(1);
	}else if(strcmp(joystick_value, JOYSTICK_LEFT)){
		LED_Out(2);
	}else if(strcmp(joystick_value, JOYSTICK_RIGHT)){
		LED_Out(3);
	}else if(strcmp(joystick_value, JOYSTICK_SELECT)){
		LED_Out(4);
	}
    strcat(string, joystick_value);
    GLCD_DisplayString(7, 0, __FI, (unsigned char*)string);

  }
}
