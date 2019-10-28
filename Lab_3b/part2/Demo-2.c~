//Gabriel Casciano, 500744076
#include <stdio.h>                                  
#include <ctype.h>      
#include "cmsis_os.h"
#include "RTL.H"		
#include "LPC17xx.H"               
#include "GLCD.h"
#include "LED.h"

#define __FI        1                   
#define __USE_LCD   0										

long global_c1 = 0, global_c2 = 0, global_c3 = 0;

__task void Appetizer (void const *arg) {
	
#ifdef __USE_LCD
	GLCD_SetTextColor(DarkGrey);
	GLCD_DisplayString(1, 1, __FI, "Appetizer");
	GLCD_DisplayString(4, 1, __FI, "Entree");
	GLCD_DisplayString(7, 1, __FI, "Dessert");
#endif
	global_c1 = 0xFEEED;
	while(global_c1>0){
		global_c1-=2;
		LED_Out(0x81);
	}

#ifdef __USE_LCD
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(1, 12, __FI, "TASTY!");
#endif
	os_tsk_delete_self();
}

__task void Entree (void const *arg) {

	global_c2 = 0xFEEED;
	while(global_c2>0){
		global_c2-=3;
		LED_Out(0x24);
	}
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(4, 12, __FI, "YUUUM!");
#endif
	os_tsk_delete_self();
			
}

__task void Dessert (void const *arg) {

	global_c3 = 0xFEEED;
	while(global_c3>0){
		global_c3 -= 4;
		LED_Out(0x18);
	}
		
	
#ifdef __USE_LCD
	GLCD_DisplayString(7, 10, __FI, "DELICIOUS!");
#endif
	os_tsk_delete_self();			
}

//thead definitions
osThreadDef (Appetizer, osPriorityNormal, 1, 0); 
osThreadDef (Entree, osPriorityNormal, 1, 0);
osThreadDef (Dessert, osPriorityNormal, 1, 0);

int main (void) {
#ifdef __USE_LCD
	GLCD_Init();                              
  	GLCD_Clear(White);
#endif
	
	SystemInit(); 
	LED_Init();
	osKernelInitialize ();//init kern
	//create threads   
	osThreadCreate (osThread(Appetizer), NULL);  
 	osThreadCreate (osThread(Entree), NULL);
	osThreadCreate (osThread(Dessert), NULL);
 	osKernelStart ();       // start kernel

	osDelay(osWaitForever);
}
