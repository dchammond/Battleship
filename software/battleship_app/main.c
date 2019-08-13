/************************************************************************
  Final Project - Battleship - Nios Software

  Dillon Hammond, Spring 2019
  Adam Newhouse, Spring 2019
 ************************************************************************/

#include "usb.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "stdint_fix.h"
#include "system.h"
#include "draw.h"
#include "board.h"
#include "weapons.h"
#include "ships.h"

#define READ_KEY_FRAME (4)

#define DEBOUNCED_KEY_READ(_counter_name) \
do {\
    static int _counter_name = 0;\
    key = kUNKNOWN;\
    if(_counter_name == READ_KEY_FRAME) {\
        key = read_key();\
        _counter_name = 0;\
    } else {\
        key = kUNKNOWN;\
        _counter_name += 1;\
    }\
} while(0);

enum key_press {
    kUNKNOWN,
    kUP,
    kDOWN,
    kLEFT,
    kRIGHT,
    kSELECT,
    kA,
    kB
};

enum game_state {
    SETUP = 0,
    P1_PLACE_FRIGATE,
    P1_PLACE_DESTROYER,
    P1_PLACE_CRUISER,
    P1_PLACE_BATTLESHIP,
    P1_PLACE_SUBMARINE,
    P1_PLACE_CARRIER,
    P2_PLACE_FRIGATE,
    P2_PLACE_DESTROYER,
    P2_PLACE_CRUISER,
    P2_PLACE_BATTLESHIP,
    P2_PLACE_SUBMARINE,
    P2_PLACE_CARRIER,
    P1_TAKE_SHOT,
    P2_TAKE_SHOT,
    P1_WIN,
    P2_WIN
};

static int multiplayer_mode = 0; // 0 == AI, 1 == serial
static int serial_fd = -1;

static enum key_press read_key(void)
{
    uint16_t key_code = usb_read_key();
    switch(key_code) {
    case 82:; return kUP;
    case 81:; return kDOWN;
    case 80:; return kLEFT;
    case 79:; return kRIGHT;
    case 26:; return kSELECT; // W
    case 29:; return kA;      // Z
    case 27:; return kB;      // X
    }
    return kUNKNOWN;
}

static void _place_ai_ships(void)
{
	for(int id = CARRIER; id >= 0; id--) {
		uint8_t r = 0;
		uint8_t c = 0;
		enum direction dir = rand() % 2 == 0 ? EAST : NORTH;
		enum placement_err ret = ERR_NO_OBJECT;
		while(ret != ERR_NONE) {
			r = rand() % 8;
			c = rand() % 12;
			ret = can_place_ship_player2(id, dir, r, c);
		}
		place_ship_player2(id, dir, r, c);
	}
}

static void _take_shot_ai(void)
{
	uint8_t meander = 5 + rand() % 10;
	uint8_t ref_r = rand() % 8;
	uint8_t ref_c = rand() % 12;
	uint8_t r, c;
	for(int i = 0; i < meander; i++) {
		SPIN_VSYNC;
		draw_board_player1(1, NO_WEAPON, NO_RECON);
		SPIN_VSYNC;
		draw_board_player1(1, NO_WEAPON, NO_RECON);
		r = 1;
		c = 1;
		int t = rand() % 3;
		if(t == 0) {
			r = MIN(MAX(r, ref_r) - MIN(r, ref_r), 7);
		} else if(t == 1) {
			r = MIN(MAX(r, ref_r) + MIN(r, ref_r), 7);
		} else {
			r = ref_r;
		}
		t = rand() % 3;
		if(t == 0) {
			c = MIN(MAX(c, ref_c) - MIN(c, ref_c), 11);
		} else if(t == 1) {
			c = MIN(MAX(c, ref_c) + MIN(c, ref_c), 11);
		} else {
			c = ref_c;
		}
		uint16_t x,y;
		board_to_pixel(r, c, &x, &y);
		DRAW_REPEAT(P2_TARGET, x, y, 30);
	}
	if(1) { // using weapon
		fire_weapon_player2(RIM_66, r, c);
	} else {
		use_recon_player2(SONAR, r, c);
	}
}

