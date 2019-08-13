module fb_controller (
	// Avalon Clock Input
	input logic CLK,
	
	// Avalon Reset Input
	input logic RESET,
	
	// NIOS Control Signals
	input 	logic 	[19:0] 	ptr,	// SRAM sprite location
	input 	logic 	[9:0] 	startx,	// Draw x location
	input 	logic 	[9:0] 	starty,	// Draw y location
	input 	logic 	[9:0] 	sizex,	// Width of sprite
	input 	logic 	[9:0] 	sizey,	// Height of sprite
	//input    logic    [1:0]    sel,	// Frame buffer selector
	output 	logic  				done,	// High when FB write is compete
	output	logic				  	start,	// High when NIOS wants to start a write
	output	logic 	[1:0] 	vsync,	// Low when starting a new frame
	
	// External connections
	output 	logic 	[4:0] 	color,
	input 	logic 	[9:0] 	drawX,
	input 	logic 	[9:0] 	drawY,
	
	// SRAM connections
	output 	logic	[19:0]	addr,	// 20 bit address space
	input   logic	[15:0]	data	// 16 data bits per address
	
);

typedef enum logic[5:0] {START, DONE, READ_1, READ_2} render_t;
render_t state;

logic [4:0] 	a_buff [307200:0];
logic [4:0] 	color_a;
logic [19:0] 	sram_ptr;
logic [4:0]		sram_color;
logic [9:0]		posx, posy;
logic sel;


always_comb begin
	if(sel == 1'b0)
		color = 1'b0;
	else
		color = color_a;
end

always_ff @ (posedge CLK) begin

	if(sel == 1'b1) 									// Select output buffer based on what is being written to
		color_a <= a_buff[drawX + 640*drawY];	// Read from A
end

always_ff @ (posedge CLK) begin
	case(state)
		START: 	begin
						sram_ptr <= ptr;
						if(done != 1'b1)
							state <= READ_1;
						sel <= 1'b0;
					end
		DONE: 	begin
						if(start == 1'b1)
							state <= START;
						done <= 1'b1;
						sel <= 1'b1;
					end	
		READ_1: 	begin
						state <= READ_2;
						sram_ptr = sram_ptr + 1'b1;
						addr = sram_ptr;
					end
		READ_2: 	begin
						if(sel == 1'b0)
							a_buff[(startx + starty*640) + sram_ptr - ptr] <= data;
						if(sram_ptr >= (ptr + ((sizex * sizey) >> 1)))
							state <= DONE;
						else
							state <= READ_1;
					end
		default: begin
						state <= START;
						done <= 0;
					end
	endcase
end

endmodule
