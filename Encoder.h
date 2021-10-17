#include "hilbert.h"
#include "morton.h"
#include "geos/geom.h"

template <class INPUT>
class Encoder {
private:
    INPUT xmin;
    INPUT xintvl;
    INPUT ymin;
    INPUT yintvl;
public:
    Encoder(INPUT xmin, INPUT xintvl, INPUT ymin, INPUT yintvl): xmin(xmin), xintvl(xintvl), ymin(ymin), yintvl(yintvl){
    }

    Encoder(INPUT xmin, INPUT xmax, int xnum, INPUT ymin, INPUT ymax, int ynum):
    xmin(xmin), xintvl((xmax - xmin) * 1.0 / xnum), ymin(ymin), yintvl((ymax - ymin) * 1.0 / ynum){
    }

    template<class OUTPUT>
    inline OUTPUT d2i (INPUT d, INPUT min, INPUT interval) {
        INPUT i = (INPUT)((d - min) / interval);
        return i;
    }
    
    inline uint_fast64_t encode_z(INPUT x, INPUT y) {
        uint_fast32_t x_int = d2i<uint_fast32_t>(x, xmin, xintvl);
        uint_fast32_t y_int = d2i<uint_fast32_t>(y, ymin, yintvl);
        return libmorton::morton2D_64_encode(x_int, y_int);
    }

    inline bitmask_t encode_h(INPUT x, INPUT y) {
        bitmask_t x_int = d2i<bitmask_t>(x, xmin, xintvl);
        bitmask_t y_int = d2i<bitmask_t>(y, ymin, yintvl);
        bitmask_t coord[2] = {x_int, y_int};
        return hilbert_c2i(2, 32, coord);
    }

    inline std::pair<uint_fast64_t, uint_fast64_t> encode_z(INPUT x1_dbl, INPUT y1_dbl, INPUT x2_dbl, INPUT y2_dbl){
        uint_fast32_t x1 = d2i<uint_fast32_t>(x1_dbl, xmin, xintvl);
        uint_fast32_t y1 = d2i<uint_fast32_t>(y1_dbl, ymin, yintvl);
        uint_fast32_t x2 = d2i<uint_fast32_t>(x2_dbl, xmin, xintvl);
        uint_fast32_t y2 = d2i<uint_fast32_t>(y2_dbl, ymin, yintvl);
        auto min = libmorton::morton2D_64_encode(x1, y1);
        auto max = libmorton::morton2D_64_encode(x2, y2);
        return std::make_pair(min, max);
    }

    // This is buggy. Need to check all points lie on the perimeter of the box
    // See https://stackoverflow.com/questions/12772893/how-to-use-morton-order-in-range-search
    // See https://github.com/davidmoten/hilbert-curve
    inline bitmask_t encode_h(INPUT x1_dbl, INPUT y1_dbl, INPUT x2_dbl, INPUT y2_dbl){
        bitmask_t x1 = d2i<bitmask_t>(x1_dbl, xmin, xintvl);
        bitmask_t y1 = d2i<bitmask_t>(y1_dbl, ymin, yintvl);
        bitmask_t x2 = d2i<bitmask_t>(x2_dbl, xmin, xintvl);
        bitmask_t y2 = d2i<bitmask_t>(y2_dbl, ymin, yintvl);
        bitmask_t co_lo[2] = {x1, y1};
        bitmask_t co_hi[2] = {x2, y2};
        std::cout << "Original index for lo hi " << hilbert_c2i(2, 32, co_lo) << " "
        << hilbert_c2i(2, 32, co_hi) << std::endl;
        hilbert_box_pt(2, 4, 32, false, co_lo, co_hi);
        std::cout << "Updated index for lo hi " << hilbert_c2i(2, 32, co_lo) << " "
                  << hilbert_c2i(2, 32, co_hi) << std::endl;
        return hilbert_c2i(2, 32, co_hi);
    }
};