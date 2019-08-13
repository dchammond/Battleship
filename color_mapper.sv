module  color_mapper ( 
	input  logic [4:0] color,						// 5 bit color
 	input        [9:0] DrawX, DrawY,       	// Current pixel coordinates
	output logic [7:0] VGA_R, VGA_G, VGA_B 	// VGA RGB output
);

logic [7:0] Red, Green, Blue;
    
    // Output colors to VGA
    assign VGA_R = Red;
    assign VGA_G = Green;
    assign VGA_B = Blue;
    
    // Assign color based on is_ball signal
    always_comb
    begin
			if(DrawX <= 192 || DrawX > 446 || DrawY < 120 || DrawY >= 359) begin
		      Red = 0;
				Blue = 0;
				Green = 0;
			end else begin
				if(color == 0) begin
					 Red = 21;
					 Green = 95;
					 Blue = 217;
				end else if(color == 1) begin
					 Red = 0;
					 Green = 0;
					 Blue = 0;
				end else if(color == 2) begin
					 Red = 173;
					 Green = 173;
					 Blue = 172;
				end else if(color == 3) begin
					 Red = 254;
					 Green = 0;
					 Blue = 255;
				end else if(color == 4) begin
					 Red = 102;
					 Green = 102;
					 Blue = 102;
				end else if(color == 5) begin
					 Red = 99;
					 Green = 176;
					 Blue = 254;
				end else if(color == 6) begin
					 Red = 0;
					 Green = 124;
					 Blue = 141;
				end else if(color == 7) begin
					 Red = 91;
					 Green = 228;
					 Blue = 48;
				end else if(color == 8) begin
					 Red = 12;
					 Green = 147;
					 Blue = 0;
				end else if(color == 9) begin
					 Red = 253;
					 Green = 129;
					 Blue = 112;
				end else if(color == 10) begin
					 Red = 181;
					 Green = 49;
					 Blue = 32;
				end else if(color == 11) begin
					 Red = 255;
					 Green = 254;
					 Blue = 255;
				end else if(color == 12) begin
					 Red = 66;
					 Green = 64;
					 Blue = 254;
				end else if(color == 13) begin
					 Red = 0;
					 Green = 42;
					 Blue = 136;
				end else if(color == 14) begin
					 Red = 190;
					 Green = 224;
					 Blue = 253;
				end else if(color == 15) begin
					 Red = 251;
					 Green = 206;
					 Blue = 191;
				end else if(color == 16) begin
					 Red = 188;
					 Green = 190;
					 Blue = 0;
				end else if(color == 17) begin
					 Red = 58;
					 Green = 0;
					 Blue = 163;
				end else if(color == 18) begin
					 Red = 117;
					 Green = 39;
					 Blue = 254;
				end else if(color == 19) begin
					 Red = 146;
					 Green = 144;
					 Blue = 255;
				end else if(color == 20) begin
					 Red = 79;
					 Green = 139;
					 Blue = 200;
				end else if(color == 21) begin
					 Red = 0;
					 Green = 82;
					 Blue = 0;
				end else if(color == 22) begin
					 Red = 17;
					 Green = 75;
					 Blue = 170;
				end else if(color == 23) begin
					 Red = 20;
					 Green = 18;
					 Blue = 166;
				end else if(color == 24) begin
					 Red = 51;
					 Green = 50;
					 Blue = 200;
				end else if(color == 25) begin
					 Red = 198;
					 Green = 118;
					 Blue = 254;
				end else if(color == 26) begin
					 Red = 234;
					 Green = 158;
					 Blue = 33;
				end else if(color == 27) begin
					 Red = 152;
					 Green = 78;
					 Blue = 0;
				end else begin
					 Red = 64;
					 Green = 64;
					 Blue = 64;
				end
			end
    end
    
endmodule
