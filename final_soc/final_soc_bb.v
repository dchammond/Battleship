
module final_soc (
	clk_clk,
	done_export,
	key_export,
	led_wire_export,
	reset_reset_n,
	sdram_clk_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	sizex_export,
	sizey_export,
	sramx_export,
	sramy_export,
	start_export,
	startx_export,
	starty_export,
	sw_export,
	vsync_export,
	otg_hpi_address_export,
	otg_hpi_data_in_port,
	otg_hpi_data_out_port,
	otg_hpi_r_export,
	otg_hpi_w_export,
	otg_hpi_cs_export,
	otg_hpi_reset_export);	

	input		clk_clk;
	input		done_export;
	input	[2:0]	key_export;
	output	[7:0]	led_wire_export;
	input		reset_reset_n;
	output		sdram_clk_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[31:0]	sdram_wire_dq;
	output	[3:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	output	[9:0]	sizex_export;
	output	[9:0]	sizey_export;
	output	[9:0]	sramx_export;
	output	[9:0]	sramy_export;
	output		start_export;
	output	[9:0]	startx_export;
	output	[9:0]	starty_export;
	input	[7:0]	sw_export;
	input		vsync_export;
	output	[1:0]	otg_hpi_address_export;
	input	[15:0]	otg_hpi_data_in_port;
	output	[15:0]	otg_hpi_data_out_port;
	output		otg_hpi_r_export;
	output		otg_hpi_w_export;
	output		otg_hpi_cs_export;
	output		otg_hpi_reset_export;
endmodule
