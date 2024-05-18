cmake_minimum_required(VERSION 3.0.0)
project(AIM VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

file(GLOB_RECURSE SRC_FILES "src/*.c")

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_STANDARD 99)

add_executable(AIM src/main.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
target_link_libraries(AIM ${CURSES_LIBRARIES})
target_include_directories(AIM PUBLIC src)
include(CPack)