#include "ball.h"
#include "resources.h"
#include "global.h"
#include "entity.h"
#include "gamemath.h"
#include "intersection.h"
#include "maths.h"

static const f16 BALL_MAX_YSPEED = FIX16(1.0);
static const f32 BALL_REFLECT_SPEED = FIX32(2.0);
static const V2f32 bb_size = { .x = FIX32(4), .y = FIX32(4) };

Ball Ball_init(V2f16 const pos) {
    Sprite *sprite = SPR_addSprite(&ball_sprite, pos.x, pos.y, TILE_ATTR(BALL_PALETTE, FALSE, FALSE, FALSE));
    PAL_setPalette(BALL_PALETTE, ball_sprite.palette->data, DMA);

    return (Ball) {
        .sprite = sprite,
        .position = pos,
        .velocity = { .x = f16s_0, .y = f16s_0 },
        .is_intersecting_rope = FALSE,
    };
}

void Ball_apply_gravity(Ball *const ball) {
    if (ball->velocity.y < f16s_0) {
        Entity_apply_gravity(&ball->velocity, FIX16(0.05), FIX16(16.0));
    }
    else {
        Entity_apply_gravity(&ball->velocity, FIX16(0.05), BALL_MAX_YSPEED);
    }
}

u8 Ball_boundaries(Ball *const ball) {
    u8 touched_floor = 0;

    Entity_clamp_pos(
        &ball->position,
        &screen_clamp_min,
        &screen_clamp_max
    );

    if (ball->position.y <= screen_clamp_min.y) {
        ball->velocity.y = f16s_0;
        ball->position.y = screen_clamp_min.y + f16s_2;
    }
    else if (ball->position.y >= screen_clamp_max.y) {
        // TODO: go to middle x
        ball->position.y = screen_clamp_min.y + f16s_2;
        // ball->velocity.y = f16s_0;
        touched_floor = BALL_HIT_FLOOR;
    }
    if (ball->position.x <= screen_clamp_min.x || ball->position.x >= screen_clamp_max.x) {
        ball->velocity.x = fix16Mul(ball->velocity.x, -(FIX16(0.5)));
    }

    return touched_floor;
}

u8 Ball_update(Ball *const ball, const V2f16 *const p1, const V2f16 *const p2) {
    Ball_apply_gravity(ball);

    if (Ball_boundaries(ball)) {
        kprintf("PERDEU!!");
        return BALL_HIT_FLOOR;
    }

    u8 result = 0;

    V2f32 bb_pos = v2_convert32(&ball->position);
    V2f32 p1_32 = v2_convert32(p1);
    V2f32 p2_32 = v2_convert32(p2);

    if (Intersections_is_box_intersecting_seg(&bb_pos, &bb_size, &p1_32, &p2_32)) {
        if (!ball->is_intersecting_rope) {
            kprintf("is intersecting");
            // TODO: maybe normalize could go after the dot operation...
            V2f16 rope_perp = v2_sub(p2, p1);
            rope_perp = v2_perp(&rope_perp);

            if (rope_perp.y < f16s_0) {
                rope_perp = v2_neg(&rope_perp);
            }

            // NOTE: it was > 0.2f before, maybe we could just use 0..
            if (v2_dot(&ball->velocity, &rope_perp) > f16s_0) {
                rope_perp = v2_neg(&rope_perp);
                V2f32 rope_perp32 = v2_convert32(&rope_perp);
                V2f32 ball_vel32 = v2_convert32(&ball->velocity);
                ball_vel32 = v2_norm32(&rope_perp32);
                ball_vel32 = v2_scale32(&ball_vel32, BALL_REFLECT_SPEED);
                ball->velocity = v2_convert16(&ball_vel32);

                // ball->velocity = v2_scale(&rope_perp, v2_len(&ball->velocity));
                kprintf("ball reflected!");
                result = BALL_HIT_ROPE;
                ball->is_intersecting_rope = TRUE;
            }
        }
    }
    else {
        ball->is_intersecting_rope = FALSE;
    }

    Entity_translate(&ball->position, &ball->velocity);

    // kprintf("final ball pos: %hd.%hd %hd.%hd vel: %hd.%hd %hd.%hd",
    //     fix16ToInt(fix16Int(ball->position.x)), fix16ToInt(fix16Mul(fix16Frac(ball->position.x), FIX16(100.0))),
    //     fix16ToInt(fix16Int(ball->position.y)), fix16ToInt(fix16Mul(fix16Frac(ball->position.y), FIX16(100.0))),
    //     fix16ToInt(fix16Int(ball->velocity.x)), fix16ToInt(fix16Mul(fix16Frac(ball->velocity.x), FIX16(100.0))),
    //     fix16ToInt(fix16Int(ball->velocity.y)), fix16ToInt(fix16Mul(fix16Frac(ball->velocity.y), FIX16(100.0)))
    // );

    return result;
}

void Ball_draw(const Ball *const ball) {
    Entity_draw(&ball->position, ball->sprite);
}
