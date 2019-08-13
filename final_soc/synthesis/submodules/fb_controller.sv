module fb_controller (
	// Avalon Clock Input
	input logic CLK,
	
	// Avalon Reset Input
	input logic RESET,
	
	// Avalon-MM Slave Signals
	input  logic AVL_READ,					// Avalon-MM Read
	input  logic AVL_WRITE,					// Avalon-MM Write
	input  logic AVL_CS,						// Avalon-MM Chip Select
	input  logic [1:0] AVL_BYTE_EN,		// Avalon-MM Byte Enable
	input  logic [20:0] AVL_ADDR,			// Avalon-MM Address
	input  logic [7:0] AVL_WRITEDATA,	// Avalon-MM Write Data
	output logic [7:0] AVL_READDATA,		// Avalon-MM Read Data
	
	// External connections
	output logic [4:0] fb_color,
	input logic [9:0] fb_drawX,
	input logic [9:0] fb_drawY
);


logic [4:0] a_buff [307200:0];	// B frame buffer
logic [1:0] fb_sel;					// Frame buffer selector
logic [4:0] fb_color_a;
logic [4:0] fb_color_b;

always_comb begin
	//if(fb_sel == 1'b1)
	//	fb_color = fb_color_a;
	//else
	//	fb_color = fb_color_b;
	AVL_READDATA = fb_sel;
end

always_ff @ (posedge CLK) begin
	if(AVL_ADDR == 20'b0 && AVL_WRITE)
		fb_sel = AVL_WRITEDATA[0];
	if(fb_sel == 1'b0) begin								// Select output buffer based on what is being written to
		if(AVL_WRITE)
			a_buff[AVL_ADDR] <= AVL_WRITEDATA[4:0];	// Buffer A write	
	end else if(fb_sel == 1'b1)
		fb_color <= a_buff[fb_drawX + 640*fb_drawY]; 					// Read from A
end

endmodule
