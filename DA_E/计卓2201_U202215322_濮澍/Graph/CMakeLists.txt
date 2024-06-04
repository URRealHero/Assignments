
cmake_minimum_required(VERSION 3.15)
project(2020ds_08_Graph)
#将srcs中的所有文件编译到bin中生成Display可执行文件
aux_source_directory(./src srcs)
#需要将生成的可执行文件放到bin中
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
add_executable(Display ${srcs})

