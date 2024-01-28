#include "gamemath.h"
#include "maths.h"

const f16 f16s_0 = FIX16(0.0);
const f16 f16s_1 = FIX16(1.0);
const f16 f16s_2 = FIX16(2.0);
const f16 f16s_4 = FIX16(4.0);
const f16 f16s_8 = FIX16(8.0);
const f16 f16s_10 = FIX16(10.0);
const f16 f16s_16 = FIX16(16.0);
const f16 f16s_32 = FIX16(32.0);

const V2f16 screen_clamp_min = { .x = FIX16(10.0), .y = FIX16(10.0)};
const V2f16 screen_clamp_max = { .x = FIX16(300.0), .y = FIX16(220.0)};

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
    const V2f16 bs = v2_scale(b, t);
    return v2_add(&as, &bs);
}

f16 v2_len_sqr(const V2f16 *const a) {
    return fix16Mul(a->x, a->x) + fix16Mul(a->y, a->y);
}

f16 v2_len(const V2f16 *const a) {
    u32 l = getApproximatedDistance(fix16ToInt(a->x), fix16ToInt(a->y));
    return intToFix16(l);
}

V2f16 v2_norm(const V2f16 *const a) {
    f16 len = v2_len_sqr(a);

    if (len > f16s_0) {
        len = fix16Sqrt(len);
        return (V2f16){
            .x = fix16Div(a->x, len),
            .y = fix16Div(a->y, len),
        };
    }

    return *a;
}

V2f16 v2_perp(const V2f16 *const a) {
    return (V2f16){ .x = -a->y, .y =  a->x };
}

V2f16 v2_neg(const V2f16 *const a) {
    return (V2f16){ .x = -a->x, .y = -a->y };
}
