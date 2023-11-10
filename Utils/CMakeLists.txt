cmake_minimum_required(VERSION 3.5)

# 收集源码
file(GLOB_RECURSE SRC_PATHS *.h *.hpp *.cc *.cpp *.c)

add_library(utils ${SRC_PATHS})
