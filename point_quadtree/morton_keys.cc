#include "morton_keys.hh"

#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace point_quadtree {
namespace morton_keys {

morton_key_t interleave_coordinates(double normalized_coordinate1
    , double normalized_coordinate2) {
    // if c1 and c2 are x and y respectively, then the curve looks like an "N"
    // in "typical" coordinate space (+y is up, +x is right).
    using IntegerCoordinate = uint32_t;
    constexpr IntegerCoordinate IntegerCoordinateMax {
        static_cast<IntegerCoordinate>(1) << (constants::MAX_TREE_DEPTH - 1)
    }; // to be multiplied by the normalized (0,1) coordinate.
    IntegerCoordinate c1 {
        static_cast<IntegerCoordinate>(IntegerCoordinateMax * normalized_coordinate1)
    };
    IntegerCoordinate c2 {
        static_cast<IntegerCoordinate>(IntegerCoordinateMax * normalized_coordinate2)
    };
    morton_key_t morton_key {static_cast<morton_key_t>(0)};
    constexpr int bytes {sizeof(IntegerCoordinate)};
    constexpr int bits {8 * bytes};
    for (int i {bits - 1}; i >= 0; --i) {
        constexpr morton_key_t last_bit_mask {static_cast<morton_key_t>(1)};
        morton_key |= (c1 >> i) & last_bit_mask;
        morton_key <<= 1;
        morton_key |= (c2 >> i) & last_bit_mask;
        if (i != 0) {
            morton_key <<= 1;
        }
    }
    return morton_key;
}

std::vector<morton_key_t> compute_point_morton_keys(const std::vector<double>& x
    , const std::vector<double>& y
    , const Domain& domain) {
    const size_t point_count {x.size()};
    std::vector<morton_key_t> point_morton_keys;
    for (size_t i {0}; i < point_count; ++i) {
        auto x_normalized {(x[i] - domain.xmin()) / domain.xdim(0)};
        auto y_normalized {(y[i] - domain.ymin()) / domain.ydim(0)};
        if (x_normalized < 0.0 or x_normalized > 1.0) {
            throw std::logic_error("out-of-bounds normalized x coordinate");
        }
        if (y_normalized < 0.0 or y_normalized > 1.0) {
            throw std::logic_error("out-of-bounds normalized y coordinate");
        }
        morton_key_t morton_key {interleave_coordinates(x_normalized, y_normalized)};
        point_morton_keys.push_back(morton_key);
    }
    return point_morton_keys;
}

InsertionPath point_insertion_path(morton_key_t key) {
    InsertionPath path;
    for(int i {1}; i < constants::MAX_TREE_DEPTH; ++i) {
        const auto shift_bits {2 * (constants::MAX_TREE_DEPTH - i - 1)};
        morton_key_t level {key >> shift_bits};
        constexpr morton_key_t quadrant_mask {static_cast<morton_key_t>(0b11)};
        const auto quadrant {static_cast<int>(level & quadrant_mask)};
        path[i - 1] = quadrant;
    }
    return path;
}

} // namespace morton_keys
} // namespace point_quadtree
