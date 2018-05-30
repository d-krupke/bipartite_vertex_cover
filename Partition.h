//
// Created by Dominik Krupke, http://krupke.cc on 10/7/17.
//

#ifndef BIPARTITE_VERTEX_COVER_PARTITION_H
#define BIPARTITE_VERTEX_COVER_PARTITION_H
namespace bipartvc
{

  // Every vertex has to be either in A or B. There are not edges within these sets allowed (bipartite graphs).
  enum class Partition
  {
    A, B
  };

}

#endif //BIPARTITE_VERTEX_COVER_PARTITION_H
