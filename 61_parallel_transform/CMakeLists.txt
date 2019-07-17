cmake_minimum_required(VERSION 3.10)
project (parallel_transforms)
add_executable(parallel_transforms parallel_transforms.cpp)
set_property(TARGET parallel_transforms PROPERTY CXX_STANDARD 17)

#https://stackoverflow.com/questions/1620918/cmake-and-libpthread
find_package (Threads)
target_link_libraries (parallel_transforms ${CMAKE_THREAD_LIBS_INIT})
