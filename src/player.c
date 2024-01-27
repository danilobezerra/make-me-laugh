#include "gamemath.h"
#include "player.h"
#include "global.h"

Player Player_init(u8 player_id, V2f16 pos) {
    return (Player) {
        .position = pos,
        .entity_id = player_id,
    };
}

void Player_update(Player *const player) {
    u16 player_input = JOY_readJoypad(player->entity_id == 0 ? JOY_1 : JOY_2);

    if (player_input != 0) {
        V2f16 movement = { .x = f16s_0, .y = f16s_0 };

        if ((player_input & BUTTON_LEFT) != 0) {
            movement.x = -PLAYER_SPEED;
        }
        else if ((player_input & BUTTON_RIGHT) != 0) {
            movement.x = PLAYER_SPEED;
        }
        if ((player_input & BUTTON_UP) != 0) {
            movement.y = -PLAYER_SPEED;
        }
        else if ((player_input & BUTTON_DOWN) != 0) {
            movement.y = PLAYER_SPEED;
        }

        Entity_translate(&player->position, &movement);
    }
}

V2f16 Player_get_center(const Player *const player) {
    return (V2f16) {
        .x = player->position.x + f16s_4,
        .y = player->position.y + f16s_4,
    };
}

void Player_draw(const Player *const player) {
    const Box player_bb = Entity_bounding_box(&player->position, (V2u16){.x = 1, .y = 1 });
    Entity_draw(&player_bb, player->entity_id == 0 ? RGB24_TO_VDPCOLOR(0xFF0000) : RGB24_TO_VDPCOLOR(0x0000FF));
}
