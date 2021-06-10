#include <iostream>
#include <opencv2/opencv.hpp>
#include <tbb/concurrent_hash_map.h>
#include <cmath>
#include "../inc/que.h"


void process_frame(my_ts_que<cv::Mat> &que_of_frames,
                   tbb::concurrent_hash_map<std::string, double> &result_map) {
    while (true) {
        cv::Mat frame = que_of_frames.pop();

        if (frame.empty()) {
            que_of_frames.push(frame);
            return;
        }

        for (size_t i = 0; i < frame.rows; i++) {
            for (size_t j = 0; j < frame.cols; j++) {
                const auto hsv_pixel = frame.at<cv::Vec3b>(i, j);

                std::string key = std::to_string((int) hsv_pixel[0]);

                double S = hsv_pixel[2];
                double L = hsv_pixel[1];
                double value = S * (pow(0.5, 2) - pow((0.5 - (L/255)), 2)) / (pow(0.5, 2) * 255);

                tbb::concurrent_hash_map<std::string, double>::accessor a;
                result_map.insert(a, key);
                a->second += value;
                a.release();
            }
        }
    }
}
