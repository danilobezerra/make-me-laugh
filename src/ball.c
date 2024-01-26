#include "ball.h"
#include "entity.h"
#include "gamemath.h"
#include "intersection.h"
#include "maths.h"

Ball Ball_init(V2f16 const pos) {
    return (Ball) { .position = pos, };
}

void Ball_apply_gravity(Ball *const ball, fix16 gravity_acc) {
    // TODO: does should really use dt?
    const f16 dt = f16s_1;
    ball->velocity.y += fix16Mul(gravity_acc, dt);
    Entity_translate(&ball->position, &ball->velocity);
}


void Ball_update(Ball *const ball, const V2f16 *const p1, const V2f16 *const p2) {
    Ball_apply_gravity(ball, FIX16(48.0));

    V2f16 bb_size = { .x = f16s_16, .y = f16s_16 };

    if (Intersections_is_box_intersecting_seg(&ball->position, &bb_size, p1, p2)) {
        // TODO: maybe normalize could go after the dot operation...
        V2f16 rope_perp = v2_sub(p2, p1);
        rope_perp = v2_perp(&rope_perp);
        rope_perp = v2_norm(&rope_perp);

        if (rope_perp.y < f16s_0) {
            rope_perp = v2_neg(&rope_perp);
        }

        // NOTE: it was > 0.2f before, maybe we could just use 0..
        if (v2_dot(&ball->velocity, &rope_perp) > f16s_0) {
            rope_perp = v2_neg(&rope_perp);
            ball->velocity = v2_scale(&rope_perp, v2_len(&ball->velocity));
        }
    }
}

void Ball_draw(const Ball *const ball) {
    const Box ball_bb = Entity_bounding_box(&ball->position, (V2u16){ .x = 16, .y = 16 });
    Entity_draw(
        &ball_bb,
        RGB24_TO_VDPCOLOR(0xFFFF00) // yellow
    );
}
