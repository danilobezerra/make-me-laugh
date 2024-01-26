#include "game.h"
#include <genesis.h>
#include "player.h"
#include "rope.h"
#include "ball.h"
#include "vdp.h"

void Game_init(Game *game) {
    JOY_init();
    VDP_init();
    SPR_init();

    game->isRunning = TRUE;
}

void Game_setup(Game *game) {
    game->ball = Ball_init((V2f16) { .x = FIX16(6.0), .y = FIX16(6.0) });
    game->players[0] = Player_init(0, (V2f16) { .x = FIX16(2.5), .y = FIX16(5.0) });
    game->players[1] = Player_init(1, (V2f16) { .x = FIX16(4.5), .y = FIX16(5.0) });
}

void Game_run(Game *game) {
    Game_setup(game);

    while (game->isRunning) {
        Game_update(game);
        Game_draw(game);
    }
}

void Game_update(Game *game) {
    for (int i = 0; i < PLAYER_COUNT; ++i) {
        Player_update(&game->players[i]);
    }
    game->p0_center = Player_get_center(&game->players[0]);
    game->p1_center = Player_get_center(&game->players[1]);

    Ball_update(&game->ball, &game->p0_center, &game->p1_center);
}

void Game_draw(Game *game) {
    VDP_clearPlane(BG_A, TRUE);
    VDP_clearPlane(BG_B, TRUE);

    for (int i = 0; i < PLAYER_COUNT; i++) {
        Player_draw(&game->players[i]);
    }

    Rope_draw(&game->p0_center, &game->p1_center);
    Ball_draw(&game->ball);

    VDP_waitVBlank(true);
    SYS_doVBlankProcess();
}
