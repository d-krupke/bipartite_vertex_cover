# Minimal Vertex Cover in Bipartite Graphs

This repository provides a simple implementation of [Koenig's theorem](https://en.wikipedia.org/wiki/Kőnig's_theorem_(graph_theory)) to obtain a minimum vertex cover in bipartite graphs using the C++ Boost Graph Library.
The implementation is not optimized but should in general be fast enough (the bottleneck should be the maximum matching algorithm of Boost).

See [example](./example) and [test file](min_vertex_cover_gtest.cpp) to obtain a quick impression on how to use it.

For my application I have already given a partition so that there is no need to compute it anew.
Hence, the basic interface also demands a functor/lambda that classifies the vertices.
There is also an interface for which this is not necessary (the computation is done by boost::is_bipartite).

**This implementation is not yet finished.**

Since the implementation uses templates, it can be considered header-only.
Thus, you can simply copy this repository into your project and use it.
No further adaptions should be necessary since you should already have the BGL included.
Otherwise, see the CMake (which only provides the unit test) on how to integrate the Boost Graph Library into your project.
