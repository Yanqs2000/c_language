#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
    // 读取图像
    cv::Mat img = cv::imread("./opencv_c++/皮卡丘.png"); // 请确保这张图在程序同目录
    if (img.empty())
    {
        std::cerr << "无法读取图片，请确保图片存在\n";
        return 1;
    }

    // 转换为灰度图像
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    // 显示图像
    cv::imshow("原图", img);
    cv::imshow("灰度图", gray);
    cv::waitKey(0); // 等待键盘输入

    // 保存灰度图
    cv::imwrite("./皮卡丘_gray.png", gray);

    return 0;
}

// mac: g++ main.cpp -o main `pkg-config --cflags --libs opencv4`
