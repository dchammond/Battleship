#ifndef _WEAPONS_H_
#define _WEAPONS_H_

#include "stdint_fix.h"
#include "board.h"

enum weapon_id {
    RIM_66 = 0,
    MK_48X = 1,
    POLARIS = 2,
    ASROC_71 = 3,
    SEADART = 4,
    TOMAHAWK_55M = 5,
    HARPOON_55M = 6,
    P3_ORION = 7,
    TALOS = 8,
    NO_WEAPON = 9
};

enum recon_id {
    SONAR = 0,
    AERIAL = 1,
    NO_RECON = 2
};

struct weapon {
    struct board_pattern firing_pattern;
    uint8_t id;
    uint8_t remaining_uses;
};

struct recon {
    struct board_pattern recon_pattern;
    uint8_t id;
    uint8_t remaining_uses;
};

struct weapon* get_weapon_player1(enum weapon_id id);
struct weapon* get_weapon_player2(enum weapon_id id);
struct recon* get_recon_player1(enum recon_id id);
struct recon* get_recon_player2(enum recon_id id);

// fire a weapon
enum placement_err fire_weapon_player1(enum weapon_id id, uint8_t pos_row, uint8_t pos_col);
enum placement_err fire_weapon_player2(enum weapon_id id, uint8_t pos_row, uint8_t pos_col);
// check if we can fire a weapon
enum placement_err can_fire_weapon_player1(enum weapon_id id, uint8_t pos_row, uint8_t pos_col);
enum placement_err can_fire_weapon_player2(enum weapon_id id, uint8_t pos_row, uint8_t pos_col);
// use a recon
enum placement_err use_recon_player1(enum recon_id id, uint8_t pos_row, uint8_t pos_col);
enum placement_err use_recon_player2(enum recon_id id, uint8_t pos_row, uint8_t pos_col);
// check if we can use a recon
enum placement_err can_use_recon_player1(enum recon_id id, uint8_t pos_row, uint8_t pos_col);
enum placement_err can_use_recon_player2(enum recon_id id, uint8_t pos_row, uint8_t pos_col);

// helpful functions to "iterate" to a weapon/recon enum that has available usages
enum weapon_id iterate_weapon_player1(enum weapon_id current_weapon);
enum weapon_id iterate_weapon_player2(enum weapon_id current_weapon);
enum recon_id iterate_recon_player1(enum recon_id current_recon);
enum recon_id iterate_recon_player2(enum recon_id current_recon);

void draw_weapon_target_player1(enum weapon_id id, uint8_t pos_row, uint8_t pos_col);
void draw_weapon_target_player2(enum weapon_id id, uint8_t pos_row, uint8_t pos_col);
void draw_recon_target_player1(enum recon_id id, uint8_t pos_row, uint8_t pos_col);
void draw_recon_target_player2(enum recon_id id, uint8_t pos_row, uint8_t pos_col);

/* For now, to reset the weapons: redeploy the NIOS
void clear_all_weapons(void);
void clear_all_recons(void);
*/

#endif
