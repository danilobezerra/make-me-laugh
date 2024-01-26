#ifndef MAKE_ME_LAUGH_GAME_H
#define MAKE_ME_LAUGH_GAME_H

#include <genesis.h>
#include "player.h"
#include "ball.h"

typedef struct {
    bool isRunning;

    Player players[PLAYER_COUNT];
    Ball ball;

    V2f16 p0_center;
    V2f16 p1_center;
} Game;

void Game_init(Game *game);
void Game_setup(Game *game);
void Game_run(Game *game);
void Game_update(Game *game);
void Game_draw(Game *game);

#endif //MAKE_ME_LAUGH_GAME_H
