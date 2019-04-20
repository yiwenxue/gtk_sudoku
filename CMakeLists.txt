cmake_minimum_required(VERSION 2.8.9)
project(sudoku_gtk)

include_directories(include)

set(SRC src/main.c )

add_library(sudoku src/sudoku.c)

add_executable(sudoku_gtk ${SRC})

FIND_PACKAGE(PkgConfig REQUIRED)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

TARGET_LINK_LIBRARIES(sudoku_gtk sudoku m ${GTK3_LIBRARIES})
