#ifndef vision_h
#define vision_h

#include <opencv2/opencv.hpp>

void test (cv::Mat&, cv::Mat&);

enum color_code 
{
    R = 0,
    G = 1,
    B = 2,
    RGB = 3
};

enum camera_code
{
    TOP_VIEW = 0,
    SIDE_VIEW = 1
};

class Vision
{
private:
    const double THRESH_VAL_R = 10;
    const double THRESH_VAL_G = 5;
    const double THRESH_VAL_B = 10.8;
    const int THRESH_VAL_BLUR = 31;
    const int COLOR_MAX_VAL = 255;
    const int WIN_SIZE_X = 400;
    const int WIN_SIZE_Y = 250;

public:
    //
    cv::VideoCapture top_view;
    cv::VideoCapture side_view;
    cv::VideoWriter outavi_top_view;
    cv::VideoWriter outavi_side_view;

    //
    void start_capture(const camera_code& camera);
    cv::Mat return_channel(const camera_code& camera, const color_code& color);
    std::vector<cv::Mat> return_all_channels(const camera_code& camera);
    void display_channel(const camera_code& camera, const color_code& color);
    void display_all_channels(const camera_code& camera);
    void end_capture(const camera_code& camera);
    void calibrate_view();

    //
    Vision();
    ~Vision();
};

#endif