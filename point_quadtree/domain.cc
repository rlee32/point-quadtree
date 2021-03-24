#include "domain.hh"

#include <algorithm>

namespace point_quadtree {

Domain::Domain(const std::vector<double>& x, const std::vector<double>& y)
    : m_x(x), m_y(y) {
    // Get domain bounds
    m_xmin = *std::min_element(std::cbegin(x), std::cend(x));
    auto xmax = *std::max_element(std::cbegin(x), std::cend(x));
    m_ymin = *std::min_element(std::cbegin(y), std::cend(y));
    auto ymax = *std::max_element(std::cbegin(y), std::cend(y));
    auto xrange = xmax - m_xmin;
    auto yrange = ymax - m_ymin;
    // Points within each node have the same Morton Key prefix.
    // So when a point is on the exact boundary,
    // it gets put into the quadrant it would go in if it was a small increment
    // larger (in either x or y). This is fine, EXCEPT at the root. There is no
    // next quadrant. So, we have to apply fudge factor to ranges to completely
    // capture boundary points within the root node.
    constexpr double RootNodeMargin {0.00001};
    m_xmin -= RootNodeMargin * xrange;
    m_ymin -= RootNodeMargin * yrange;
    xrange *= 1 + 2 * RootNodeMargin;
    yrange *= 1 + 2 * RootNodeMargin;
    int grid_dim {1};
    for (int depth {0}; depth < constants::MAX_TREE_DEPTH; ++depth)
    {
        m_xdim[depth] = xrange / static_cast<double>(grid_dim);
        m_ydim[depth] = yrange / static_cast<double>(grid_dim);
        grid_dim <<= 1;
    }
}

double Domain::xmin() const { return m_xmin; }

double Domain::ymin() const { return m_ymin; }

double Domain::xdim(int depth) const { return m_xdim[depth]; }

double Domain::ydim(int depth) const { return m_ydim[depth]; }

const std::vector<double> &Domain::x() const { return m_x; }

const std::vector<double> &Domain::y() const { return m_y; }

} // namespace point_quadtree
