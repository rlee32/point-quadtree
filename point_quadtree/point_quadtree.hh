#pragma once

#include "domain.hh"
#include "node.hh"
#include "point_inserter.hh"

namespace point_quadtree {

Node make_quadtree(const std::vector<double>& x
    , const std::vector<double>& y
    , const Domain&);

void insert_points(const std::vector<double>& x
    , const std::vector<double>& y
    , const Domain& domain
    , Node& root);

size_t count_points(const Node& node);
size_t count_nodes(const Node& node);

void validate(const Node& node, int depth = 0);

size_t max_leaf_points(const Node& node);
int max_depth(const Node& node, int depth = 0);

} // namespace point_quadtree


