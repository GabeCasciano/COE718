///*#############################################################################/
//	Using threads, signal, and wait for thread scheduling and synchronization
//	CMSIS RTX Example
//	Anita Tino
//*#############################################################################*/
//#include "LPC17xx.h"
//#include "cmsis_os.h"
//#include "RTL.H"
//#include "LED.h"

//void led_Thread1 (void const *argument);
//void led_Thread2 (void const *argument);
//void led_Thread3 (void const *argument);

//osThreadDef(led_Thread1, osPriorityNormal, 1, 0);
//osThreadDef(led_Thread2, osPriorityNormal, 1, 0);
//osThreadDef(led_Thread3, osPriorityNormal, 1, 0);

///*###########################################################
//	Virtual Timer declaration and call back method
//############################################################*/
//osThreadId T_led_ID1;
//osThreadId T_led_ID2;	
//osThreadId T_led_ID3;	

//// Toggle the LED associated with the timer
//void callback(void const *param){
//	switch( (uint32_t) param){
//		case 0:
//			LED_On(4); LED_Off(5);
//			osDelay(1000);
//		  LED_Off(4); LED_Off(5);
//			break;
//		case 1:
//			LED_Off(6); LED_On(7);
//		  osDelay(1000);
//		  LED_Off(6); LED_Off(7);
//		  break;
//	}
//}
//osTimerDef(timer0_handle, callback);
//osTimerDef(timer1_handle, callback);
////#############################################################

///*#############################################################
//  Flash LED 0, signal to thread 2, wait for 3 to finish
//*#############################################################*/
//void led_Thread1 (void const *argument) {
//	for (;;) {
//		LED_On(0);
//		osDelay(5000);
//		osSignalSet	(T_led_ID2,0x01);
//		LED_Off(0); 
//		osSignalWait (0x03,osWaitForever);
//	}
//}

///*################################################################
//  Flash LED 2, signal to thread 3, wait for thread 1 to finish
//*################################################################*/
//void led_Thread2 (void const *argument) {
//	for (;;) 	{
//		LED_Off(2);	
//		osSignalWait (0x01,osWaitForever);
//		LED_On(2);
//    osDelay(5000);		
//		LED_Off(2);
//		osSignalSet	(T_led_ID3,0x02);
//	}
//}

///*################################################################
//  Flash LED 4, signal to thread 1, wait for thread 2 to finish
//*################################################################*/
//void led_Thread3 (void const *argument){
//	for (;;) 	{
//		LED_Off(4);
//		osSignalWait (0x02,osWaitForever);
//		LED_On(4); 
//		osDelay(5000);
//		LED_Off(4);
//		osSignalSet	(T_led_ID1,0x03);
//		
//	}
//}

///*###################################################################
//  Create and start threads
// *###################################################################*/
//int main (void) {
//		
//	//Virtual timer create and start
//	osTimerId timer_0 = osTimerCreate(osTimer(timer0_handle), osTimerPeriodic, (void *)0);	
//	osTimerId timer_1 = osTimerCreate(osTimer(timer1_handle), osTimerPeriodic, (void *)1);	
//	
//  LED_Init ();	
//	osTimerStart(timer_0, 6000);	
//	osTimerStart(timer_1, 2000);	
//	
//	//Signal and wait threads
//	T_led_ID1 = osThreadCreate(osThread(led_Thread1), NULL);
//	T_led_ID2 = osThreadCreate(osThread(led_Thread2), NULL);
//  T_led_ID3 = osThreadCreate(osThread(led_Thread3), NULL);
//	osDelay(osWaitForever);               						
//	
//	for (;;);
//}
/*********/
// by adam yang
//for coe718
#include "LPC17xx.h"
#include "cmsis_os.h"
#include "RTL.h"
#include "LED.h"


// define the three operational threads

void thr_At (void const *arg);
void thr_Bt (void const *arg);
void thr_Ct (void const *arg);

// thread definitions are completed now define it using os
osSemaphoreId download_more_ram;
osSemaphoreDef(download_more_ram);

