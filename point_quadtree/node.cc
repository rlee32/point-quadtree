#include "node.hh"

#include <algorithm>

namespace point_quadtree {

Node::Node(const Box& box) : m_box(box) {}

void Node::insert(int i) {
    m_points.push_back(i);
}

Node *Node::create_child(int quadrant, const Box& box) {
    if (m_children[quadrant]) {
        return m_children[quadrant].get();
    }
    m_children[quadrant] = std::make_unique<Node>(box);
    return m_children[quadrant].get();
}

bool Node::touches(const Box& box) const {
    return m_box.touches(box);
}

std::vector<int>
    Node::get_points(int i
    , const Box& search_box) const {
    std::vector<int> points;
    get_points(i, search_box, points);
    return points;
}

void Node::get_points(int i
    , const Box& search_box
    , std::vector<int>& points) const {
    if (m_points.empty()) {
        for (const auto& unique_ptr : m_children) {
            if (unique_ptr and unique_ptr->touches(search_box)) {
                unique_ptr->get_points(i, search_box, points);
            }
        }
    } else {
        for (const auto p : m_points) {
            points.push_back(p);
        }
    }
}

bool Node::leaf() const {
    return std::all_of(std::cbegin(m_children)
        , std::cend(m_children)
        , [](const auto& child) { return not child; });
}

int Node::pop() {
    auto back = m_points.back();
    m_points.pop_back();
    return back;
}

} // namespace point_quadtree
