//
// Created by Danilo Bezerra on 23/01/24.
//

#ifndef MAKE_ME_LAUGH_ROPE_H
#define MAKE_ME_LAUGH_ROPE_H

#include "global.h"
#include "entity.h"
#include "rope_unit.h"

typedef struct {
    RopeUnit units[ROPE_LENGTH];
} Rope;

void Rope_init(Rope* rope);
void Rope_update(Rope* rope, Vect2D_f16 player1_pos, Vect2D_f16 player2_pos);
void Rope_draw(Rope* rope);
void Rope_get_segment(Rope* rope);

#endif //MAKE_ME_LAUGH_ROPE_H
