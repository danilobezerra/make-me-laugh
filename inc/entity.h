//
// Created by Danilo Bezerra on 23/01/24.
//

#ifndef MAKE_ME_LAUGH_ENTITY_H
#define MAKE_ME_LAUGH_ENTITY_H

#include <genesis.h>

typedef struct {
    Vect2D_f16 position;
    Sprite sprite;
    Vect2D_f16 size;
} Entity;

Entity Entity_init(Vect2D_f16 position, Sprite sprite, Vect2D_f16 size);
void Entity_translate(Entity* entity, Vect2D_f16 translation);
Box Entity_bounding_box(Entity* entity);
void Entity_draw(Entity* entity);

#endif //MAKE_ME_LAUGH_ENTITY_H
