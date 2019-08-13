#include <string.h>
#include "stdint_fix.h"
#include "board.h"
#include "weapons.h"
#include "draw.h"

// define init weapons/recon

#define RIM_66_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[1]){0},\
        .col_offsets = (uint8_t[1]){0},\
        .len = 1\
    },\
    .id = RIM_66,\
    .remaining_uses = 255\
}

#define MK_48X_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[5]){0,1,1,1,2},\
        .col_offsets = (uint8_t[5]){1,0,1,2,1},\
        .len = 5\
    },\
    .id = MK_48X,\
    .remaining_uses = 1\
}

#define POLARIS_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[4]){0,0,2,2},\
        .col_offsets = (uint8_t[4]){0,2,0,2},\
        .len = 4\
    },\
    .id = POLARIS,\
    .remaining_uses = 1\
}

#define ASROC_71 \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[4]){0,0,1,1},\
        .col_offsets = (uint8_t[4]){0,4,0,4},\
        .len = 4\
    },\
    .id = ASROC_71,\
    .remaining_uses = 1\
}

#define SEADART_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[5]){0,0,1,2,2},\
        .col_offsets = (uint8_t[5]){0,2,1,0,2},\
        .len = 5\
    },\
    .id = SEADART,\
    .remaining_uses = 1\
}

#define TOMAHAWK_55M_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[6]){0,0,1,1,2,2},\
        .col_offsets = (uint8_t[6]){0,3,1,2,0,3},\
        .len = 6\
    },\
    .id = TOMAHAWK_55M,\
    .remaining_uses = 1\
}

#define HARPOON_55M_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[6]){0,1,1,2,2,3},\
        .col_offsets = (uint8_t[6]){1,0,2,0,2,1},\
        .len = 6\
    },\
    .id = HARPOON_55M,\
    .remaining_uses = 1\
}

#define P3_ORION_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[8]){0,0,1,1,2,2,3,3},\
        .col_offsets = (uint8_t[8]){0,2,1,3,0,2,1,3},\
        .len = 8\
    },\
    .id = P3_ORION,\
    .remaining_uses = 1\
}

#define TALOS_INIT \
{\
    .firing_pattern = {\
        .row_offsets = (uint8_t[7]){0,1,2,3,3,3,3},\
        .col_offsets = (uint8_t[7]){0,0,0,0,1,2,3},\
        .len = 7\
    },\
    .id = TALOS,\
    .remaining_uses = 1\
}

#define SONAR_INIT \
{\
    .recon_pattern = {\
        .row_offsets = (uint8_t[8]){0,0,0,1,1,2,2,2},\
        .col_offsets = (uint8_t[8]){0,1,2,0,2,0,1,2},\
        .len = 8\
    },\
    .id = SONAR,\
    .remaining_uses = 1\
}

#define AERIAL_INIT \
{\
    .recon_pattern = {\
        .row_offsets = (uint8_t[4]){0,0,1,1},\
        .col_offsets = (uint8_t[4]){0,1,0,1},\
        .len = 4\
    },\
    .id = AERIAL,\
    .remaining_uses = 1\
}

static struct weapon rim_66[2] = {RIM_66_INIT, RIM_66_INIT};

static struct weapon mk_48x[2] = {MK_48X_INIT, MK_48X_INIT};

static struct weapon polaris[2] = {POLARIS_INIT, POLARIS_INIT};

static struct weapon asroc_71[2] = {ASROC_71, ASROC_71};

static struct weapon seadart[2] = {SEADART_INIT, SEADART_INIT};

static struct weapon tomahawk_55m[2] = {TOMAHAWK_55M_INIT, TOMAHAWK_55M_INIT};

static struct weapon harpoon_55m[2] = {HARPOON_55M_INIT, HARPOON_55M_INIT};

static struct weapon p3_orion[2] = {P3_ORION_INIT, P3_ORION_INIT};

static struct weapon talos[2] = {TALOS_INIT, TALOS_INIT};

static struct recon sonar[2] = {SONAR_INIT, SONAR_INIT};

static struct recon aerial[2] = {AERIAL_INIT, AERIAL_INIT};

static struct weapon* weapons_list[9] = {rim_66, mk_48x, polaris, asroc_71, seadart, tomahawk_55m, harpoon_55m, p3_orion, talos};
static struct recon* recon_list[2] = {sonar, aerial};

struct weapon* get_weapon_player1(enum weapon_id id)
{
    return &weapons_list[id][0];
}

struct weapon* get_weapon_player2(enum weapon_id id)
{
    return &weapons_list[id][1];
}

struct recon* get_recon_player1(enum recon_id id)
{
    return &recon_list[id][0];
}

struct recon* get_recon_player2(enum recon_id id)
{
    return &recon_list[id][1];
}

// fire if uses remain
enum placement_err fire_weapon_player1(enum weapon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct weapon* w = get_weapon_player1(id);
    if(w->remaining_uses == 0) return ERR_NO_OBJECT;
    enum placement_err ret = hit_or_miss(player2_board, &w->firing_pattern, pos_row, pos_col);
    if(ret == ERR_NONE) w->remaining_uses -= 1;
    return ret;
}

// fire if uses remain
enum placement_err fire_weapon_player2(enum weapon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct weapon* w = get_weapon_player2(id);
    if(w->remaining_uses == 0) return ERR_NO_OBJECT;
    enum placement_err ret = hit_or_miss(player1_board, &w->firing_pattern, pos_row, pos_col);
    if(ret == ERR_NONE) w->remaining_uses -= 1;
    return ret;
}

