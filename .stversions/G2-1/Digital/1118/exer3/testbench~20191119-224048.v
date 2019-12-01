`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:18:38 11/18/2019
// Design Name:   mod3
// Module Name:   C:/Users/user/Desktop/1118/exer3/testbench.v
// Project Name:  exer3
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mod3
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module testbench;

	// Inputs
	reg clk;
	reg D;
	reg reset;

	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	mod3 uut (
		.Q(Q), 
		.clk(clk), 
		.D(D), 
		.reset(reset)
	);

	initial #100 $finish;
	initial begin clk = 0; forever #5 clk = ~clk; end
	initial fork
		D = 1;
		reset = 1;
		#20 D = 0;
		#40 D = 1;
		#50 D = 0;
		#60 D = 1;
		#70 D = 0;
		#90 D = 1;
		#47 reset = 0;
		#72 reset = 1;
	join
endmodule

