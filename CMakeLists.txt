cmake_minimum_required(VERSION 3.21)
project(conteiner)

#file(GLOB
#        FC "al_test/test_vector/vector_iterators/vector_iterators_r_iterator.cpp")

#file(GLOB
#        FC "test/sources/map_tests/upper_bound().cpp")

#file(GLOB
#        FC "testing.cpp")

file(GLOB
        FC "main.cpp")

set(CMAKE_CXX_STANDARD 98)

add_executable(conteiner ${FC})
