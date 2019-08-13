#include <stddef.h>
#include "stdint_fix.h"
#include "board.h"
#include "ships.h"
#include "weapons.h"
#include "draw.h"

// first we have the initialization of the ships
// we ended up not using names

#define SUBMARINE_INIT \
{\
    .name = "SUBMARINE",\
    .layout_horizontal = {\
        .row_offsets = (uint8_t[1]){0},\
        .col_offsets = (uint8_t[1]){0},\
        .len = 1\
    },\
    .layout_vertical = {\
        .row_offsets = (uint8_t[1]){0},\
        .col_offsets = (uint8_t[1]){0},\
        .len = 1\
    },\
    .dir = EAST,\
    .weapon1 = MK_48X,\
    .weapon2 = NO_WEAPON,\
    .recon = NO_RECON,\
    .id = SUBMARINE,\
    .health = 1,\
    .pos_row = 0,\
    .pos_col = 0,\
    .placed = 0\
}

#define FRIGATE_INIT \
{\
    .name = "FRIGATE",\
    .layout_horizontal = {\
        .row_offsets = (uint8_t[2]){0,0},\
        .col_offsets = (uint8_t[2]){0,1},\
        .len = 2\
    },\
    .layout_vertical = {\
        .row_offsets = (uint8_t[2]){0,1},\
        .col_offsets = (uint8_t[2]){0,0},\
        .len = 2\
    },\
    .dir = EAST,\
    .weapon1 = POLARIS,\
    .weapon2 = NO_WEAPON,\
    .recon = NO_RECON,\
    .id = FRIGATE,\
    .health = 2,\
    .pos_row = 0,\
    .pos_col = 0,\
    .placed = 0\
}

#define DESTROYER_INIT \
{\
    .name = "DESTROYER",\
    .layout_horizontal = {\
        .row_offsets = (uint8_t[3]){0,0,0},\
        .col_offsets = (uint8_t[3]){0,1,2},\
        .len = 3\
    },\
    .layout_vertical = {\
        .row_offsets = (uint8_t[3]){0,1,2},\
        .col_offsets = (uint8_t[3]){0,0,0},\
        .len = 3\
    },\
    .dir = EAST,\
    .weapon1 = ASROC_71,\
    .weapon2 = NO_WEAPON,\
    .recon = SONAR,\
    .id = DESTROYER,\
    .health = 3,\
    .pos_row = 0,\
    .pos_col = 0,\
    .placed = 0\
}

#define CRUISER_INIT \
{\
    .name = "CRUISER",\
    .layout_horizontal = {\
        .row_offsets = (uint8_t[4]){0,0,0,0},\
        .col_offsets = (uint8_t[4]){0,1,2,3},\
        .len = 4\
    },\
    .layout_vertical = {\
        .row_offsets = (uint8_t[4]){0,1,2,3},\
        .col_offsets = (uint8_t[4]){0,0,0,0},\
        .len = 4\
    },\
    .dir = EAST,\
    .weapon1 = SEADART,\
    .weapon2 = NO_WEAPON,\
    .recon = AERIAL,\
    .id = CRUISER,\
    .health = 4,\
    .pos_row = 0,\
    .pos_col = 0,\
    .placed = 0\
}

#define BATTLESHIP_INIT \
{\
    .name = "BATTLESHIP",\
    .layout_horizontal = {\
        .row_offsets = (uint8_t[5]){0,0,0,0,0},\
        .col_offsets = (uint8_t[5]){0,1,2,3,4},\
        .len = 5\
    },\
    .layout_vertical = {\
        .row_offsets = (uint8_t[5]){0,1,2,3,4},\
        .col_offsets = (uint8_t[5]){0,0,0,0,0},\
        .len = 5\
    },\
    .dir = EAST,\
    .weapon1 = TOMAHAWK_55M,\
    .weapon2 = HARPOON_55M,\
    .recon = NO_RECON,\
    .id = BATTLESHIP,\
    .health = 5,\
    .pos_row = 0,\
    .pos_col = 0,\
    .placed = 0\
}

#define CARRIER_INIT \
{\
    .name = "CARRIER",\
    .layout_horizontal = {\
        .row_offsets = (uint8_t[8]){0,0,0,0,1,1,1,1},\
        .col_offsets = (uint8_t[8]){0,1,2,3,0,1,2,3},\
        .len = 8\
    },\
    .layout_vertical = {\
        .row_offsets = (uint8_t[8]){0,1,2,3,0,1,2,3},\
        .col_offsets = (uint8_t[8]){0,0,0,0,1,1,1,1},\
        .len = 8\
    },\
    .dir = EAST,\
    .weapon1 = TALOS,\
    .weapon2 = P3_ORION,\
    .recon = NO_RECON,\
    .id = CARRIER,\
    .health = 6,\
    .pos_row = 0,\
    .pos_col = 0,\
    .placed = 0\
}

