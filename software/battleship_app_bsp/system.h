/*
 * system.h - SOPC Builder system and BSP software package information
 *
 * Machine generated for CPU 'nios2_gen2_0' in SOPC Builder design 'final_soc'
 * SOPC Builder design path: ../../final_soc.sopcinfo
 *
 * Generated: Sat Apr 27 20:24:47 CDT 2019
 */

/*
 * DO NOT MODIFY THIS FILE
 *
 * Changing this file will have subtle consequences
 * which will almost certainly lead to a nonfunctioning
 * system. If you do modify this file, be aware that your
 * changes will be overwritten and lost when this file
 * is generated again.
 *
 * DO NOT MODIFY THIS FILE
 */

/*
 * License Agreement
 *
 * Copyright (c) 2008
 * Altera Corporation, San Jose, California, USA.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * This agreement shall be governed in all respects by the laws of the State
 * of California and by the laws of the United States of America.
 */

#ifndef __SYSTEM_H_
#define __SYSTEM_H_

/* Include definitions from linker script generator */
#include "linker.h"


/*
 * CPU configuration
 *
 */

#define ALT_CPU_ARCHITECTURE "altera_nios2_gen2"
#define ALT_CPU_BIG_ENDIAN 0
#define ALT_CPU_BREAK_ADDR 0x00001020
#define ALT_CPU_CPU_ARCH_NIOS2_R1
#define ALT_CPU_CPU_FREQ 50000000u
#define ALT_CPU_CPU_ID_SIZE 1
#define ALT_CPU_CPU_ID_VALUE 0x00000000
#define ALT_CPU_CPU_IMPLEMENTATION "tiny"
#define ALT_CPU_DATA_ADDR_WIDTH 0x1d
#define ALT_CPU_DCACHE_LINE_SIZE 0
#define ALT_CPU_DCACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_DCACHE_SIZE 0
#define ALT_CPU_EXCEPTION_ADDR 0x10000020
#define ALT_CPU_FLASH_ACCELERATOR_LINES 0
#define ALT_CPU_FLASH_ACCELERATOR_LINE_SIZE 0
#define ALT_CPU_FLUSHDA_SUPPORTED
#define ALT_CPU_FREQ 50000000
#define ALT_CPU_HARDWARE_DIVIDE_PRESENT 0
#define ALT_CPU_HARDWARE_MULTIPLY_PRESENT 0
#define ALT_CPU_HARDWARE_MULX_PRESENT 0
#define ALT_CPU_HAS_DEBUG_CORE 1
#define ALT_CPU_HAS_DEBUG_STUB
#define ALT_CPU_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define ALT_CPU_HAS_JMPI_INSTRUCTION
#define ALT_CPU_ICACHE_LINE_SIZE 0
#define ALT_CPU_ICACHE_LINE_SIZE_LOG2 0
#define ALT_CPU_ICACHE_SIZE 0
#define ALT_CPU_INST_ADDR_WIDTH 0x1d
#define ALT_CPU_NAME "nios2_gen2_0"
#define ALT_CPU_OCI_VERSION 1
#define ALT_CPU_RESET_ADDR 0x10000000


/*
 * CPU configuration (with legacy prefix - don't use these anymore)
 *
 */

#define NIOS2_BIG_ENDIAN 0
#define NIOS2_BREAK_ADDR 0x00001020
#define NIOS2_CPU_ARCH_NIOS2_R1
#define NIOS2_CPU_FREQ 50000000u
#define NIOS2_CPU_ID_SIZE 1
#define NIOS2_CPU_ID_VALUE 0x00000000
#define NIOS2_CPU_IMPLEMENTATION "tiny"
#define NIOS2_DATA_ADDR_WIDTH 0x1d
#define NIOS2_DCACHE_LINE_SIZE 0
#define NIOS2_DCACHE_LINE_SIZE_LOG2 0
#define NIOS2_DCACHE_SIZE 0
#define NIOS2_EXCEPTION_ADDR 0x10000020
#define NIOS2_FLASH_ACCELERATOR_LINES 0
#define NIOS2_FLASH_ACCELERATOR_LINE_SIZE 0
#define NIOS2_FLUSHDA_SUPPORTED
#define NIOS2_HARDWARE_DIVIDE_PRESENT 0
#define NIOS2_HARDWARE_MULTIPLY_PRESENT 0
#define NIOS2_HARDWARE_MULX_PRESENT 0
#define NIOS2_HAS_DEBUG_CORE 1
#define NIOS2_HAS_DEBUG_STUB
#define NIOS2_HAS_ILLEGAL_INSTRUCTION_EXCEPTION
#define NIOS2_HAS_JMPI_INSTRUCTION
#define NIOS2_ICACHE_LINE_SIZE 0
#define NIOS2_ICACHE_LINE_SIZE_LOG2 0
#define NIOS2_ICACHE_SIZE 0
#define NIOS2_INST_ADDR_WIDTH 0x1d
#define NIOS2_OCI_VERSION 1
#define NIOS2_RESET_ADDR 0x10000000


