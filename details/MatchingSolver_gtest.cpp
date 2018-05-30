//
// Created by Dominik Krupke, http://krupke.cc on 10/7/17.
//

#include <gtest/gtest.h>
#include <boost/graph/adjacency_list.hpp>
#include "MatchingSolver.h"

TEST(MatchingSolver, MatchWithIsolatedVertex){
  using Graph = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS>;
  Graph graph{7};
  auto e1 = boost::add_edge(0,3, graph).first;
  boost::add_edge(0,4, graph);
  boost::add_edge(0,5, graph);
  auto e2 = boost::add_edge(1,4, graph).first;
  auto e3 = boost::add_edge(2,5, graph).first;

  bipartvc::details::MatchingSolver<Graph> matchingSolver{graph};
  ASSERT_TRUE(matchingSolver.solve());
  for(unsigned int i=0; i<6; ++i){

    ASSERT_TRUE(matchingSolver.isMatched(i));
  }
  ASSERT_FALSE(matchingSolver.isMatched(6));

  ASSERT_EQ(matchingSolver.getPartner(0), 3);
  ASSERT_EQ(matchingSolver.getPartner(1), 4);
  ASSERT_EQ(matchingSolver.getPartner(2), 5);
  ASSERT_EQ(matchingSolver.getPartner(3), 0);
  ASSERT_EQ(matchingSolver.getPartner(4), 1);
  ASSERT_EQ(matchingSolver.getPartner(5), 2);
  ASSERT_EQ(matchingSolver.getPartner(6), boost::graph_traits<Graph>::null_vertex());
}