# geospatial-sfc

A geospatial range query implementation using space filling curve

Two curves are used:
1. Doug Moore's implementation of Hilbert curve
2. Libmorton's implementation of Z order curve (AKA Morton curve)

New functions
1. Support non-integer coordinates. Given min and interval values, this function will truncate double values into integers. In other words, the  2D space is divided into many uniform grids.
2. Generate a min-max Z order or Hilbert range for rectangles.

TODO:

Generate more than one range for a rectangle. The number of ranges can be tuned by a parameter called "max_skip_per_range".