osThreadDef(thr_At,osPriorityNormal, 1, 0); //last two are # of instances and stack size requirements
osThreadDef(thr_Bt,osPriorityAboveNormal,1,0);
osThreadDef(thr_Ct,osPriorityHigh,1,0);

// define the virtual timer and callback stuff
osThreadId TRA;
osThreadId TRB;
osThreadId TRC;

// for this we can either do all in callbacks or we can do it via scheduling. FOR RMS let us try doing it 
//via callbacks
// note via the declaration of priority, we have enabled preemption of one thread by another, therefore
// the virtual timers need to simply start a thread in order to make it go
// we need the threads to run a finitie specified duration before we let it go
// preemption will suffice for RMS
// INSERT THE FUNCTIONAL DEFEIJNINKS
// can use timers to signal to threads when to start operations !
void t_s (void const *param){
osSignalSet(TRB,0x01);
osSignalSet(TRA,0x01);
	osSignalSet(TRC,0x01);
}
void thr_A (void const *param){

osSignalSet(TRA,0x01);
}

void thr_B (void const *param){

osSignalSet(TRB,0x01);
}

void thr_C (void const *param){

osSignalSet(TRC,0x01);
}


// timer thread declaraionts
osTimerDef(tms, t_s);
osTimerDef(tm0, thr_A);
osTimerDef(tm1,thr_B);
osTimerDef(tm2,thr_C);
void thr_At( void const *param){
int k =0;
	int b=0;
	int c=0;
	int d=0;
for(;;){
LED_On(1);
LED_On(5);


osSignalWait(0x01,osWaitForever); // each for = .073 s
	osThreadSetPriority(TRA,osPriorityRealtime);
			osSemaphoreWait(download_more_ram,osWaitForever);
 for(k =0;k<0xFFFF;k++)for(b =0;b<58;b++);//for(b =0;b<0xFFFFFFF;b++);//for(c =0;c<0xFFFFFFF;c++);
k=0;
	b=0;
c=0;
k=0;
osSemaphoreRelease(download_more_ram);
		osThreadSetPriority(TRA,osPriorityNormal);
LED_Off(1);
}

}

void thr_Bt( void const *param){
int k =0;
	int b=0;
	int c=0;
	int d=0;
for(;;){
LED_On(2);


osSignalWait(0x01,osWaitForever);
			osSemaphoreWait(download_more_ram,osWaitForever);
for(k =0;k<0xFFFF;k++)for(b =0;b<28;b++);//for(b =0;b<0xFFFFFFF;b++);//for(c =0;c<0xFFFFFFF;c++);
k=0;
	b=0;
c=0;
k=0;
	osSemaphoreRelease(download_more_ram);

LED_On(6);
//some random time length stuff


LED_Off(2);
}
}
void thr_Ct( void const *param){
int k =0;
	int b=0;
	int c=0;
	int d=0;
	
for(;;){
LED_On(3);
LED_On(7);

osSignalWait(0x01,osWaitForever); // 3.943ms
		osThreadSetPriority(TRA,osPriorityRealtime);
		osSemaphoreWait(download_more_ram,osWaitForever);
for(k =0;k<0xFFFF;k++)for(b =0;b<13;b++);//for(b =0;b<0xFFFFFFF;b++);//for(c =0;c<0xFFFFFFF;c++);
k=0;
	b=0;
c=0;
osSemaphoreRelease(download_more_ram);

		osThreadSetPriority(TRA,osPriorityHigh);

LED_Off(3);
}
}

//now the main

int main(void){
osTimerId tm_S = osTimerCreate(osTimer(tms),osTimerOnce,(void *)0); // note the last statement refers to passing

osTimerId tm0 = osTimerCreate(osTimer(tm0),osTimerPeriodic,(void *)0); // note the last statement refers to passing
// parameters. we must pass the address of a variable if we want to use it. ie &var
osTimerId tm1 = osTimerCreate(osTimer(tm1),osTimerPeriodic,(void *) 0);
osTimerId tm2 = osTimerCreate(osTimer(tm2),osTimerPeriodic,(void *) 0);

// ciompleted timer declarations. now we must start the timers initi stuff

LED_Init();
	download_more_ram= osSemaphoreCreate(osSemaphore(download_more_ram),1);

osTimerStart(tm_S,1);
osTimerStart(tm0,4000);
osTimerStart(tm1,3000);
osTimerStart(tm2,2000);

TRA = osThreadCreate(osThread(thr_At),NULL);
TRB = osThreadCreate(osThread(thr_Bt),NULL);
TRC = osThreadCreate(osThread(thr_Ct),NULL);

// if we dont run the threads then we can simply let the timers keep calling? YES
osDelay(osWaitForever);
for(;;);
}

