#ifndef MAKE_ME_LAUGH_INTERSECTION_H
#define MAKE_ME_LAUGH_INTERSECTION_H

#include <genesis.h>

bool Intersections_is_segs_intersections(
    const V2f16 *const o1, const V2f16 *const e1,
    const V2f16 *const o2, const V2f16 *const e2
);

bool Intersections_is_box_intersecting_seg(
    const V2f16 *const box_origin, const V2f16 *const box_size,
    const V2f16 *const seg_origin, const V2f16 *const seg_ending
);

#endif // MAKE_ME_LAUGH_INTERSECTION_H
