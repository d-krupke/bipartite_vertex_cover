# Minimal Vertex Cover in Bipartite Graphs

This repository provides a simple implementation of [Koenig's theorem](https://en.wikipedia.org/wiki/Kőnig's_theorem_(graph_theory)) to obtain a minimum vertex cover in bipartite graphs using the C++ Boost Graph Library.
The implementation is not optimized but should in general be fast enough (the bottleneck should be the maximum matching algorithm of Boost).

See [example](./example) and [test file](./library_gtest.cpp) to obtain a quick impression on how to use it.

For my application I have already given a partition so that there is no need to compute it anew.
Hence, the basic interface also demands a functor/lambda that classifies the vertices.
There is also an interface for which this is not necessary (the computation is done by boost::is_bipartite).

**This implementation is not yet finished.**

