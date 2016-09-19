#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "package_bgs/FrameDifferenceBGS.h"

#include "package_tracking/BlobTracking.h"

#include <opencv2/imgproc.hpp>
 #include <iostream>

using namespace cv;
 using namespace std;

int main()
 {
	 
	std::cout << "Using OpenCV " << CV_MAJOR_VERSION << "." << CV_MINOR_VERSION << "." << CV_SUBMINOR_VERSION << std::endl;
cout<<"hello";

	 //Mat image;
	 //image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR); // Read the file
	 //
		//  if (!image.data) // Check for invalid input
		//  {
		//  cout << "Could not open or find the image" << std::endl;
		//  return -1;
		//  }
	 //
		//  namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	 //imshow("Display window", image); // Show our image inside it.


	  VideoCapture capture;
	  

	  IBGS *bgs;
	  bgs = new FrameDifferenceBGS;

	  /* Blob Tracking Algorithm */
	  Mat img_blob;
	  BlobTracking* blobTracking;
	  blobTracking = new BlobTracking;

	  
	  capture.open("./dataset/video2.mp4");
	  if (!capture.isOpened())  // check if we succeeded
		  cout<<"err";


	  while (1)
	  {
			Mat frame;
		  capture>>frame;
		  //frame = cvQueryFrame(capture);
		  if (frame.empty())
		  {
			  printf(" --(!) No captured frame -- Break!");
			  break;
		  }

		  Mat img_input(frame);
		  //imshow("Input", img_input);

		  Mat img_mask;
		  Mat img_bkgmodel;
		  bgs->process(img_input, img_mask, img_bkgmodel);

		 if(!img_mask.empty())
		   imshow("Foreground", img_mask);

		  if (!img_mask.empty())
		  {
			  // Perform blob tracking
			  blobTracking->process(img_input, img_mask, img_blob);
		  }
		  line(img_input, Point(0, 0), Point(500, 500), Scalar(100, 155, 30));
		 // imshow("drawing", img_input);





		  if (waitKey(30) >= 0) break;
//cvWaitKey(33);
		
	  }

	 
		 cvWaitKey(0); // Wait for a keystroke in the window
	  return 0;
	 
}