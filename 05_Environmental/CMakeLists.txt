cmake_minimum_required(VERSION 3.14)
project(pcreshow VERSION 1.1.1.1 LANGUAGES C CXX)

include_directories(lib)
add_executable(pcreshow window.c)

add_subdirectory(lib)


if(WITHOUT_UTF)
	add_definitions(-DWITHOUT_UTF)
endif()
message("flag = " ${WITHOUT_UTF})

find_library(PCRE2_LIBRARIES NAMES pcre2 pcre2-8)
find_path(PCRE2_INCLUDE_DIRS pcre2.h)
add_custom_target(pcre2)

find_package(Curses REQUIRED)

include_directories(
	${CURSES_INCLUDE_DIRS}
	${PCRE2_INCLUDE_DIRS} )

target_link_libraries(pcreshow pcre ncurses ${CURSES_LIBRSRIES}  ${PCRE2_LIBRARIES})
