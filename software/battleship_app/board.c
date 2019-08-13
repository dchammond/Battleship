#include <stdlib.h>
#include <string.h>
#include "stdint_fix.h"
#include "board.h"
#include "ships.h"
#include "draw.h"
#include "weapons.h"

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define SWAP(a,b,type) \
    type temp = (a);\
    (a) = (b);\
    (a) = temp;

uint8_t player1_board[8][12];
uint8_t player2_board[8][12]; // Also the computer/serial opponent
uint8_t board_copy[8][12];

static void backup_board(uint8_t board[8][12])
{
    memcpy(board_copy, board, sizeof(board_copy));
}

static void restore_board(uint8_t board[8][12])
{
    memcpy(board, board_copy, sizeof(board_copy));
}

void clear_board(uint8_t* board)
{
    memset(board, EMPTY, sizeof(player1_board));
}

// test placing the ship
enum placement_err can_place_ship(uint8_t my_board[8][12], const struct board_pattern* location, uint8_t start_row, uint8_t start_col)
{
	enum placement_err ret = ERR_NONE;
    for(uint8_t i = 0; i < location->len; i++) {
        uint8_t r = location->row_offsets[i] + start_row;
        uint8_t c = location->col_offsets[i] + start_col;
        if(r >= 8) return ERR_OOB_ROW;
        if(c >= 12) return ERR_OOB_COL;
        if(my_board[r][c] != EMPTY) ret = ERR_OCCUPIED;
    }
    return ret;
}

// actually place the ship, bounds checking should have already been done
enum placement_err place_ship(uint8_t my_board[8][12], const struct board_pattern* location, uint8_t start_row, uint8_t start_col)
{
    backup_board(my_board);
    for(uint8_t i = 0; i < location->len; i++) {
        uint8_t r = location->row_offsets[i] + start_row;
        uint8_t c = location->col_offsets[i] + start_col;
        if(r >= 8) {
            restore_board(my_board);
            return ERR_OOB_ROW;
        }
        if(c >= 12) {
            restore_board(my_board);
            return ERR_OOB_COL;
        }
        if(my_board[r][c] != EMPTY) {
            restore_board(my_board);
            return ERR_OCCUPIED;
        }
        my_board[r][c] = SHIP_PRESENT;
    }
    return ERR_NONE;
}

// Firing at player 1
static void check_ship_sunk_player1(uint8_t board[8][12], uint8_t r, uint8_t c)
{
    struct ship* ship = in_ship_border_player1(r, c);
    struct board_pattern* bp = get_active_layout_player1(ship->id);
    if(ship->health <= 1) {
    	ship->health = 0;
        sink_ship_player1(ship->id);
        for(uint8_t j = 0; j < bp->len; j++) { // update ship to be sunk
            uint8_t ship_r = bp->row_offsets[j] + ship->pos_row;
            uint8_t ship_c = bp->col_offsets[j] + ship->pos_col;
            board[ship_r][ship_c] = SHIP_SUNK;
        }
    } else {
    	ship->health -= 1;
    }
}

// Firing at player 2
static void check_ship_sunk_player2(uint8_t board[8][12], uint8_t r, uint8_t c)
{
    struct ship* ship = in_ship_border_player2(r, c);
    struct board_pattern* bp = get_active_layout_player2(ship->id);
    if(ship->health <= 1) {
    	ship->health = 0;
        sink_ship_player2(ship->id);
        for(uint8_t j = 0; j < bp->len; j++) { // update ship to be sunk
            uint8_t ship_r = bp->row_offsets[j] + ship->pos_row;
            uint8_t ship_c = bp->col_offsets[j] + ship->pos_col;
            board[ship_r][ship_c] = SHIP_SUNK;
        }
    } else {
    	ship->health -= 1;
    }
}

