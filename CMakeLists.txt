cmake_minimum_required(VERSION 3.24)
project(RayMarching_SFML)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
add_executable(tests Object.h Ray.h Camera.h Camera.cpp Math.h Math.cpp RMalgo.h main.cpp RMalgo.cpp)
target_link_libraries(tests sfml-graphics sfml-audio)
