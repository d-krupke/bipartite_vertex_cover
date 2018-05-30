//
// Created by Dominik Krupke, http://krupke.cc on 10/7/17.
//

#ifndef BIPARTITE_VERTEX_COVER_MATCHINGSOLVER_H
#define BIPARTITE_VERTEX_COVER_MATCHINGSOLVER_H

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include "./utils.h"

namespace bipartvc
{
  namespace details
  {
    template<typename G>
    class MatchingSolver
    {
      std::vector<Vertex<G>> partner;
      const G* graph;

    public:
      explicit MatchingSolver(const G &graph) : graph{&graph}
      {
        partner.resize(boost::num_vertices(graph), boost::graph_traits<G>::null_vertex());
      }

      bool
      solve()
      {
        bool success = boost::checked_edmonds_maximum_cardinality_matching(*graph, &partner[0]);
        return success;
      }

      Vertex<G>
      getPartner(Vertex<G> v)
      const
      {
        auto idx = boost::get(boost::vertex_index, *graph, v);
        return partner.at(idx);
      }

      bool
      isMatched(Vertex<G> v)
      const
      {
        return getPartner(v) != boost::graph_traits<G>::null_vertex();
      }
    };

  }
}


#endif //BIPARTITE_VERTEX_COVER_MATCHINGSOLVER_H
