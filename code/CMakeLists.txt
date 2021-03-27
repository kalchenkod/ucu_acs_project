cmake_minimum_required(VERSION 3.17)
project(Semester_project)

set(CMAKE_CXX_STANDARD 14)
find_package( OpenCV REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(Semester_project main.cpp)

target_link_libraries( Semester_project ${OpenCV_LIBS} )