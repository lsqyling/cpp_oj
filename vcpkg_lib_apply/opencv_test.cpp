#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>




int main()
{
    std::string image_path = "D:\\Users\\10580\\Pictures\\photo\\1V3A8117.JPG";
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);

    imshow("Display window", img);
    int k = cv::waitKey(0); // Wait for a keystroke in the window
    return 0;
}