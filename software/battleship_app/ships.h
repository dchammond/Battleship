#ifndef _SHIPS_H_
#define _SHIPS_H_

#include "stdint_fix.h"
#include "board.h"
#include "weapons.h"

enum ship_id {
    FRIGATE = 0,
    DESTROYER = 1,
    CRUISER = 2,
    BATTLESHIP = 3,
    SUBMARINE = 4,
    CARRIER = 5
};

struct ship {
    char* name;
    struct board_pattern layout_horizontal;
    struct board_pattern layout_vertical;
    enum direction dir;
    enum weapon_id weapon1;
    enum weapon_id weapon2;
    enum recon_id recon;
    enum ship_id id;
    uint8_t health;
    uint8_t pos_row;
    uint8_t pos_col;
    uint8_t placed;
};

char* get_ship_name(enum ship_id ship_id);
struct weapon* get_weapon1_player1(enum ship_id ship_id);
struct weapon* get_weapon1_player2(enum ship_id ship_id);
struct weapon* get_weapon2_player1(enum ship_id ship_id);
struct weapon* get_weapon2_player2(enum ship_id ship_id);
struct recon* get_ship_recon_player1(enum ship_id ship_id);
struct recon* get_ship_recon_player2(enum ship_id ship_id);
enum direction* get_direction_player1(enum ship_id ship_id);
enum direction* get_direction_player2(enum ship_id ship_id);
struct board_pattern* get_active_layout_player1(enum ship_id ship_id);
struct board_pattern* get_active_layout_player2(enum ship_id ship_id);

// puts a ship on the board
enum placement_err place_ship_player1(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col);
enum placement_err place_ship_player2(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col);
// tests placing ship on the board
enum placement_err can_place_ship_player1(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col);
enum placement_err can_place_ship_player2(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col);

// checking bounding box
struct ship* in_ship_border_player1(uint8_t pos_row, uint8_t pos_col);
struct ship* in_ship_border_player2(uint8_t pos_row, uint8_t pos_col);

void sink_ship_player1(enum ship_id ship_id);
void sink_ship_player2(enum ship_id ship_id);

// returns 1 if dead
int is_dead_player1(void);
int is_dead_player2(void);

void draw_ships_player1(void);
void draw_ships_player2(void);

#endif