/*
 * DONE configuration
 *
 */

#define ALT_MODULE_CLASS_DONE altera_avalon_pio
#define DONE_BASE 0x200
#define DONE_BIT_CLEARING_EDGE_REGISTER 0
#define DONE_BIT_MODIFYING_OUTPUT_REGISTER 0
#define DONE_CAPTURE 0
#define DONE_DATA_WIDTH 1
#define DONE_DO_TEST_BENCH_WIRING 0
#define DONE_DRIVEN_SIM_VALUE 0
#define DONE_EDGE_TYPE "NONE"
#define DONE_FREQ 50000000
#define DONE_HAS_IN 1
#define DONE_HAS_OUT 0
#define DONE_HAS_TRI 0
#define DONE_IRQ -1
#define DONE_IRQ_INTERRUPT_CONTROLLER_ID -1
#define DONE_IRQ_TYPE "NONE"
#define DONE_NAME "/dev/DONE"
#define DONE_RESET_VALUE 0
#define DONE_SPAN 16
#define DONE_TYPE "altera_avalon_pio"


/*
 * Define for each module class mastered by the CPU
 *
 */

#define __ALTERA_AVALON_JTAG_UART
#define __ALTERA_AVALON_NEW_SDRAM_CONTROLLER
#define __ALTERA_AVALON_ONCHIP_MEMORY2
#define __ALTERA_AVALON_PIO
#define __ALTERA_AVALON_SYSID_QSYS
#define __ALTERA_AVALON_TIMER
#define __ALTERA_NIOS2_GEN2
#define __ALTPLL


/*
 * SIZEX configuration
 *
 */

#define ALT_MODULE_CLASS_SIZEX altera_avalon_pio
#define SIZEX_BASE 0x230
#define SIZEX_BIT_CLEARING_EDGE_REGISTER 0
#define SIZEX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SIZEX_CAPTURE 0
#define SIZEX_DATA_WIDTH 10
#define SIZEX_DO_TEST_BENCH_WIRING 0
#define SIZEX_DRIVEN_SIM_VALUE 0
#define SIZEX_EDGE_TYPE "NONE"
#define SIZEX_FREQ 50000000
#define SIZEX_HAS_IN 0
#define SIZEX_HAS_OUT 1
#define SIZEX_HAS_TRI 0
#define SIZEX_IRQ -1
#define SIZEX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SIZEX_IRQ_TYPE "NONE"
#define SIZEX_NAME "/dev/SIZEX"
#define SIZEX_RESET_VALUE 0
#define SIZEX_SPAN 16
#define SIZEX_TYPE "altera_avalon_pio"


/*
 * SIZEY configuration
 *
 */

#define ALT_MODULE_CLASS_SIZEY altera_avalon_pio
#define SIZEY_BASE 0x220
#define SIZEY_BIT_CLEARING_EDGE_REGISTER 0
#define SIZEY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SIZEY_CAPTURE 0
#define SIZEY_DATA_WIDTH 10
#define SIZEY_DO_TEST_BENCH_WIRING 0
#define SIZEY_DRIVEN_SIM_VALUE 0
#define SIZEY_EDGE_TYPE "NONE"
#define SIZEY_FREQ 50000000
#define SIZEY_HAS_IN 0
#define SIZEY_HAS_OUT 1
#define SIZEY_HAS_TRI 0
#define SIZEY_IRQ -1
#define SIZEY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SIZEY_IRQ_TYPE "NONE"
#define SIZEY_NAME "/dev/SIZEY"
#define SIZEY_RESET_VALUE 0
#define SIZEY_SPAN 16
#define SIZEY_TYPE "altera_avalon_pio"


