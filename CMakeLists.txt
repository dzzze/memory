cmake_minimum_required(VERSION 3.13)

project(dze_memory)

add_library(dze_memory INTERFACE)
target_include_directories(dze_memory INTERFACE include)
add_library(dze::memory ALIAS dze_memory)
