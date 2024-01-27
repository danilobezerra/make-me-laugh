#include "player.h"
#include "resources.h"
#include "global.h"
#include "entity.h"
#include "gamemath.h"

const f16 PLAYER_SPEED = FIX16(0.04);

Player Player_init(u8 player_id, V2f16 pos) {
    Sprite *playerSprite = SPR_addSprite(&player_sprite, pos.x, pos.y, TILE_ATTR(PLAYER_PALETTE, FALSE, FALSE, FALSE));
    PAL_setPalette(PLAYER_PALETTE, player_sprite.palette->data, DMA);

    return (Player) {
        .sprite = playerSprite,
        .position = pos,
        .velocity = { .x = f16s_0, .y = f16s_0 },
        .entity_id = player_id,
    };
}

void Player_apply_gravity(Player *const player) {
    Entity_apply_gravity(&player->velocity, FIX16(0.02), f16s_16);
}

void Player_boundaries(Player *const player) {
    // TODO: abstract over Entity boundaries
    Entity_clamp_pos(
        &player->position,
        &screen_clamp_min,
        &screen_clamp_max
    );

    if (player->position.x <= screen_clamp_min.x || player->position.x >= screen_clamp_max.x) {
        player->velocity.x = f16s_0;
    }
    if (player->position.y <= screen_clamp_min.y || player->position.y >= screen_clamp_max.y) {
        player->velocity.y = f16s_0;
    }
}


void Player_update(Player *const player) {
    u16 player_input = JOY_readJoypad(player->entity_id == 0 ? JOY_1 : JOY_2);
    Player_apply_gravity(player);

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

        Entity_accelerate_x(&player->velocity, movement.x, f16s_16);
        Entity_accelerate_y(&player->velocity, movement.y, f16s_16);
    }

    Entity_translate(&player->position, &player->velocity);
    Player_boundaries(player);

    // kprintf("final player pos: %hd.%hd %hd.%hd vel: %hd.%hd %hd.%hd",
    //     fix16ToInt(fix16Int(player->position.x)), fix16ToInt(fix16Mul(fix16Frac(player->position.x), FIX16(100.0))),
    //     fix16ToInt(fix16Int(player->position.y)), fix16ToInt(fix16Mul(fix16Frac(player->position.y), FIX16(100.0))),
    //     fix16ToInt(fix16Int(player->velocity.x)), fix16ToInt(fix16Mul(fix16Frac(player->velocity.x), FIX16(100.0))),
    //     fix16ToInt(fix16Int(player->velocity.y)), fix16ToInt(fix16Mul(fix16Frac(player->velocity.y), FIX16(100.0)))
    // );
}

V2f16 Player_get_center(const Player *const player) {
    return (V2f16) {
        .x = player->position.x + f16s_4,
        .y = player->position.y + f16s_4,
    };
}

void Player_draw(const Player *const player) {
    const Box player_bb = Entity_bounding_box(&player->position, (V2u16){ .x = 1, .y = 1 });
    // kprintf("player draw pos %hd %hd", player_bb.x, player_bb.y);

    SPR_setPosition(player->sprite, player_bb.x, player_bb.y);
    Entity_draw(&player_bb, player->entity_id == 0 ? RGB24_TO_VDPCOLOR(0xFF0000) : RGB24_TO_VDPCOLOR(0x0000FF));
}
