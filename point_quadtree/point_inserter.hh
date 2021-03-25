#pragma once

#include "domain.hh"
#include "grid_position.hh"
#include "node.hh"
#include "morton_keys.hh"
#include "constants.hh"

#include <stdexcept>
#include <vector>

namespace point_quadtree {

class PointInserter {
public:
    PointInserter(const GridPosition& grid_position
        , const std::vector<morton_keys::morton_key_t>& morton_keys
        , int point
        , point_quadtree::Node* current_node
        , int current_depth);

    void place();

private:
    const std::vector<morton_keys::morton_key_t>& m_morton_keys;

    const int        m_point {constants::INVALID_POINT};
    const morton_keys::InsertionPath    m_path;

    Node*   m_current_node  {nullptr};
    int     m_current_depth {0}; // 0 is root.
    GridPosition            m_grid_position;

    void descend();
};

} // namespace point_quadtree

