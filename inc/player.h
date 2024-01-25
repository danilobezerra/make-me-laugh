#ifndef MAKE_ME_LAUGH_PLAYER_H
#define MAKE_ME_LAUGH_PLAYER_H

#include <genesis.h>
#include "entity.h"
#include "global.h"

typedef struct {
    V2f16 position;
    u8 entity_id;
} Player;

Player Player_init(u8 player_id, Vect2D_f16 pos);
void Player_update(Player *player);
Vect2D_f16 Player_get_center(const Player *player);
void Player_draw(const Player *player);

#endif //MAKE_ME_LAUGH_PLAYER_H
