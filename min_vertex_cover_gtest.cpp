//
// Created by Dominik Krupke, dominik@krupke.cc on 10/7/17.
//

#include <gtest/gtest.h>
#include <boost/graph/adjacency_list.hpp>
#include "min_vertex_cover.h"

TEST(Library, IsValidVertexCover) {
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

TEST(Library, MinVertexCover) {
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

  auto partition_classifier = [](boost::graph_traits<Graph>::vertex_descriptor v) -> bipartvc::Partition {
    if (v < 3) {
      return bipartvc::Partition::A;
    } else {
      return bipartvc::Partition::B;
    }
  };
  auto vertex_cover = bipartvc::get_minimal_vertex_cover(graph, partition_classifier);

  ASSERT_EQ(vertex_cover.size(), 3);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover));

  //swap partitions (A is treated differently than B by the algorithm so we should check this)
  auto complementary_partition_classifier = [](boost::graph_traits<Graph>::vertex_descriptor v) -> bipartvc::Partition {
    if (v < 3) {
      return bipartvc::Partition::B;
    } else {
      return bipartvc::Partition::A;
    }
  };
  auto vertex_cover_2 = bipartvc::get_minimal_vertex_cover(graph, complementary_partition_classifier);

  ASSERT_EQ(vertex_cover_2.size(), 3);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_2));

  //and with automatic partition detection.
  auto vertex_cover_3 = bipartvc::get_minimal_vertex_cover(graph);
  ASSERT_EQ(vertex_cover_3.size(), 3);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_3));
}

TEST(MinVertexCover, Star) {
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{7};
  boost::add_edge(0, 2, graph);
  boost::add_edge(0, 3, graph);
  boost::add_edge(0, 4, graph);
  boost::add_edge(0, 5, graph);
  boost::add_edge(0, 6, graph);
  boost::add_edge(1, 2, graph);
  boost::add_edge(1, 3, graph);
  boost::add_edge(1, 4, graph);
  boost::add_edge(1, 5, graph);
  boost::add_edge(1, 6, graph);
  auto partition_classifier = [](boost::graph_traits<Graph>::vertex_descriptor v) -> bipartvc::Partition {
    if (v < 2) {
      return bipartvc::Partition::A;
    } else {
      return bipartvc::Partition::B;
    }
  };
  auto vertex_cover = bipartvc::get_minimal_vertex_cover(graph, partition_classifier);

  ASSERT_EQ(vertex_cover.size(), 2);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover));

  //swap partitions (A is treated differently than B by the algorithm so we should check this)
  auto complementary_partition_classifier = [](boost::graph_traits<Graph>::vertex_descriptor v) -> bipartvc::Partition {
    if (v < 2) {
      return bipartvc::Partition::B;
    } else {
      return bipartvc::Partition::A;
    }
  };
  auto vertex_cover_2 = bipartvc::get_minimal_vertex_cover(graph, complementary_partition_classifier);

  ASSERT_EQ(vertex_cover_2.size(), 2);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_2));

  //and with automatic partition detection.
  auto vertex_cover_3 = bipartvc::get_minimal_vertex_cover(graph);
  ASSERT_EQ(vertex_cover_3.size(), 2);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_3));

}

TEST(MinVertexCover, ConnectedStar) {
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{12};
  boost::add_edge(0, 2, graph);
  boost::add_edge(0, 3, graph);
  boost::add_edge(0, 4, graph);
  boost::add_edge(0, 5, graph);
  boost::add_edge(0, 6, graph);
  boost::add_edge(1, 7, graph);
  boost::add_edge(1, 8, graph);
  boost::add_edge(1, 9, graph);
  boost::add_edge(1, 10, graph);
  boost::add_edge(1, 11, graph);
  boost::add_edge(0, 1, graph);

  auto vertex_cover_3 = bipartvc::get_minimal_vertex_cover(graph);
  ASSERT_EQ(vertex_cover_3.size(), 2);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_3));

}

TEST(MinVertexCover, EvenCycle) {
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{12};
  boost::add_edge(0, 1, graph);
  boost::add_edge(1, 2, graph);
  boost::add_edge(2, 3, graph);
  boost::add_edge(3, 4, graph);
  boost::add_edge(4, 5, graph);
  boost::add_edge(5, 6, graph);
  boost::add_edge(6, 7, graph);
  boost::add_edge(7, 8, graph);
  boost::add_edge(8, 9, graph);
  boost::add_edge(9, 10, graph);
  boost::add_edge(10, 11, graph);
  boost::add_edge(11, 0, graph);

  auto vertex_cover_3 = bipartvc::get_minimal_vertex_cover(graph);
  ASSERT_EQ(vertex_cover_3.size(), 6);
  ASSERT_TRUE(bipartvc::is_valid_vertex_cover(graph, vertex_cover_3));

}

