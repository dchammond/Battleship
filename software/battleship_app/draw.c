#include "stdint_fix.h"
#include "system.h"
#include "draw.h"
#include "usb.h"

volatile uint8_t*  BS_VSYNC   = (uint8_t*)  VSYNC_BASE;
volatile uint8_t*  BS_DONE    = (uint8_t*)  DONE_BASE;
volatile uint8_t*  BS_START   = (uint8_t*)  START_BASE;
volatile uint16_t* BS_SIZEX   = (uint16_t*) SIZEX_BASE;
volatile uint16_t* BS_SIZEY   = (uint16_t*) SIZEY_BASE;
volatile uint16_t* BS_SPRITEX = (uint16_t*) STARTX_BASE;
volatile uint16_t* BS_SPRITEY = (uint16_t*) STARTY_BASE;
volatile uint16_t* BS_SRAMX   = (uint16_t*) SRAMX_BASE;
volatile uint16_t* BS_SRAMY   = (uint16_t*) SRAMY_BASE;

void board_to_pixel(uint8_t row, uint8_t col, uint16_t* x, uint16_t* y)
{
	*x = 32 + 16*col;
	*y = 32 + 16*row;
}

void draw_string(char* string, enum text_color color, uint16_t x, uint16_t y)
{   // chars are 8x8
    uint16_t x_start = 200; uint16_t y_start = 480;
//    uint8_t count = 0;
    switch(color) {
    case BLUE:;  { y_start += 8 * 0; } // 480
    break;
    case GREEN:; { y_start += 8 * 1; } // 488
    break;
    case RED:;   { y_start += 8 * 2; } // 496
    }
    while(*string) {
        switch(*string) {
        case ' ':; { draw_func(x_start + (8 * -1), y_start, 8, 8, x, y); }
        break;
        case '0':; { draw_func(x_start + (8 *  0), y_start, 8, 8, x, y); }
        break;
        case '1':; { draw_func(x_start + (8 *  1), y_start, 8, 8, x, y); }
        break;
        case '2':; { draw_func(x_start + (8 *  2), y_start, 8, 8, x, y); }
        break;
        case '3':; { draw_func(x_start + (8 *  3), y_start, 8, 8, x, y); }
        break;
        case '4':; { draw_func(x_start + (8 *  4), y_start, 8, 8, x, y); }
        break;
        case '5':; { draw_func(x_start + (8 *  5), y_start, 8, 8, x, y); }
        break;
        case '6':; { draw_func(x_start + (8 *  6), y_start, 8, 8, x, y); }
        break;
        case '7':; { draw_func(x_start + (8 *  7), y_start, 8, 8, x, y); }
        break;
        case '8':; { draw_func(x_start + (8 *  8), y_start, 8, 8, x, y); }
        break;
        case '9':; { draw_func(x_start + (8 *  9), y_start, 8, 8, x, y); }
        break;
        case 'A':; { draw_func(x_start + (8 * 10), y_start, 8, 8, x, y); }
        break;
        case 'B':; { draw_func(x_start + (8 * 11), y_start, 8, 8, x, y); }
        break;
        case 'C':; { draw_func(x_start + (8 * 12), y_start, 8, 8, x, y); }
        break;
        case 'D':; { draw_func(x_start + (8 * 13), y_start, 8, 8, x, y); }
        break;
        case 'E':; { draw_func(x_start + (8 * 14), y_start, 8, 8, x, y); }
        break;
        case 'F':; { draw_func(x_start + (8 * 15), y_start, 8, 8, x, y); }
        break;
        case 'G':; { draw_func(x_start + (8 * 16), y_start, 8, 8, x, y); }
        break;
        case 'H':; { draw_func(x_start + (8 * 17), y_start, 8, 8, x, y); }
        break;
        case 'I':; { draw_func(x_start + (8 * 18), y_start, 8, 8, x, y); }
        break;
        case 'J':; { draw_func(x_start + (8 * 19), y_start, 8, 8, x, y); }
        break;
        case 'K':; { draw_func(x_start + (8 * 20), y_start, 8, 8, x, y); }
        break;
        case 'L':; { draw_func(x_start + (8 * 21), y_start, 8, 8, x, y); }
        break;
        case 'M':; { draw_func(x_start + (8 * 22), y_start, 8, 8, x, y); }
        break;
        case 'N':; { draw_func(x_start + (8 * 23), y_start, 8, 8, x, y); }
        break;
        case 'O':; { draw_func(x_start + (8 * 24), y_start, 8, 8, x, y); }
        break;
        case 'P':; { draw_func(x_start + (8 * 25), y_start, 8, 8, x, y); }
        break;
        case 'Q':; { draw_func(x_start + (8 * 26), y_start, 8, 8, x, y); }
        break;
        case 'R':; { draw_func(x_start + (8 * 27), y_start, 8, 8, x, y); }
        break;
        case 'S':; { draw_func(x_start + (8 * 28), y_start, 8, 8, x, y); }
        break;
        case 'T':; { draw_func(x_start + (8 * 29), y_start, 8, 8, x, y); }
        break;
        case 'U':; { draw_func(x_start + (8 * 30), y_start, 8, 8, x, y); }
        break;
        case 'V':; { draw_func(x_start + (8 * 31), y_start, 8, 8, x, y); }
        break;
        case 'W':; { draw_func(x_start + (8 * 32), y_start, 8, 8, x, y); }
        break;
        case 'X':; { draw_func(x_start + (8 * 33), y_start, 8, 8, x, y); }
        break;
        case 'Y':; { draw_func(x_start + (8 * 34), y_start, 8, 8, x, y); }
        break;
        case 'Z':; { draw_func(x_start + (8 * 35), y_start, 8, 8, x, y); }
        break;
        case '%':; { draw_func(x_start + (8 * 36), y_start, 8, 8, x, y); }
        break;
        case '-':; { draw_func(x_start + (8 * 37), y_start, 8, 8, x, y); }
        break;
        case '?':; { draw_func(x_start + (8 * 38), y_start, 8, 8, x, y); }
        break;
        case '.':; { draw_func(x_start + (8 * 39), y_start, 8, 8, x, y); }
        break;
        case '!':; { draw_func(x_start + (8 * 40), y_start, 8, 8, x, y); }
        break;
        }
//        if(count == 2) {
//        	SPIN_VSYNC;
//        	count = 0;
//        } else {
//        	count += 1;
//        }
        //printf("%c\n", *string);
        string += 1;
        x += 8;
        //usleep(100);
        //usb_read_key();
    }
}

void draw_func(uint16_t sram_x, uint16_t sram_y, uint8_t x_size, uint8_t y_size, uint16_t x_pos, uint16_t y_pos)
{
    *BS_SRAMX = sram_x;
    *BS_SRAMY = sram_y;
    *BS_SIZEX = x_size;
    *BS_SIZEY = y_size;
    *BS_SPRITEX = x_pos;
    *BS_SPRITEY = y_pos;
    *BS_START = 1;
    while(*BS_DONE != 0) ;
    *BS_START = 0;
}

