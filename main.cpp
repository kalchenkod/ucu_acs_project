#include <iostream>
#include <string>
#include <thread>
#include <tbb/concurrent_hash_map.h>
#include <opencv2/opencv.hpp>
#include "inc/time_measurement.h"
#include "inc/get_frames.h"
#include "inc/process_frame.h"
#include "inc/write_to_file.h"


int main() {
    std::string videoPath = "../test_4.mp4";
    int threads_num = 8;
    const auto fence_0 = get_current_time_fenced();

    std::vector<std::thread> threads;
    tbb::concurrent_hash_map<std::string, double> result_map;
    my_ts_que<cv::Mat> que_of_frames;

    std::thread frames_producer{get_frames, std::cref(videoPath), std::ref(que_of_frames)};

    for (int j = 0; j < threads_num; j++) {
        threads.emplace_back(process_frame, std::ref(que_of_frames), std::ref(result_map));
    }

    frames_producer.join();

    for(auto &thread: threads)
        thread.join();

    threads.clear();

    const auto fence_1 = get_current_time_fenced();
    std::cout << "Full time: " << to_us(fence_1 - fence_0) << std::endl;

    write_to_file(result_map);

    return 0;
}
