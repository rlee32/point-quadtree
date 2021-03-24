#include "box.hh"

namespace point_quadtree {

bool Box::touches(const Box& other) const {
    bool too_high   {ymin > other.ymax};
    bool too_low    {ymax < other.ymin};
    bool left       {xmax < other.xmin};
    bool right      {xmin > other.xmax};
    bool outside {too_high or too_low or left or right};
    return not outside;
}

bool Box::touches(double x, double y) const {
    bool within_x = x >= xmin and x <= xmax;
    bool within_y = y >= ymin and y <= ymax;
    return within_x and within_y;
}

void Box::include(double x, double y) {
    xmin = std::min(x, xmin);
    xmax = std::max(x, xmax);
    ymin = std::min(y, ymin);
    ymax = std::max(y, ymax);
}

void Box::include(const Box &box) {
    include(box.xmin, box.ymin);
    include(box.xmin, box.ymax);
    include(box.xmax, box.ymin);
    include(box.xmax, box.ymax);
}

} // namespace point_quadtree
