#ifndef MAKE_ME_LAUGH_PLAYER_INPUT_H
#define MAKE_ME_LAUGH_PLAYER_INPUT_H

#include <genesis.h>

typedef struct {
    bool is_moving;
    Vect2D_f16 moving;
} PlayerInput;

PlayerInput PlayerInput_get(u8 player_id);

#endif //MAKE_ME_LAUGH_PLAYER_INPUT_H