static void setup_game(void)
{
    clear_board(player1_board);
    clear_board(player2_board);

    SLIDE_UP_ANIMATION(BG_START, WIDE_BLUE, 2);

    enum key_press key = kUNKNOWN;
    while(key != kSELECT) {
        SPIN_VSYNC;
        DRAW(BG_START, 0, 0);
        DEBOUNCED_KEY_READ(_f);
        if(multiplayer_mode == 0) {
            DRAW(ARROW, 175, 185);
        } else {
            DRAW(ARROW, 175, 197);
        }
        if(key == kUP || key == kDOWN) {
            multiplayer_mode = !multiplayer_mode;
        }
    }
    if(multiplayer_mode == 0) _place_ai_ships();
}

void _place_ship(enum ship_id ship_id,
                 enum placement_err (*draw_place_board_cb)(void),
                 enum placement_err (*can_place_ship_cb)(enum ship_id, enum direction, uint8_t, uint8_t),
                 enum placement_err (*place_ship_cb)    (enum ship_id, enum direction, uint8_t, uint8_t))
{
    uint8_t r = 0;
    uint8_t c = 0;
    uint16_t x,y;
    enum key_press key = kUNKNOWN;
    enum direction dir = EAST;
    while(key != kSELECT) {
        enum placement_err ret = can_place_ship_cb(ship_id, dir, r, c);
        board_to_pixel(r, c, &x, &y);
_place_ship_draw:
        SPIN_VSYNC;

        draw_place_board_cb();
        
        switch(dir) {
        case NORTH:
        case SOUTH:;
        {
            switch(ship_id) {
            case FRIGATE:;    { DRAW(FRIG_V, x, y); }
            break;
            case DESTROYER:;  { DRAW(DEST_V, x, y); }
            break;
            case CRUISER:;    { DRAW(CRUI_V, x, y); }
            break;
            case BATTLESHIP:; { DRAW(BATT_V, x, y); }
            break;
            case SUBMARINE:;  { DRAW(SUB_V,  x, y); }
            break;
            case CARRIER:;    { DRAW(CARR_V, x, y); }
            break;
            }
        }
        break;
        case EAST:
        case WEST:;
        {
            switch(ship_id) {
            case FRIGATE:;    { DRAW(FRIG_H, x, y); }
            break;
            case DESTROYER:;  { DRAW(DEST_H, x, y); }
            break;
            case CRUISER:;    { DRAW(CRUI_H, x, y); }
            break;
            case BATTLESHIP:; { DRAW(BATT_H, x, y); }
            break;
            case SUBMARINE:;  { DRAW(SUB_V,  x, y); } // no horizontal, its one tile
            break;
            case CARRIER:;    { DRAW(CARR_H, x, y); }
            break;
            }
        }
        break;
        default:;
        }

        //draw_string(get_ship_name(ship_id), GREEN, 32, 175);

        static int draw_twice = 0;
        if(key == kB) {
            if(draw_twice == 0) {
                draw_twice = 1;
                goto _place_ship_draw;
            }
            draw_twice = 0;
            usleep(MS_TO_US(MS_PER_FRAME * 2));
        }

        DEBOUNCED_KEY_READ(main_counter);

        switch(key) {
        case kUP:;    { r = r ==  0 ?  0 : r - 1; }
		break;
		case kDOWN:;  { r = r ==  7 ?  7 : r + 1; }
		break;
		case kLEFT:;  { c = c ==  0 ?  0 : c - 1; }
		break;
		case kRIGHT:; { c = c == 11 ? 11 : c + 1; }
		break;
        case kB:;     { dir = dir == EAST ? NORTH : EAST; }
        break;
        case kSELECT:; { key = ret == ERR_NONE ? key : kUNKNOWN; } // Enforce valid place
        break;
        }
        // Make sure we aren't putting ourselves outside the board
        enum placement_err err = can_place_ship_cb(ship_id, dir, r, c);
        switch(key) {
        case kUP:
        case kDOWN:
        case kLEFT:
        case kRIGHT:;
        {
            switch(err) {
            case ERR_OOB_ROW:; { r -= 1; }
            break;
            case ERR_OOB_COL:; { c -= 1; }
            break;
            }
        }
        break;
        case kB:;
        {
            switch(err) {
            case ERR_OOB_ROW:; { dir = EAST; }
            break;
            case ERR_OOB_COL:; { dir = NORTH; }
            break;
            }
        }
        break;
        }
    }
    place_ship_cb(ship_id, dir, r, c);
}

