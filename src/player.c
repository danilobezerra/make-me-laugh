#include "player.h"
#include "player_input.h"
#include "global.h"

Player Player_init(u8 player_id, Vect2D_f16 pos) {
    return (Player) {
        .position = pos,
        .entity_id = player_id,
    };
}

void Player_update(Player *const player) {
    u8 player_input = PlayerInput_get(player->entity_id);

    if (player_input != 0) {
        V2f16 movement = { .x = FIX16(0.0), .y = FIX16(0.0) };

        if ((player_input & PlayerInput_LEFT) != 0) {
            movement.x = -PLAYER_SPEED;
        }
        else if ((player_input & PlayerInput_RIGHT) != 0) {
            movement.x = PLAYER_SPEED;
        }
        if ((player_input & PlayerInput_UP) != 0) {
            movement.y = -PLAYER_SPEED;
        }
        else if ((player_input & PlayerInput_DOWN) != 0) {
            movement.y = PLAYER_SPEED;
        }

        Entity_translate(&player->position, movement);
    }
}

Vect2D_f16 Player_get_center(const Player *const player) {

}

void Player_draw(const Player *const player) {

}