module fb_controller (
	// Avalon Clock Input
	input logic CLK,
	
	// Avalon Reset Input
	input logic RESET,
	
	// NIOS Control Signals
	input 	logic 	[9:0] 	sramx,	// SRAM x location
	input		logic		[9:0]		sramy,	// SRAM y location
	input 	logic 	[9:0] 	startx,	// Draw x location
	input 	logic 	[9:0] 	starty,	// Draw y location
	input 	logic 	[9:0] 	sizex,	// Width of sprite
	input 	logic 	[9:0] 	sizey,	// Height of sprite
	output 	logic  				done,		// High when FB write is compete
	input		logic				  	start,	// High when NIOS wants to start a write
	
	// External connections
	output 	logic 	[4:0] 	color,
	input 	logic 	[9:0] 	drawX,
	input 	logic 	[9:0] 	drawY,
	input 	logic 				frame_sync,
	
	// SRAM connections
	output 	logic	[19:0]	addr,	// 20 bit address space
	input   logic	[15:0]	data	// 16 data bits per address
	
);

typedef enum logic[5:0] {START, DONE, READ_1, READ_2, READ_3} render_t;
render_t state;
render_t next_state;

logic [4:0] 	a_buff [61440:0]; // 256 by 240
logic [4:0] 	b_buff [61440:0]; // 256 by 240
logic [4:0] 	color_a, color_b, next_color;
logic [19:0] 	count, next_count, next_addr;
logic [9:0]		posx, posy, next_posx, next_posy;
logic sel;
logic next_done;

always_comb begin
	if(sel == 1'b1)
		color = color_a;
	else
		color = color_b;
end

always_ff @ (posedge CLK) begin
	if(sel == 1'b1) 													// Select output buffer based on what is being written to
		color_a <= a_buff[(drawX-192) + 256*(drawY-120)];	// Read A
	else
		color_b <= b_buff[(drawX-192) + 256*(drawY-120)];	// Read B
end

always_ff @ (negedge frame_sync) begin
	sel <= ~sel;
end

always_ff @ (posedge CLK) begin
	state <= next_state;
	posx <= next_posx;
	posy <= next_posy;
	done <= next_done;
	count <= next_count;
	addr <= next_addr;
	if(next_state == READ_2) begin
		if(data[4:0] != 3) begin // Check alpha (don't write if transparent)
			if(sel == 1'b0)
				a_buff[startx + posx + ((starty + posy) * 256)] <= data[4:0];	// Write A
			else
				b_buff[startx + posx + ((starty + posy) * 256)] <= data[4:0];	// Write B
		end
	end
end

always_comb begin
	next_state = START;
	next_posy = posy;
	next_posx = posx;
	next_done = done;
	next_count = count;
	next_addr = addr;
	case(state)
		START: 	begin
						if(start == 1)
							next_state = READ_1;
						next_posy = 0;
						next_posx = 0;
						next_done = 0;
						next_count = 0;
						next_addr = 0;
					end
		DONE: 	begin
						next_done = 1'b1;
						if(start == 0)
							next_state = START;
						else
							next_state = DONE;
					end	
		READ_1: 	begin
						next_addr = sramx + posx + ((sramy + posy)*1024);
						next_state = READ_2;
						next_posy = posy;
						if(posx > (sizex-2)) begin
							next_posx = 0;
							next_posy = posy + 1;
						end else
							next_posx = posx + 1;
					end
		READ_2:  begin
						//next_state = READ_3;
	/*				end
		READ_3: 	begin*/				
						if(count > ((sizex * sizey)-2)) // Check if write is done
								next_state = DONE;
						else
								next_state = READ_1;
						next_count = count + 1;		
					end
	endcase
end

endmodule
