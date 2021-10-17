#include "hilbert.h"
#include "morton.h"
#include "Encoder.h"
int main() {
    // Test libmorton curve
    uint_fast32_t x = 1;
    uint_fast32_t y = 1;
    uint_fast32_t x1;
    uint_fast32_t y1;
    auto index_zorder = libmorton::morton2D_64_encode(x, y);
    libmorton::morton2D_64_decode(index_zorder, x1, y1);
    assert(x1 == x && y1 == y);

    // Test moore hilbert curve
    bitmask_t coord[2] = {1, 1};
    bitmask_t coord1[2] = {0, 0};
    auto index_hilbert = hilbert_c2i(2, 32, coord);
    hilbert_i2c(2, 32, index_hilbert, coord1);
    assert(coord[0] == coord1[0] && coord[1] == coord1[1]);

    // Test rounded double type coordinates
    auto encoder = new Encoder<double>(0.0, 1.0, 0.0, 1.0);
    auto index_double_h = encoder->encode_h(1.5, 1.5);
    assert(index_double_h == index_hilbert);

    // Hard coded test cases
    assert(encoder->encode_h(1.5, 2.5) == 13);
    assert(encoder->encode_h(2.5, 1.5) == 7);

    auto index_double_z = encoder->encode_z(1.5, 1.5);
    assert(index_double_z == index_zorder);

    // Hard coded test cases
    auto range = encoder->encode_z(0.0, 2.0, 4.0, 3.0);
    assert(range.first == 8 && range.second == 26);
    return 0;
}