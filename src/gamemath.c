#include "gamemath.h"
#include "maths.h"

const f16 f16s_0 = FIX16(0.0);
const f16 f16s_1 = FIX16(1.0);
const f16 f16s_16 = FIX16(16.0);
const f16 f16s_32 = FIX16(32.0);

V2f16 v2_add(const V2f16 *const a, const V2f16 *const b) {
    return (V2f16){
        .x = a->x + b->x,
        .y = a->y + b->y,
    };
}

V2f16 v2_sub(const V2f16 *const a, const V2f16 *const b) {
    return (V2f16){
        .x = a->x - b->x,
        .y = a->y - b->y,
    };
}

f16 v2_cross(const V2f16 *const a, const V2f16 *const b) {
    return fix16Mul(a->x, b->y) - fix16Mul(a->y, b->x);
}

f16 v2_dot(const V2f16 *const a, const V2f16 *const b) {
    return fix16Mul(a->x, b->x) + fix16Mul(a->y, b->y);
}

V2f16 v2_scale(const V2f16 *const a, const f16 s) {
    return (V2f16){
        .x = fix16Mul(a->x, s),
        .y = fix16Mul(a->y, s),
    };
}

V2f16 v2_lerp(const V2f16 *const a, const V2f16 *const b, const f16 t) {
    const V2f16 as = v2_scale(a, f16s_1 - t);
    const V2f16 bs = v2_scale(b, f16s_1 - t);
    return v2_add(&as, &bs);
}

