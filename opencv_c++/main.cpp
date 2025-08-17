#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 读取图像
    Mat image = imread("/Users/yanqs/Documents/GitHub/c_language/opencv_c++/皮卡丘.png");
    if (image.empty())
    {
        cerr << "无法加载图像！" << endl;
        return -1;
    }

    // 二值化
    Mat gray, binary;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    threshold(gray, binary, 128, 255, THRESH_BINARY);

    // 连通域标记（使用OpenCV函数）
    Mat labels, stats, centroids;
    int numObjects = connectedComponentsWithStats(binary, labels, stats, centroids);

    // 可视化结果
    Mat colorLabels(labels.size(), CV_8UC3);
    vector<Vec3b> colors(numObjects);
    colors[0] = Vec3b(0, 0, 0); // 背景

    for (int i = 1; i < numObjects; i++)
    {
        colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
    }

    for (int y = 0; y < labels.rows; y++)
    {
        for (int x = 0; x < labels.cols; x++)
        {
            int label = labels.at<int>(y, x);
            colorLabels.at<Vec3b>(y, x) = colors[label];
        }
    }

    // 显示结果
    imshow("原始图像", image);
    imshow("二值图像", binary);
    imshow("连通域标记", colorLabels);

    // 保存结果
    imwrite("binary_opencv.jpg", binary);
    imwrite("labels_opencv.jpg", colorLabels);

    waitKey(0);
    return 0;
}

// mac: g++ main.cpp -o main `pkg-config --cflags --libs opencv4`
