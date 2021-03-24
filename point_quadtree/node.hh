#pragma once

// Only leaf nodes have points.

#include "box.hh"

#include <array>
#include <iostream>
#include <memory> // unique_ptr
#include <vector>

namespace point_quadtree {

class Node {
public:
    Node(const Box&);

    Node* create_child(int, const Box& box);
    const std::array<std::unique_ptr<Node>, 4>& children() const { return m_children; }
    Node* child(int q) { return m_children[q].get(); }

    void insert(int i);

    size_t empty() const { return m_points.empty(); }
    size_t size() const { return m_points.size(); }

    // TODO: consider making this non-member.
    std::vector<int> get_points (int i, const Box& search_box) const;

    const auto& box() const { return m_box; }
    bool leaf() const;
    int pop();

private:
    // Children are indexed by Morton key quadrant.
    std::array<std::unique_ptr<Node>, 4> m_children;

    std::vector<int> m_points;
    const Box m_box;

    bool touches(const Box&) const;
    void get_points(int i
        , const Box& search_box
        , std::vector<int>& points) const;

};

} // namespace point_quadtree
