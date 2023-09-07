cmake_minimum_required(VERSION 3.20)

project(string-c)

include_directories(include)

set(LIB_C_SOURCE_FILES src/str.c)
set(C_SOURCE_FILES src/main.c)

add_library(string_c ${LIB_C_SOURCE_FILES})

add_executable(${PROJECT_NAME} ${C_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} string_c)
