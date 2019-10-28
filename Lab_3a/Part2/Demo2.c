//Gabriel Casciano, 500744076
#include <stdio.h>
#include "LPC17xx.h"
#include <RTL.h>
#include "GLCD.h"
#include "LED.h"
#include <string.h>

#define __FI        1                    /* Font index 16x24        */
//#define __USE_LCD   0

OS_TID MEMid, CPUid, APPid, DEVid, id5;
double  MEMcnt, CPUcnt, APPcnt, DEVcnt, users;
OS_MUT mutex;
char logger[];

// Bit Band Macros used to calculate the alias address at run time
#define ADDRESS(x)    (*((volatile unsigned long *)(x)))
#define BitBand(x, y) 	ADDRESS(((unsigned long)(x) & 0xF0000000) | 0x02000000 |(((unsigned long)(x) & 0x000FFFFF) << 5) | ((y) << 2))
#define L1 (*((volatile unsigned long *)0x233806F0)) 				//assigns LED on port1.28 for bitbanding

int r1 = 1, r2 = 0, r3 = 5;

int i,j;
void delay(){
	for(i = 0 ; i < 10000000; i++){
		j=i;
	}
}

__task void MemoryM (void);
__task void CPUM (void);
__task void AppI (void);
__task void DeviceM (void);
__task void UserI (void);


__task void MemoryM (void) {
	
#ifdef __USE_LCD
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(7, 1, __FI, "Memory Management");
	LED_Out(1);
	delay();
#endif
	
	MEMid = os_tsk_self();	//identify myself and create CPU management
	os_tsk_pass(); 									//passes control to CPU management
	MEMcnt++; 											//increment counter
	L1 = 1;												 //bitbanding
	
	
	

	if(os_evt_wait_and(0x0004, 0xFFFF)){		//receives signal back from CPUm
		L1 = 0;		//bitbanding switch port 1.28 off
		//delay();
		os_tsk_delete_self(); //delete itself (MemoryM)
	}
}

__task void CPUM (void) {

#ifdef __USE_LCD
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(7, 1, __FI, "CPU Management    ");
	LED_Out(2);
	delay();
#endif

	CPUid = os_tsk_self(); //obtain my identity
	//os_tsk_pass(); //pass to Memory M
		// barrel-shifter	& conditional execution
	  while(r2 <= 0x18){
			if((r1 - r2) > 0){
				r1 = r1 + 2;
				r2 = r1 + (r3*4);
				r3 = r3/2;
			}
			else{
				r2 = r2 + 1;
			}
		}
		CPUcnt++; //increment counter
		//delay();
		os_evt_set(0X0004,MEMid); //signals back to memory management
		os_tsk_delete_self();
}
				

__task void AppI (void) {
	
#ifdef __USE_LCD
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(7, 1, __FI, "App Interface   ");
	LED_Out(4);
	delay();
#endif	
	APPid = os_tsk_self(); 							//obtain my identity
	os_mut_init(mutex);								//initialization of the system
	os_mut_wait(&mutex, 0xffff);			// in the task seeking mutual exclusion
	strcpy(logger,"Start-");
	os_tsk_pass(); //passing token to Device Management
	//os_tsk_prio_self(7);	//increase my priority so that I may get Device Management's signal
	if(os_evt_wait_and(0x0008, 0xFFFF)){		//receives signal back from DeviceM
		APPcnt++;			//increment counter
		//delay();
		os_tsk_delete(DEVid);		//delete device manager
	}
}

__task void DeviceM (void) {	
#ifdef __USE_LCD
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(7, 1, __FI, "Device Manager  ");
	LED_Out(8);
	delay();
#endif

	DEVid = os_tsk_self(); //obtain my identity
	os_evt_set(0X0008,APPid); //signals back to App Interface
	os_tsk_pass();	//pass to App Interface so it executes before Device Management
	strcpy(logger,"End");
	DEVcnt++; //increment counter
	//delay();
}

__task void UserI (void) {

#ifdef __USE_LCD
	GLCD_SetTextColor(Magenta);
	GLCD_DisplayString(7, 1, __FI, "User Interface  ");
	LED_Out(16);
	delay();
#endif
	users++; //increment users
	//delay();
	os_tsk_delete_self();
}

int main (void) {
	LED_Init();                                /* LED Initialization            */
	
#ifdef __USE_LCD
	GLCD_Init();                                /* Initialize graphical LCD (if enabled  */

	GLCD_Clear(White);                         /* Clear graphical LCD display   */
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0, 0, __FI, "Anne's COE718 Demo     ");
	GLCD_SetTextColor(White);
	GLCD_DisplayString(1, 0, __FI, "       Demo2.c      ");
	GLCD_DisplayString(2, 0, __FI, "Preemptive Scheduling");
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(DarkCyan);
	GLCD_DisplayString(5, 0, __FI, "Task:          ");
#endif
	os_tsk_create(MemoryM, 1); //create MemoryManagement and initialize system
	os_tsk_create(CPUM, 1);
	os_tsk_create(DeviceM, 2);
	os_tsk_create(AppI, 2);
	os_tsk_create(UserI, 5);
	SystemInit();
	os_mut_init(&mutex);
	os_tsk_delete_self();
}
