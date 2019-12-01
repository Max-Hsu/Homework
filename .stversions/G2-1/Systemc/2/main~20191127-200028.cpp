#include "full_adder.h"
#include "pattern.h"
#include "Monitor.h"
#include "clockreset.h"
#include <iostream>

using namespace std;

int sc_main(int argc,char* argv[])
{
	sc_signal<bool> clk;
	sc_signal<sc_bv<4> > A,B,S;
	sc_signal<sc_bit> C0,C_out;
	pattern_gen pattern("Generation");
	FULL full("full");
	Monitor monitor("mon");
	Clock clock("clock",10);
	
	clock(clk);
	pattern(clk,A,B,C0);
	full(A,B,C0,S,C_out);
	monitor(clk,A,B,S,C_out);
	
	
	sc_start(500,SC_NS);
	return 0;

}


