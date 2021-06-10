#ifndef VIDEO_GET_FRAMES_H
#define VIDEO_GET_FRAMES_H

#include <opencv2/opencv.hpp>
#include <string>
#include "que.h"

void get_frames(const std::string &path, my_ts_que<cv::Mat> &que_of_frames);

#endif //VIDEO_GET_FRAMES_H
