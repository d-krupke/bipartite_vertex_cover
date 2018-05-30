//
// Created by Dominik Krupke, http://krupke.cc on 10/7/17.
//

#ifndef BIPARTITE_VERTEX_COVER_UTILS_H
#define BIPARTITE_VERTEX_COVER_UTILS_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

namespace bipartvc
{
  namespace details
  {
    template<typename G>
    using Edge = typename boost::graph_traits<G>::edge_descriptor;

    template<typename G>
    using Vertex = typename boost::graph_traits<G>::vertex_descriptor;

    template<typename G>
    bool
    is_edge_covered(Edge<G> e, const G &graph, const std::vector<Vertex<G>> &vertex_cover)
    {
      const auto &v = boost::source(e, graph);
      const auto &w = boost::target(e, graph);
      return !(std::find(vertex_cover.begin(), vertex_cover.end(), v) == vertex_cover.end() &&
               std::find(vertex_cover.begin(), vertex_cover.end(), w) == vertex_cover.end());
    }


  }
}


#endif //BIPARTITE_VERTEX_COVER_UTILS_H
