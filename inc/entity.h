#ifndef MAKE_ME_LAUGH_ENTITY_H
#define MAKE_ME_LAUGH_ENTITY_H

#include <genesis.h>

void Entity_translate(Vect2D_f16 *position, Vect2D_f16 translation);
Box Entity_bounding_box(const Vect2D_f16 *position, Vect2D_f16 size);
void Entity_draw(Box bb, u16 color);

#endif //MAKE_ME_LAUGH_ENTITY_H
