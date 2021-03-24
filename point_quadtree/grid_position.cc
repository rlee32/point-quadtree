#include "grid_position.hh"

namespace point_quadtree {

GridPosition::GridPosition(const Domain &domain) : m_domain(&domain) {}

void GridPosition::descend(int q) {
    ++m_depth;
    m_x <<= 1;
    m_x += quadrant_x(q);
    m_y <<= 1;
    m_y += quadrant_y(q);
}

Box GridPosition::make_box() const {
    Box box;
    box.xmin = m_domain->xmin() + m_x * m_domain->xdim(m_depth);
    box.ymin = m_domain->ymin() + m_y * m_domain->ydim(m_depth);
    box.xmax = box.xmin + m_domain->xdim(m_depth);
    box.ymax = box.ymin + m_domain->ydim(m_depth);
    return box;
}

double GridPosition::x() const { return m_x; }

double GridPosition::y() const { return m_y; }

int GridPosition::quadrant_x(int q) {
    // assuming "N" curve; see morton_keys::interleave_coordinates for an explanation.
    switch(q) {
        case 0:
        case 1: {
            return 0;
        }
        case 2:
        case 3: {
            return 1;
        }
        default: return 0;
    }
}

int GridPosition::quadrant_y(int q) {
    // assuming "N" curve; see morton_keys::interleave_coordinates for an explanation.
    switch(q) {
        case 0:
        case 2: {
            return 0;
        }
        case 1:
        case 3: {
            return 1;
        }
        default: return 0;
    }
}

} // namespace point_quadtree