//// PRIORITY INVERSION
//#include "LPC17xx.h"
//#include "cmsis_os.h"
//#include "RTL.h"
//#include "LED.h"

//void thr_At (void const *arg);

//void thr_Bt (void const *arg);

//void thr_Ct (void const *arg);
//osThreadDef(thr_At,osPriorityHigh, 1, 0); //last two are # of instances and stack size requirements
//osThreadDef(thr_Bt,osPriorityAboveNormal,1,0);
//osThreadDef(thr_Ct,osPriorityAboveNormal,1,0);
//osThreadId TRA;
//osThreadId TRB;
//osThreadId TRC;
//osSemaphoreDef(download_more_ram);
//osSemaphoreId(minecraft);
//void t_s (void const *param){
//osSignalSet(TRB,0x01);
//osSignalSet(TRA,0x01);
//	osSignalSet(TRC,0x01);
//}
//void thr_A (void const *param){

//osSignalSet(TRA,0x01);
//}

//void thr_B (void const *param){

//osSignalSet(TRB,0x01);
//}

//void thr_C (void const *param){

//osSignalSet(TRC,0x01);
//}













//osTimerDef(tms, t_s);
//osTimerDef(tm0, thr_A);
//osTimerDef(tm1,thr_B);
//osTimerDef(tm2,thr_C);
//void thr_At( void const *param){
//int k =0;
//	int b=0;
//int c=0;
//int d=0;
//for(;;){
//LED_On(1);
//LED_On(5);
//osSemaphoreWait(minecraft,osWaitForever);
//for(k =0;k<0xFFF;k++);//for(b =0;b<15;b++);
//osSemaphoreRelease(minecraft);

//LED_Off(1);
//}

//}

//void thr_Bt( void const *param){
//int k =0;
//	int b=0;
//	int c=0;
//int d=0;
//for(;;){
//LED_On(2);
//osSemaphoreWait(minecraft,osWaitForever);
//for(k =0;k<0xFFF;k++);///for(b =0;b<15;b++);

//osSemaphoreRelease(minecraft);

//LED_On(6);
////some random time length stuff


//LED_Off(2);
//}
//}
//void thr_Ct( void const *param){
//int k =0;
//int b=0;
//int c=0;
//int d=0;
//for(;;){
//LED_On(3);
//LED_On(7);
//osSignalWait(0x01,osWaitForever);
//osSemaphoreWait(minecraft,0);
//for(k =0;k<0xFFF;k++);//for(b =0;b<10;b++);

//osSemaphoreRelease(minecraft);


//LED_Off(3);
//}
//}
//int main(void){



//// ciompleted timer declarations. now we must start the timers initi stuff

//osTimerId tm_S = osTimerCreate(osTimer(tms),osTimerOnce,(void *)0); // note the last statement refers to passing

//osTimerId tm0 = osTimerCreate(osTimer(tm0),osTimerPeriodic,(void *)0); // note the last statement refers to passing
//// parameters. we must pass the address of a variable if we want to use it. ie &var
//osTimerId tm1 = osTimerCreate(osTimer(tm1),osTimerPeriodic,(void *) 0);
//osTimerId tm2 = osTimerCreate(osTimer(tm2),osTimerPeriodic,(void *) 0);
//LED_Init();
//osTimerStart(tm_S,1);
//osTimerStart(tm0,400);
//osTimerStart(tm1,400);
//osTimerStart(tm2,200);


//TRA = osThreadCreate(osThread(thr_At),NULL);
//TRB = osThreadCreate(osThread(thr_Bt),NULL);
//TRC = osThreadCreate(osThread(thr_Ct),NULL);

