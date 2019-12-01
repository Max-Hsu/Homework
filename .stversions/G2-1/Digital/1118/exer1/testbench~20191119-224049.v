`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   09:38:34 11/18/2019
// Design Name:   mod1
// Module Name:   C:/Users/user/Desktop/1118/exer1/testbench.v
// Project Name:  exer1
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mod1
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
	reg D;
	reg En;

	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	mod1 uut (
		.Q(Q), 
		.D(D), 
		.En(En)
	);

	initial begin
		// Initialize Inputs
		D = 0;
		En = 0;
		#20;
		
		D = 1;
		En = 0;
		#20;

		D = 0;
		En = 1;
		#20;

		D = 1;
		En = 1;
		#20;

		D = 0;
		En = 0;
		#20;
		
		D = 1;
		En = 0;
		#20;
	end
      
endmodule

