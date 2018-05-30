//
// Created by Dominik Krupke, http://krupke.cc on 10/7/17.
//

#ifndef BIPARTITE_VERTEX_COVER_VERTEXCOVERSOLVER_H
#define BIPARTITE_VERTEX_COVER_VERTEXCOVERSOLVER_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "../Partition.h"
#include "MatchingSolver.h"

namespace bipartvc {
namespace details {
template<typename G, typename F>
class VertexCoverSolver {
 public:
  VertexCoverSolver(const G &graph, F partition_classifier) : graph{&graph},
                                                              partition_classifier{partition_classifier} {
    in_vertex_cover.resize(boost::num_vertices(graph), false);
  }

  bool
  solve() {
    details::MatchingSolver<G> matchingSolver{*graph};
    matchingSolver.solve();
    add_necessary_vertices_of_partition_a(matchingSolver);
    add_remaining_necessary_vertices_from_partition_b(matchingSolver);
    return true;
  }

  bool
  isInVertexCover(Vertex<G> v) {
    const auto idx = boost::get(boost::vertex_index, *graph, v);
    return in_vertex_cover.at(idx);
  }

 private:
  void
  add_necessary_vertices_of_partition_a(const details::MatchingSolver<G> &matchingSolver) {
    for (const auto &v: boost::make_iterator_range(boost::vertices(*graph))) {
      if (partition_classifier(v) == Partition::A) {
        if (matchingSolver.isMatched(v)) {
          for (const auto &n: make_iterator_range(boost::adjacent_vertices(v, *graph))) {
            if (!matchingSolver.isMatched(n)) {
              recursive_add(v, matchingSolver);
            }
          }
        }
      }
    }
  }

  void
  add_remaining_necessary_vertices_from_partition_b(const details::MatchingSolver<G> &matchingSolver) {
    for (const auto &v: boost::make_iterator_range(boost::vertices(*graph))) {
      if (partition_classifier(v) == Partition::B) {
        if (matchingSolver.isMatched(v)) {
          if (!in_vertex_cover.at(matchingSolver.getPartner(v))) {
            const auto idx = boost::get(boost::vertex_index, *graph, v);
            in_vertex_cover[idx] = true;
            size += 1;
          }
        }
      }
    }
  }

  void
  recursive_add(Vertex<G> v, const details::MatchingSolver<G> &matchingSolver) {
    const auto idx = boost::get(boost::vertex_index, *graph, v);
    if (in_vertex_cover.at(idx)) { return; }
    in_vertex_cover.at(idx) = true;
    size += 1;
    auto n = matchingSolver.getPartner(v);
    for (const auto &nn: boost::make_iterator_range(boost::adjacent_vertices(n, *graph))) {
      assert(matchingSolver.isMatched(nn));
      recursive_add(nn, matchingSolver);
    }
  }

  const G *graph;
  F partition_classifier;
  std::vector<bool> in_vertex_cover;
  size_t size = 0;
};
}
}

#endif //BIPARTITE_VERTEX_COVER_VERTEXCOVERSOLVER_H