// responsible for playing firing animations, and then checking if a ship was sunk
enum placement_err hit_or_miss(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col)
{
    static int show_a = 0;
    backup_board(enemy_board);
    for(size_t i = 0; i < pattern->len; i++) {
        uint8_t r = pattern->row_offsets[i] + start_row;
        uint8_t c = pattern->col_offsets[i] + start_col;
        SPIN_VSYNC;
        if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
        else DRAW(BG_WTR_B, 0, 0);

        if(enemy_board[r][c] == EMPTY ||
           enemy_board[r][c] == MISSED) {
            enemy_board[r][c] = MISSED;
            int x = 0, y = 0;
            for(; x < (128 - 16 - 16), y < (128 - 16 - 16); x += 2, y += 2) { // Draw bullet firing
                SPIN_VSYNC;
                if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
                else DRAW(BG_WTR_B, 0, 0);
                DRAW(P1_BULLET, x, y);
                show_a += 1;
                if(show_a == 25) show_a = 0;
            }
            for(int t = 0; t < 15; t++) {
				SPIN_VSYNC;
				if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
				else DRAW(BG_WTR_B, 0, 0);
				DRAW(SPLASH_A, x, y);                  // first splash sprite
				show_a += 1;
				if(show_a == 25) show_a = 0;
            }
            for(int t = 0; t < 15; t++) {
				SPIN_VSYNC;
				if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
				else DRAW(BG_WTR_B, 0, 0);
				DRAW(SPLASH_B, x, y);                 // second flash sprite
				show_a += 1;
				if(show_a == 25) show_a = 0;
			}
            for(int t = 0; t < 15; t++) {
				SPIN_VSYNC;
				if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
				else DRAW(BG_WTR_B, 0, 0);
				DRAW(SPLASH_C, x - 4, y - 4);         // third flash sprite
				show_a += 1;
				if(show_a == 25) show_a = 0;
			}
        } else if(enemy_board[r][c] == SHIP_PRESENT ||
                  enemy_board[r][c] == SHIP_HIT     ||
                  enemy_board[r][c] == SHIP_SUNK) {
            enemy_board[r][c] = enemy_board[r][c] == SHIP_SUNK ? SHIP_SUNK : SHIP_HIT;
            int x = 0, y = 0;
            for(; x < (128 - 16), y < (128 - 16); x += 2, y += 2) { // draw bullet hitting ship
                SPIN_VSYNC;
                if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
                else DRAW(BG_WTR_B, 0, 0);
                DRAW(P1_BULLET, x, y);
                show_a += 1;
                if(show_a == 25) show_a = 0;
            }
            for(int t = 0; t < 15; t++) {
				SPIN_VSYNC;
				if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
				else DRAW(BG_WTR_B, 0, 0);
				DRAW(EXPLO_A, x, y);                    // first explosion sprite
				show_a += 1;
				if(show_a == 25) show_a = 0;
			}
			for(int t = 0; t < 15; t++) {
				SPIN_VSYNC;
				if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
				else DRAW(BG_WTR_B, 0, 0);
				DRAW(EXPLO_B, x, y);                    // second explosion sprite
				show_a += 1;
				if(show_a == 25) show_a = 0;
			}
			for(int t = 0; t < 15; t++) {
				SPIN_VSYNC;
				if(show_a <= 12) DRAW(BG_WTR_A, 0, 0);
				else DRAW(BG_WTR_B, 0, 0);              // third explosion sprite
				DRAW(EXPLO_C, x - 4, y - 4);
				show_a += 1;
				if(show_a == 25) show_a = 0;
			}
            // checking if ship sunk also decrements the health if needed
            if(enemy_board == player1_board) check_ship_sunk_player1(player1_board, r, c);
            else check_ship_sunk_player2(player2_board, r, c);
        }
        show_a += 1;
        if(show_a == 25) show_a = 0;
    }
    return ERR_NONE;
}

// error detection for firing
enum placement_err try_hit_or_miss(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col)
{
    for(size_t i = 0; i < pattern->len; i++) {
        uint8_t r = pattern->row_offsets[i] + start_row;
        if(r >=  8) return ERR_OOB_ROW;
        uint8_t c = pattern->col_offsets[i] + start_col;
        if(c >= 12) return ERR_OOB_COL;
    }
    return ERR_NONE;
}

// recon logic
enum placement_err detect_ship(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col)
{
    backup_board(enemy_board);
    uint16_t x,y;
    for(size_t i = 0; i < pattern->len; i++) {
    	SPIN_VSYNC;
        uint8_t r = pattern->row_offsets[i] + start_row;
        uint8_t c = pattern->col_offsets[i] + start_col;
        board_to_pixel(r, c, &x, &y);
        if(enemy_board[r][c] == SHIP_PRESENT) { // If a ship is there we play the "larger" sine-wave animation
        	DRAW_REPEAT(RECON_C, x, y, 50);
        	SPIN_VSYNC;
        	DRAW_REPEAT(RECON_A, x, y, 2);
        } else {                               // otherwise play the small sine-waves
        	DRAW_REPEAT(RECON_B, x, y, 50);
        	SPIN_VSYNC;
			DRAW_REPEAT(RECON_A, x, y, 2);
        }
    }
    return ERR_NONE;
}

