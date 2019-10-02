#include <stdio.h>
#include "LPC17xx.h"
#include <RTL.h>

OS_TID id1, id2;
double  cnt1,cnt2, cnt3;

__task void job1 (void);
__task void job2 (void);
__task void job3 (void);

__task void job1 (void) {
	id1 = os_tsk_self(); //identify myself and create job 3
	id2 = os_tsk_create(job3, 0x0); //create and return
	
	for(;;){
		if(cnt1 < 200){
			cnt1++;
			os_tsk_pass(); //increment alongside job 3 by passing token (same priority)
		}else{
			os_evt_set(0x0004, id2); //finished counting. Signal to job3
		}
	}
}

__task void job2 (void) {
	for(;;){
		if(cnt2 < 700){ //increment to 700 and delete
			cnt2++;
			os_tsk_pass();
		}else{
				os_tsk_delete_self(); //should go to idle_deamon after this
		}
	}

}

__task void job3 (void) {
	id2 = os_tsk_self(); //obtain my identity
	for(;;){
		if(cnt3 < 100){
			cnt3++;
			os_tsk_pass(); //keep incrementing and passing token to job 1
		}else if(cnt3 >= 100){	
				os_tsk_prio_self(0x05); //once finished, increase my priority so that I may get job1's signal
				if(os_evt_wait_and(0x0004, 0xFFFF)){ 
					os_tsk_create(job2, 0x0); //and create job 2 while deleting job 1 and myself
					os_tsk_delete(id1);
					os_tsk_delete_self();
				}
			}
		}
}


int main (void) {
	os_tsk_create(job1, 0x0); //create job1 and initialize system
	SystemInit();

	os_tsk_delete_self();
}
