#include "game.h"

#include <genesis.h>

void Game_init(Game *game) {
    JOY_init();
    VDP_init();
    SPR_init();

    game->isRunning = TRUE;
}

void Game_setup(Game *game) {

}

void Game_run(Game *game) {
    Game_setup(game);

    while (game->isRunning) {
        Game_handle_input(game);

        Game_update(game);
        Game_draw(game);
    }
}

void Game_handle_input(Game *game) {

}

void Game_update(Game *game) {

}

void Game_draw(Game *game) {
    SYS_doVBlankProcess();
}