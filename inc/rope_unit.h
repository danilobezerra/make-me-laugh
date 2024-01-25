#ifndef MAKE_ME_LAUGH_ROPE_UNIT_H
#define MAKE_ME_LAUGH_ROPE_UNIT_H

#include "entity.h"

typedef struct {
    Entity entity;
} RopeUnit;

void RopeUnit_draw(RopeUnit* rope_unit);
void RopeUnit_update(RopeUnit* rope_unit, Vect2D_f16 origin, Vect2D_f16 ending, float i);

#endif //MAKE_ME_LAUGH_ROPE_UNIT_H
