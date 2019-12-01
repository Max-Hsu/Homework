`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   10:01:21 11/18/2019
// Design Name:   mod2
// Module Name:   C:/Users/user/Desktop/1118/exer2/testbench.v
// Project Name:  exer2
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: mod2
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

	// Outputs
	wire Q;

	// Instantiate the Unit Under Test (UUT)
	mod2 uut (
		.Q(Q), 
		.clk(clk), 
		.D(D)
	);
	initial #100 $finish;
	initial begin
		clk = 0;
		forever #5 clk = ~clk;
	end
	initial fork
		// Initialize Inputs
				
		#0 D = 0; 
		#20 D = 1; 
		#40 D = 0; 
		#60 D = 1; 
		#80 D = 0; 

     join
		// Add stimulus here
      
endmodule

