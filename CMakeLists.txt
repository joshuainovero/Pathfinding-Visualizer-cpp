cmake_minimum_required(VERSION 3.16.3)

project(PathfindingVisualizer)

set(GCC_FLAGS "-Wall -std=c++17")
set(SF_LIB "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${GCC_FLAGS} ${SF_LIB}")
else()
    set(CMAKE_CXX_FLAGS "${GCC_FLAGS} -L../External/SFML/lib  ${SF_LIB}")
endif ()

include_directories(${PROJECT_SOURCE_DIR}/External/SFML/include)

add_executable(PathfindingVisualizer ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB HEADERS_ ${PROJECT_SOURCE_DIR}/src/utils/*.hpp)
file (GLOB CPP_ ${PROJECT_SOURCE_DIR}/src/utils/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_library(pv_app ${HEADERS_} ${CPP_})
target_link_libraries(PathfindingVisualizer pv_app ${SF_LIB})