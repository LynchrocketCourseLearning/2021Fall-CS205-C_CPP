cmake_minimum_required(VERSION 3.16.3)
project(matmul)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_FLAGS "-O3 -mavx -I /opt/OpenBLAS/include/ -L/opt/OpenBLAS/lib -lopenblas")

aux_source_directory(. DIR_SRC)

add_executable(matmul ${DIR_SRC})

target_link_libraries(matmul ${BLAS_LIBRARY})
