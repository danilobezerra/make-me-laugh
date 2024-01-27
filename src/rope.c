#include "rope.h"
#include "resources.h"
#include "gamemath.h"
#include "global.h"
#include "maths.h"

Rope Rope_init(V2f16 pos) {
    Rope rope;

    for (int i = 0; i < ROPE_LENGTH; ++i) {
        rope.units[i].sprite = SPR_addSprite(&rope_sprite, pos.x, pos.y, TILE_ATTR(ROPE_PALETTE, FALSE, FALSE, FALSE));
    }

    PAL_setPalette(ROPE_PALETTE, rope_sprite.palette->data, DMA);
    return rope;
}

void Rope_draw(const Rope *const rope, const V2f16 *const p1, const V2f16 *const p2) {
    const f16 len = FIX16(ROPE_LENGTH);
    const f16 lenm1 = len - f16s_1; // m1: minus 1

    //PAL_setColor(2, RGB24_TO_VDPCOLOR(0xFFFFFF));

    // kprintf("rope draw p1: %hd %hd", fix16ToInt(p1->x), fix16ToInt(p1->y));
    // kprintf("rope draw p2: %hd %hd", fix16ToInt(p2->x), fix16ToInt(p2->y));

    for (int i = 0; i < ROPE_LENGTH; ++i) {
        const f16 t = fix16Div(intToFix16(i), lenm1);
        V2f16 p = v2_lerp(p1, p2, t);
        s16 px = fix16ToRoundedInt(p.x);
        s16 py = fix16ToRoundedInt(p.y);
        // kprintf("rope draw: %d %hd %hd %hd %hd.%hd",
        //     i,
        //     fix16ToInt(p.x),
        //     fix16ToInt(p.y),
        //     fix16ToInt(fix16Mul(t, FIX16(10.0))),
        //     fix16ToInt(fix16Int(t)),
        //     fix16ToInt(fix16Mul(fix16Frac(t), FIX16(100)))
        // );
        // VDP_fillTileMapRect(BG_A, TILE_ATTR_FULL(PAL0, 0, FALSE, FALSE, 2), px, py, 1, 1);

        SPR_setPosition(rope->units[i].sprite, px, py);
    }
}
