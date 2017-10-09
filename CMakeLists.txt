cmake_minimum_required(VERSION 3.8)
project(BipartiteVertexCover CXX)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS graph REQUIRED)
set(LIBRARIES ${Boost_LIBRARIES})
set(INCLUDE_DIRS ${CPLEX_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

add_subdirectory(./testing)