#include <iostream>
#include <cstdio>
#include <string>
#include "opencv2/opencv.hpp"

#define NUM_COMNMAND_LINE_ARGUMENTS 1
#define DISPLAY_WINDOW_NAME "Assignment 1: Raster Graphics Editor"

int TOOL = 0;
cv::Vec3b COLOR = {255, 255, 255};
int CROP_START [] = {0, 0};
int CROP_END [] = {0, 0};
bool DRAWING_MODE = false;
cv::Mat IMAGE_IN;
std::string IMG_PATH;

// function will be called on mouse input
static void clickCallback(int event, int x, int y, int flags, void* param)
{
    cv::Mat imageIn = *(cv::Mat *)param;
    if (event == cv::EVENT_RBUTTONDOWN)
    {
        // toggling through tools
        if (TOOL < 4)
        {
            TOOL++;
        }
        else
        {
            TOOL = 0;
        }
        switch (TOOL)
        {
            // Printing active tool to console
            case 0:
                std::cout << "EYEDROPPER TOOL ACTIVE" << std::endl;
                break;
            case 1:
                std::cout << "\nPENCIL TOOL ACTIVE\n" << std::endl;
                break;
            case 2:
                std::cout << "PAINT BUCKET TOOL ACTIVE\n" << std::endl;
                break;
            case 3:
                std::cout << "CROP TOOL ACTIVE\n" << std::endl;
                break;
            case 4:
                std::cout << "RESET TOOL ACTIVE\n" << std::endl;
                break;
        }
    }

    switch(TOOL)
    {
        // Eyedropper Tool
        case 0:
            if (event == cv::EVENT_LBUTTONDOWN)
            {
                // saves color at selected point and prints it to console
                COLOR = IMAGE_IN.at<cv::Vec3b>(y, x);
                std::cout << "COLOR CHANGE: " << COLOR << std::endl;
            }
            break;

        // Pencil Tool
        case 1:
            if (event == cv::EVENT_LBUTTONDOWN)
            {
                // Setting drawing mode to true when user clicks left mouse button
                DRAWING_MODE = true;

                // displays a circle of previously set color at mouse point
                cv::Point center(x, y);
                cv::circle(IMAGE_IN, center, 5, (COLOR), -1);
                cv::imshow(DISPLAY_WINDOW_NAME, IMAGE_IN);
                cv::waitKey();
            }
            if (event == cv::EVENT_LBUTTONUP)
            {
                // Sets drawing mode to false when user is no longer holding left click down
                DRAWING_MODE = false;
            }
            if (event == cv::EVENT_MOUSEMOVE)
            {
                if (DRAWING_MODE)
                {
                    // displays a circle of previously set color at mouse point
                    cv::Point center(x, y);
                    cv::circle(IMAGE_IN, center, 5, (COLOR), -1);
                    cv::imshow(DISPLAY_WINDOW_NAME, IMAGE_IN);
                    cv::waitKey();
                }
            }
            break;

        // Paint Bucket Tool
        case 2:
            if (event == cv::EVENT_LBUTTONDOWN)
            {
                // saves point the mouse clicked
                cv::Point cursor(x, y);
                // fills surrounding points with selected color if they are the
                // same color as the original point using floodFill()
                cv::floodFill(IMAGE_IN, cursor, COLOR);
                cv::imshow(DISPLAY_WINDOW_NAME, IMAGE_IN);
                cv::waitKey();
            }
            break;

        // Cropping Tool
        case 3:
            if (event == cv:: EVENT_LBUTTONDOWN)
            {
                // saving the start point
                CROP_START[0] = x;
                CROP_START[1] = y;

            }
            if (event == cv:: EVENT_LBUTTONUP)
            {
                // saving the end point
                CROP_END[0] = x;
                CROP_END[1] = y;

                if ((CROP_START[0] < CROP_END[0]) && (CROP_START[1] < CROP_END[1]))
                {
                    // creating a rectagular crop from start point to end point
                    cv::Rect crop(CROP_START[0], CROP_START[1], (CROP_END[0]-CROP_START[0]), (CROP_END[1]-CROP_START[1]));
                    IMAGE_IN = IMAGE_IN(crop);
                    cv::Mat resized;
                    cv::resize(IMAGE_IN, resized, cv::Size(CROP_END[0]-CROP_START[0], CROP_END[1]-CROP_START[1]));
                    cv::imshow(DISPLAY_WINDOW_NAME, resized);
                    cv::waitKey();
                    }
                else
                {
                    std::cout << "You must crop starting from the TOP LEFT corner and ending in the BOTTOM RIGHT corner!\n" << std::endl;
                }
            }
            break;

        // Reset Tool
        case 4:
            if (event == cv::EVENT_LBUTTONDBLCLK)
            {
                // resetting IMAGE_IN to the orginal image from the given path
                IMAGE_IN = cv::imread(IMG_PATH, cv::IMREAD_COLOR);
                cv::imshow(DISPLAY_WINDOW_NAME, IMAGE_IN);
                cv::waitKey();
            }
            break;
    }
}

int main(int argc, char **argv)
{
    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        std::printf("USAGE: %s <image_path> \n", argv[0]);
        return 0;
    }
    else
    {
        // open the input image
		cv::Mat imageIn;
		imageIn = cv::imread(argv[1], cv::IMREAD_COLOR);
		IMAGE_IN = cv::imread(argv[1], cv::IMREAD_COLOR);
		IMG_PATH = argv[1];

		// check for file error
		if(!imageIn.data)
		{
			std::cout << "Error while opening file " << argv[1] << std::endl;
			return 0;
		}
		else
		{
            // display window
            cv::namedWindow(DISPLAY_WINDOW_NAME, cv::WINDOW_AUTOSIZE);
			cv::imshow(DISPLAY_WINDOW_NAME, IMAGE_IN);

            // print first active tool
            std::cout << "EYEDROPPER TOOL ACTIVE" << std::endl;

            //highgui function called when mouse event occurs
            cv::setMouseCallback(DISPLAY_WINDOW_NAME, clickCallback, &imageIn);

            cv::waitKey();
            //cv::destroyAllWindows();
		}
    }
}
