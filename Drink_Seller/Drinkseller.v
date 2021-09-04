module DrinkSeller(total, exchange, clk, clear, coin, drink_choose);
    input   clk, clear, coin, drink_choose;
	output  total, exchange;
	
	reg  [7:0]  total, exchange;
	
	wire  [7:0]  coin;
	wire [2:0]  drink_choose;
	
	reg  keeptoss;
	reg  [7:0]  totaltemp;
	
	parameter S0 = 3'd0,
			  S1 = 3'd1,
			  S2 = 3'd2,
			  S3 = 3'd3;
	reg [2:0] state, next_state;
	
	initial 
		begin
			total = 0;
			exchange = 0;
			$display("Hello world");
		end
	always@(clk)
		if(clear)
			state = S0;
		else
			state = next_state;
	
	always@(posedge clk)
	  begin
		case(state)
			S0: begin
				total = total + coin;
				end
			S1: begin
				if ( total < 10)
					$display("coin %d,	total %d dollars	Nope\n", coin, total);
				else if( total >= 10 )
					$display("coin %d,	total %d dollars	tea\n", coin, total);
				else if ( total >= 15)
					$display("coin %d,	total %d dollars	tea|coke\n", coin, total);
				else if ( total >= 20)
					$display("coin %d,	total %d dollars	tea|coke|coffee\n", coin, total);
				else
					$display("coin %d,	total %d dollars	tea|coke|coffee|milk\n", coin, total);
				end
			S2: begin
				if ( drink_choose == 1 )
				  begin
					total = total - 10;
					$display("tea out\n");
				  end
				else if ( drink_choose == 2)
				  begin
					total = total - 15;
					$display("coke out\n");
				  end
				else if ( drink_choose == 3)
				  begin 
					total = total - 20;
					$display("coffee out\n");
				  end	
				else if ( drink_choose == 4)
				  begin
					total = total - 25;
					$display("milk out\n");
				  end
				else 
					;
				end
			S3: begin
				exchange = total;
				$display("exchange %d dollars\n", exchange);
				end
		endcase
	  end
	
	always@( posedge reset or posedge clk)
	  begin
	    case(state)
		
		  S0:begin
				if ( reset )
					next_state = S3;
				if ( total < 10)
					next_state = S1;
				else if ( total < 10)
					next_state = S0;
				else 
					next_state = S3;
			 end
			 
		  S1:begin
				if ( keeptoss == 1'b1 )
					next_state = S0;
				else 
					begin
					next_state = S2;
					keeptoss =1'b0 ;
					end
			 end
		  S2:   next_state = S3;
		  
		  S3:	next_state = S0; 
		  
		  default: keeptoss = 1'b0;
	    endcase
	  end

endmodule