#ifndef MAKE_ME_LAUGH_PLAYER_H
#define MAKE_ME_LAUGH_PLAYER_H

#include <genesis.h>
#include "entity.h"
#include "global.h"

typedef struct {
    Entity entity;
    u8 entity_id;
} Player;

Player Player_init(u8 player_id, Vect2D_f16 position);
void Player_update(Player* player);
void Player_draw(Player* player);

#endif //MAKE_ME_LAUGH_PLAYER_H
