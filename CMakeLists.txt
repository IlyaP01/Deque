cmake_minimum_required (VERSION 3.8)

project ("Deque" LANGUAGES CXX)

add_executable (main "src/main.cpp"  "src/Deque/deque.hpp")

set (gtest_force_shared_crt ON CACHE BOOL "MSVC defaults to shared CRT" FORCE)
add_subdirectory(dependencies/googletest)
target_compile_definitions(gtest
  PUBLIC
    GTEST_LANG_CXX17
    GTEST_HAS_TR1_TUPLE=0
)
add_executable(tests)
target_sources(tests
  PRIVATE
    tests/tests.cpp
)
set_target_properties(tests PROPERTIES COMPILE_FLAGS "${cxx_strict}")
target_link_libraries(tests gtest_main)
enable_testing()
#add_test(NAME sample_test COMMAND tests)
include(GoogleTest)
gtest_add_tests(TARGET tests SOURCES tests/tests.cpp)