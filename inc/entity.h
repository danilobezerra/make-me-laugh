#ifndef MAKE_ME_LAUGH_ENTITY_H
#define MAKE_ME_LAUGH_ENTITY_H

#include <genesis.h>

void Entity_translate(V2f16 *position, const V2f16 *translation);
void Entity_clamp_pos(V2f16 *pos, const V2f16 *posmin, const V2f16 *posmax);
Box Entity_bounding_box(const V2f16 *position, V2u16 size);
void Entity_draw(const Box *bb, u16 color);

#endif //MAKE_ME_LAUGH_ENTITY_H
