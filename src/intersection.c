#include "intersection.h"
#include "gamemath.h"

// tests the intersections between two segments: o1-->e1 and o2-->e2
// might be a bit expensive.
bool Intersections_is_segs_intersections(
    const V2f16 *const o1, const V2f16 *const e1,
    const V2f16 *const o2, const V2f16 *const e2
) {
    // ported from the intersections module of the Nene game framework
    // o1, o2, e1, e2: o stands for origin, e stands for ending.
    const V2f16 v1 = v2_sub(e1, o1);
    const V2f16 v2 = v2_sub(e2, o2);
    const f16 cross12 = v2_cross(&v1, &v2);

    if (cross12 == f16s_0) {
        return false;
    }

    const V2f16 oo = v2_sub(o2, o1);
    const f16 intersecting_scalar1 = fix16Div( v2_cross(&oo, &v2), cross12);
    const f16 intersecting_scalar2 = fix16Div(-v2_cross(&v1, &oo), cross12);

    return (
        f16s_0 <= intersecting_scalar1 && intersecting_scalar1 <= f16s_1 &&
        f16s_0 <= intersecting_scalar2 && intersecting_scalar2 <= f16s_1
    );
}

// tests 
bool Intersections_is_box_intersecting_seg(
    const V2f16 *const box_origin, const V2f16 *const box_size,
    const V2f16 *const seg_origin, const V2f16 *const seg_ending
) {
    // ported from the intersections module of the Nene game framework

    // test top side
    V2f16 boxside_origin = *box_origin;
    V2f16 boxside_ending = { .x = box_origin->x + box_size->x, .y = box_origin->y };
    if (Intersections_is_segs_intersections(&boxside_origin, &boxside_ending, seg_origin, seg_ending)) {
        return true;
    }

    // test right side
    boxside_origin = boxside_ending;
    boxside_ending = (V2f16){ .x = boxside_origin.x, .y = boxside_origin.y + box_size->y };
    if (Intersections_is_segs_intersections(&boxside_origin, &boxside_ending, seg_origin, seg_ending)) {
        return true;
    }

    // test bottom side
    boxside_origin = boxside_ending;
    boxside_ending = (V2f16){ .x = boxside_origin.x - box_size->x, .y = boxside_origin.y };
    if (Intersections_is_segs_intersections(&boxside_origin, &boxside_ending, seg_origin, seg_ending)) {
        return true;
    }

    // test left side
    boxside_origin = boxside_ending;
    boxside_ending = *box_origin;
    if (Intersections_is_segs_intersections(&boxside_origin, &boxside_ending, seg_origin, seg_ending)) {
        return true;
    }

    return false;
}
