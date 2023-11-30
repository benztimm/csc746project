cmake_minimum_required(VERSION 3.0)
project(KMPSearch VERSION 1.0)
find_package(OpenMP)

set(CMAKE_CXX_FLAGS_RELEASE "-O0")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(benchmark OBJECT benchmark.cpp)
target_compile_features(benchmark PRIVATE cxx_std_11)


add_executable(kmpsearch_basic kmp_basic.cpp)
target_link_libraries(kmpsearch_basic PRIVATE benchmark)
target_compile_features(kmpsearch_basic PRIVATE c_std_11 c_restrict)
target_compile_options(kmpsearch_basic PRIVATE -Wall -pedantic -march=native -O1)

add_executable(kmpsearch-openmp kmp_omp.cpp)
target_link_libraries(kmpsearch-openmp PRIVATE benchmark)
target_link_options(kmpsearch-openmp PRIVATE -fopenmp)
target_compile_features(kmpsearch-openmp PRIVATE c_std_11 c_restrict)
target_compile_options(kmpsearch-openmp PRIVATE -fopenmp -Wall -pedantic -march=native -O1)
set(BENCHMARK "openmp")