#ifndef MAKE_ME_LAUGH_BALL_H
#define MAKE_ME_LAUGH_BALL_H

#include <genesis.h>
#include "entity.h"
#include "rope.h"

typedef struct {
    Entity entity;
    Vect2D_f16 velocity;
} Ball;

Ball Ball_init(Vect2D_f16 position);
void Ball_apply_gravity(Ball* ball, Rope* rope);
void Ball_update(Ball* ball, Rope* rope);
void Ball_draw(Ball* ball);

#endif //MAKE_ME_LAUGH_BALL_H
