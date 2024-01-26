#include "entity.h"
#include "gamemath.h"
#include "maths.h"


void Entity_translate(V2f16 *const position, const V2f16 *const translation) {
    // TODO: should we use deltatime?
    const f16 dt = f16s_1;
    const V2f16 delta = v2_scale(translation, dt);
    *position = v2_add(position, &delta);
}

Box Entity_bounding_box(const V2f16 *const position, const V2u16 size) {
    return (Box) {
        .x = position->x,
        .y = position->y,
        .w = size.x,
        .h = size.y,
    };
}

void Entity_draw(const Box *const bb, const u16 color) {
    PAL_setColor(1, color);
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 1), bb->x, bb->y, bb->w, bb->h);

    PAL_setColor(2, RGB24_TO_VDPCOLOR(0xFFFFFF));
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), bb->x, bb->y, 2, 2);
}
