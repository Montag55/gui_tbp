#include <iostream>
#include <string.h>
#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include "base.hpp"

using namespace cv;
using namespace std;

int main(int argc, char** argv )
{
  Mat image;
  if(argc==2) {
    std::string file=argv[1];
    Base* test_base = new Base(file);
    imwrite( "./test.jpg", test_base->get_result());
  }
  else {
    std::cout<<"videopfad angeben?\n";
  }
  std::cout << "done!" << endl;
  return 0;
}
