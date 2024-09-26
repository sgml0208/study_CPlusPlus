#声明要求的cmake最低版本
cmake_minimum_required(VERSION 3.10)

#设置c++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#声明一个cmake工程
project("STUDY_C++")

# 添加警告调试信息
add_definitions(-Wall -g)

#添加头文件  ${PROJECT_SOURCE_DIR}是一个内置变量，它代表了项目的源代码根目录。include是相对于项目源代码根目录的路径。
# include_directories(${PROJECT_SOURCE_DIR}/include)

#添加可执行程序
add_executable(study_c++ 
        base_knowledges/3_function.cpp
) 

