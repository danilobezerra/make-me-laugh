#include "rope.h"
#include "gamemath.h"
#include "global.h"
#include "maths.h"

void Rope_draw(const V2f16 *const p1, const V2f16 *const p2) {
    const f16 len = FIX16(ROPE_LENGTH);
    const f16 lenm1 = len - 1; // m1: minus 1

    PAL_setColor(2, RGB24_TO_VDPCOLOR(0xFFFFFF));

    for (int i = 0; i < ROPE_LENGTH; ++i) {
        V2f16 p = v2_lerp(p1, p2, fix16Div(intToFix16(i), lenm1));
        p.x = fix16Div(p.x, f16s_16);
        p.y = fix16Div(p.y, f16s_16);
        s16 px = fix16ToRoundedInt(p.x);
        s16 py = fix16ToRoundedInt(p.y);
        VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), px, py, 1, 1);
    }
}
