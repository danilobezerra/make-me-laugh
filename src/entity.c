#include "entity.h"

void Entity_translate(Vect2D_f16 *const position, Vect2D_f16 translation) {
//    *position = nene_Vec2_add(
//        *position,
//        nene_Vec2_scale(translation, nene_Core_get_delta_time())
//    );
}

Box Entity_bounding_box(const Vect2D_f16 *const position, const Vect2D_f16 size) {
//    return (nene_Rectf){
//            .pos = *position,
//            .size = size,
//    };
    return (Box) {};
}

void Entity_draw(const Box bb, u16 color) {
//    nene_Core_render_draw_rect(
//            nene_Rectf_to_rect(bb),
//            false,
//            color,
//            false
//    );
    PAL_setColor(1, color);
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 1), bb.x, bb.y, bb.w, bb.h);

//    nene_Core_render_draw_rect(
//            (nene_Rect){ .pos = nene_Vec2_to_vec2i(bb.pos), .size = {.x = 2, .y = 2 } },
//            false,
//            nene_Color_white(),
//            false
//    );
    PAL_setColor(2, RGB24_TO_VDPCOLOR(0xFFFFFF));
    VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), bb.x, bb.y, 2, 2);
}