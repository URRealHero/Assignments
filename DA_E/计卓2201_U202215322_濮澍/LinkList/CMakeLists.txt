cmake_minimum_required (VERSION 3.10)
project(LinkList)
message(STATUS "root This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "root This is SOURCE dir " ${PROJECT_SOURCE_DIR})
aux_source_directory(. VAR)
add_executable(Display ${VAR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)


