module Simulate();

	reg			clk, clear;
	reg[2:0]	drink_choose; // 0=reset, 1=tea, 2=coke, 3= coffee, 4=milk
	reg[7:0] 	coin;
	wire [7:0]  total, exchange;
	
	parameter t=10;
	parameter th=5;

	DrinkSeller drinkseller(total, exchange, clk, clear, coin, drink_choose);

	always #th clk = ~clk;
	
	initial 
		begin
		clear = 0;
		clear = 1;
		
		clk = 0;
		drink_choose = 0 ;
		coin = 0;
		
		#t coin = 10;		// coin 10,	total 10 dollars	tea
		#t coin = 5;		// coin 5,	total 15 dollars	tea|coke
		#t coin = 1;		// coin 1,	total 16 dollars	tea|coke
		#t coin = 10;		// coin 10,	total 26 dollars	tea|coke|coffee|milk
		
		#t coin = 0;
		#t drink_choose = 3;// coffee out
		#t drink_choose = 0;
							// exchange 6 dollars
		#t $stop;
		end
endmodule