// error checking for recon
enum placement_err can_detect_ship(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col)
{
    for(size_t i = 0; i < pattern->len; i++) {
        uint8_t r = pattern->row_offsets[i] + start_row;
        if(r >=  8) return ERR_OOB_ROW;
        uint8_t c = pattern->col_offsets[i] + start_col;
        if(c >= 12) return ERR_OOB_COL;
    }
    return ERR_NONE;
}

void draw_board_player1(int show_ships, int weapon, int recon)
{
    static int show_a = 0;
    DRAW(BG_P1_BRD, 0, 0);
    if(show_ships) { // looking at our own screen
        draw_ships_player1();
        for(uint8_t r = 0; r < 8; r++) {
            for(uint8_t c = 0; c < 12; c++) {
                uint16_t x, y;
                board_to_pixel(r, c, &x, &y);
                switch(player1_board[r][c]) {
                case MISSED:;{
                    if(show_a <= 3)
                        DRAW(MISS_A, x, y);    // water animation for missed shot
                    else if(show_a <= 7)
                        DRAW(MISS_B, x, y);
                    else
                    	DRAW(MISS_C, x, y);
                }
                break;
                case SHIP_HIT:
                case SHIP_SUNK:;
                {
                    if(show_a <= 3)
                        DRAW(FIRE_A, x, y);    // fire animation for hit shot
                    else if(show_a <= 7)
                        DRAW(FIRE_B, x, y);
                    else
                    	DRAW(FIRE_C, x, y);
                }
                break;
                }
            }
        }
        show_a += 1;
        if(show_a == 12) show_a = 0;
    } else {
        for(uint8_t r = 0; r < 8; r++) {
            for(uint8_t c = 0; c < 12; c++) {
                uint16_t x, y;
                board_to_pixel(r, c, &x, &y);
                switch(player1_board[r][c]) {
                case MISSED:;    { DRAW(MISS_MRK, x, y); } // solid blue dot
                break;
                case SHIP_HIT:;  { DRAW(HIT_MRK,  x, y); } // word "hit"
                break;
                case SHIP_SUNK:; { DRAW(SUNK_MRK, x, y); } // solid red dot
                break;
                }
            }
        }
    }
    if(weapon != NO_WEAPON) { // weapon picture in bottom left
        switch(weapon) {
        case RIM_66:;       { DRAW(RIM,      36, 171); }
        break;
        case MK_48X:;       { DRAW(MK,       36, 171); }
        break;
        case POLARIS:;      { DRAW(POLARIS,  36, 171); }
        break;
        case ASROC_71:;     { DRAW(ASROC,    36, 171); }
        break;
        case SEADART:;      { DRAW(SEADART,  36, 171); }
        break;
        case TOMAHAWK_55M:; { DRAW(TOMAHAWK, 36, 171); }
        break;
        case HARPOON_55M:;  { DRAW(HARPOON,  36, 171); }
        break;
        case P3_ORION:;     { DRAW(ORION,    36, 171); }
        break;
        case TALOS:;        { DRAW(TALOS,    36, 171); }
        break;
        }
    } else if(recon != NO_RECON) { // or recon picture of that is selected
        switch(recon) {
        case SONAR:;        { DRAW(SONAR,    36, 171); }
        break;
        case AERIAL:;       { DRAW(AERIAL,   36, 171); }
        break;
        }
    }
}
// this is a direct copy of draw_board_player1 except using player2's board
void draw_board_player2(int show_ships, int weapon, int recon)
{
    static int show_a = 0;
    DRAW(BG_P2_BRD, 0, 0);
    if(show_ships) { // looking at our own screen
        draw_ships_player2();
        for(uint8_t r = 0; r < 8; r++) {
            for(uint8_t c = 0; c < 12; c++) {
                uint16_t x, y;
                board_to_pixel(r, c, &x, &y);
                switch(player2_board[r][c]) {
                case MISSED:;{
                    if(show_a <= 3)
                        DRAW(MISS_A, x, y);
                    else if(show_a <= 7)
                        DRAW(MISS_B, x, y);
                    else
                        DRAW(MISS_C, x, y);
                }
                break;
                case SHIP_HIT:
                case SHIP_SUNK:;
                {
                    if(show_a <= 3)
                        DRAW(FIRE_A, x, y);
                    else if(show_a <= 7)
                        DRAW(FIRE_B, x, y);
                    else
                        DRAW(FIRE_C, x, y);
                }
                break;
                }
            }
        }
        show_a += 1;
        if(show_a == 12) show_a = 0;
    } else {
        for(uint8_t r = 0; r < 8; r++) {
            for(uint8_t c = 0; c < 12; c++) {
                uint16_t x, y;
                board_to_pixel(r, c, &x, &y);
                switch(player2_board[r][c]) {
                case MISSED:;    { DRAW(MISS_MRK, x, y); }
                break;
                case SHIP_HIT:;  { DRAW(HIT_MRK,  x, y); }
                break;
                case SHIP_SUNK:; { DRAW(SUNK_MRK, x, y); }
                break;
                }
            }
        }
    }
    if(weapon != NO_WEAPON) {
        switch(weapon) {
        case RIM_66:;       { DRAW(RIM,      36, 171); }
        break;
        case MK_48X:;       { DRAW(MK,       36, 171); }
        break;
        case POLARIS:;      { DRAW(POLARIS,  36, 171); }
        break;
        case ASROC_71:;     { DRAW(ASROC,    36, 171); }
        break;
        case SEADART:;      { DRAW(SEADART,  36, 171); }
        break;
        case TOMAHAWK_55M:; { DRAW(TOMAHAWK, 36, 171); }
        break;
        case HARPOON_55M:;  { DRAW(HARPOON,  36, 171); }
        break;
        case P3_ORION:;     { DRAW(ORION,    36, 171); }
        break;
        case TALOS:;        { DRAW(TALOS,    36, 171); }
        break;
        }
    } else if(recon != NO_RECON) {
        switch(recon) {
        case SONAR:;        { DRAW(SONAR,    36, 171); }
        break;
        case AERIAL:;       { DRAW(AERIAL,   36, 171); }
        break;
        }
    }
}

