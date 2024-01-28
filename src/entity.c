#include "entity.h"
#include "gamemath.h"
#include "maths.h"

void Entity_translate(V2f16 *const position, const V2f16 *const translation) {
    *position = v2_add(position, translation);
}

void Entity_accelerate_x(V2f16 *const velocity, f16 acc, f16 max_speed) {
    velocity->x = clamp(velocity->x + acc, -max_speed, max_speed);
}

void Entity_accelerate_y(V2f16 *const velocity, f16 acc, f16 max_speed) {
    velocity->y = clamp(velocity->y + acc, -max_speed, max_speed);
}

void Entity_apply_gravity(V2f16 *const velocity, f16 grav_acc, f16 max_speed) {
    Entity_accelerate_y(velocity, grav_acc, max_speed);
}

void Entity_clamp_pos(V2f16 *const pos, const V2f16 *const posmin, const V2f16 *const posmax) {
    *pos = (V2f16){
        .x = clamp(pos->x, posmin->x, posmax->x),
        .y = clamp(pos->y, posmin->y, posmax->y),
    };
}

void Entity_draw(const V2f16 *const position, Sprite *sprite) {
    s16 x = fix16ToRoundedInt(position->x);
    s16 y = fix16ToRoundedInt(position->y);

    SPR_setPosition(sprite, x, y);
}
