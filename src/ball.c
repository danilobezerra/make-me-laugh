#include "ball.h"
#include "resources.h"
#include "global.h"
#include "entity.h"
#include "gamemath.h"
#include "intersection.h"
#include "maths.h"

static const f16 BALL_MAX_YSPEED = FIX16(0.8);

Ball Ball_init(V2f16 const pos) {
    Sprite *sprite = SPR_addSprite(&ball_sprite, pos.x, pos.y, TILE_ATTR(BALL_PALETTE, FALSE, FALSE, FALSE));
    PAL_setPalette(BALL_PALETTE, ball_sprite.palette->data, DMA);

    return (Ball) {
        .sprite = sprite,
        .position = pos,
        .velocity = { .x = f16s_0, .y = f16s_0 },
    };
}

void Ball_apply_gravity(Ball *const ball) {
    Entity_apply_gravity(&ball->velocity, FIX16(0.05), BALL_MAX_YSPEED);
}

bool Ball_boundaries(Ball *const ball) {
    bool touched_floor = FALSE;

    Entity_clamp_pos(
        &ball->position,
        &screen_clamp_min,
        &screen_clamp_max
    );

    if (ball->position.y <= screen_clamp_min.y) {
        ball->velocity.y = f16s_0;
    }
    else if (ball->position.y >= screen_clamp_max.y) {
        // TODO: go to middle x
        ball->position.y = screen_clamp_min.y + f16s_8;
        ball->velocity.y = f16s_0;
        touched_floor = TRUE;
    }
    if (ball->position.x <= screen_clamp_min.x || ball->position.x >= screen_clamp_max.x) {
        ball->velocity.x = fix16Mul(ball->velocity.x, -(FIX16(0.5)));
    }

    return touched_floor;
}

bool Ball_update(Ball *const ball, const V2f16 *const p1, const V2f16 *const p2) {
    Ball_apply_gravity(ball);

    if (Ball_boundaries(ball)) {
        kprintf("PERDEU!!");
        return TRUE;
    }

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

    Entity_translate(&ball->position, &ball->velocity);

    // kprintf("final ball pos: %hd.%hd %hd.%hd vel: %hd.%hd %hd.%hd",
    //     fix16ToInt(fix16Int(ball->position.x)), fix16ToInt(fix16Mul(fix16Frac(ball->position.x), FIX16(100.0))),
    //     fix16ToInt(fix16Int(ball->position.y)), fix16ToInt(fix16Mul(fix16Frac(ball->position.y), FIX16(100.0))),
    //     fix16ToInt(fix16Int(ball->velocity.x)), fix16ToInt(fix16Mul(fix16Frac(ball->velocity.x), FIX16(100.0))),
    //     fix16ToInt(fix16Int(ball->velocity.y)), fix16ToInt(fix16Mul(fix16Frac(ball->velocity.y), FIX16(100.0)))
    // );

    return FALSE;
}

void Ball_draw(const Ball *const ball) {
    Entity_draw(&ball->position, ball->sprite);
}
