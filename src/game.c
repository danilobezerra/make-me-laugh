#include "game.h"
#include <genesis.h>
#include "resources.h"
#include "player.h"
#include "rope.h"
#include "ball.h"
#include "tools.h"
#include <string.h>

u16 main_palette[64];
u16 user_index;
char str_score[4] = "0";

V2f16 p0_center;
V2f16 p1_center;

Map* bga;

void Game_init(Game *game) {
    JOY_init();
    SPR_init();

    game->is_running = TRUE;
}

void Game_setup(Game *game) {
    PAL_setColors(PAL0, palette_black, 64, DMA);
    user_index = TILE_USER_INDEX;

    VDP_drawImageEx(BG_B, &splash, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, user_index), 0, 0, FALSE, TRUE);
    user_index += splash.tileset->numTile;

    memcpy(&main_palette[0], splash.palette->data, 32);

    PAL_fadeIn(0, 63, main_palette, 30, FALSE);
    waitTick(TICKPERSECOND * 3);
    PAL_fadeOutAll(30, FALSE);

    game->current_state = STATE_MAIN_MENU;



    VDP_clearPlane(BG_B, TRUE);
    DMA_waitCompletion();

    waitTick(TICKPERSECOND);

    VDP_drawText("     Rope We Communicate     ", 5, 1);
    VDP_drawText("   Press START to Continue   ", 5, 14);
    VDP_drawText("Programming by Danilo & Andre", 5, 26);

    PAL_fadeIn(0, 63, main_palette, 60, FALSE);
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
    u16 p1_joypad_value = JOY_readJoypad(JOY_1);
    u16 p2_joypad_value = JOY_readJoypad(JOY_2);

    switch (game->current_state) {
        case STATE_MAIN_MENU:
            if ((p1_joypad_value & BUTTON_START) || (p2_joypad_value & BUTTON_START)) {
                VDP_clearPlane(BG_A, TRUE);
                DMA_waitCompletion();

                VDP_clearPlane(BG_B, TRUE);
                DMA_waitCompletion();

                game->current_state = STATE_GAMEPLAY;
                game->is_game_over = FALSE;
                game->score = 0;

                game->ball = Ball_init((V2f16) { .x = FIX16(150.0), .y = FIX16(10.0) });
                game->players[0] = Player_init(0, (V2f16) { .x = FIX16(120.0), .y = FIX16(150.0) });
                game->players[1] = Player_init(1, (V2f16) { .x = FIX16(180.0), .y = FIX16(150.0) });
                game->rope = Rope_init((V2f16) { .x = FIX16(6.0), .y = FIX16(6.0) });

                XGM_startPlay(music);
            }

            break;
        case STATE_GAMEPLAY:
            if (game->is_game_over) {
                if ((p1_joypad_value & BUTTON_START) || (p2_joypad_value & BUTTON_START)) {
                    SYS_reset();
                }

                return;
            }

            for (int i = 0; i < PLAYER_COUNT; ++i) {
                Player_update(&game->players[i]);
            }

            p0_center = Player_get_center(&game->players[0]);
            p1_center = Player_get_center(&game->players[1]);

            Rope_update(&game->players[0], &game->players[1]);

            u8 ball_hit = Ball_update(&game->ball, &p0_center, &p1_center);

            if (ball_hit & BALL_HIT_ROPE) {
                game->score++;
            }

            if (ball_hit & BALL_HIT_FLOOR) {
                game->is_game_over = TRUE;

                if (XGM_isPlaying()) {
                    XGM_stopPlay();
                }
            }

            break;
    }
}

void Game_draw(Game *game) {
    switch (game->current_state) {
        case STATE_MAIN_MENU:
            break;
        case STATE_GAMEPLAY:
            if (game->is_game_over) {
                VDP_drawText("          GAME OVER          ", 5, 11);
                VDP_drawText("   Thank You For Playing!!   ", 5, 13);
                VDP_drawText(" GGJ 2024 - Baixada Santista ", 5, 15);

                return;
            }

            for (int i = 0; i < PLAYER_COUNT; i++) {
                // kprintf("-- PLAYER %d--", i);
                Player_draw(&game->players[i]);
            }

            // kprintf("-- ROPE -- ");
            Rope_draw(&game->rope, &p0_center, &p1_center);
            Ball_draw(&game->ball);

            sprintf(str_score,"SCORE: %03d", game->score);
            VDP_clearText(15, 1, 10);
            VDP_drawText(str_score, 15, 1);

            break;
    }
}