static struct ship frigate[2] = {FRIGATE_INIT, FRIGATE_INIT};

static struct ship destroyer[2] = {DESTROYER_INIT, DESTROYER_INIT};

static struct ship cruiser[2] = {CRUISER_INIT, CRUISER_INIT};

static struct ship battleship[2] = {BATTLESHIP_INIT, BATTLESHIP_INIT};

static struct ship submarine[2] = {SUBMARINE_INIT, SUBMARINE_INIT};

static struct ship carrier[2] = {CARRIER_INIT, CARRIER_INIT};

static struct ship* ship_list[6] = {frigate, destroyer, cruiser, battleship, submarine, carrier};

char* get_ship_name(enum ship_id ship_id)
{
    return ship_list[ship_id][0].name;
}

struct weapon* get_weapon1_player1(enum ship_id ship_id)
{
    return get_weapon_player1(ship_list[ship_id][0].weapon1);
}

struct weapon* get_weapon1_player2(enum ship_id ship_id)
{
    return get_weapon_player2(ship_list[ship_id][1].weapon1);
}

struct weapon* get_weapon2_player1(enum ship_id ship_id)
{
    enum weapon_id id = ship_list[ship_id][0].weapon2;
    return id == NO_WEAPON ? NULL : get_weapon_player1(id);
}

struct weapon* get_weapon2_player2(enum ship_id ship_id)
{
    enum weapon_id id = ship_list[ship_id][1].weapon2;
    return id == NO_WEAPON ? NULL : get_weapon_player2(id);
}

struct recon* get_ship_recon_player1(enum ship_id ship_id)
{
    return get_recon_player1(ship_list[ship_id][0].recon);
}

struct recon* get_ship_recon_player2(enum ship_id ship_id)
{
    return get_recon_player2(ship_list[ship_id][1].recon);
}

enum direction* get_direction_player1(enum ship_id ship_id)
{
    return &ship_list[ship_id][0].dir;
}

enum direction* get_direction_player2(enum ship_id ship_id)
{
    return &ship_list[ship_id][1].dir;
}

// valid placement should already have been checked
enum placement_err place_ship_player1(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col)
{
    struct ship* ship = &ship_list[ship_id][0];
    ship->dir = dir;
    ship->pos_row = pos_row;
    ship->pos_col = pos_col;
    enum placement_err err = place_ship(player1_board, get_active_layout_player1(ship->id), pos_row, pos_col);
    switch(err) {
    case ERR_NONE:; { ship->placed = 1; }
    break;
    default:; { ship->placed = 0; }
    }
    return err;
}

// valid placement should already have been checked
enum placement_err place_ship_player2(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col)
{
    struct ship* ship = &ship_list[ship_id][1];
    ship->dir = dir;
    ship->pos_row = pos_row;
    ship->pos_col = pos_col;
    enum placement_err err = place_ship(player2_board, get_active_layout_player2(ship->id), pos_row, pos_col);
    switch(err) {
    case ERR_NONE:; { ship->placed = 1; }
    break;
    default:; { ship->placed = 0; }
    }
    return err;
}

// check placement
enum placement_err can_place_ship_player1(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col)
{
    struct ship* ship = &ship_list[ship_id][0];
    ship->dir = dir;
    ship->pos_row = pos_row;
    ship->pos_col = pos_col;
    return can_place_ship(player1_board, get_active_layout_player1(ship->id), pos_row, pos_col);
}

// check placement
enum placement_err can_place_ship_player2(enum ship_id ship_id, enum direction dir, uint8_t pos_row, uint8_t pos_col)
{
    struct ship* ship = &ship_list[ship_id][1];
    ship->dir = dir;
    ship->pos_row = pos_row;
    ship->pos_col = pos_col;
    return can_place_ship(player2_board, get_active_layout_player2(ship->id), pos_row, pos_col);
}

static inline struct board_pattern* get_active_layout(struct ship* ship)
{
    switch(ship->dir) {
    case NORTH:
    case SOUTH:;
    {
        return &ship->layout_vertical;
    }
    break;
    case EAST:
    case WEST:;
    {
        return &ship->layout_horizontal;
    }
    break;
    }
    return NULL;
}

