#include <iostream>
#include <fstream>
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


std::vector<std::vector<int>> read_image (const std::string &path) {
    std::vector<std::vector<int>> content;
    cv::Mat image = cv::imread(path);

    //get_info(image);
    if(image.empty())
    {
        std::cerr << "Image reading error" << std::endl;
        return content;
    }

    for(size_t i = 0;i < image.rows; i++)
    {
        for(size_t j = 0; j<image.cols; j++)
        {
            cv::Vec3b intensity = image.at<cv::Vec3b>(i, j);
            std::vector<int> point = { (int)intensity.val[2],
                                       (int)intensity.val[1],
                                       (int)intensity.val[0]};
            content.push_back(point);
        }
    }
    return content;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Invalid arguments" << std::endl;
        return -1;
    }

    const auto data = read_image(argv[1]);
    //rgb

    std::ofstream output_file;
    output_file.open(argv[2]);
    if( !output_file ) {
        std::cerr << "File opening error" << std::endl;
        return -1;
    }
    for (const auto &x: data) {
        output_file << x[0] << " " << x[1] << " " << x[2] << std::endl;
    }
    output_file.close();

    return 0;
}



