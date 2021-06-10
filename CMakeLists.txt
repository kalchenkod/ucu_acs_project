cmake_minimum_required(VERSION 3.17)
project(video)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)
find_package(tbb REQUIRED)
find_package(Threads REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(video main.cpp
        src/get_frames.cpp
        src/process_frame.cpp
        src/write_to_file.cpp
        inc/write_to_file.h
        inc/process_frame.h
        inc/get_frames.h
        inc/time_measurement.h
        inc/que.h)

target_link_libraries(video LINK_PUBLIC ${OpenCV_LIBS})
target_link_libraries(video LINK_PUBLIC TBB::tbb)
TARGET_LINK_LIBRARIES(video LINK_PUBLIC Threads::Threads )