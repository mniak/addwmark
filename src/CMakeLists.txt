cmake_minimum_required(VERSION 3.0.2)

find_package(OpenCV REQUIRED)

project(addwmark)
add_executable(addwmark addwmark.cpp)
target_link_libraries(addwmark ${OpenCV_LIBS})