/*
 * SRAMX configuration
 *
 */

#define ALT_MODULE_CLASS_SRAMX altera_avalon_pio
#define SRAMX_BASE 0x260
#define SRAMX_BIT_CLEARING_EDGE_REGISTER 0
#define SRAMX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SRAMX_CAPTURE 0
#define SRAMX_DATA_WIDTH 10
#define SRAMX_DO_TEST_BENCH_WIRING 0
#define SRAMX_DRIVEN_SIM_VALUE 0
#define SRAMX_EDGE_TYPE "NONE"
#define SRAMX_FREQ 50000000
#define SRAMX_HAS_IN 0
#define SRAMX_HAS_OUT 1
#define SRAMX_HAS_TRI 0
#define SRAMX_IRQ -1
#define SRAMX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAMX_IRQ_TYPE "NONE"
#define SRAMX_NAME "/dev/SRAMX"
#define SRAMX_RESET_VALUE 0
#define SRAMX_SPAN 16
#define SRAMX_TYPE "altera_avalon_pio"


/*
 * SRAMY configuration
 *
 */

#define ALT_MODULE_CLASS_SRAMY altera_avalon_pio
#define SRAMY_BASE 0x1e0
#define SRAMY_BIT_CLEARING_EDGE_REGISTER 0
#define SRAMY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SRAMY_CAPTURE 0
#define SRAMY_DATA_WIDTH 10
#define SRAMY_DO_TEST_BENCH_WIRING 0
#define SRAMY_DRIVEN_SIM_VALUE 0
#define SRAMY_EDGE_TYPE "NONE"
#define SRAMY_FREQ 50000000
#define SRAMY_HAS_IN 0
#define SRAMY_HAS_OUT 1
#define SRAMY_HAS_TRI 0
#define SRAMY_IRQ -1
#define SRAMY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SRAMY_IRQ_TYPE "NONE"
#define SRAMY_NAME "/dev/SRAMY"
#define SRAMY_RESET_VALUE 0
#define SRAMY_SPAN 16
#define SRAMY_TYPE "altera_avalon_pio"


/*
 * START configuration
 *
 */

#define ALT_MODULE_CLASS_START altera_avalon_pio
#define START_BASE 0x210
#define START_BIT_CLEARING_EDGE_REGISTER 0
#define START_BIT_MODIFYING_OUTPUT_REGISTER 0
#define START_CAPTURE 0
#define START_DATA_WIDTH 1
#define START_DO_TEST_BENCH_WIRING 0
#define START_DRIVEN_SIM_VALUE 0
#define START_EDGE_TYPE "NONE"
#define START_FREQ 50000000
#define START_HAS_IN 0
#define START_HAS_OUT 1
#define START_HAS_TRI 0
#define START_IRQ -1
#define START_IRQ_INTERRUPT_CONTROLLER_ID -1
#define START_IRQ_TYPE "NONE"
#define START_NAME "/dev/START"
#define START_RESET_VALUE 0
#define START_SPAN 16
#define START_TYPE "altera_avalon_pio"


/*
 * STARTX configuration
 *
 */

#define ALT_MODULE_CLASS_STARTX altera_avalon_pio
#define STARTX_BASE 0x250
#define STARTX_BIT_CLEARING_EDGE_REGISTER 0
#define STARTX_BIT_MODIFYING_OUTPUT_REGISTER 0
#define STARTX_CAPTURE 0
#define STARTX_DATA_WIDTH 10
#define STARTX_DO_TEST_BENCH_WIRING 0
#define STARTX_DRIVEN_SIM_VALUE 0
#define STARTX_EDGE_TYPE "NONE"
#define STARTX_FREQ 50000000
#define STARTX_HAS_IN 0
#define STARTX_HAS_OUT 1
#define STARTX_HAS_TRI 0
#define STARTX_IRQ -1
#define STARTX_IRQ_INTERRUPT_CONTROLLER_ID -1
#define STARTX_IRQ_TYPE "NONE"
#define STARTX_NAME "/dev/STARTX"
#define STARTX_RESET_VALUE 0
#define STARTX_SPAN 16
#define STARTX_TYPE "altera_avalon_pio"


