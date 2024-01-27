#include "game.h"
#include <genesis.h>
#include <resources.h>
#include "player.h"
#include "rope.h"
#include "ball.h"
#include "tools.h"

u16 main_palette[64];
u16 user_index;

V2f16 p0_center;
V2f16 p1_center;

void Game_init(Game *game) {
    JOY_init();
    SPR_init();

    game->is_running = TRUE;
}

void Game_setup(Game *game) {
    PAL_setColors(0, palette_black, 64, DMA);
    user_index = TILE_USER_INDEX;

    game->current_state = STATE_SPLASH;
}

void Game_run(Game *game) {
    Game_setup(game);

    while (game->is_running) {
        Game_update(game);
        Game_draw(game);

        SPR_update();
        SYS_doVBlankProcess();
    }
}

void Game_update(Game *game) {
    kprintf(":: GAME UPDATE ::");
    switch (game->current_state) {
        case STATE_SPLASH:
            game->ball = Ball_init((V2f16) { .x = FIX16(6.0), .y = FIX16(6.0) });
            game->players[0] = Player_init(0, (V2f16) { .x = FIX16(2.5), .y = FIX16(5.0) });
            game->players[1] = Player_init(1, (V2f16) { .x = FIX16(4.5), .y = FIX16(5.0) });

            break;
        case STATE_MAIN_MENU:
            break;
        case STATE_GAMEPLAY:
            for (int i = 0; i < PLAYER_COUNT; ++i) {
                kprintf("-- PLAYER %d --", i);
                Player_update(&game->players[i]);
            }

            p0_center = Player_get_center(&game->players[0]);
            p1_center = Player_get_center(&game->players[1]);

            kprintf("-- BALL --");
            Ball_update(&game->ball, &p0_center, &p1_center);

            break;
    }
}

void Game_draw(Game *game) {
    kprintf(":: GAME DRAW ::");

    VDP_clearPlane(BG_A, TRUE);
    DMA_waitCompletion();

    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    switch (game->current_state) {
        case STATE_SPLASH:
            VDP_drawImageEx(BG_B, &splash, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, user_index), 0, 0, FALSE, TRUE);
            user_index += splash.tileset->numTile;

            memcpy(&main_palette[0], splash.palette->data, 32);

            PAL_fadeIn(0, 63, main_palette, 30, FALSE);
            waitTick(TICKPERSECOND * 3);
            PAL_fadeOutAll(30, FALSE);

            game->current_state = STATE_GAMEPLAY;
            break;
        case STATE_MAIN_MENU:
            break;
        case STATE_GAMEPLAY:
            for (int i = 0; i < PLAYER_COUNT; i++) {
                kprintf("-- PLAYER %d--", i);
                Player_draw(&game->players[i]);
            }

            kprintf("-- ROPE -- ");
            Rope_draw(&p0_center, &p1_center);
            kprintf("-- BALL -- ");
            Ball_draw(&game->ball);

            break;
    }
}
