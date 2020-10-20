cmake_minimum_required(VERSION 3.10)
project(learn_cxx)

set(CMAKE_CXX_STANDARD 11)

add_executable(learn_cxx.out main.cpp)
add_executable(readFile.out readFile.cpp)
add_executable(bloom.out bloomFilter.cpp fnv.h myVector.cpp)
add_executable(helloTemplate.out helloTemplate.cpp)
add_executable(helloMultisets.out helloMultisets.cpp)
add_executable(serialize.out serialize.cpp)
add_executable(myVector.out myVector.cpp)
