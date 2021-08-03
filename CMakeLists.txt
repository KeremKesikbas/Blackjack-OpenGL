cmake_minimum_required(VERSION 3.2)

project(Blackjack)

file(GLOB PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp
                          ${CMAKE_SOURCE_DIR}/src/*.hpp
                          ${CMAKE_SOURCE_DIR}/src/*.h
                          ${CMAKE_SOURCE_DIR}/src/*.rc
                          ${CMAKE_SOURCE_DIR}/Dependencies/glad/glad.c)

set(glfw3_DIR ${CMAKE_SOURCE_DIR}/Dependencies/GLFW/lib/cmake/glfw3)
find_package(glfw3 3.3 REQUIRED)

set(Freetype_DIR ${CMAKE_SOURCE_DIR}/Dependencies/freetype/lib/cmake/freetype)
find_package(Freetype CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/Dependencies)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} freetype)