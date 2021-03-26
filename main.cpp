#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>


void get_info (const cv::Mat &image) {
    std::cout << "-------------------------" << std::endl;
    std::cout << "cols " << image.cols << std::endl;
    std::cout << "rows " << image.rows << std::endl;
    std::cout << "height " << image.size().height << std::endl;
    std::cout << "width " << image.size().width << std::endl;
    std::cout << "channels  " << image.channels() << std::endl;
    std::cout << "depth  " << image.depth() << std::endl;
    std::cout << "type  " << image.type() << std::endl;
    std::cout << "-------------------------" << std::endl;
}


std::vector<std::vector<std::vector<int>>> read_image (const std::string &path) {
    std::vector<std::vector<std::vector<int>>> content;
    cv::Mat image = cv::imread(path);

    //get_info(image);
    if(image.empty())
    {
        std::cerr << "Image reading error" << std::endl;
        return content;
    }

    for(size_t i = 0;i < image.rows; i++)
    {
        std::vector<std::vector<int>> row;
        for(size_t j = 0; j<image.cols; j++)
        {
            cv::Vec3b intensity = image.at<cv::Vec3b>(i, j);
            std::vector<int> point = { (int)intensity.val[1],
                                       (int)intensity.val[0],
                                       (int)intensity.val[2]};
            row.push_back(point);
        }
        content.push_back(row);
    }
    return content;
}


int main() {
    const auto data = read_image("../bad.jpg");

    //blue - green - red

    return 0;
}



