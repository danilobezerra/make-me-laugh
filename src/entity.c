#include "entity.h"
#include "gamemath.h"
#include "maths.h"


void Entity_translate(V2f16 *const position, const V2f16 *const translation) {
    *position = v2_add(position, translation);
}

void Entity_clamp_pos(V2f16 *const pos, const V2f16 *const posmin, const V2f16 *const posmax) {
    *pos = (V2f16){
        .x = clamp(pos->x, posmin->x, posmax->x),
        .y = clamp(pos->y, posmin->y, posmax->y),
    };
}

Box Entity_bounding_box(const V2f16 *const position, const V2u16 size) {
    return (Box) {
        .x = fix16ToRoundedInt(position->x),
        .y = fix16ToRoundedInt(position->y),
        .w = size.x,
        .h = size.y,
    };
}

void Entity_draw(const Box *const bb, const u16 color) {
    f16 px = fix16Div(bb->x, f16s_16);
    f16 py = fix16Div(bb->y, f16s_16);
    s16 x = fix16ToRoundedInt(px);
    s16 y = fix16ToRoundedInt(py);

    PAL_setColor(1, color);
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 1), x, y, 1, 1);

    PAL_setColor(2, RGB24_TO_VDPCOLOR(0xFFFFFF));
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), x, y, 1, 1);
}
