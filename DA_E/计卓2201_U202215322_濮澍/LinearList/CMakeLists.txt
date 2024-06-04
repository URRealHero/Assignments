# CMake 最低版本号要求
cmake_minimum_required (VERSION 3.10)
# 项目工程名
project (LinearList)
message(STATUS "root This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "root This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 添加子目录
ADD_SUBDIRECTORY(src Funcs)
