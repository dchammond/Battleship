#ifndef _DRAW_H_
#define _DRAW_H_

#include "stdint_fix.h"
#include "sprite_map.h"

// vsync active low (low means new frame start)

extern volatile uint8_t*  BS_VSYNC;
extern volatile uint8_t*  BS_DONE;
extern volatile uint8_t*  BS_START;
extern volatile uint16_t* BS_SIZEX;
extern volatile uint16_t* BS_SIZEY;
extern volatile uint16_t* BS_SPRITEX;
extern volatile uint16_t* BS_SPRITEY;
extern volatile uint16_t* BS_SRAMX;
extern volatile uint16_t* BS_SRAMY;

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define MS_TO_US(MS) (MS * 1000)
#define MS_PER_FRAME 16
#define US_PER_FRAME (MS_TO_US(MS_PER_FRAME))

#define SPIN_VSYNC while(*BS_VSYNC != 0);

#define DRAW(_X, LOC_X, LOC_Y) \
do {\
    *BS_SRAMX = _X ## _XPOS;\
    *BS_SRAMY = _X ## _YPOS;\
    *BS_SIZEX = _X ## _XSIZE;\
    *BS_SIZEY = _X ## _YSIZE;\
    *BS_SPRITEX = LOC_X;\
    *BS_SPRITEY = LOC_Y;\
    *BS_START = 1;\
    while(*BS_DONE != 1) ;\
    *BS_START = 0;\
} while(0)

#define DRAW_REPEAT(_X, LOC_X, LOC_Y, _N) \
do {\
	for(int _n = 0; _n < _N; _n++) {\
		SPIN_VSYNC;\
		DRAW(_X, LOC_X, LOC_Y);\
	}\
} while(0)

#define DRAW_SIZE(_X, LOC_X, LOC_Y, SIZE_X, SIZE_Y) \
do {\
    *BS_SRAMX = _X ## _XPOS;\
    *BS_SRAMY = _X ## _YPOS;\
    *BS_SIZEX = SIZE_X;\
    *BS_SIZEY = SIZE_Y;\
    *BS_SPRITEX = LOC_X;\
    *BS_SPRITEY = LOC_Y;\
    *BS_START = 1;\
    while(*BS_DONE != 1) ;\
    *BS_START = 0;\
} while(0)

// solid tiles have the same x and y width of 32, so 8x8 will cover screen
#define DRAW_SOLID_SCREEN(_X) \
do {\
    for(int _t = 0; _t < 2; _t++) {\
        SPIN_VSYNC;\
        for(int _r = 0; _r < 8; _r++) {\
            DRAW(_X, 0, _r * 32);\
        }\
    }\
} while(0)

// very useful macro for a common animation
#define SLIDE_UP_ANIMATION(_SPRITE, _TILE, _SPEED)\
do {\
    DRAW_SOLID_SCREEN(_TILE);\
	for(int _i = 0; _i < 240; _i += _SPEED) {\
		SPIN_VSYNC;\
		DRAW_SIZE(_SPRITE, 0, 240 - _i, _SPRITE ## _XSIZE, _i + 1);\
	}\
	SPIN_VSYNC;\
	DRAW(_SPRITE, 0, 0);\
	SPIN_VSYNC;\
	DRAW(_SPRITE, 0, 0);\
} while(0)

// 240 is the height of the screen

enum text_color {
    BLUE,
    RED,
    GREEN
};

void board_to_pixel(uint8_t row, uint8_t col, uint16_t* x, uint16_t* y);

// does correctly draw text but we ended up not using it
void draw_string(char* string, enum text_color color, uint16_t x, uint16_t y);

// for the rare case that we can't use the DRAW macro, less convenient
void draw_func(uint16_t sram_x, uint16_t sram_y, uint8_t x_size, uint8_t y_size, uint16_t x_pos, uint16_t y_pos);

#endif