/*
 * STARTY configuration
 *
 */

#define ALT_MODULE_CLASS_STARTY altera_avalon_pio
#define STARTY_BASE 0x240
#define STARTY_BIT_CLEARING_EDGE_REGISTER 0
#define STARTY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define STARTY_CAPTURE 0
#define STARTY_DATA_WIDTH 10
#define STARTY_DO_TEST_BENCH_WIRING 0
#define STARTY_DRIVEN_SIM_VALUE 0
#define STARTY_EDGE_TYPE "NONE"
#define STARTY_FREQ 50000000
#define STARTY_HAS_IN 0
#define STARTY_HAS_OUT 1
#define STARTY_HAS_TRI 0
#define STARTY_IRQ -1
#define STARTY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define STARTY_IRQ_TYPE "NONE"
#define STARTY_NAME "/dev/STARTY"
#define STARTY_RESET_VALUE 0
#define STARTY_SPAN 16
#define STARTY_TYPE "altera_avalon_pio"


/*
 * System configuration
 *
 */

#define ALT_DEVICE_FAMILY "Cyclone IV E"
#define ALT_ENHANCED_INTERRUPT_API_PRESENT
#define ALT_IRQ_BASE NULL
#define ALT_LOG_PORT "/dev/null"
#define ALT_LOG_PORT_BASE 0x0
#define ALT_LOG_PORT_DEV null
#define ALT_LOG_PORT_TYPE ""
#define ALT_NUM_EXTERNAL_INTERRUPT_CONTROLLERS 0
#define ALT_NUM_INTERNAL_INTERRUPT_CONTROLLERS 1
#define ALT_NUM_INTERRUPT_CONTROLLERS 1
#define ALT_STDERR "/dev/jtag_uart_0"
#define ALT_STDERR_BASE 0x2c8
#define ALT_STDERR_DEV jtag_uart_0
#define ALT_STDERR_IS_JTAG_UART
#define ALT_STDERR_PRESENT
#define ALT_STDERR_TYPE "altera_avalon_jtag_uart"
#define ALT_STDIN "/dev/jtag_uart_0"
#define ALT_STDIN_BASE 0x2c8
#define ALT_STDIN_DEV jtag_uart_0
#define ALT_STDIN_IS_JTAG_UART
#define ALT_STDIN_PRESENT
#define ALT_STDIN_TYPE "altera_avalon_jtag_uart"
#define ALT_STDOUT "/dev/jtag_uart_0"
#define ALT_STDOUT_BASE 0x2c8
#define ALT_STDOUT_DEV jtag_uart_0
#define ALT_STDOUT_IS_JTAG_UART
#define ALT_STDOUT_PRESENT
#define ALT_STDOUT_TYPE "altera_avalon_jtag_uart"
#define ALT_SYSTEM_NAME "final_soc"


/*
 * VSYNC configuration
 *
 */

#define ALT_MODULE_CLASS_VSYNC altera_avalon_pio
#define VSYNC_BASE 0x1f0
#define VSYNC_BIT_CLEARING_EDGE_REGISTER 0
#define VSYNC_BIT_MODIFYING_OUTPUT_REGISTER 0
#define VSYNC_CAPTURE 0
#define VSYNC_DATA_WIDTH 1
#define VSYNC_DO_TEST_BENCH_WIRING 0
#define VSYNC_DRIVEN_SIM_VALUE 0
#define VSYNC_EDGE_TYPE "NONE"
#define VSYNC_FREQ 50000000
#define VSYNC_HAS_IN 1
#define VSYNC_HAS_OUT 0
#define VSYNC_HAS_TRI 0
#define VSYNC_IRQ -1
#define VSYNC_IRQ_INTERRUPT_CONTROLLER_ID -1
#define VSYNC_IRQ_TYPE "NONE"
#define VSYNC_NAME "/dev/VSYNC"
#define VSYNC_RESET_VALUE 0
#define VSYNC_SPAN 16
#define VSYNC_TYPE "altera_avalon_pio"


/*
 * hal configuration
 *
 */

