cmake_minimum_required(VERSION 3.12)

# add_definitions(-DWITH_NEON)
# add_definitions(-DWITH_AVX2)

project(cnn)

set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_CXX_FLAGS "-O3 -mavx -I /opt/OpenBLAS/include/ -L/opt/OpenBLAS/lib -lopenblas")

find_package(OpenCV CONFIG REQUIRED)
# find_package(OpenMP REQUIRED)

ADD_EXECUTABLE(cnn main.cpp matrix.hpp face_binary_cls.cpp)

target_link_libraries(cnn ${OpenCV_LIBS})
# target_link_libraries(cnn ${BLAS_LIBRARY})

