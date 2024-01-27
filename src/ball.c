#include "ball.h"
#include "entity.h"
#include "gamemath.h"
#include "intersection.h"
#include "maths.h"

static const f16 BALL_MAX_YSPEED = FIX16(32.0);
static const V2f16 ball_clamp_min = { .x = FIX16(10.0), .y = FIX16(10.0)};
static const V2f16 ball_clamp_max = { .x = FIX16(300.0), .y = FIX16(220.0)};

Ball Ball_init(V2f16 const pos) {
    return (Ball) { .position = pos, };
}

void Ball_apply_gravity(Ball *const ball, fix16 gravity_acc) {
    // TODO: does should really use dt?
    const f16 dt = f16s_1;
    ball->velocity.y = clamp(ball->velocity.y + fix16Mul(gravity_acc, dt), f16s_0, BALL_MAX_YSPEED);
    Entity_translate(&ball->position, &ball->velocity);
    Entity_clamp_pos(
        &ball->position,
        &ball_clamp_min,
        &ball_clamp_max
    );
}

void Ball_boundaries(Ball *const ball) {
    if (ball->position.y <= ball_clamp_min.y) {
        ball->velocity.y = f16s_0;
    }
    if (ball->position.x <= ball_clamp_min.x && ball->position.x >= ball_clamp_min.x) {
        ball->velocity.x = -ball->velocity.x;
    }
    else if (ball->position.y >= ball_clamp_max.y) {
        ball->position.y = ball_clamp_min.y;
    }
}

void Ball_update(Ball *const ball, const V2f16 *const p1, const V2f16 *const p2) {
    Ball_apply_gravity(ball, FIX16(0.5));
    Ball_boundaries(ball);

    V2f16 bb_size = { .x = f16s_4, .y = f16s_4 };

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
            kprintf("ball reflected!");
        }
    }
    kprintf("final ball pos: %hd.%hd %hd.%hd vel: %hd.%hd %hd.%hd",
        fix16ToInt(fix16Int(ball->position.x)), fix16ToInt(fix16Mul(fix16Frac(ball->position.x), FIX16(100.0))),
        fix16ToInt(fix16Int(ball->position.y)), fix16ToInt(fix16Mul(fix16Frac(ball->position.y), FIX16(100.0))),
        fix16ToInt(fix16Int(ball->velocity.x)), fix16ToInt(fix16Mul(fix16Frac(ball->velocity.x), FIX16(100.0))),
        fix16ToInt(fix16Int(ball->velocity.y)), fix16ToInt(fix16Mul(fix16Frac(ball->velocity.y), FIX16(100.0)))
    );
}

void Ball_draw(const Ball *const ball) {
    const Box ball_bb = Entity_bounding_box(&ball->position, (V2u16){ .x = 8, .y = 8 });
    kprintf("ball draw pos %hd %hd", ball_bb.x, ball_bb.y);
    // Entity_draw(
    //     &ball_bb,
    //     RGB24_TO_VDPCOLOR(0xFFFF00) // yellow
    // );
}
