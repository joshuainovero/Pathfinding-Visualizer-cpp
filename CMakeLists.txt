cmake_minimum_required(VERSION 3.16.3)

project(PathfindingVisualizer)

set(GCC_FLAGS "-Wall -std=c++17")
set(SF_LIB "-lsfml-graphics -lsfml-window -lsfml-system")
set(ICON_RES "")

if (UNIX AND NOT APPLE)
    set(CMAKE_CXX_FLAGS "${GCC_FLAGS} ${SF_LIB}")
else()
    set(CMAKE_CXX_FLAGS "${GCC_FLAGS} -mwindows -L../External/SFML/lib  ${SF_LIB}")
    set(ICON_RES ${PROJECT_SOURCE_DIR}/src/iconres.res)
endif ()

include_directories(${PROJECT_SOURCE_DIR}/External/SFML/include)

add_executable(PathfindingVisualizer ${PROJECT_SOURCE_DIR}/src/main.cpp)

file(GLOB HEADERS_ ${PROJECT_SOURCE_DIR}/src/Pathfinding-Visualizer/*.hpp)
file (GLOB CPP_ ${PROJECT_SOURCE_DIR}/src/Pathfinding-Visualizer/*.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

add_library(pv_app ${HEADERS_} ${CPP_})
target_link_libraries(PathfindingVisualizer pv_app ${SF_LIB} ${ICON_RES})