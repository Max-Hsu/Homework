`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    10:08:57 11/18/2019 
// Design Name: 
// Module Name:    mod3 
// Project Name: 
// Target Devices: 
// Tool versions: 
// Description: 
//
// Dependencies: 
//
// Revision: 
// Revision 0.01 - File Created
// Additional Comments: 
//
//////////////////////////////////////////////////////////////////////////////////
module mod3(output Q , input clk , input D , input reset);
	wire out_A;
	wire out_B;
	wire out_C;
	wire out_D;
	wire not_Q;
	
	nand(out_A,out_D,out_B);
	nand(out_B,out_A,clk,reset);
	nand(out_C,out_B,clk,out_D);
	nand(out_D,out_C,D,reset);
	
	nand(Q,out_B,not_Q);
	nand(not_Q,out_B,Q,reset);

endmodule
