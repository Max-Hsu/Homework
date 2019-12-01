`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date:    09:58:33 11/18/2019 
// Design Name: 
// Module Name:    mod2 
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
module mod1(output Q , input D , input En);
	wire not_D;
	wire For_Q;
	wire For_notQ;
	wire not_Q;
	not(not_D,D);
	nand(For_Q,D,En);
	nand(Q,For_Q,not_Q);
	nand(For_notQ,not_D,En);
	nand(not_Q,For_notQ,Q);
endmodule

module mod2(output Q , input clk , input D);
	wire not_clk;
	wire Y;
	not(not_clk,clk);
	mod1 master(Y,D,not_clk);
	mod1 slave(Q,Y,clk);
endmodule
