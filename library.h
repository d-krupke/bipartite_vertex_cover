#ifndef BIPARTITE_VERTEX_COVER_LIBRARY_H
#define BIPARTITE_VERTEX_COVER_LIBRARY_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include "details/utils.h"
#include "details/MatchingSolver.h"
#include "./Partition.h"
#include "details/VertexCoverSolver.h"

namespace bipartvc
{

  template<typename G, typename F>
  bool
  is_bipartite(const G &graph, F partition_classifier)
  {
    for (const auto &v: boost::make_iterator_range(boost::vertices(graph))) {
      for (const auto &n: boost::make_iterator_range(boost::adjacent_vertices(v, graph))) {
        if (partition_classifier(v) == partition_classifier(n)) { return false; }
      }
    }
    return true;
  };

  template<typename G>
  bool
  is_valid_vertex_cover(const G &graph,
                        const std::vector<typename boost::graph_traits<G>::vertex_descriptor> &vertex_cover)
  {
    for (const auto &e: boost::make_iterator_range(boost::edges(graph))) {
      if (!details::is_edge_covered<G>(e, graph, vertex_cover)) {
        return false;
      }
    }
    return true;
  }

  /// Returns a vector with all selected vertices
  /// @input graph: A BGL graph
  /// @input partition_classifier: (vertex_descriptor)->Partition A functor (e.g. lambda) that classifies the vertices
  /// into the partitions.
  template<typename G, typename F>
  std::vector<typename boost::graph_traits<G>::vertex_descriptor>
  get_minimal_vertex_cover(const G &graph, F partition_classifier)
  {
    std::vector<typename boost::graph_traits<G>::vertex_descriptor> vertex_cover;

    assert(is_bipartite(graph, partition_classifier));
    details::VertexCoverSolver<G, F> vertex_cover_solver{graph, partition_classifier};
    vertex_cover_solver.solve();

    for (const auto &v: boost::make_iterator_range(boost::vertices(graph))) {
      if (vertex_cover_solver.isInVertexCover(v)) {
        vertex_cover.push_back(v);
      }
    }
    assert(is_valid_vertex_cover<G>(graph, vertex_cover)); //if this fails, the library is buggy.
    return vertex_cover;
  }
}

#endif