

# Importing all files ending with "_gtest.cpp". While I do not recommand this way in general, it makes sure that no
# test has been forgotten (which happens too easily). However, only files that were existant while loading CMake are
# integrated. If you add a new test, you have to add it manually or reload CMake.
file(GLOB_RECURSE GTEST_SOURCES "../**/*_gtest.cpp")
MESSAGE("Including the following gtest files: ${GTEST_SOURCES}")

add_executable(unit_tester ${GTEST_SOURCES} ./gtest_main.cpp ../library_gtest.cpp)

target_link_libraries(unit_tester gtest)

target_include_directories(unit_tester PRIVATE ${INCLUDE_DIRS})
target_link_libraries(unit_tester ${LIBRARIES})