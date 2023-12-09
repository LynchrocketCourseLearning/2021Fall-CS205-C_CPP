cmake_minimum_required(VERSION 3.16.3)

project(matmul)

aux_source_directory(./src DIR_SRCS)

add_executable(matmul ${DIR_SRCS})