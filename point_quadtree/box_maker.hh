#pragma once

#include "box.hh"

#include <vector>

namespace point_quadtree {

class BoxMaker {
public:
    BoxMaker() = default;
    BoxMaker(const std::vector<double>& x
        , const std::vector<double>& y)
        : m_x(&x), m_y(&y) {}

    auto operator()(int i, double radius) const {
        Box box;
        const auto& x = *m_x;
        box.xmin = x[i] - radius;
        box.xmax = x[i] + radius;
        const auto& y = *m_y;
        box.ymin = y[i] - radius;
        box.ymax = y[i] + radius;
        return box;
    }

private:
    const std::vector<double>* m_x {nullptr};
    const std::vector<double>* m_y {nullptr};
};

} // namespace point_quadtree