#define ALT_INCLUDE_INSTRUCTION_RELATED_EXCEPTION_API
#define ALT_MAX_FD 32
#define ALT_SYS_CLK TIMER_0
#define ALT_TIMESTAMP_CLK none


/*
 * jtag_uart_0 configuration
 *
 */

#define ALT_MODULE_CLASS_jtag_uart_0 altera_avalon_jtag_uart
#define JTAG_UART_0_BASE 0x2c8
#define JTAG_UART_0_IRQ 5
#define JTAG_UART_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define JTAG_UART_0_NAME "/dev/jtag_uart_0"
#define JTAG_UART_0_READ_DEPTH 64
#define JTAG_UART_0_READ_THRESHOLD 8
#define JTAG_UART_0_SPAN 8
#define JTAG_UART_0_TYPE "altera_avalon_jtag_uart"
#define JTAG_UART_0_WRITE_DEPTH 64
#define JTAG_UART_0_WRITE_THRESHOLD 8


/*
 * key configuration
 *
 */

#define ALT_MODULE_CLASS_key altera_avalon_pio
#define KEY_BASE 0x270
#define KEY_BIT_CLEARING_EDGE_REGISTER 0
#define KEY_BIT_MODIFYING_OUTPUT_REGISTER 0
#define KEY_CAPTURE 0
#define KEY_DATA_WIDTH 3
#define KEY_DO_TEST_BENCH_WIRING 0
#define KEY_DRIVEN_SIM_VALUE 0
#define KEY_EDGE_TYPE "NONE"
#define KEY_FREQ 50000000
#define KEY_HAS_IN 1
#define KEY_HAS_OUT 0
#define KEY_HAS_TRI 0
#define KEY_IRQ -1
#define KEY_IRQ_INTERRUPT_CONTROLLER_ID -1
#define KEY_IRQ_TYPE "NONE"
#define KEY_NAME "/dev/key"
#define KEY_RESET_VALUE 0
#define KEY_SPAN 16
#define KEY_TYPE "altera_avalon_pio"


/*
 * led configuration
 *
 */

#define ALT_MODULE_CLASS_led altera_avalon_pio
#define LED_BASE 0x290
#define LED_BIT_CLEARING_EDGE_REGISTER 0
#define LED_BIT_MODIFYING_OUTPUT_REGISTER 0
#define LED_CAPTURE 0
#define LED_DATA_WIDTH 8
#define LED_DO_TEST_BENCH_WIRING 0
#define LED_DRIVEN_SIM_VALUE 0
#define LED_EDGE_TYPE "NONE"
#define LED_FREQ 50000000
#define LED_HAS_IN 0
#define LED_HAS_OUT 1
#define LED_HAS_TRI 0
#define LED_IRQ -1
#define LED_IRQ_INTERRUPT_CONTROLLER_ID -1
#define LED_IRQ_TYPE "NONE"
#define LED_NAME "/dev/led"
#define LED_RESET_VALUE 0
#define LED_SPAN 16
#define LED_TYPE "altera_avalon_pio"


/*
 * onchip_memory2_0 configuration
 *
 */

#define ALT_MODULE_CLASS_onchip_memory2_0 altera_avalon_onchip_memory2
#define ONCHIP_MEMORY2_0_ALLOW_IN_SYSTEM_MEMORY_CONTENT_EDITOR 0
#define ONCHIP_MEMORY2_0_ALLOW_MRAM_SIM_CONTENTS_ONLY_FILE 0
#define ONCHIP_MEMORY2_0_BASE 0x0
#define ONCHIP_MEMORY2_0_CONTENTS_INFO ""
#define ONCHIP_MEMORY2_0_DUAL_PORT 0
#define ONCHIP_MEMORY2_0_GUI_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_INIT_CONTENTS_FILE "final_soc_onchip_memory2_0"
#define ONCHIP_MEMORY2_0_INIT_MEM_CONTENT 1
#define ONCHIP_MEMORY2_0_INSTANCE_ID "NONE"
#define ONCHIP_MEMORY2_0_IRQ -1
#define ONCHIP_MEMORY2_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define ONCHIP_MEMORY2_0_NAME "/dev/onchip_memory2_0"
#define ONCHIP_MEMORY2_0_NON_DEFAULT_INIT_FILE_ENABLED 0
#define ONCHIP_MEMORY2_0_RAM_BLOCK_TYPE "AUTO"
#define ONCHIP_MEMORY2_0_READ_DURING_WRITE_MODE "DONT_CARE"
#define ONCHIP_MEMORY2_0_SINGLE_CLOCK_OP 0
#define ONCHIP_MEMORY2_0_SIZE_MULTIPLE 1
#define ONCHIP_MEMORY2_0_SIZE_VALUE 16
#define ONCHIP_MEMORY2_0_SPAN 16
#define ONCHIP_MEMORY2_0_TYPE "altera_avalon_onchip_memory2"
#define ONCHIP_MEMORY2_0_WRITABLE 1