void _place_ship_player1(enum ship_id ship_id)
{
    _place_ship(ship_id, draw_place_board_player1, can_place_ship_player1, place_ship_player1);
}

void _place_ship_player2(enum ship_id ship_id)
{
    _place_ship(ship_id, draw_place_board_player2, can_place_ship_player2, place_ship_player2);
}

void _take_shot(enum placement_err (*_can_fire_weapon)(enum weapon_id, uint8_t, uint8_t),
                enum placement_err (*_can_use_recon)(enum recon_id, uint8_t, uint8_t),
                enum placement_err (*_fire_weapon)(enum weapon_id, uint8_t, uint8_t),
                enum placement_err (*_use_recon)(enum recon_id, uint8_t, uint8_t),
                void (*_draw_weapon_target)(enum weapon_id, uint8_t, uint8_t),
                void (*_draw_recon_target)(enum recon_id, uint8_t, uint8_t),
                void (*_draw_opponent_board)(int, enum weapon_id, enum recon_id recon),
                void (*_draw_self_place_board)(void),
                enum weapon_id (*_iterate_weapon)(enum weapon_id),
                enum recon_id (*_iterate_recon)(enum recon_id),
                int blue_board
                )
{
    uint8_t r = 0;
    uint8_t c = 0;
    uint16_t x,y;
    enum key_press key = kUNKNOWN;
    enum weapon_id active_weapon = RIM_66;
    enum recon_id active_recon = SONAR;
    uint8_t using_weapon = 1; // 1 for weapon, 0 for recon
    while(key != kSELECT) {
        enum placement_err ret;
        if(using_weapon) ret = _can_fire_weapon(active_weapon, r, c);
        else ret = _can_use_recon(active_recon, r, c);

        board_to_pixel(r, c, &x, &y);
        SPIN_VSYNC;

        _draw_opponent_board(0,
                             using_weapon ? active_weapon : NO_WEAPON,
                             !using_weapon ? active_recon : NO_RECON); // don't show ships

        if(using_weapon) _draw_weapon_target(active_weapon, r, c);
        else _draw_recon_target(active_recon, r, c);

        DEBOUNCED_KEY_READ(main_counter);
    
        enum weapon_id prev_weapon = active_weapon;
        enum recon_id prev_recon = active_recon;
        switch(key) {
        case kUP:;    { r = r <=  0 ?  0 : r - 1; }
        break;
        case kDOWN:;  { r = r >=  7 ?  7 : r + 1; }
        break;
        case kLEFT:;  { c = c <=  0 ?  0 : c - 1; }
        break;
        case kRIGHT:; { c = c >= 11 ? 11 : c + 1; }
        break;
        case kB:;
        {
            if(using_weapon) {
                active_weapon = _iterate_weapon(active_weapon);
                if(active_weapon == NO_WEAPON) {
                    active_recon = _iterate_recon(NO_RECON); // wraps around
                    if(active_recon == NO_RECON) active_weapon = RIM_66; // No recon available so back to weapons
                    else using_weapon = 0; // we switched to recon
                }
            } else {
                active_recon = _iterate_recon(active_recon);
                if(active_recon == NO_RECON) {
                    active_weapon = RIM_66; // This is always true because RIM_66 has unlimited uses
                    using_weapon = 1;
                }
            }
        }
        break;
        case kA:;
        {
            SLIDE_UP_ANIMATION(BG_P1_PLACE, WIDE_BLK, 4);
            key = kUNKNOWN;
            while(key != kA) {
                SPIN_VSYNC;
                _draw_self_place_board();
                DEBOUNCED_KEY_READ(board_switch_frame);
            }
            if(blue_board) {
                SLIDE_UP_ANIMATION(BG_P2_BRD, WIDE_BLK, 4);
            } else {
                SLIDE_UP_ANIMATION(BG_P1_BRD, WIDE_BLK, 4);
            }
        }
        break;
        case kSELECT:; { key = ret == ERR_NONE ? key : kUNKNOWN; } // Enforce bounds
        break;
        }
        // Make sure we aren't putting ourselves outside the board
        enum placement_err err;
        if(using_weapon) err = _can_fire_weapon(active_weapon, r, c);
        else err = _can_use_recon(active_recon, r, c);

        switch(key) {
        case kUP:
        case kDOWN:
        case kLEFT:
        case kRIGHT:;
        {
            switch(err) {
            case ERR_OOB_ROW:; { r -= 1; }
            break;
            case ERR_OOB_COL:; { c -= 1; }
            break;
            }
        }
        break;
        case kB:;
        {
            switch(err) {
            case ERR_OOB_ROW:
            case ERR_OOB_COL:;
            {
                if(using_weapon) active_weapon = prev_weapon;
                else active_recon = prev_recon;
            }
            break;
            }
        }
        break;
        }
    }
    if(using_weapon) {
        _fire_weapon(active_weapon, r, c);
    } else {
        _use_recon(active_recon, r, c);
    }
    SPIN_VSYNC;
    _draw_opponent_board(0,
                         using_weapon ? active_weapon : NO_WEAPON,
                         !using_weapon ? active_recon : NO_RECON); // don't show ships
    SPIN_VSYNC;
    _draw_opponent_board(0,
                         using_weapon ? active_weapon : NO_WEAPON,
                         !using_weapon ? active_recon : NO_RECON); // don't show ships
}

