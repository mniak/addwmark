cmake_minimum_required(VERSION 3.0.2)

set(BOOST_ROOT /usr/bin)
set(BOOST_INCLUDEDIR 1.67)

find_package(OpenCV REQUIRED)
#find_package(Boost 1.67 REQUIRED)

project(addwmark)
add_executable(addwmark addwmark.cpp)
