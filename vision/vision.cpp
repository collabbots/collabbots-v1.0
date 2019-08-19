#include "vision.h"
#include <iostream>
#include <string>

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
    std::vector<cv::Mat> colourChannels(4);
    
    cv::Mat redColourChannel = return_channel(camera, color_code::R);
    cv::Mat blueColourChannel = return_channel(camera, color_code::B);
    cv::Mat greenColourChannel = return_channel(camera, color_code::G);
    cv::Mat rgbColourChannels = return_channel(camera, color_code::RGB);

    colourChannels.push_back(redColourChannel); 
    colourChannels.push_back(blueColourChannel); 
    colourChannels.push_back(greenColourChannel);
    colourChannels.push_back(rgbColourChannels);

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

    if (color == R)
    {
        cv::threshold(imgChannels[2] - grayscaleFrame, currentColourChannel, THRESH_VAL_R, COLOR_MAX_VAL, cv::THRESH_BINARY_INV);
        cv::medianBlur(currentColourChannel, currentColourChannel, THRESH_VAL_BLUR);

        test(currentColourChannel, currentFrame);
    }
    else if (color == B)
    {
        cv::threshold(imgChannels[0] - grayscaleFrame, currentColourChannel, THRESH_VAL_B, COLOR_MAX_VAL, cv::THRESH_BINARY_INV);
        cv::medianBlur(currentColourChannel, currentColourChannel, THRESH_VAL_BLUR);

        test(currentColourChannel, currentFrame);
    }
    else if (color == G)
    {
        cv::threshold(imgChannels[1] - grayscaleFrame, currentColourChannel, THRESH_VAL_G, COLOR_MAX_VAL, cv::THRESH_BINARY_INV);
        cv::medianBlur(currentColourChannel, currentColourChannel, THRESH_VAL_BLUR);

        test(currentColourChannel, currentFrame);
    }
    else if (color == RGB)
        currentColourChannel = currentFrame;

    return(currentColourChannel);
}

void Vision::display_all_channels(const camera_code& camera)
{    
    display_channel(camera, color_code::R);
    display_channel(camera, color_code::B);
    display_channel(camera, color_code::G);
    display_channel(camera, color_code::RGB);
}

void Vision::display_channel(const camera_code& camera, const color_code& color) {
    std::string colorName;
    cv::Mat currentColourChannel;
    int x_pos, y_pos; 

    if (color == R){
        colorName = "R" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");
        x_pos = WIN_SIZE_X + 50; y_pos = 0; 
    }
    else if (color == B){
        colorName = "B" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");
        x_pos = 0; y_pos = WIN_SIZE_Y + 60; 
    }
    else if (color == G){
        colorName = "G" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");
        x_pos = WIN_SIZE_X + 50; y_pos = WIN_SIZE_Y + 60; 
    }
    else if (color == RGB){
        colorName = "RGB" + std::string((camera == TOP_VIEW) ? "_TOP" : "_SIDE");
        x_pos = 0; y_pos = 0; 
    }

    currentColourChannel = return_channel(camera, color);
    cv::namedWindow(colorName, cv::WINDOW_NORMAL);
    cv::resizeWindow(colorName, WIN_SIZE_X, WIN_SIZE_Y); 
    cv::moveWindow(colorName, x_pos, y_pos); 
    cv::imshow(colorName, currentColourChannel);
}

void Vision::calibrate_view()
{
    std::vector<cv::Mat> top_cam_channels = return_all_channels(camera_code::TOP_VIEW);
    // std::vector<cv::Mat> side_cam_channels = return_all_channels(camera_code::SIDE_VIEW);

    // iterate through R, G, and B channels and not the RGB (coloured) channel
    for (int i = 0; i < 3; ++i)
    {
        std::cout << "********************************" << std::endl;

        cv::Moments m = cv::moments(top_cam_channels[i], true);
        cv::Point p(m.m10/m.m00, m.m01/m.m00);
        
        // coordinates of centroid
        std::cout<< cv::Mat(p)<< std::endl;
        std::cout << "********************************" << std::endl;
        // show the image with a point mark at the centroid
        cv::circle(top_cam_channels[i], p, 5, cv::Scalar(128,0,0), -1);
    }

    // for (int i = 0; i < 3; ++i)
    // {
    //     std::cout << "********************************" << std::endl;

    //     cv::Moments m = cv::moments(side_cam_channels[i], true);
    //     cv::Point p(m.m10/m.m00, m.m01/m.m00);
        
    //     // coordinates of centroid
    //     std::cout<< cv::Mat(p)<< endl;
    //     std::cout << "********************************" << std::endl;
    //     // show the image with a point mark at the centroid
    //     cv::circle(src, p, 5, cv::Scalar(128,0,0), -1);
    // }
}

void test (cv::Mat& currentColourChannel, cv::Mat& currentFrame)
{
    std::cout << "*******************************" << std::endl;
    cv::Mat canny_output;
    cv::Mat tempFrame = cv::Mat(cv::Size(currentColourChannel.cols, currentColourChannel.rows), currentColourChannel.type());
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // detect edges using canny
    cv::Canny(currentColourChannel, canny_output, 50, 150, 3 );

    // find contours
    cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // get the moments
    std::vector<cv::Moments> mu(contours.size());
    for( int i = 0; i<contours.size(); i++ )
    { mu[i] = moments( contours[i], false ); }

    // get the centroid of figures.
    std::vector<cv::Point2f> mc(contours.size());
    for( int i = 0; i<contours.size(); i++)
    {
        mc[i] = cv::Point2f( mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00 );
        std::cout << mc[i] << std::endl;
    }


    // draw contours
    for( int i = 0; i<contours.size(); i++ )
    {
        cv::Scalar color = cv::Scalar(167,151,0); // B G R values
        drawContours(tempFrame, contours, i, color, 2, 8, hierarchy, 0, cv::Point());
        circle(tempFrame, mc[i], 4, color, -1, 8, 0 );
    }

    cv::namedWindow("testWindow", cv::WINDOW_NORMAL);
    cv::imshow("testWindow", tempFrame);
    std::cout << "*******************************" << std::endl;
}