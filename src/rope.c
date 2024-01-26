#include "rope.h"
#include "gamemath.h"
#include "global.h"
#include "maths.h"

void Rope_draw(const V2f16 *const p1, const V2f16 *const p2) {
    const f16 len = FIX16(ROPE_LENGTH);
    const f16 lenm1 = len - 1; // m1: minus 1

    PAL_setColor(2, RGB24_TO_VDPCOLOR(0xFFFFFF));

    for (f16 i = 0; i < len; ++i) {
        const V2f16 p = v2_lerp(p1, p2, fix16Div(i, lenm1));
        VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), p.x, p.y, 2, 2);
    }
}
