cmake_minimum_required(VERSION 3.5)

project(SimpleNetRoutine)

# 添加源代码目录
aux_source_directory(./src DIR_SOURCES_1)
include_directories(./src)

# 添加可执行文件
add_executable(SNR ${DIR_SOURCES_1})