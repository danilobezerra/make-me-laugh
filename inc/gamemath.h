#ifndef MAKE_ME_LAUGH_GAMEMATH_H
#define MAKE_ME_LAUGH_GAMEMATH_H

#include <genesis.h>
#include "maths.h"

V2f32 v2_convert32(const V2f16 *a);
V2f16 v2_convert16(const V2f32 *a);
V2f16 v2_add(const V2f16 *a, const V2f16 *b);
V2f16 v2_sub(const V2f16 *a, const V2f16 *b);
V2f32 v2_sub32(const V2f32 *a, const V2f32 *b);
f16 v2_cross(const V2f16 *a, const V2f16 *b);
f32 v2_cross32(const V2f32 *a, const V2f32 *b);
f16 v2_dot(const V2f16 *a, const V2f16 *b);
V2f16 v2_scale(const V2f16 *a, f16 s);
V2f32 v2_scale32(const V2f32 *a, f32 s);
V2f16 v2_lerp(const V2f16 *a, const V2f16 *b, f16 t);
f16 v2_len_sqr(const V2f16 *a);
f16 v2_len(const V2f16 *a);
f32 v2_len32(const V2f32 *a);
V2f16 v2_norm(const V2f16 *a);
V2f32 v2_norm32(const V2f32 *a);
V2f16 v2_norm_with_sqrt(const V2f16 *a);
V2f16 v2_perp(const V2f16 *a);
V2f16 v2_neg(const V2f16 *a);

extern const f16 f16s_0;
extern const f16 f16s_1;
extern const f16 f16s_2;
extern const f16 f16s_4;
extern const f16 f16s_8;
extern const f16 f16s_10;
extern const f16 f16s_16;
extern const f16 f16s_32;

extern const V2f16 screen_clamp_min;
extern const V2f16 screen_clamp_max;

#endif // MAKE_ME_LAUGH_GAMEMATH_H
 