// player 1 is shooting
void _take_shot_player1(void)
{
    _take_shot(can_fire_weapon_player1,
               can_use_recon_player1,
               fire_weapon_player1,
               use_recon_player1,
               draw_weapon_target_player1,
               draw_recon_target_player1,
               draw_board_player2, // opponent
               draw_place_board_player1,
               iterate_weapon_player1,
               iterate_recon_player1,
			   1
    );
}

// player 2 is shooting
void _take_shot_player2(void)
{
    // 1. Send board to serial client
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 12; c++) {
            uint8_t data = player1_board[r][c];
            // Censor data
            if(data == SHIP_PRESENT) data = EMPTY;
            write(serial_fd, &data, sizeof(uint8_t));
        }
    }
    uint8_t r, c;
    read(serial_fd, &r, sizeof(uint8_t)); // 2. read row of shot
    read(serial_fd, &c, sizeof(uint8_t)); // 3. read col of shot
    fire_weapon_player2(RIM_66, r, c);
    // 4. Send board to serial client
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 12; c++) {
            uint8_t data = player1_board[r][c];
            // Censor data
            if(data == SHIP_PRESENT) data = EMPTY;
            write(serial_fd, &data, sizeof(uint8_t));
        }
    }
    /*
    _take_shot(can_fire_weapon_player2,
               can_use_recon_player2,
               fire_weapon_player2,
               use_recon_player2,
               draw_weapon_target_player2,
               draw_recon_target_player2,
               draw_board_player1, // opponent
               draw_place_board_player2,
               iterate_weapon_player2,
               iterate_recon_player2,
			   0
    );
    */
}

