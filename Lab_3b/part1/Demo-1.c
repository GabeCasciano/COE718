//Gabriel Casciano, 500744076
#include <stdio.h>                                  
#include <ctype.h>                    
#include <string.h>     
#include <math.h>
#include "cmsis_os.h"
#include "RTL.H"		
#include "LPC17xx.H"            
#include "GLCD.h"

#define __FI        1                    
//#define __USE_LCD   0 //uncomment for DEM0


osThreadId idA, idB, idC, idD, idE;
int x, i, p, j, n, m;
char out[20];
#define PI 3.142

double factor;

__task void threadA (void const *arg) {
	int A = 0;
	for (x=0; x<257; x++){  
		A = A + (x + (x+2));
		os_tsk_pass() ;//for concurrent execution
	}
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	sprintf(out, "%d", (char)A);
	GLCD_DisplayString(4, 12, __FI, out);
#endif
	osThreadTerminate(idA);
}

__task void threadB (void const *arg) {
	
	int B = 0;
	factor=1;
	for(i = 1; i<17; i++){
		factor = factor*i;
		B = B + pow(2,i)/factor;
		os_tsk_pass() ;//for concurrent execution
	}
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	sprintf(out, "%d", (char)B);
	GLCD_DisplayString(5, 12, __FI, out);
#endif
	osThreadTerminate(idB);
}

__task void threadC (void const *arg) {
	int C = 0;
	for (n=1; n<17; n++){
		C = C + (n+1)/n;
	} 
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	sprintf(out, "%d", (char)C);
	GLCD_DisplayString(6, 12, __FI, out);
#endif
	osThreadTerminate(idC);	
}

__task void threadD (void const *arg) {
	int D = 0;
	factor=1;
	for (m=0; m<6; m++){
		factor = factor*m;
		if(factor == 0){
			factor=1;
		}
		else{
		os_tsk_pass() ;
		D = D + pow(5, m)/(double)factor;
		}
	}
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	sprintf(out, "%d", (char)D);
	GLCD_DisplayString(7, 12, __FI, out);
#endif
	osThreadTerminate(idD);
}

__task void threadE(void const *arg) {
	int E = 0;
	int radius=1;
	for (p=1; p<13; p++){
		E = E + p*PI*(pow(radius, 2));
		os_tsk_pass() ;
	}
#ifdef __USE_LCD
	GLCD_SetTextColor(Red);
	sprintf(out, "%d", (char)E);
	GLCD_DisplayString(8, 12, __FI, out);
#endif	
	osThreadTerminate(idE);	
}

osThreadDef (threadA, osPriorityBelowNormal, 1, 0); //lowest priority
osThreadDef (threadB, osPriorityBelowNormal, 1, 0); //lowest priority
osThreadDef (threadC, osPriorityHigh, 1, 0); //highest Priority 
osThreadDef (threadD, osPriorityAboveNormal, 1, 0); //medium priority
osThreadDef (threadE, osPriorityAboveNormal, 1, 0); //medium priority

int main (void) {
	SystemInit(); // initialize the Coretx-M3 processor
	
#ifdef __USE_LCD
	GLCD_Init();                               
	GLCD_Clear(White);                        
	GLCD_SetBackColor(Blue);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0, 0, __FI, "  COE718 Demo Lab3b  ");
	GLCD_DisplayString(1, 0, __FI, "   Gabriel Casciano  ");
	GLCD_DisplayString(2, 0, __FI, "     500744076       ");
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, __FI, "Task A  :            ");
	GLCD_DisplayString(5, 0, __FI, "Task B  :            ");
	GLCD_DisplayString(6, 0, __FI, "Task C  :            ");
	GLCD_DisplayString(7, 0, __FI, "Task D  :            ");
	GLCD_DisplayString(8, 0, __FI, "Task E  :            ");
#endif
	
	osKernelInitialize ();   // setup kernel
	idA = osThreadCreate (osThread(threadA), NULL);   // create threads
 	idB = osThreadCreate (osThread(threadB), NULL);
	idC = osThreadCreate (osThread(threadC), NULL); 
	idD = osThreadCreate (osThread(threadD), NULL); 
	idE = osThreadCreate (osThread(threadE), NULL); 
 	osKernelStart ();       // start kernel

	osDelay(osWaitForever);
	
}
