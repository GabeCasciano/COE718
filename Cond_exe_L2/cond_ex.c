//conditional execution code example
#include <LPC17xx.h>

//barrel shifter code
#include "LPC17xx.h"

int main(void){
	int r1 = 1;

	while(r1 < 20){
		r1 += (r1 * 2);
	}
	return 0;
}
