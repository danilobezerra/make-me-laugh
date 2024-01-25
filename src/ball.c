#include "ball.h"
#include "entity.h"

Ball Ball_init(V2f16 pos) {
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

    Entity_translate(&ball->position, ball->velocity);
}

bool Ball_is_segments_intersecting(const V2f16 *const o1, const V2f16 *const e1, const V2f16 *const o2, const V2f16 *const e2) {
    // ported from Nene framework, from nene/src/intersections.c
    // "o" stands for "origin", "e" stands for "ending"
//    const nene_Vec2 v1 = nene_Vec2_sub(*e1, *o1);
//    const nene_Vec2 v2 = nene_Vec2_sub(*e2, *o2);
//    const float cross12 = nene_Vec2_cross(v1, v2);
//
//    if (cross12 == 0.0f) {
        return false;
//    }
//
//    const nene_Vec2 oo = nene_Vec2_sub(*o2, *o1);
//    const float intersecting_scalar1 = nene_Vec2_cross(oo, v2) / cross12;
//    const float intersecting_scalar2 = -nene_Vec2_cross(v1, oo) / cross12;
//
//    return (
//            0.0f <= intersecting_scalar1 && intersecting_scalar1 <= 1.0f &&
//            0.0f <= intersecting_scalar2 && intersecting_scalar2 <= 1.0f
//    );
}

bool Ball_is_intersecting_rope(Ball *const ball, const V2f16 *const ro, const V2f16 *const re) {
    // ro, re: rope origin, rope ending
    // bbo, bbe: bounding-box origin, bounding-box ending
    Box ball_bb = Entity_bounding_box(&ball->position, (V2f16) { .x = 16, .y = 16 });
    V2f16 bbo, bbe;

    // top side
//    bbo = ball_bb.pos;
//    bbe = nene_Vec2_add(bbo, (nene_Vec2){ .x = ball_bb.size.x });
//    if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
//        return true;
//    }

    // right side
//    bbo = bbe;
//    bbe = nene_Vec2_add(bbe, (nene_Vec2){ .y = ball_bb.size.y });
//    if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
//        return true;
//    }

    // bottom side
//    bbo = bbe;
//    bbe = nene_Vec2_add(ball_bb.pos, (nene_Vec2){ .y = ball_bb.size.y });
//    if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
//        return true;
//    }

    // left side
//    bbo = bbe;
//    bbe = ball_bb.pos;
//    if (game_is_segments_intersecting(ro, re, &bbo, &bbe)) {
//        return true;
//    }

    return false;
}

void Ball_update(Ball *const ball, const V2f16 *const p1, const V2f16 *const p2) {
    Ball_apply_gravity(ball, FIX16(48.0));

    if (Ball_is_intersecting_rope(ball, p1, p2)) {
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
    Entity_draw(
        Entity_bounding_box(&ball->position, (V2f16) { .x = 16, .y = 16 }),
        RGB24_TO_VDPCOLOR(0xFFFF00) // yellow
    );
}