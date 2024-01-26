#ifndef MAKE_ME_LAUGH_GAMEMATH_H
#define MAKE_ME_LAUGH_GAMEMATH_H

#include <genesis.h>

V2f16 v2_add(const V2f16 *const a, const V2f16 *const b);
V2f16 v2_sub(const V2f16 *const a, const V2f16 *const b);
f16 v2_cross(const V2f16 *const a, const V2f16 *const b);
f16 v2_dot(const V2f16 *const a, const V2f16 *const b);
V2f16 v2_scale(const V2f16 *const a, const f16 s);
V2f16 v2_lerp(const V2f16 *const a, const V2f16 *const b, const f16 t);

extern const f16 f16s_0;
extern const f16 f16s_1;
extern const f16 f16s_16;
extern const f16 f16s_32;

#endif // MAKE_ME_LAUGH_GAMEMATH_H
 
