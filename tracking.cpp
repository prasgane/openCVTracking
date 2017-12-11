#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <cstring>

using namespace std;
using namespace cv;

#define SSTR( x ) static_cast< std::ostringstream & >( \
( std::ostringstream() << std::dec << x ) ).str()

int main( int argc, char** argv)
{
  Rect2d roi;
  Mat frame;

  Ptr<Tracker> tracker = TrackerKCF::create();
  //Ptr<Tracker> tracker = TrackerMIL::create();

  //VideoCapture cap("chaplin.mp4");
  VideoCapture cap(0);
  
  cap >> frame;

  if (frame.empty())
  {
    cout<<"Import Fail!!";
    return EXIT_FAILURE;
  }


  roi = selectROI("tracker",frame);


  if(roi.width == 0 || roi.height == 0)
    return 0;

  tracker->init(frame,roi);

  cout << "Start the tracking process , press ESC to quit" << endl;

  while(1)
  {
      cap >> frame;

      if(frame.rows == 0 || frame.cols == 0)
        break;

      tracker->update(frame,roi);

      rectangle(frame,roi,Scalar(255,0,0),2,1);
      Point center_of_rect  =(roi.br() + roi.tl()) * 0.5;
      circle(frame,center_of_rect,3,Scalar(0,0,255));
      putText(frame, "KCF Tracker", Point(100,20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(50,170,50),2);
      putText(frame,"X " + SSTR(double(center_of_rect.x)) + " Y " + SSTR(double(center_of_rect.y)), Point(100,50), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(255,0,50),2 );
      imshow("tracker",frame);

      if(waitKey(1) == 27)break;

  }

  return 0;

}
