#include "eco/eco.h"
#include "eco/parameters.h"

using namespace eco;

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Usage: "<<argv[0]<<" video_path" << std::endl;
        return -1;
    }
    cv::VideoCapture cap(argv[1]);
    if(!cap.isOpened())
    {
        printf("Error read video \r\n ");
        return -1;
    }
    ECO eco_tracker;
    EcoParameters params;
    cv::Mat frame, frame_display;
    bool initTrack = false;
    cv::Rect2f trackbox;
    double timercount;
    int framecount = 0;
    float fps = 0.0f;
    while(true)
    {
        //auto start = std::chrono::high_resolution_clock::now();
        framecount++;
        if(cap.read(frame))
        {
            frame_display = frame.clone();
            cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
            if (initTrack == true)
            {
                timercount = (double)cv::getTickCount();
                bool pass = eco_tracker.update(frame, trackbox);
                fps = cv::getTickFrequency()/((double)cv::getTickCount() - timercount);
                if (pass)
                {
                    cv::rectangle(frame_display, trackbox, cv::Scalar(255, 0, 255), 2, 1);
                }
                else
                {
                    cv::putText(frame_display, "LOST TRACK!!!", cv::Point(100, 80), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(255, 0, 255), 2);
                }
            }
            else
            {
                cv::imshow("Image", frame);
                std::cout<<"Press Q to select ROI. Start tracking ... "<<std::endl;
                int c =  cv::waitKey(0);
                if (c == int('q'))
                {
                    trackbox = cv::selectROI(frame);
                    eco_tracker.init(frame, trackbox, params);
                    initTrack = true;
                }
                //trackbox = cv::Rect2f(30, 20, 40, 80);
                //eco_tracker.init(frame, trackbox, params);
                //initTrack = true;
            }
            std::cout << "Frame: " << framecount << " - FPS: " << fps << std::endl;
            imshow("Image", frame_display);
            int key = cv::waitKey(10);
            if (key == int('p'))
                cv::waitKey(-1);
            if (key == 27 || key == int('q'))
                break;
        }
        else
        {
            printf("End read frame \r\n ");
            break;
        }
        //auto end = std::chrono::high_resolution_clock::now();
        //std::cout<<"Time = "<<std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()<< " ms" << std::endl;
    }
    return 0;
}