/*
 * otg_hpi_address configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_address altera_avalon_pio
#define OTG_HPI_ADDRESS_BASE 0x1d0
#define OTG_HPI_ADDRESS_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_ADDRESS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_ADDRESS_CAPTURE 0
#define OTG_HPI_ADDRESS_DATA_WIDTH 2
#define OTG_HPI_ADDRESS_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_ADDRESS_DRIVEN_SIM_VALUE 0
#define OTG_HPI_ADDRESS_EDGE_TYPE "NONE"
#define OTG_HPI_ADDRESS_FREQ 50000000
#define OTG_HPI_ADDRESS_HAS_IN 0
#define OTG_HPI_ADDRESS_HAS_OUT 1
#define OTG_HPI_ADDRESS_HAS_TRI 0
#define OTG_HPI_ADDRESS_IRQ -1
#define OTG_HPI_ADDRESS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_ADDRESS_IRQ_TYPE "NONE"
#define OTG_HPI_ADDRESS_NAME "/dev/otg_hpi_address"
#define OTG_HPI_ADDRESS_RESET_VALUE 0
#define OTG_HPI_ADDRESS_SPAN 16
#define OTG_HPI_ADDRESS_TYPE "altera_avalon_pio"


/*
 * otg_hpi_cs configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_cs altera_avalon_pio
#define OTG_HPI_CS_BASE 0x190
#define OTG_HPI_CS_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_CS_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_CS_CAPTURE 0
#define OTG_HPI_CS_DATA_WIDTH 1
#define OTG_HPI_CS_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_CS_DRIVEN_SIM_VALUE 0
#define OTG_HPI_CS_EDGE_TYPE "NONE"
#define OTG_HPI_CS_FREQ 50000000
#define OTG_HPI_CS_HAS_IN 0
#define OTG_HPI_CS_HAS_OUT 1
#define OTG_HPI_CS_HAS_TRI 0
#define OTG_HPI_CS_IRQ -1
#define OTG_HPI_CS_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_CS_IRQ_TYPE "NONE"
#define OTG_HPI_CS_NAME "/dev/otg_hpi_cs"
#define OTG_HPI_CS_RESET_VALUE 0
#define OTG_HPI_CS_SPAN 16
#define OTG_HPI_CS_TYPE "altera_avalon_pio"


/*
 * otg_hpi_data configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_data altera_avalon_pio
#define OTG_HPI_DATA_BASE 0x1c0
#define OTG_HPI_DATA_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_DATA_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_DATA_CAPTURE 0
#define OTG_HPI_DATA_DATA_WIDTH 16
#define OTG_HPI_DATA_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_DATA_DRIVEN_SIM_VALUE 0
#define OTG_HPI_DATA_EDGE_TYPE "NONE"
#define OTG_HPI_DATA_FREQ 50000000
#define OTG_HPI_DATA_HAS_IN 1
#define OTG_HPI_DATA_HAS_OUT 1
#define OTG_HPI_DATA_HAS_TRI 0
#define OTG_HPI_DATA_IRQ -1
#define OTG_HPI_DATA_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_DATA_IRQ_TYPE "NONE"
#define OTG_HPI_DATA_NAME "/dev/otg_hpi_data"
#define OTG_HPI_DATA_RESET_VALUE 0
#define OTG_HPI_DATA_SPAN 16
#define OTG_HPI_DATA_TYPE "altera_avalon_pio"


/*
 * otg_hpi_r configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_r altera_avalon_pio
#define OTG_HPI_R_BASE 0x1b0
#define OTG_HPI_R_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_R_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_R_CAPTURE 0
#define OTG_HPI_R_DATA_WIDTH 1
#define OTG_HPI_R_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_R_DRIVEN_SIM_VALUE 0
#define OTG_HPI_R_EDGE_TYPE "NONE"
#define OTG_HPI_R_FREQ 50000000
#define OTG_HPI_R_HAS_IN 0
#define OTG_HPI_R_HAS_OUT 1
#define OTG_HPI_R_HAS_TRI 0
#define OTG_HPI_R_IRQ -1
#define OTG_HPI_R_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_R_IRQ_TYPE "NONE"
#define OTG_HPI_R_NAME "/dev/otg_hpi_r"
#define OTG_HPI_R_RESET_VALUE 0
#define OTG_HPI_R_SPAN 16
#define OTG_HPI_R_TYPE "altera_avalon_pio"


/*
 * otg_hpi_reset configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_reset altera_avalon_pio
#define OTG_HPI_RESET_BASE 0x180
#define OTG_HPI_RESET_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_RESET_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_RESET_CAPTURE 0
#define OTG_HPI_RESET_DATA_WIDTH 1
#define OTG_HPI_RESET_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_RESET_DRIVEN_SIM_VALUE 0
#define OTG_HPI_RESET_EDGE_TYPE "NONE"
#define OTG_HPI_RESET_FREQ 50000000
#define OTG_HPI_RESET_HAS_IN 0
#define OTG_HPI_RESET_HAS_OUT 1
#define OTG_HPI_RESET_HAS_TRI 0
#define OTG_HPI_RESET_IRQ -1
#define OTG_HPI_RESET_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_RESET_IRQ_TYPE "NONE"
#define OTG_HPI_RESET_NAME "/dev/otg_hpi_reset"
#define OTG_HPI_RESET_RESET_VALUE 0
#define OTG_HPI_RESET_SPAN 16
#define OTG_HPI_RESET_TYPE "altera_avalon_pio"


/*
 * otg_hpi_w configuration
 *
 */

