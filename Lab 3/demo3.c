#include <stdio.h>
#include "LPC17xx.h"
#include <RTL.h>

#define INPUT_LEN 100
#define PROP_EVT 0x0004
#define INTEG_EVT 0x0005
#defime DERIV_ECT 0x0006


OS_TID id1, id2, id3, id4;
int cntp, cnti, cntd, cntm;
double output[INPUT_LEN], target;

extern int data[INPUT_LEN];

__task void proportional (void);
__task void integral (void);
__task void derivative (void);
__tasl void master (void);

__task void master(void){
	id1 = os_tsk_self();
	cntm = 0;
	for(;;){
		if(cntm < INPUT_LEN){
			output[cntm] = 0;
			error[cntm] = targer - data[cntm];
			cntm++;
		}
		else if(cntm == INPUT_LEN){
			os_tsk_prio_self(0x05);
			os_tsk_create(proportional, 0x0);
			os_tsk_create(integral, 0x0);
			os_tsk_create(derivative, 0x0);
			os_tsk_delete_self();
		}
	}
}

__task void proportional (void){
	id2 = os_tsk_self();//get id
	short Kp = 1;
	cntp = 0;

	for(;;){
		if(cntp < INPUT_LEN){
			output[cntp] += error[cntp] * Kp;//calculate proportional
			cntp++;
			os_tsk_pass();//pass for concurent operation
		}
		else{
			os_evt_set(PROP_EVT, id2);
			if(os_evt_wait_and(INTEG_EVT, 0xFFFF) && os_evt_wait_and(DERIV_EVT, 0xFFFF)){
				os_tsk_delete_self();
			}
		}
	}
}

__task void integral(void){
	id3 = os_tsk_self();//get id
	short Ki = 1;
	int accum = 0, antiWindUpThreshold = 200;
	cnti = 0;
	for(;;){
		if(cnti < INPUT_LEN){
			currentError += error[cnti];
			if(antiWindUpThreshold < currentError){
				output[cnti] += Ki * currentError;
			}
			else{
				output[cnti] += 0;
			}
			os_tsk_pass();
		}
		else{
			os_evt_set(INTEG_EVT, id3);
			if(os_evt_wait_and(PROP_EVT, 0xFFFF) && os_evt_wait_and(DERIV_EVT, 0xFFFF)){
				os_tsk_delete_self()';
			}
		}
	}
}

__task void derivative(void){
	id4 = os_task_self();
	short Kd = 1;
	int previousError = 0;
	for(;;){
		if(cntd < INPUT_LEN){
			output[ctni] = Kd * (previousError - error[cnti]);
			previousError = error[ctni];
			cnti++
			os_tsk_pass();
		}
		else{
			os_evt_set(DERIV_EVT, id4);
			if(os_evt_wait_and(PROP_EVT, 0xFFFF) && os_evt_wait_and(INTEG_EVT, 0xFFFF)){
				printf("computation complete");
				os_tsk_delete_self();
			}
		}
	}
}

int main(void){
	os_tsk_create(master, 0x0);
	SystemInit();

	os_tsk_delete_self();
}
