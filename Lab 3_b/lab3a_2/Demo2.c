#include <stdio.h>
#include "LPC17xx.h"
#include <RTL.h>
#include "GLCD.h"

#define __FI 1
#define __USE_LCD 1

#define DELAY_TIME 7600 //roughly 1ms

#define ADDRESS(x) (*((volatile unsigned long *)(x)))
#define BitBand(x, y) ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))

volatile unsigned long * led1;
volatile unsigned long * led2;
volatile unsigned long * led3;
volatile unsigned long * led5;
volatile unsigned long * led7;

char val[20];

OS_TID id1, id2;
int  cnt1 = 0, cnt2 = 0, temp = 0;

__task void job1 (void);
__task void job2 (void);

#define GPIO2_LED2 (*((volatile unsigned long *) 0x23380A88))//finish the address


void allOff(void ){
	*led1 = 0;
	*led2 = 0;
	*led3 = 0;
	*led5 = 0;
	*led7 = 0;
}

__task void delay(int ms){
	int i = 0;
	int j = 0;
	for(i = 0; i < ms; i++){
		for(j = 0; j < DELAY_TIME; j++);
	}
}

__task void job1 (void) {//incement forever
	id1 = os_tsk_self(); 
	for(;;){
		cnt1++;
		sprintf(val, "0x%04X", cnt1);
		GLCD_DisplayString(0, 0, __FI, (unsigned char *)"Task 1");
		GLCD_DisplayString(2, 0, __FI, (unsigned char *)val);
	}
}

__task void job2 (void) {//check if cnt1 has a prime factor of 1, 2, 3, 5, 7, turn corresponding led on and add the factor to cnt2
	id2 = os_tsk_self();
	for(;;){
		cnt2++;
		sprintf(val, "0x%04X", cnt2);
		GLCD_DisplayString(0, 0, __FI, (unsigned char *)"Task 2");//Display the Barrel shifting equation
		GLCD_DisplayString(3, 0, __FI, (unsigned char *)val);
	}
}

int main (void) {
	SystemInit();
	
	GLCD_Init();//Init the LCD for displaying Barrel Shifting
	GLCD_Clear(White);//clear screen
	GLCD_SetBackColor(Blue);//blue background behind text
	GLCD_SetTextColor(White);//White text
	GLCD_DisplayString(1, 0, __FI, (unsigned char *)"Value:");
	
	os_tsk_create(job1, 0x0); //create job1 and initialize system
	os_tsk_create(job2, 0x0);
	
	os_tsk_delete_self();
	
	os_sys_init(job1);

	
}