#define ALT_MODULE_CLASS_otg_hpi_w altera_avalon_pio
#define OTG_HPI_W_BASE 0x1a0
#define OTG_HPI_W_BIT_CLEARING_EDGE_REGISTER 0
#define OTG_HPI_W_BIT_MODIFYING_OUTPUT_REGISTER 0
#define OTG_HPI_W_CAPTURE 0
#define OTG_HPI_W_DATA_WIDTH 1
#define OTG_HPI_W_DO_TEST_BENCH_WIRING 0
#define OTG_HPI_W_DRIVEN_SIM_VALUE 0
#define OTG_HPI_W_EDGE_TYPE "NONE"
#define OTG_HPI_W_FREQ 50000000
#define OTG_HPI_W_HAS_IN 0
#define OTG_HPI_W_HAS_OUT 1
#define OTG_HPI_W_HAS_TRI 0
#define OTG_HPI_W_IRQ -1
#define OTG_HPI_W_IRQ_INTERRUPT_CONTROLLER_ID -1
#define OTG_HPI_W_IRQ_TYPE "NONE"
#define OTG_HPI_W_NAME "/dev/otg_hpi_w"
#define OTG_HPI_W_RESET_VALUE 0
#define OTG_HPI_W_SPAN 16
#define OTG_HPI_W_TYPE "altera_avalon_pio"


/*
 * sdram configuration
 *
 */

