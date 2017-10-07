# Minimal Vertex Cover in Bipartite Graphs

This repository provides a simple implementation of [Koenig's theorem](https://en.wikipedia.org/wiki/Kőnig's_theorem_(graph_theory)) to obtain a minimum vertex cover in bipartite graphs using the C++ Boost Graph Library.
The implementation is not optimized but should in general be fast enough (the bottleneck should be the maximum matching algorithm of Boost).

See [example](./example) and [test file](./library_gtest.cpp) to obtain a quick impression on how to use it.

As the partition of the bipartite graph is for most applications that come to my mind known, it has to be provided by you via a simple Lambda/functor.
Maybe I will implement a version with automatic detection.

**This implementation is not yet finished.**