int main(void)
{
    setup_usb();
    srand(clock());
    serial_fd = fileno(fopen("/dev/uart0", "r+"));
    SPIN_VSYNC;
    enum game_state state = SETUP;
    while(1) {
        switch(state) {
        case SETUP:;               { setup_game();                    state = P1_PLACE_SUBMARINE;    }
        break;
        case P1_PLACE_SUBMARINE:;  { _place_ship_player1(SUBMARINE);  state = P1_PLACE_FRIGATE;    }
		break;
        case P1_PLACE_FRIGATE:;    { _place_ship_player1(FRIGATE);    state = P1_PLACE_DESTROYER;  }
        break;
        case P1_PLACE_DESTROYER:;  { _place_ship_player1(DESTROYER);  state = P1_PLACE_CRUISER;    }
        break;
        case P1_PLACE_CRUISER:;    { _place_ship_player1(CRUISER);    state = P1_PLACE_BATTLESHIP; }
        break;
        case P1_PLACE_BATTLESHIP:; { _place_ship_player1(BATTLESHIP); state = P1_PLACE_CARRIER;  }
        break;
        case P1_PLACE_CARRIER:;    { _place_ship_player1(CARRIER);    state = multiplayer_mode == 0 ? P1_TAKE_SHOT : P2_PLACE_SUBMARINE; }
        break;
        case P2_PLACE_SUBMARINE:;  { _place_ship_player2(SUBMARINE);  state = P2_PLACE_FRIGATE;    }
		break;
        case P2_PLACE_FRIGATE:;    { _place_ship_player2(FRIGATE);    state = P2_PLACE_DESTROYER;  }
        break;
        case P2_PLACE_DESTROYER:;  { _place_ship_player2(DESTROYER);  state = P2_PLACE_CRUISER;    }
        break;
        case P2_PLACE_CRUISER:;    { _place_ship_player2(CRUISER);    state = P2_PLACE_BATTLESHIP; }
        break;
        case P2_PLACE_BATTLESHIP:; { _place_ship_player2(BATTLESHIP); state = P2_PLACE_CARRIER;  }
        break;
        case P2_PLACE_CARRIER:;    { _place_ship_player2(CARRIER);    state = P1_TAKE_SHOT;    }
        break;
        case P1_TAKE_SHOT:; { _take_shot_player1(); state = is_dead_player2() ? P1_WIN : P2_TAKE_SHOT;  }
        break;
        case P2_TAKE_SHOT:;
        {
            if(multiplayer_mode == 0)
                _take_shot_ai();
            else
                _take_shot_player2();
            state = is_dead_player1() ? P2_WIN : P1_TAKE_SHOT;
        }
        break;
        case P1_WIN:; { SPIN_VSYNC; DRAW(BG_REPORT_H, 0, 0); SPIN_VSYNC; DRAW(BG_REPORT_H, 0, 0); state = read_key() == kSELECT ? SETUP : P1_WIN; }
        break;
        case P2_WIN:; { SPIN_VSYNC; DRAW(BG_REPORT_L, 0, 0); SPIN_VSYNC; DRAW(BG_REPORT_L, 0, 0); state = read_key() == kSELECT ? SETUP : P2_WIN; }
        break;
        }
        usleep(MS_TO_US(MS_PER_FRAME * 5));
    }
}

/*
Stage 1-2: 9946
Stage 1-3: 8472
Stage 1-4: 5535
Stage 1-5: 1929
Stage 2-1: 7390
Stage 2-2: 6501
Stage 2-3: 5340
Stage 2-4: 1536
Stage 2-5: 3328
Stage 3-1: 9537
Stage 3-2: 8777
Stage 3-3: 2037
Stage 3-4: 5289
Stage 3-5: 3500
Stage 4-1: 3500
Stage 4-2: 3642
Stage 4-3: 4412
Stage 4-4: 8379
Stage 4-5: 8182
Stage 5-1: 8004
Stage 5-2: 5529
Stage 5-3: 4524
Stage 5-4: 4797
Stage 5-5: 9376
Stage 6-1: 1553
Stage 6-2: 7850
Stage 6-3: 5669
Stage 6-4: 9381
Stage 6-5: 9374
Stage 7-1: 4653
Stage 7-2: 5012
Stage 7-3: 8831
Stage 7-4: 9457
Stage 7-5: 6098
Stage 8-1: 9617
Stage 8-2: 5036
Stage 8-3: 6297
Stage 8-4: 8629
Stage 8-5: 8397
Ending: 1992
*/
