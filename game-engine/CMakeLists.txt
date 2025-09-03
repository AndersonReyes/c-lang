cmake_minimum_required(VERSION 3.15...4.0)

SET (CMAKE_CXX_FLAGS_INIT "-Wall -Werror")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CORE_SOURCE ./src/*.cpp)
file(GLOB_RECURSE CORE_HEADER ./include/*.hpp)

project(GameEngine LANGUAGES CXX)


# SDL
# 
# This assumes you have added SDL as a submodule in vendored/SDL
add_subdirectory(vendor/SDL EXCLUDE_FROM_ALL)
## Glm 
add_subdirectory(vendor/glm EXCLUDE_FROM_ALL)

# Engine Lib
add_library(gamelib STATIC ${CORE_HEADER} ${CORE_SOURCE})
target_include_directories(gamelib PUBLIC include)
target_compile_features(gamelib PUBLIC cxx_std_23)

## SDL Dep
target_link_libraries(gamelib PRIVATE SDL3::SDL3)
target_include_directories(gamelib PUBLIC vendor/SDL/include)

## Glm Dep
target_link_libraries(gamelib PRIVATE glm::glm)
target_include_directories(gamelib PUBLIC vendor/glm)


# Apps
add_executable(hello apps/hello_main.cpp)
target_link_libraries(hello PUBLIC gamelib)

## Particles
add_executable(particles apps/particles.cpp)
target_link_libraries(particles PUBLIC gamelib)