enum placement_err can_fire_weapon_player1(enum weapon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct weapon* w = get_weapon_player1(id);
    if(w->remaining_uses == 0) return ERR_NO_OBJECT;
    return try_hit_or_miss(player2_board, &w->firing_pattern, pos_row, pos_col);
}

enum placement_err can_fire_weapon_player2(enum weapon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct weapon* w = get_weapon_player2(id);
    if(w->remaining_uses == 0) return ERR_NO_OBJECT;
    return try_hit_or_miss(player1_board, &w->firing_pattern, pos_row, pos_col);
}

enum placement_err use_recon_player1(enum recon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct recon* r = get_recon_player1(id);
    if(r->remaining_uses == 0) return ERR_NO_OBJECT;
    enum placement_err ret = detect_ship(player2_board, &r->recon_pattern, pos_row, pos_col);
    if(ret == ERR_NONE) r->remaining_uses -= 1;
    return ret;
}

enum placement_err use_recon_player2(enum recon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct recon* r = get_recon_player2(id);
    if(r->remaining_uses == 0) return ERR_NO_OBJECT;
    enum placement_err ret = detect_ship(player1_board, &r->recon_pattern, pos_row, pos_col);
    if(ret == ERR_NONE) r->remaining_uses -= 1;
    return ret;
}

enum placement_err can_use_recon_player1(enum recon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct recon* r = get_recon_player1(id);
    if(r->remaining_uses == 0) return ERR_NO_OBJECT;
    return can_detect_ship(player2_board, &r->recon_pattern, pos_row, pos_col);
}

enum placement_err can_use_recon_player2(enum recon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct recon* r = get_recon_player2(id);
    if(r->remaining_uses == 0) return ERR_NO_OBJECT;
    return can_detect_ship(player1_board, &r->recon_pattern, pos_row, pos_col);
}

enum weapon_id iterate_weapon_player1(enum weapon_id current_weapon)
{
    current_weapon += 1;
    for(; current_weapon < NO_WEAPON; current_weapon += 1) {
        if(get_weapon_player1(current_weapon)->remaining_uses > 0) return current_weapon;
    }
    return NO_WEAPON;
}

enum weapon_id iterate_weapon_player2(enum weapon_id current_weapon)
{
    current_weapon += 1;
    for(; current_weapon < NO_WEAPON; current_weapon += 1) {
        if(get_weapon_player2(current_weapon)->remaining_uses > 0) return current_weapon;
    }
    return NO_WEAPON;
}

enum recon_id iterate_recon_player1(enum recon_id current_recon)
{
	current_recon = current_recon == NO_RECON ? SONAR : current_recon + 1;
    for(; current_recon < NO_RECON; current_recon += 1) {
        if(get_recon_player1(current_recon)->remaining_uses > 0) return current_recon;
    }
    return NO_RECON;
}

enum recon_id iterate_recon_player2(enum recon_id current_recon)
{
	current_recon = current_recon == NO_RECON ? SONAR : current_recon + 1;
    for(; current_recon < NO_RECON; current_recon += 1) {
        if(get_recon_player2(current_recon)->remaining_uses > 0) return current_recon;
    }
    return NO_RECON;
}

// weapon_target is the aiming reticle that you move around
void draw_weapon_target_player1(enum weapon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct board_pattern* firing_pattern = &(get_weapon_player1(id)->firing_pattern);
    for(int i = 0; i < firing_pattern->len; i++) {
        uint8_t r = firing_pattern->row_offsets[i] + pos_row;
        uint8_t c = firing_pattern->col_offsets[i] + pos_col;
        uint16_t x,y;
        board_to_pixel(r, c, &x, &y);
        DRAW(P1_TARGET, x, y);
    }
}

void draw_weapon_target_player2(enum weapon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct board_pattern* firing_pattern = &(get_weapon_player2(id)->firing_pattern);
    for(int i = 0; i < firing_pattern->len; i++) {
        uint8_t r = firing_pattern->row_offsets[i] + pos_row;
        uint8_t c = firing_pattern->col_offsets[i] + pos_col;
        uint16_t x,y;
        board_to_pixel(r, c, &x, &y);
        DRAW(P2_TARGET, x, y);
    }
}

// recon_target is the aiming radar that you move around
void draw_recon_target_player1(enum recon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct board_pattern* recon_pattern = &(get_recon_player1(id)->recon_pattern);
    for(int i = 0; i < recon_pattern->len; i++) {
        uint8_t r = recon_pattern->row_offsets[i] + pos_row;
        uint8_t c = recon_pattern->col_offsets[i] + pos_col;
        uint16_t x,y;
        board_to_pixel(r, c, &x, &y);
        DRAW(RECON_A, x, y);
    }
}

void draw_recon_target_player2(enum recon_id id, uint8_t pos_row, uint8_t pos_col)
{
    struct board_pattern* recon_pattern = &(get_recon_player2(id)->recon_pattern);
    for(int i = 0; i < recon_pattern->len; i++) {
        uint8_t r = recon_pattern->row_offsets[i] + pos_row;
        uint8_t c = recon_pattern->col_offsets[i] + pos_col;
        uint16_t x,y;
        board_to_pixel(r, c, &x, &y);
        DRAW(RECON_A, x, y);
    }
}

