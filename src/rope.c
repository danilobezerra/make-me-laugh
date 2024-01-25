#include "rope.h"
#include "global.h"

void Rope_draw(const V2f16 *const p1, const V2f16 *const p2) {
    const fix16 len = (fix16) ROPE_LENGTH;
    const V2s16 size = { .x = 2, .y = 2 };

    for (fix16 i = 0; i < ROPE_LENGTH; ++i) {
        // TODO: Render Draw Rect
    }
}