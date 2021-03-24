#pragma once

#include "constants.hh"

#include <array>
#include <vector>

namespace point_quadtree {

class Domain {
public:
    Domain(const std::vector<double>& x, const std::vector<double>& y);
    auto xmin() const;
    auto ymin() const;
    auto xdim(int depth) const;
    auto ydim(int depth) const;

    const auto& x() const;
    const auto& y() const;

private:
    const std::vector<double>& m_x;
    const std::vector<double>& m_y;

    double m_xmin {0};
    double m_ymin {0};
    std::array<double, constants::MAX_TREE_DEPTH> m_xdim; // x-dimension of boxes.
    std::array<double, constants::MAX_TREE_DEPTH> m_ydim; // y-dimension of boxes.
};

} // namespace point_quadtree
