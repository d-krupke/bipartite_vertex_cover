#ifndef BIPARTITE_VERTEX_COVER_LIBRARY_H
#define BIPARTITE_VERTEX_COVER_LIBRARY_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <vector>
#include "details/utils.h"
#include "details/MatchingSolver.h"
#include "./Partition.h"
#include "details/VertexCoverSolver.h"
#include <boost/graph/bipartite.hpp>

namespace bipartvc
{

  /// For checking if a given partition is a valid bipartition of the graph.
  /// You can also use boost::is_bipartite. This one is just to evaluate the partition_classifier.
  /// \tparam G A boost graph, e.g., boost::adjacency_list<...>
  /// \tparam F A functor/lambda '(vertex_descriptor)->Partition' that classifies the partition. See ./Partition.cpp
  /// \param graph The graph
  /// \param partition_classifier The functor/lambda
  /// \return True, iff valid bipartition.
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

  /// Checks if a given vertex cover actually covers all edges in a graph. Does not check for optimality.
  /// \tparam G A boost graph, e.g., boost::adjacency_list<...>
  /// \param graph The graph
  /// \param vertex_cover A list with all the vertices in the vertex cover.
  /// \return true iff valid
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

  /// Computes a min vertex cover of a bipartite graph.
  /// \tparam G A BGL graph, e.g., boost::adjacency_list<...>
  /// \tparam F A functor/lambda '(vertex_descriptor)->Partition' that classifies the partition. See ./Partition.cpp
  /// \param graph The bipartite graph
  /// \param partition_classifier The functor/lambda
  /// \return A vector with all the vertices selected for the vertex cover. No repetitions in it.
  template<typename G, typename F>
  std::vector<typename boost::graph_traits<G>::vertex_descriptor>
  get_minimal_vertex_cover(const G &graph, F partition_classifier)
  {
    std::vector<typename boost::graph_traits<G>::vertex_descriptor> vertex_cover;

    assert(bipartvc::is_bipartite(graph, partition_classifier));
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

  /// Computes a min vertex cover of a bipartite graph.
  /// \tparam G A BGL graph, e.g., boost::adjacency_list<...>
  /// \param graph The bipartite graph
  /// \return A vector with all the vertices selected for the vertex cover. No repetitions in it.
  template<typename G>
  std::vector<typename boost::graph_traits<G>::vertex_descriptor>
  get_minimal_vertex_cover(const G &graph)
  {
    //see http://www.boost.org/doc/libs/1_61_0/libs/graph/example/bipartite_example.cpp
    using partition_t = std::vector<boost::default_color_type>;
    using index_map_t = typename boost::property_map<G, boost::vertex_index_t>::type;
    using partition_map_t = boost::iterator_property_map<partition_t::iterator, index_map_t>;

    partition_t partition(boost::num_vertices(graph));
    partition_map_t partition_map(partition.begin(), get(boost::vertex_index, graph));

    auto is_bip = boost::is_bipartite(graph, boost::get(boost::vertex_index, graph), partition_map);
    assert(is_bip);

    auto partition_classifier = [&](typename boost::graph_traits<G>::vertex_descriptor v) {
        if (boost::get(partition_map, v) == boost::color_traits<boost::default_color_type>::white()) {
          return Partition::A;
        } else {
          return Partition::B;
        }
    };

    return get_minimal_vertex_cover(graph, partition_classifier);
  }
}

#endif