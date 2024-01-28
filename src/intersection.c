#include "intersection.h"
#include "gamemath.h"
#include "timer.h"

// tests the intersections between two segments: o1-->e1 and o2-->e2
// might be a bit expensive.
bool Intersections_is_segs_intersections(
    const V2f32 *const o1, const V2f32 *const e1,
    const V2f32 *const o2, const V2f32 *const e2
) {
    // ported from the intersections module of the Nene game framework
    // o1, o2, e1, e2: o stands for origin, e stands for ending.
    const V2f32 v1 = v2_sub32(e1, o1);
    const V2f32 v2 = v2_sub32(e2, o2);
    const f32 cross12 = v2_cross32(&v1, &v2);

    if (cross12 == FIX32(0)) {
        return false;
    }

    const V2f32 oo = v2_sub32(o2, o1);
    const f32 intersecting_scalar1 = fix32Div( v2_cross32(&oo, &v2), cross12);
    const f32 intersecting_scalar2 = fix32Div(-v2_cross32(&v1, &oo), cross12);

    return (
        FIX32(0) <= intersecting_scalar1 && intersecting_scalar1 <= FIX32(1) &&
        FIX32(0) <= intersecting_scalar2 && intersecting_scalar2 <= FIX32(1)
    );
}

// tests 
bool Intersections_is_box_intersecting_seg(
    const V2f32 *const box_origin, const V2f32 *const box_size,
    const V2f32 *const seg_origin, const V2f32 *const seg_ending
) {
    // ported from the intersections module of the Nene game framework

    // test top side
    V2f32 boxside_origin = *box_origin; // top-left
    V2f32 boxside_ending = { .x = boxside_origin.x + box_size->x, .y = boxside_origin.y }; // top-right
    if (Intersections_is_segs_intersections(seg_origin, seg_ending, &boxside_origin, &boxside_ending)) {
        return true;
    }

    // test right side
    boxside_origin = boxside_ending;
    boxside_ending = (V2f32){ .x = boxside_ending.x, .y = boxside_ending.y + box_size->y }; // bottom-right
    if (Intersections_is_segs_intersections(seg_origin, seg_ending, &boxside_origin, &boxside_ending)) {
        return true;
    }

    // test bottom side
    boxside_origin = boxside_ending;
    boxside_ending = (V2f32){ .x = box_origin->x, .y = box_origin->y + box_size->y }; // bottom-left
    if (Intersections_is_segs_intersections(seg_origin, seg_ending, &boxside_origin, &boxside_ending)) {
        return true;
    }

    // test left side
    boxside_origin = boxside_ending;
    boxside_ending = *box_origin; // top-left
    if (Intersections_is_segs_intersections(seg_origin, seg_ending, &boxside_origin, &boxside_ending)) {
        return true;
    }

    return false;
}
