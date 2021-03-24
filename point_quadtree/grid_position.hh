#pragma once

#include "domain.hh"
#include "box.hh"

namespace point_quadtree {

class GridPosition {
public:
    GridPosition(const Domain& domain);

    void descend(int q);

    Box make_box() const;

    double x() const;

    double y() const;

private:
    int quadrant_x(int q);

    int quadrant_y(int q);

    const Domain* m_domain {nullptr};
    int m_depth {0};
    int m_x {0};
    int m_y {0};
};

} // namespace point_quadtree

