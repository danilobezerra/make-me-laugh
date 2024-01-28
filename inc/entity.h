#ifndef MAKE_ME_LAUGH_ENTITY_H
#define MAKE_ME_LAUGH_ENTITY_H

#include <genesis.h>

void Entity_translate(V2f16 *position, const V2f16 *translation);
void Entity_clamp_pos(V2f16 *pos, const V2f16 *posmin, const V2f16 *posmax);
void Entity_accelerate_x(V2f16 *velocity, f16 acc, f16 max_acc);
void Entity_accelerate_y(V2f16 *velocity, f16 acc, f16 max_acc);
void Entity_apply_gravity(V2f16 *velocity, f16 grav_acc, f16 max_speed);
void Entity_draw(const V2f16 *position, Sprite *sprite);

#endif //MAKE_ME_LAUGH_ENTITY_H
