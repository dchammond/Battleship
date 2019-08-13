#ifndef _BOARD_H_
#define _BOARD_H_

#include "stdint_fix.h"

enum direction {
    NORTH = 0,
    EAST = 1,
    SOUTH = 2,
    WEST = 3
};

enum square_state {
    EMPTY = 0,
    SHIP_PRESENT = 1,
    MISSED = 2,
    SHIP_HIT = 3,
    SHIP_SUNK = 4
};

enum placement_err {
    ERR_NONE = 0,
    ERR_OOB_ROW = 1,
    ERR_OOB_COL = 2,
    ERR_OCCUPIED = 3,
    ERR_NO_OBJECT = 4
};

struct board_pattern {
    uint8_t* row_offsets;
    uint8_t* col_offsets;
    uint8_t len; // Same for both because parsed as (row,col) pairs
};

// 8 rows, 12 columns, (0,0) is top left and (7,11) is bottom right
extern uint8_t player1_board[8][12];
extern uint8_t player2_board[8][12]; // Also the computer

void clear_board(uint8_t* board);
enum placement_err can_place_ship(uint8_t my_board[8][12], const struct board_pattern* location, uint8_t start_row, uint8_t start_col);
enum placement_err place_ship(uint8_t my_board[8][12], const struct board_pattern* location, uint8_t start_row, uint8_t start_col);
// start_(row/col) is added to each element in the respective offset array
enum placement_err hit_or_miss(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col);
enum placement_err try_hit_or_miss(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col);
enum placement_err detect_ship(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col);
enum placement_err can_detect_ship(uint8_t enemy_board[8][12], const struct board_pattern* pattern, uint8_t start_row, uint8_t start_col);

void draw_board_player1(int show_ships, int weapon, int recon);
void draw_board_player2(int show_ships, int weapon, int recon);
void draw_place_board_player1(void);
void draw_place_board_player2(void);

#endif
