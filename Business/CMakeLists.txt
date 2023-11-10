cmake_minimum_required(VERSION 3.5)

link_directories(../)

# 收集源码
file(GLOB_RECURSE SRC_PATHS *.h *.hpp *.cc *.cpp *.c)

add_library(business ${SRC_PATHS})

target_link_libraries(business utils)
