#ifndef MAKE_ME_LAUGH_PLAYER_H
#define MAKE_ME_LAUGH_PLAYER_H

#include <genesis.h>

typedef struct {
    Sprite *sprite;
    V2f16 position;
    V2f16 velocity;
    u8 entity_id;
} Player;

extern const f16 PLAYER_SPEED;

void Player_boundaries(Player *ball);
Player Player_init(u8 player_id, V2f16 pos);
void Player_apply_gravity(Player *player);
void Player_update(Player *player);
V2f16 Player_get_center(const Player *player);
void Player_draw(const Player *player);

#endif //MAKE_ME_LAUGH_PLAYER_H
