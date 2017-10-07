//
// Created by Dominik Krupke, dominik@krupke.cc on 10/7/17.
//

#include <gtest/gtest.h>
#include <boost/graph/adjacency_list.hpp>
#include "utils.h"

TEST(Utils, IsEdgeCovered)
{
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{6};
  auto e0 = boost::add_edge(0,3, graph).first;
  boost::add_edge(0,4, graph);
  boost::add_edge(0,5, graph);
  boost::add_edge(1,3, graph);
  boost::add_edge(1,4, graph);
  boost::add_edge(1,5, graph);
  boost::add_edge(2,3, graph);
  boost::add_edge(2,4, graph);
  auto e1 = boost::add_edge(2,5, graph).first;

  std::vector<boost::graph_traits<Graph>::vertex_descriptor> vertex_cover;
  vertex_cover.push_back(0);
  vertex_cover.push_back(1);

  ASSERT_TRUE(bipartvc::details::is_edge_covered(e0, graph, vertex_cover));
  ASSERT_FALSE(bipartvc::details::is_edge_covered(e1, graph, vertex_cover));
}