//// if we dont run the threads then we can simply let the timers keep calling? YES
//osDelay(osWaitForever);
//for(;;);
//}
/////*#############################################################################/
////	Using threads, signal, and wait for thread scheduling and synchronization
////	CMSIS RTX Example
////	Anita Tino
////*#############################################################################*/
////#include "LPC17xx.h"
////#include "cmsis_os.h"
////#include "RTL.H"
////#include "LED.h"

////void led_Thread1 (void const *argument);
////void led_Thread2 (void const *argument);
////void led_Thread3 (void const *argument);

////osThreadDef(led_Thread1, osPriorityNormal, 1, 0);
////osThreadDef(led_Thread2, osPriorityNormal, 1, 0);
////osThreadDef(led_Thread3, osPriorityNormal, 1, 0);

/////*###########################################################
////	Virtual Timer declaration and call back method
////############################################################*/
////osThreadId T_led_ID1;
////osThreadId T_led_ID2;	
////osThreadId T_led_ID3;	

////// Toggle the LED associated with the timer
////void callback(void const *param){
////	switch( (uint32_t) param){
////		case 0:
////			LED_On(4); LED_Off(5);
////			osDelay(1000);
////		  LED_Off(4); LED_Off(5);
////			break;
////		case 1:
////			LED_Off(6); LED_On(7);
////		  osDelay(1000);
////		  LED_Off(6); LED_Off(7);
////		  break;
////	}
////}
////osTimerDef(timer0_handle, callback);
////osTimerDef(timer1_handle, callback);
//////#############################################################

/////*#############################################################
////  Flash LED 0, signal to thread 2, wait for 3 to finish
////*#############################################################*/
////void led_Thread1 (void const *argument) {
////	for (;;) {
////		LED_On(0);
////		osDelay(5000);
////		osSignalSet	(T_led_ID2,0x01);
////		LED_Off(0); 
////		osSignalWait (0x03,osWaitForever);
////	}
////}

/////*################################################################
////  Flash LED 2, signal to thread 3, wait for thread 1 to finish
////*################################################################*/
////void led_Thread2 (void const *argument) {
////	for (;;) 	{
////		LED_Off(2);	
////		osSignalWait (0x01,osWaitForever);
////		LED_On(2);
////    osDelay(5000);		
////		LED_Off(2);
////		osSignalSet	(T_led_ID3,0x02);
////	}
////}

/////*################################################################
////  Flash LED 4, signal to thread 1, wait for thread 2 to finish
////*################################################################*/
////void led_Thread3 (void const *argument){
////	for (;;) 	{
////		LED_Off(4);
////		osSignalWait (0x02,osWaitForever);
////		LED_On(4); 
////		osDelay(5000);
////		LED_Off(4);
////		osSignalSet	(T_led_ID1,0x03);
////		
////	}
////}

/////*###################################################################
////  Create and start threads
//// *###################################################################*/
////int main (void) {
////		
////	//Virtual timer create and start
////	osTimerId timer_0 = osTimerCreate(osTimer(timer0_handle), osTimerPeriodic, (void *)0);	
////	osTimerId timer_1 = osTimerCreate(osTimer(timer1_handle), osTimerPeriodic, (void *)1);	
////	
////  LED_Init ();	
////	osTimerStart(timer_0, 6000);	
////	osTimerStart(timer_1, 2000);	
////	
////	//Signal and wait threads
////	T_led_ID1 = osThreadCreate(osThread(led_Thread1), NULL);
////	T_led_ID2 = osThreadCreate(osThread(led_Thread2), NULL);
////  T_led_ID3 = osThreadCreate(osThread(led_Thread3), NULL);
////	osDelay(osWaitForever);               						
////	
////	for (;;);
////}
///*********/
//// by adam yang
////for coe718
//#include "LPC17xx.h"
//#include "cmsis_os.h"
//#include "RTL.h"
//#include "LED.h"


//// define the three operational threads

//void thr_At (void const *arg);
//void thr_Bt (void const *arg);
//void thr_Ct (void const *arg);

//// thread definitions are completed now define it using os

//osThreadDef(thr_At,osPriorityNormal, 1, 0); //last two are # of instances and stack size requirements
//osThreadDef(thr_Bt,osPriorityAboveNormal,1,0);
//osThreadDef(thr_Ct,osPriorityHigh,1,0);

