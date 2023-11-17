cmake_minimum_required(VERSION 3.20)

project(Music-Player)

add_executable(${PROJECT_NAME} main.cpp str.cpp song.cpp UI.cpp)

include_directories(${PROJECT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE Resource.rc)

# target_link_libraries(${PROJECT_NAME} winmm)
