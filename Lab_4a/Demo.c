//Gabriel Casciano, 500744076
#include <stdio.h>
#include "LPC17xx.h"
#include <RTL.h>
#include "GLCD.h"
#include "LED.h"

#define __FI        1                    /* Font index 16x24        */
//#define __USE_LCD   0	

long global_c1 = 0, global_c2 = 0, global_c3 = 0;


__task void task1(void){
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

__task void task2(void){
	global_c2 = 0xFEEED;
	while(global_c2>0){
		global_c2-=3;
		LED_Out(0x24);
	}
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	GLCD_DisplayString(4, 12, __FI, "YUUUM!");
	os_tsk_delete_self();
#endif
}

__task void task3(void){
	global_c3 = 0xFEEED;
	while(global_c3>0){
		global_c3 -= 4;
		LED_Out(0x18);
	}
#ifdef __USE_LCD
	GLCD_DisplayString(7, 10, __FI, "DELICIOUS!");
	os_tsk_delete_self();
#endif
}

int main(void){
#ifdef __USE_LCD
	GLCD_Init();                              
	GLCD_Clear(White);
#endif
	SystemInit();
	LED_Init();
	os_tsk_create(task1, 1);
	os_tsk_create(task2, 1);
	os_tsk_create(task3, 1);

	os_tsk_delete_self();

	os_sys_init(task1);
}
