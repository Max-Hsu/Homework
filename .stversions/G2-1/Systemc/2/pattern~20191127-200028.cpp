#include "pattern.h"

void pattern_gen::pattern(){
	A = rand()%16;
	B = rand()%16;
	if(rand()%2){
		for_c = '1';
	}
	else{
		for_c = '0';
	}
	C0 = for_c;
}