#define ALT_MODULE_CLASS_sdram altera_avalon_new_sdram_controller
#define SDRAM_BASE 0x10000000
#define SDRAM_CAS_LATENCY 3
#define SDRAM_CONTENTS_INFO
#define SDRAM_INIT_NOP_DELAY 0.0
#define SDRAM_INIT_REFRESH_COMMANDS 2
#define SDRAM_IRQ -1
#define SDRAM_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_IS_INITIALIZED 1
#define SDRAM_NAME "/dev/sdram"
#define SDRAM_POWERUP_DELAY 200.0
#define SDRAM_REFRESH_PERIOD 7.8125
#define SDRAM_REGISTER_DATA_IN 1
#define SDRAM_SDRAM_ADDR_WIDTH 0x19
#define SDRAM_SDRAM_BANK_WIDTH 2
#define SDRAM_SDRAM_COL_WIDTH 10
#define SDRAM_SDRAM_DATA_WIDTH 32
#define SDRAM_SDRAM_NUM_BANKS 4
#define SDRAM_SDRAM_NUM_CHIPSELECTS 1
#define SDRAM_SDRAM_ROW_WIDTH 13
#define SDRAM_SHARED_DATA 0
#define SDRAM_SIM_MODEL_BASE 0
#define SDRAM_SPAN 134217728
#define SDRAM_STARVATION_INDICATOR 0
#define SDRAM_TRISTATE_BRIDGE_SLAVE ""
#define SDRAM_TYPE "altera_avalon_new_sdram_controller"
#define SDRAM_T_AC 5.5
#define SDRAM_T_MRD 3
#define SDRAM_T_RCD 20.0
#define SDRAM_T_RFC 70.0
#define SDRAM_T_RP 20.0
#define SDRAM_T_WR 14.0


/*
 * sdram_pll configuration
 *
 */

#define ALT_MODULE_CLASS_sdram_pll altpll
#define SDRAM_PLL_BASE 0x2a0
#define SDRAM_PLL_IRQ -1
#define SDRAM_PLL_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SDRAM_PLL_NAME "/dev/sdram_pll"
#define SDRAM_PLL_SPAN 16
#define SDRAM_PLL_TYPE "altpll"


/*
 * sw configuration
 *
 */

#define ALT_MODULE_CLASS_sw altera_avalon_pio
#define SW_BASE 0x280
#define SW_BIT_CLEARING_EDGE_REGISTER 0
#define SW_BIT_MODIFYING_OUTPUT_REGISTER 0
#define SW_CAPTURE 0
#define SW_DATA_WIDTH 8
#define SW_DO_TEST_BENCH_WIRING 0
#define SW_DRIVEN_SIM_VALUE 0
#define SW_EDGE_TYPE "NONE"
#define SW_FREQ 50000000
#define SW_HAS_IN 1
#define SW_HAS_OUT 0
#define SW_HAS_TRI 0
#define SW_IRQ -1
#define SW_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SW_IRQ_TYPE "NONE"
#define SW_NAME "/dev/sw"
#define SW_RESET_VALUE 0
#define SW_SPAN 16
#define SW_TYPE "altera_avalon_pio"


/*
 * sysid_qsys_0 configuration
 *
 */

#define ALT_MODULE_CLASS_sysid_qsys_0 altera_avalon_sysid_qsys
#define SYSID_QSYS_0_BASE 0x2c0
#define SYSID_QSYS_0_ID 0
#define SYSID_QSYS_0_IRQ -1
#define SYSID_QSYS_0_IRQ_INTERRUPT_CONTROLLER_ID -1
#define SYSID_QSYS_0_NAME "/dev/sysid_qsys_0"
#define SYSID_QSYS_0_SPAN 8
#define SYSID_QSYS_0_TIMESTAMP 1556412523
#define SYSID_QSYS_0_TYPE "altera_avalon_sysid_qsys"


/*
 * timer_0 configuration
 *
 */

#define ALT_MODULE_CLASS_timer_0 altera_avalon_timer
#define TIMER_0_ALWAYS_RUN 0
#define TIMER_0_BASE 0x40
#define TIMER_0_COUNTER_SIZE 32
#define TIMER_0_FIXED_PERIOD 0
#define TIMER_0_FREQ 50000000
#define TIMER_0_IRQ 1
#define TIMER_0_IRQ_INTERRUPT_CONTROLLER_ID 0
#define TIMER_0_LOAD_VALUE 49999
#define TIMER_0_MULT 0.001
#define TIMER_0_NAME "/dev/timer_0"
#define TIMER_0_PERIOD 1
#define TIMER_0_PERIOD_UNITS "ms"
#define TIMER_0_RESET_OUTPUT 0
#define TIMER_0_SNAPSHOT 1
#define TIMER_0_SPAN 32
#define TIMER_0_TICKS_PER_SEC 1000
#define TIMER_0_TIMEOUT_PULSE_OUTPUT 0
#define TIMER_0_TYPE "altera_avalon_timer"

#endif /* __SYSTEM_H_ */
