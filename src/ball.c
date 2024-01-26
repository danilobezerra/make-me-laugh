#include "ball.h"
#include "entity.h"
#include "gamemath.h"
#include "intersection.h"

Ball Ball_init(V2f16 const pos) {
    return (Ball) { .position = pos, };
}

void Ball_apply_gravity(Ball *const ball, fix16 gravity_acc) {
//    ball->velocity = nene_Vec2_add(
//        ball->velocity,
//        nene_Vec2_scale(
//                (nene_Vec2){ .y = gravity_acc },
//                nene_Core_get_delta_time()
//        )
//    );

    Entity_translate(&ball->position, &ball->velocity);
}

void Ball_update(Ball *const ball, const V2f16 *const p1, const V2f16 *const p2) {
    Ball_apply_gravity(ball, FIX16(48.0));

    V2f16 bbsize = { .x = f16s_16, .y = f16s_16 };
    if (Intersections_is_box_intersecting_seg(&ball->position, p1, p2)) {
        // TODO: maybe normalize could go after the dot operation...
//        nene_Vec2 rope_perp = nene_Vec2_normalize(
//                nene_Vec2_perpendicular(
//                        nene_Vec2_sub(*p2, *p1)
//                )
//        );

//        if (rope_perp.y < 0.0f) {
//            rope_perp = nene_Vec2_negate(rope_perp);
//        }

//        if (nene_Vec2_dot(ball->velocity, rope_perp) > 0.2f) {
//            ball->velocity = nene_Vec2_scale(
//                    nene_Vec2_negate(rope_perp),
//                    nene_Vec2_len(ball->velocity)
//            );
//        }
    }
}

void Ball_draw(const Ball *const ball) {
    const Box ball_bb = Entity_bounding_box(&ball->position, (V2u16){ .x = 16, .y = 16 });
    Entity_draw(
        ,
        RGB24_TO_VDPCOLOR(0xFFFF00) // yellow
    );
}
