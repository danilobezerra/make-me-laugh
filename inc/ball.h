#ifndef MAKE_ME_LAUGH_BALL_H
#define MAKE_ME_LAUGH_BALL_H

#include <genesis.h>

typedef struct {
    V2f16 position;
    V2f16 velocity;
} Ball;

Ball Ball_init(V2f16 pos);
bool Ball_boundaries(Ball *ball);
void Ball_apply_gravity(Ball *ball);
bool Ball_update(Ball *ball, const V2f16 *p1, const V2f16 *p2);
void Ball_draw(const Ball *ball);

#endif //MAKE_ME_LAUGH_BALL_H
