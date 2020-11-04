#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <raspicam/raspicam_cv.h>
#include <wiringPi.h>
#include <iostream>

using namespace cv;
using namespace std;

static void help()
{
    cout << "\nThis program demonstrates circle finding with the Hough transform.\n"
            "Usage:\n"
            "./houghcircles <image_name>, Default is ../data/board.jpg\n" << endl;
}

int main(int argc, char** argv)
{
    if (wiringPiSetup()==-1)
    {
        return 1;
    }
    raspicam::RaspiCam_Cv Camera;
    Camera.set( CV_CAP_PROP_FORMAT,CV_8UC3 );
    Camera.set( CV_CAP_PROP_FRAME_WIDTH,320 );
    Camera.set( CV_CAP_PROP_FRAME_HEIGHT,240 );

    cv::CommandLineParser parser(argc, argv,
        "{help h ||}{@image|../data/board.jpg|}"
    );
    if (parser.has("help"))
    {
        help();
        return 0;
    }
    /**
    string filename = parser.get<string>("@image");
    if (filename.empty())
    {
        help();
        cout << "no image_name provided" << endl;
        return -1;
    }
    Mat img = imread(filename, 0);
    if(img.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }
    */
    /*
    VideoCapture cap(0);
    */
    if ( !Camera.open() )  // if not success, exit program
    {
        cout << "Cannot open the web cam" << endl;
        return -1;
    }

    Mat img,cimg,timg;
    for(;;)
    {

        //bool bSuccess = cap.read(img); // read a new frame from video

        Camera.grab();
        Camera.retrieve(cimg);
        flip(cimg, cimg, -1);
        /*
        if (!bSuccess) //if not success, break loop
        {
            cout << "Cannot read a frame from video stream" << endl;
            return -1;
        }
        */
        //imshow("Original Image", img);

        medianBlur(cimg, cimg, 5);
        //cout << "Image size is " << img.size().width << " by " << img.size().height << endl;

        //cout << "Img depth is " << img.depth() << " Channels: " << img.channels() << endl;
        cvtColor(cimg, img, COLOR_GRAY2BGR);
        //cvtColor(img,cimg,COLOR_BGR2GRAY,1);

        vector<Vec3f> circles;
        HoughCircles(cimg, circles, HOUGH_GRADIENT, 
                    1, // accumulator resolution
                    5, // minimum distance between two circles
                    50, // high threshold
                    40, // votes
                    5,  // minimum size
                    200 // change the last two parameters
                        // (min_radius & max_radius) to detect larger circles
                    );
        int max_radius=0;
        int found=0;
        Vec3i biggest;
        cout << "Found " << circles.size() << " Balls" << endl;
        for( size_t i = 0; i < circles.size(); i++ )
        {
            //cout << "Circle"<< endl;
            Vec3i c = circles[i];
            if( c[2]>max_radius ){
                found=1;
                biggest=c;
            }
        }
        if( found==1 ){  
            circle( img, Point(biggest[0], biggest[1]), biggest[2], Scalar(0,0,255), 3, LINE_AA); // red line around outside
            circle( img, Point(biggest[0], biggest[1]), 2, Scalar(0,255,0), 3, LINE_AA); // green dot
            //cout << "Biggest at " << biggest[0] << "," << biggest[1] << endl;
        }
        imshow("detected circles", img);
        
        int c = waitKey(10);
        if( c == 27 || c == 'q' || c == 'Q' )
            break;
    }
}
