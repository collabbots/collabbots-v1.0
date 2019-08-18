#include "vision.h"
#include <iostream>
#include <string>

int main()
{
    Vision vision;
    
    while(1)
    {
        vision.display_all_channels(camera_code::TOP_VIEW);
        vision.display_all_channels(camera_code::SIDE_VIEW);
        char c=(char)cv::waitKey(1);
        if (c == 27)
            break;
    }

    return 0;
}


Vision::Vision()
{
    start_capture(camera_code::TOP_VIEW);
    start_capture(camera_code::SIDE_VIEW);
}

Vision::~Vision()
{
    end_capture(camera_code::TOP_VIEW);
    end_capture(camera_code::SIDE_VIEW);
    cv::destroyAllWindows();
}

void Vision::start_capture(const camera_code& camera)
{
    int frame_width, frame_height;

    switch (camera)
    {
        case TOP_VIEW:
            top_view = cv::VideoCapture(0);
            
            try
            {
                if(!top_view.isOpened())
                    throw std::runtime_error("Error opening top view camera video stream");
            }
            catch(const std::exception& e)
            {    
                std::cerr << e.what() << std::endl;
                return;
            }
            
            frame_width = top_view.get(cv::CAP_PROP_FRAME_WIDTH);
            frame_height = top_view.get(cv::CAP_PROP_FRAME_HEIGHT);
            outavi_top_view = cv::VideoWriter("top_view.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(frame_width,frame_height));
            
            break;

        case SIDE_VIEW:
            side_view = cv::VideoCapture(2);

            try
            {
                if(!side_view.isOpened())
                    throw std::runtime_error("Error opening side view camera video stream");
            }
            catch(const std::exception& e)
            {    
                std::cerr << e.what() << std::endl;
                return;
            }

            frame_width = side_view.get(cv::CAP_PROP_FRAME_WIDTH);
            frame_height = side_view.get(cv::CAP_PROP_FRAME_HEIGHT);
            outavi_side_view = cv::VideoWriter("side_view.avi", cv::VideoWriter::fourcc('M','J','P','G'), 10, cv::Size(frame_width,frame_height));
            
            break;
        
        default:
            throw std::runtime_error("Incorrect camera code entered");
            break;
    }
}

void Vision::end_capture(const camera_code& camera)
{
    switch (camera)
    {
        case TOP_VIEW:
            top_view.release();
            outavi_top_view.release();    
            break;

        case SIDE_VIEW:
            side_view.release();
            outavi_side_view.release();    
            break;

        default:
            break;
    }
}

std::vector<cv::Mat> Vision::return_all_channels(const camera_code& camera)
{
    std::vector<cv::Mat> colourChannels; 
    
    cv::Mat redColourChannel = return_channel(camera, color_code::RED); 
    cv::Mat blueColourChannel = return_channel(camera, color_code::BLUE); 
    cv::Mat greenColourChannel = return_channel(camera, color_code::GREEN); 
    
    colourChannels.push_back(redColourChannel); 
    colourChannels.push_back(blueColourChannel); 
    colourChannels.push_back(greenColourChannel); 

    return(colourChannels);
}


cv::Mat Vision::return_channel(const camera_code& camera, const color_code& color)
{    
    cv::Mat currentFrame, grayscaleFrame;
    if (camera == TOP_VIEW)
        top_view.read(currentFrame); 
    else if (camera == SIDE_VIEW) 
        side_view.read(currentFrame);

    cv::cvtColor(currentFrame, grayscaleFrame, cv::COLOR_BGR2GRAY);

    cv::Mat imgChannels[3];
    cv::split(currentFrame, imgChannels);
    if (imgChannels[0].empty() || imgChannels[1].empty() || imgChannels[2].empty())
        throw std::runtime_error("Empty image channel(s)!");

    cv::Mat currentColourChannel = cv::Mat(cv::Size(imgChannels[0].cols, imgChannels[0].rows), imgChannels[0].type());
    std::string colorName = "";

    if (color == RED)
        cv::threshold(imgChannels[2] - grayscaleFrame, currentColourChannel, THRESH_VAL_R, COLOR_MAX_VAL, cv::THRESH_BINARY_INV);
    else if (color == BLUE)
        cv::threshold(imgChannels[0] - grayscaleFrame, currentColourChannel, THRESH_VAL_B, COLOR_MAX_VAL, cv::THRESH_BINARY_INV);
    else if (color == GREEN)
        cv::threshold(imgChannels[1] - grayscaleFrame, currentColourChannel, THRESH_VAL_G, COLOR_MAX_VAL, cv::THRESH_BINARY_INV);

    return(currentColourChannel);
}

void Vision::display_all_channels(const camera_code& camera)
{    
    display_channel(camera, color_code::RED); 
    display_channel(camera, color_code::BLUE); 
    display_channel(camera, color_code::GREEN); 
}

void Vision::display_channel(const camera_code& camera, const color_code& color) {
    std::string colorName;
    cv::Mat currentColourChannel;

    if (color == RED)
        colorName = "R" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");
    else if (color == BLUE)
        colorName = "B" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");
    else if (color == GREEN)
        colorName = "G" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");

    currentColourChannel = return_channel(camera, color);
    cv::namedWindow(colorName, cv::WINDOW_NORMAL);
    cv::imshow(colorName, currentColourChannel);
}