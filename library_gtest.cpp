//
// Created by Dominik Krupke, dominik@krupke.cc on 10/7/17.
//

#include <gtest/gtest.h>
#include <boost/graph/adjacency_list.hpp>
#include "library.h"

TEST(Library, IsValidVertexCover)
{
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{6};
  boost::add_edge(0, 3, graph);
  boost::add_edge(0, 4, graph);
  boost::add_edge(0, 5, graph);
  boost::add_edge(1, 3, graph);
  boost::add_edge(1, 4, graph);
  boost::add_edge(1, 5, graph);
  boost::add_edge(2, 3, graph);
  boost::add_edge(2, 4, graph);
  boost::add_edge(2, 5, graph);

  std::vector<boost::graph_traits<Graph>::vertex_descriptor> vertex_cover_1;
  vertex_cover_1.push_back(0);
  vertex_cover_1.push_back(1);
  std::vector<boost::graph_traits<Graph>::vertex_descriptor> vertex_cover_2;
  vertex_cover_2.push_back(0);
  vertex_cover_2.push_back(1);
  vertex_cover_2.push_back(2);

  ASSERT_FALSE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_1));
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_2));
}

TEST(Library, MinVertexCover)
{
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{7};
  boost::add_edge(0, 3, graph);
  boost::add_edge(0, 4, graph);
  boost::add_edge(0, 5, graph);
  boost::add_edge(1, 3, graph);
  boost::add_edge(1, 4, graph);
  boost::add_edge(1, 5, graph);
  boost::add_edge(2, 3, graph);
  boost::add_edge(2, 4, graph);
  boost::add_edge(2, 5, graph);
  boost::add_edge(2, 6, graph);

  auto vertex_cover = bipartvc::get_minimal_vertex_cover(graph,
                                                         [](boost::graph_traits<Graph>::vertex_descriptor v) -> bipartvc::Partition {
                                                             if (v < 3) {
                                                               return bipartvc::Partition::A;
                                                             } else {
                                                               return bipartvc::Partition::B;
                                                             }
                                                         });

  ASSERT_EQ(vertex_cover.size(), 3);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover));
}