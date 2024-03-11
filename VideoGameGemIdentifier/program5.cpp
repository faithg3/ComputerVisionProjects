// include necessary dependencies
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include <vector>

// configuration parameters
#define NUM_COMNMAND_LINE_ARGUMENTS 1
#define DISPLAY_WINDOW_NAME "Video Frame"

// declare function prototypes
bool processFrame(const cv::Mat &imageIn, cv::Mat &imageOut);

/*******************************************************************************************************************//**
 * @brief Process a single image frame
 * @param[in] imageIn the input image frame
 * @param[out] imageOut the processed image frame
 * @return true if frame was processed successfully
 * @author Christopher D. McMurrough
 **********************************************************************************************************************/
bool processFrame(const cv::Mat &imageIn, cv::Mat &imageOut)
{
    // copy the input image frame to the ouput image (deep copy)
    imageOut = imageIn.clone();

    // copy the input image frame to the ouput image (shallow copy, if you just want to display)
    //imageOut = imageIn;

    // return true on success
    return true;
}

int main(int argc, char **argv)
{
    // store video capture parameters
    std::string fileName;
    cv::Mat imageTemplate;

    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        std::printf("USAGE: %s <file_path> \n", argv[0]);
        return 0;
    }
    else
    {
        fileName = argv[1];
        imageTemplate = cv::imread("gem_template.PNG", cv::IMREAD_COLOR);
    }

    // open the video file
    cv::VideoCapture capture(fileName);
    if(!capture.isOpened())
    {
        std::printf("Unable to open video source, terminating program! \n");
        return 0;
    }

    // create image window
    cv::namedWindow(DISPLAY_WINDOW_NAME, cv::WINDOW_AUTOSIZE);

    // process data until program termination
    bool doCapture = true;
    int frameCount = 0;

    while(doCapture)
    {
        // get the start time
        double startTicks = static_cast<double>(cv::getTickCount());

        // attempt to acquire and process an image frame
        cv::Mat captureFrame;
        cv::Mat imageScene;
        bool captureSuccess = capture.read(captureFrame);
        if(captureSuccess)
        {
            // process the image frame
            processFrame(captureFrame, imageScene);

            // convert the images to grayscale
            cv::Mat imageSceneGray;
            cv::cvtColor(imageScene, imageSceneGray, cv::COLOR_BGR2GRAY);
            cv::Mat imageTemplateGray;
            cv::cvtColor(imageTemplate, imageTemplateGray, cv::COLOR_BGR2GRAY);

            // perform the matching step
            cv::Mat searchResult(imageScene.rows - imageTemplate.rows + 1, imageScene.cols - imageTemplate.cols+1, CV_32FC1);
            int match_method = CV_TM_CCOEFF_NORMED;
            cv::matchTemplate(imageSceneGray, imageTemplateGray, searchResult, match_method);
            //cv::normalize(searchResult, searchResult, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
            
            // apply threshold to search result
            cv::Mat imageThreshold;
            double thresh = 0.60;
            double maxval = 1;
            int thresholdType = CV_THRESH_TOZERO;
            cv::threshold(searchResult, searchResult, thresh, maxval, thresholdType);

            // find max point in searchResult, draw rectangle, flood fill point, repeat until maxVal is no longer >=  threshold
            while (true)
            {
                double minVal, maxVal, threshold = 0.65;
                cv::Point minLoc, maxLoc;
                cv::minMaxLoc(searchResult, &minVal, &maxVal, &minLoc, &maxLoc);

                if (maxVal >= threshold)
                {
                    // get gem color
                    cv::Point rectanglePoint(maxLoc.x + (imageTemplate.cols*.5) - 8, maxLoc.y + (imageTemplate.rows*.5) - 8);
                    cv::Vec3b rectanglePointColor = imageScene.at<cv::Vec3b>(rectanglePoint);
                    cv::Scalar color;
                    
                    // draw rectangle around gem
                    cv::Point pt1 = cv::Point(maxLoc.x - 2 , maxLoc.y - 3);
                    cv::Point pt2 = cv::Point(maxLoc.x + imageTemplate.cols + 2 , maxLoc.y + imageTemplate.rows + 3);
                    cv::rectangle(imageScene, pt1, pt2, rectanglePointColor, 2);

                    // flood fill max point
                    cv::floodFill(searchResult, maxLoc, cv::Scalar(0), 0, cv::Scalar(0.1), cv::Scalar(1));
                }
                else
                {
                    break;
                }
            }

            // increment the frame counter
            frameCount++;
        }
        else
        {
            std::printf("Unable to acquire image frame! \n");
        }

        // update the GUI window if necessary
        if(captureSuccess)
        {

            cv::imshow(DISPLAY_WINDOW_NAME, imageScene);

            // check for program termination
            if(((char) cv::waitKey(1)) == 'q')
            {
                doCapture = false;
            }
        }
    }

    // release program resources before returning
    capture.release();
    cv::destroyAllWindows();
}
