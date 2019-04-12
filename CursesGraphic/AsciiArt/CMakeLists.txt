cmake_minimum_required (VERSION 2.6)
project (AsciiArt)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(ascii_art ascii_art.c)
target_link_libraries(ascii_art ${CURSES_LIBRARIES})
