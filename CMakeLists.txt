cmake_minimum_required(VERSION 3.8)
project(bipartite_vertex_cover)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS graph REQUIRED)
set(LIBRARIES ${Boost_LIBRARIES})
set(INCLUDE_DIRS ${CPLEX_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

set(SOURCE_FILES library.cpp library.h details/utils.h details/MatchingSolver.cpp details/MatchingSolver.h details/VertexCoverSolver.cpp details/VertexCoverSolver.h Partition.cpp Partition.h)
add_library(bipartite_vertex_cover ${SOURCE_FILES})

target_link_libraries(bipartite_vertex_cover ${LIBRARIES})

add_subdirectory(./testing)