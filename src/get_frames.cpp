#include <iostream>
#include <opencv2/opencv.hpp>
#include "../inc/time_measurement.h"
#include "../inc/que.h"


void get_frames(const std::string &path, my_ts_que<cv::Mat> &que_of_frames) {
    cv::VideoCapture capture;
    cv::Mat BGR, HSV, resized;

    if (!capture.open(path)) {
        std::cerr << "Video Not Found" << std::endl;
        return;
    }

    const auto fence_0 = get_current_time_fenced();

    while (true) {
        capture >> BGR;

        if (BGR.empty()) {
            que_of_frames.push(BGR);
            break;
        }

        cv::cvtColor(BGR, HSV, cv::COLOR_BGR2HLS);
        cv::resize(HSV, resized, cv::Size(144,144));

        que_of_frames.push(resized);
    }
    capture.release();
    const auto fence_1 = get_current_time_fenced();

    //std::cout << "Read finished in: " << to_us(fence_1 - fence_0) << std::endl;
}

