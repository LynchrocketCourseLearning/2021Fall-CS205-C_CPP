cmake_minimum_required(VERSION 3.16.3)

project(lab_exercise)

aux_source_directory(./e1 DIR_SRCS)

add_executable(lab_exercise ${DIR_SRCS})