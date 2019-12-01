#include "full_adder.h"


void FULL::full()
{
	c = C0;
	for(int i = 0 ; i < 4;i++){
		a = A[i];
		b = B[i];
		s = S[i];
		xor1 = a ^ b;
		and1 = a & b;
		s = xor1 ^ c;
		and2 = xor1 & c;
		c = and1 | and2;
		S_temp[i] = s;
	}
	S = S_temp;
	C_out = c;
}
