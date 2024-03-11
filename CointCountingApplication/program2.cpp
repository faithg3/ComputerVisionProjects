#include <iostream>
#include <string>
#include "opencv2/opencv.hpp"

#define NUM_COMNMAND_LINE_ARGUMENTS 1
#define QUARTER .25
#define DIME .10
#define NICKEL .05
#define PENNY .01

int main(int argc, char **argv)
{
    cv::Mat imageIn;
    cv::Mat imageEllipse;

    int PennyCount = 0, NickleCount = 0, DimeCount = 0, QuarterCount = 0;
    float TotalAmount = 0;

    // validate and parse the command line arguments
    if(argc != NUM_COMNMAND_LINE_ARGUMENTS + 1)
    {
        std::printf("USAGE: %s <image_path> \n", argv[0]);
        return 0;
    }
    else
    {
        imageIn = cv::imread(argv[1], cv::IMREAD_COLOR);
        imageEllipse = cv::imread(argv[1], cv::IMREAD_COLOR);

        // check for file error
        if(!imageIn.data)
        {
            std::cout << "Error while opening file " << argv[1] << std::endl;
            return 0;
        }
    }

    // convert the image to grayscale
    cv::Mat imageGray;
    cv::cvtColor(imageIn, imageGray, cv::COLOR_BGR2GRAY);

    // find the image edges
    cv::Mat imageEdges;
    cv::Canny(imageGray, imageEdges, 100, 200, 3);

    // erode and dilate the edges to remove noise
    cv::Mat edgesDilated;
    cv::dilate(imageEdges, edgesDilated, cv::Mat(), cv::Point(-1, -1), 1);
    cv::Mat edgesEroded;
    cv::erode(edgesDilated, edgesEroded, cv::Mat(), cv::Point(-1, -1), 1);

    // locate the image contours (after applying a threshold or canny)
    std::vector<std::vector<cv::Point> > contours;
    //std::vector<int> hierarchy;
    cv::findContours(edgesEroded, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

    // compute minimum area bounding rectangles
    std::vector<cv::RotatedRect> minAreaRectangles(contours.size());
    for(int i = 0; i < contours.size(); i++)
    {
        // compute a minimum area bounding rectangle for the contour
        minAreaRectangles[i] = cv::minAreaRect(contours[i]);
    }

    // fit ellipses to contours containing sufficient inliers and draw elipses
    std::vector<cv::RotatedRect> fittedEllipses(contours.size());
    const int minEllipseInliers = 50;

    for(int i = 0; i < contours.size(); i++)
    {
        // compute an ellipse only if the contour has more than 5 points (the minimum for ellipse fitting)
        // draw any ellipse with sufficient inliers
        if((contours.at(i).size() > 5) && (contours.at(i).size() > minEllipseInliers))
        {
            fittedEllipses[i] = cv::fitEllipse(contours[i]);
            float coin_size = fittedEllipses[i].size.width;

            // Dime
            if ((coin_size > 64) && (coin_size < 66))
            {
                cv::ellipse(imageEllipse, fittedEllipses[i], cv::Scalar(255, 0, 0), 1);
                DimeCount++;
            }
            // Penny
            else if ((coin_size > 68) && (coin_size < 71))
            {
                cv::ellipse(imageEllipse, fittedEllipses[i], cv::Scalar(0, 0, 255), 1);
                PennyCount++;
            }
            // Nickel
            else if ((coin_size > 74) && (coin_size < 77))
            {
                cv::ellipse(imageEllipse, fittedEllipses[i], cv::Scalar(0, 255, 255), 1);
                NickleCount++;
            }
            // Quarter
            else if ((coin_size > 86) && (coin_size < 89))
            {
                cv::ellipse(imageEllipse, fittedEllipses[i], cv::Scalar(0, 255, 0), 1);
                QuarterCount++;
            }
        }
    }

    // calculating Total Amount
    TotalAmount = (DimeCount*DIME) + (PennyCount*PENNY) + (NickleCount*NICKEL) + (QuarterCount*QUARTER);

    // printing results
    std::cout << "Penny - " << PennyCount << std::endl;
    std::cout << "Nickel - " << NickleCount << std::endl;
    std::cout << "Dime - " << DimeCount << std::endl;
    std::cout << "Quarter - " << QuarterCount << std::endl;
    std::cout << "Total - $" << TotalAmount << std::endl;

    // display the images
    cv::imshow("imageIn", imageEllipse);
    cv::imshow("imageEllipse", imageIn);

    cv::waitKey();
}
