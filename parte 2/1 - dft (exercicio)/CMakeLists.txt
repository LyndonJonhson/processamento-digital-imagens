cmake_minimum_required(VERSION 3.0.0)
project(dft VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(dft dft.cpp)
target_link_libraries(dft ${OpenCV_LIBS})

cmake_minimum_required(VERSION 3.0.0)
project(dft_filestorage VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(dft_filestorage dft_filestorage.cpp)
target_link_libraries(dft_filestorage ${OpenCV_LIBS})