// the "place" board does not have the area for a weapon/recon sprite at the bottom
void draw_place_board_player1(void)
{
    DRAW(BG_P1_PLACE, 0, 0);
    static int show_a = 0;
	draw_ships_player1();
	for(uint8_t r = 0; r < 8; r++) {
		for(uint8_t c = 0; c < 12; c++) {
			uint16_t x, y;
			board_to_pixel(r, c, &x, &y);
			switch(player1_board[r][c]) {
			case MISSED:;{
				if(show_a <= 3)
					DRAW(MISS_A, x, y);
				else if(show_a <= 7)
					DRAW(MISS_B, x, y);
				else
					DRAW(MISS_C, x, y);
			}
			break;
			case SHIP_HIT:
			case SHIP_SUNK:;
			{
				if(show_a <= 3)
					DRAW(FIRE_A, x, y);
				else if(show_a <= 7)
					DRAW(FIRE_B, x, y);
				else
					DRAW(FIRE_C, x, y);
			}
			break;
			}
		}
	}
	show_a += 1;
	if(show_a == 12) show_a = 0;
}

// the "place" board does not have the area for a weapon/recon sprite at the bottom
void draw_place_board_player2(void)
{
    DRAW(BG_P1_PLACE, 0, 0);
    static int show_a = 0;
    draw_ships_player2();
	for(uint8_t r = 0; r < 8; r++) {
		for(uint8_t c = 0; c < 12; c++) {
			uint16_t x, y;
			board_to_pixel(r, c, &x, &y);
			switch(player2_board[r][c]) {
			case MISSED:;{
				if(show_a <= 3)
					DRAW(MISS_A, x, y);
				else if(show_a <= 7)
					DRAW(MISS_B, x, y);
				else
					DRAW(MISS_C, x, y);
			}
			break;
			case SHIP_HIT:
			case SHIP_SUNK:;
			{
				if(show_a <= 3)
					DRAW(FIRE_A, x, y);
				else if(show_a <= 7)
					DRAW(FIRE_B, x, y);
				else
					DRAW(FIRE_C, x, y);
			}
			break;
			}
		}
	}
	show_a += 1;
	if(show_a == 12) show_a = 0;
}

