message(STATUS "src This is BINARY dir " ${PROJECT_BINARY_DIR})
message(STATUS "src This is SOURCE dir " ${PROJECT_SOURCE_DIR})

# 定义源文件列表
AUX_SOURCE_DIRECTORY(. SRC_LIST)

# 指定最终生成的可执行文件的路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../lib)

# 指定生成目标 目标名字随便写；${SRC_LIST}代表前面定义的源文件列表变量
ADD_LIBRARY(Funcs MODULE ${SRC_LIST})
# 指定静态库名 
ADD_LIBRARY(Funcs_Static STATIC ${SRC_LIST})
# 改变最终生成的静态库的名字
SET_TARGET_PROPERTIES(Funcs_Static PROPERTIES OUTPUT_NAME Funcs)
# 获取指定构建目标的指定属性的值；这里获取math_static的属性OUTPUT_NAME值赋值给OUTPUT_VALUE变量
GET_TARGET_PROPERTY(OUTPUT_VALUE Funcs_Static OUTPUT_NAME)
MESSAGE(STATUS "This is the math_static OUTPUT_NAME:" ${OUTPUT_VALUE})
