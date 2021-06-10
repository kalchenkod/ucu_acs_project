#ifndef VIDEO_PROCESS_FRAME_H
#define VIDEO_PROCESS_FRAME_H

#include <opencv2/opencv.hpp>
#include <tbb/concurrent_hash_map.h>
#include "que.h"

void process_frame(my_ts_que<cv::Mat> &que_of_frames,
                   tbb::concurrent_hash_map<std::string, double> &result_map);

#endif //VIDEO_PROCESS_FRAME_H
