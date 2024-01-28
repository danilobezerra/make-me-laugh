#ifndef MAKE_ME_LAUGH_ROPE_H
#define MAKE_ME_LAUGH_ROPE_H

#include <genesis.h>
#include "global.h"
#include "player.h"

typedef struct {
    Sprite *sprite;
} RopeUnit;

typedef struct {
    RopeUnit units[ROPE_LENGTH];
} Rope;

Rope Rope_init(V2f16 pos);
void Rope_draw(const Rope *rope, const V2f16 *p1, const V2f16 *p2);
void Rope_update(Player *p1, Player *p2);

#endif //MAKE_ME_LAUGH_ROPE_H
