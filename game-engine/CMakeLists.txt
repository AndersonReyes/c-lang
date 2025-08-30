cmake_minimum_required(VERSION 3.15...4.0)

SET (CMAKE_CXX_FLAGS_INIT "-Wall -Werror")

project(GameEngine LANGUAGES CXX)

add_library(gamelib STATIC src/hello.cpp include/hello.hpp)
target_include_directories(gamelib PUBLIC include)
target_compile_features(gamelib PUBLIC cxx_std_17)

add_executable(hello apps/hello_main.cpp)
target_link_libraries(hello PUBLIC gamelib)
