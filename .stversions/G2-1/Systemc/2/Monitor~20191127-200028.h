#include "systemc.h"
#include <iostream>

using namespace std;

SC_MODULE(Monitor)
{	
	sc_in_clk clock;
	sc_in<sc_bv<4> > A,B,S;
	sc_in<sc_bit> C_out;
	void monitor();
	
	SC_CTOR(Monitor)
	{	

		SC_METHOD(monitor);
		sensitive << clock.pos();
	}
};

