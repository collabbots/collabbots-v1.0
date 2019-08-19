#include "vision/vision.h"

int main()
{
    Vision vision;

    while(1)
    {
        vision.display_all_channels(camera_code::TOP_VIEW);
        char c=(char)cv::waitKey(1);
        if (c == 27)
            break;
    }

    return 0;
}