//// define the virtual timer and callback stuff
//osThreadId TRA;
//osThreadId TRB;
//osThreadId TRC;

//// for this we can either do all in callbacks or we can do it via scheduling. FOR RMS let us try doing it 
////via callbacks
//// note via the declaration of priority, we have enabled preemption of one thread by another, therefore
//// the virtual timers need to simply start a thread in order to make it go
//// we need the threads to run a finitie specified duration before we let it go
//// preemption will suffice for RMS
//// INSERT THE FUNCTIONAL DEFEIJNINKS
//// can use timers to signal to threads when to start operations !
//void t_s (void const *param){
//osSignalSet(TRB,0x01);
//osSignalSet(TRA,0x01);
//	osSignalSet(TRC,0x01);
//}
//void thr_A (void const *param){

//osSignalSet(TRA,0x01);
//}

//void thr_B (void const *param){

//osSignalSet(TRB,0x01);
//}

//void thr_C (void const *param){

//osSignalSet(TRC,0x01);
//}


//// timer thread declaraionts
//osTimerDef(tms, t_s);
//osTimerDef(tm0, thr_A);
//osTimerDef(tm1,thr_B);
//osTimerDef(tm2,thr_C);
//void thr_At( void const *param){
//int k =0;
//	int b=0;
//	int c=0;
//	int d=0;
//for(;;){
//LED_On(1);
//LED_On(5);
//osSignalWait(0x01,osWaitForever); // each for = .073 s
//for(k =0;k<0xFFFF;k++)for(b =0;b<58;b++);//for(b =0;b<0xFFFFFFF;b++);//for(c =0;c<0xFFFFFFF;c++);
//k=0;
//	b=0;
//c=0;
//k=0;

//LED_Off(1);
//}

//}

//void thr_Bt( void const *param){
//int k =0;
//	int b=0;
//	int c=0;
//	int d=0;
//for(;;){
//LED_On(2);
//osSignalWait(0x01,osWaitForever);
//for(k =0;k<0xFFFF;k++)for(b =0;b<28;b++);//for(b =0;b<0xFFFFFFF;b++);//for(c =0;c<0xFFFFFFF;c++);
//k=0;
//	b=0;
//c=0;
//k=0;
//LED_On(6);
////some random time length stuff


//LED_Off(2);
//}
//}
//void thr_Ct( void const *param){
//int k =0;
//	int b=0;
//	int c=0;
//	int d=0;
//	
//for(;;){
//LED_On(3);
//LED_On(7);
//osSignalWait(0x01,osWaitForever); // 3.943ms
//for(k =0;k<0xFFFF;k++)for(b =0;b<13;b++);//for(b =0;b<0xFFFFFFF;b++);//for(c =0;c<0xFFFFFFF;c++);
//k=0;
//	b=0;
//c=0;


//LED_Off(3);
//}
//}

////now the main

//int main(void){

//osTimerId tm_S = osTimerCreate(osTimer(tms),osTimerOnce,(void *)0); // note the last statement refers to passing

//osTimerId tm0 = osTimerCreate(osTimer(tm0),osTimerPeriodic,(void *)0); // note the last statement refers to passing
//// parameters. we must pass the address of a variable if we want to use it. ie &var
//osTimerId tm1 = osTimerCreate(osTimer(tm1),osTimerPeriodic,(void *) 0);
//osTimerId tm2 = osTimerCreate(osTimer(tm2),osTimerPeriodic,(void *) 0);

//// ciompleted timer declarations. now we must start the timers initi stuff

//LED_Init();
//osTimerStart(tm_S,1);
//osTimerStart(tm0,4000);
//osTimerStart(tm1,4000);
//osTimerStart(tm2,2000);

//TRA = osThreadCreate(osThread(thr_At),NULL);
//TRB = osThreadCreate(osThread(thr_Bt),NULL);
//TRC = osThreadCreate(osThread(thr_Ct),NULL);

//// if we dont run the threads then we can simply let the timers keep calling? YES
//osDelay(osWaitForever);
//for(;;);
//}
