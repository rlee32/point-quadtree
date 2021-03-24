#pragma once

#include <iostream>
#include <algorithm>
#include <limits>

namespace point_quadtree {

struct Box {
    double xmin {std::numeric_limits<double>::max()};
    double xmax {std::numeric_limits<double>::min()};
    double ymin {std::numeric_limits<double>::max()};
    double ymax {std::numeric_limits<double>::min()};

    bool touches(const Box &other) const;

    bool touches(double x, double y) const;

    // if x, y is not in this box, the box is enlarged to contain it.
    void include(double x, double y);

    // this is enlarged to contain box.
    void include(const Box &box);
};

inline auto &operator<<(std::ostream &o, const Box &b) {
    o << "(" << b.xmin << ", " << b.ymin << ") "
        << "(" << b.xmax << ", " << b.ymax << ")" << std::endl;
    return o;
}

} // namespace point_quadtree
