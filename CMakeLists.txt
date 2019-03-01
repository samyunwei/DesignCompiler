cmake_minimum_required(VERSION 3.10)

project(DesignComplier)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_library(LEX_LIB l REQUIRED)

set(CMAKE_AUTOMOC ON)

add_subdirectory(calculator)
add_subdirectory(crowbar)