struct board_pattern* get_active_layout_player1(enum ship_id ship_id)
{
    return get_active_layout(&ship_list[ship_id][0]);
}

struct board_pattern* get_active_layout_player2(enum ship_id ship_id)
{
    return get_active_layout(&ship_list[ship_id][1]);
}

// check bounding box - generic
static int in_ship_border(struct ship* ship, uint8_t pos_row, uint8_t pos_col)
{
    struct board_pattern* layout = get_active_layout(ship);
    uint8_t ship_row = ship->pos_row;
    uint8_t ship_col = ship->pos_col;
    for(uint8_t i = 0; i < layout->len; i++) {
        uint8_t r = layout->row_offsets[i] + ship_row;
        uint8_t c = layout->col_offsets[i] + ship_col;
        if(r == pos_row && c == pos_col) return 1;
    }
    return 0;
}

struct ship* in_ship_border_player1(uint8_t pos_row, uint8_t pos_col)
{
    for(enum ship_id id = FRIGATE; id <= CARRIER; id++) {
        struct ship* ship = &ship_list[id][0];
        if(in_ship_border(ship, pos_row, pos_col)) {
            return ship;
        }
    }
    return NULL;
}

struct ship* in_ship_border_player2(uint8_t pos_row, uint8_t pos_col)
{
    for(enum ship_id id = FRIGATE; id <= CARRIER; id++) {
        struct ship* ship = &ship_list[id][1];
        if(in_ship_border(ship, pos_row, pos_col)) {
            return ship;
        }
    }
    return NULL;
}

// if a ship sinks, remove its weapons/recon
void sink_ship_player1(enum ship_id ship_id)
{
    struct ship* ship = &ship_list[ship_id][0];
    ship->health = 0;
    get_weapon1_player1(ship->id)->remaining_uses = 0;
    {
        struct weapon* w = get_weapon2_player1(ship->id);
        if(w) w->remaining_uses = 0;
    }
    {
        struct recon* r = get_recon_player1(ship->id);
        if(r) r->remaining_uses = 0;
    }
}

void sink_ship_player2(enum ship_id ship_id)
{
    struct ship* ship = &ship_list[ship_id][1];
    ship->health = 0;
    get_weapon1_player2(ship->id)->remaining_uses = 0;
    {
        struct weapon* w = get_weapon2_player2(ship->id);
        if(w) w->remaining_uses = 0;
    }
    {
        struct recon* r = get_recon_player2(ship->id);
        if(r) r->remaining_uses = 0;
    }
}

// you are dead if all ship health is 0
int is_dead_player1(void)
{
    for(enum ship_id id = 0; id <= CARRIER; id++) {
    	struct ship* ship = &ship_list[id][0];
        if(ship->health > 0) return 0;
    }
    return 1;
}

int is_dead_player2(void)
{
    for(enum ship_id id = 0; id <= CARRIER; id++) {
        struct ship* ship = &ship_list[id][1];
        if(ship->health > 0) return 0;
    }
    return 1;
}

void draw_ships_player1(void)
{ // TODO: This technically redraws the ship sprite every time it sees it
    for(enum ship_id id = 0; id <= CARRIER; id++) {
        struct ship* ship = &ship_list[id][0];
        if(ship->placed) {
            struct board_pattern* bp = get_active_layout_player1(ship->id);
            uint8_t start_row = bp->row_offsets[0] + ship->pos_row;
            uint8_t start_col = bp->col_offsets[0] + ship->pos_col;
            uint16_t x,y;
            board_to_pixel(start_row, start_col, &x, &y);
            switch(ship->dir) {
            case NORTH:
            case SOUTH:;
            {
                switch(id) {
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
                switch(id) {
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
            }
        }
    }
}

void draw_ships_player2(void)
{ // TODO: This technically redraws the ship sprite every time it sees it
    for(enum ship_id id = 0; id <= CARRIER; id++) {
        struct ship* ship = &ship_list[id][1];
        if(ship->placed) {
            struct board_pattern* bp = get_active_layout_player2(ship->id);
            uint8_t start_row = bp->row_offsets[0] + ship->pos_row;
            uint8_t start_col = bp->col_offsets[0] + ship->pos_col;
            uint16_t x,y;
            board_to_pixel(start_row, start_col, &x, &y);
            switch(ship->dir) {
            case NORTH:
            case SOUTH:;
            {
                switch(id) {
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
                switch(id) {
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
            }
        }
    }
}

