#ifndef MAKE_ME_LAUGH_INTERSECTION_H
#define MAKE_ME_LAUGH_INTERSECTION_H

#include <genesis.h>

bool Intersections_is_segs_intersections(
    const V2f16 *o1, const V2f16 *e1,
    const V2f16 *o2, const V2f16 *e2
);

bool Intersections_is_box_intersecting_seg(
    const V2f16 *box_origin, const V2f16 *box_size,
    const V2f16 *seg_origin, const V2f16 *seg_ending
);

#endif // MAKE_ME_LAUGH_INTERSECTION_H
