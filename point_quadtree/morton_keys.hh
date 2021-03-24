#pragma once

// Morton keys are interleaved coordinates, which are integer representations
// of x, y coordinates normalized to [0, 1].

#include "domain.hh"
#include "constants.hh"

#include <cstdint>
#include <vector>

namespace point_quadtree {
namespace morton_keys {

using morton_key_t = uint64_t;

morton_key_t interleave_coordinates(double normalized_coordinate1
    , double normalized_coordinate2);

std::vector<morton_key_t> compute_point_morton_keys(const std::vector<double>& x
    , const std::vector<double>& y
    , const Domain& domain);

// The number of steps to get to max_tree_depth from the root is max_tree_depth - 1.
using InsertionPath = std::array<int, constants::MAX_TREE_DEPTH - 1>;

InsertionPath point_insertion_path(morton_key_t key);

} // namespace morton_keys
} // namespace point_quadtree
