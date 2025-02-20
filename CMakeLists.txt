cmake_minimum_required(VERSION 3.17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER /usr/bin/clang)
set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(rpg)

set(CMAKE_BUILD_TYPE Debug)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(MAIN_TARGET main)

    # If I need later...
# file(GLOB SOURCES ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

add_subdirectory(${LIB_DIR}/raylib)
add_subdirectory(${LIB_DIR}/tmx)
# add_subdirectory(${LIB_DIR}/raylib-tmx)

add_executable(${MAIN_TARGET} ${SOURCES})

target_include_directories(${MAIN_TARGET} PRIVATE ${SRC_DIR})
target_include_directories(${MAIN_TARGET} PRIVATE ${LIB_DIR}/raylib/src)
target_include_directories(${MAIN_TARGET} PRIVATE ${LIB_DIR}/tmx/src)
target_include_directories(${MAIN_TARGET} PRIVATE ${LIB_DIR}/raylib-tmx/include)

target_compile_features(${MAIN_TARGET} PRIVATE cxx_std_17)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(${MAIN_TARGET} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(${MAIN_TARGET} PRIVATE -lstdc++fs)
target_link_libraries(${MAIN_TARGET} PRIVATE raylib)
target_link_libraries(${MAIN_TARGET} PRIVATE tmx)

set_target_properties(${MAIN_TARGET} PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

