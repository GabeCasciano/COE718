#include <stdio.h>
#include <stdlib.h>
#include "LPC17xx.h"
#include <RTL.h>
#include "GLCD.h"
#include <math.h>

#define true 1
#define false 0

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

OS_TID id1, id2, id3, id4;
char val[3][3] = { {0,0,0} , {0,0,0} , {0,0,0} };

int i, j; //global loop vars

__task void counter (void);
__task void isOdd (void);
__task void isPrime (void);
__task void display(void);

#define GPIO2_LED2 (*((volatile unsigned long *) 0x23380A88))//finish the address

int checkPrime(int n){
    if(n <= 1){
        return true;
		}
    for(i = 2 ; i < n; i++){
            if(n % i == 0){
                return false;
						}
    }
    return true;

}

void del(int n){
	int cnt = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < DELAY_TIME; j++){
			cnt++;
		}
		cnt = 0;
	}
}

__task void display(void){
	char out1[30], out2[30], out3[30];
	id4 = os_tsk_self();
	
	
	if(__USE_LCD){
		id1 = os_tsk_create(counter, 2);
		id2 = os_tsk_create(isOdd, 2);
		id3 = os_tsk_create(isPrime, 2);
	}
	
	GLCD_Clear(White);//clear screen
	GLCD_SetBackColor(Blue);//blue background behind text
	GLCD_SetTextColor(White);//White text
	GLCD_DisplayString(0, 0, __FI, (unsigned char *)"COE718 - Lab3a_1");
	GLCD_DisplayString(1, 0, __FI, (unsigned char *)"Gabriel Casciano");
	
	for(;;){
		sprintf(out1, "1 -> cnt: %d odd: %d prm: %d ", val[0][0], val[0][1], val[0][2]);
		sprintf(out2, "2 -> cnt: %d odd: %d prm: %d ", val[1][0], val[1][1], val[1][2]);
		sprintf(out3, "3 -> cnt: %d odd: %d prm: %d ", val[2][0], val[2][1], val[2][2]);
		GLCD_DisplayString(2, 0, __FI, (unsigned char *)out1);
		GLCD_DisplayString(3, 0, __FI, (unsigned char *)out2);
		GLCD_DisplayString(4, 0, __FI, (unsigned char *)out3);
		if(__USE_LCD){
			del(100);
		}
	}
}

__task void counter (void) {//incement forever
	id1 = os_tsk_self(); 
	for(;;){
		if(val[0][0] < 100){
			for(i = 0; i < 3; i++){
				val[i][0] += pow(2,i);
			}
		}
		else{
			for(i = 0; i < 3; i++){
				val[i][0] = 0;
			}
		}
		os_tsk_pass();
	}
}

__task void isOdd (void) {//check if cnt1 has a prime factor of 1, 2, 3, 5, 7, turn corresponding led on and add the factor to cnt2
	id2 = os_tsk_self();
	for(;;){
		for(i = 0; i < 3; i++){
			val[i][1] = val[i][0] % 2;
		}
		os_tsk_pass();
	}
}

__task void isPrime(void){
	id3 = os_tsk_self();
	for(;;){
		for(i = 0; i < 3; i++){
			val[i][2] = checkPrime(val[i][0]);
		}
		os_tsk_pass();
	}
	
}

int main (void) {
	SystemInit();
	
	GLCD_Init();//Init the LCD for displaying Barrel Shifting
	
	if(__USE_LCD){
		os_tsk_create(display, 1);
		
		os_sys_init(display);
	}else{
		os_tsk_create(counter, 1);
		os_tsk_create(isOdd, 1);
		os_tsk_create(isPrime, 1);
		os_sys_init(counter);
	}
	
	os_tsk_delete_self();
	
}
