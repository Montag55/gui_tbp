#ifndef SEGMENT_HPP
#define SEGMENT_HPP

/*
a SEGMENT is a piece in space and time. it is a kind of volume. it always belongs
to a base/mother. we can interpret such a segment in different ways. maybe we seperate
segment and interpretation later...
*/

#include <opencv2/opencv.hpp> //opencv library
#include <string.h>

class Base;                   //forward declaraiton
#include "base.hpp"
using namespace cv;

class Segment {

public:
  Segment(std::string file, int img_type, Point min, Point max, int start_frame, int last_frame, double intensity_local, double intensity_gloabl, Base* mother, Mat& mother_val, Mat& mother_fac, double& mother_uni);
  ~Segment();

  bool work(int work_size);  //continues a piece of computation

  //interpretations:
  bool average(int work_size);

  /*needs to be reimplemented with a owned segment:
  void boost_diff();
  void boost_diff_smooth(int power);
  void boost_similarities(int power);//modal();
  */

  //EDIT THE SEGMENT:
  void move_in_time(int delta);
  void set_exposure(int new_exposure);
  void set_startframe(int imgs);
  void set_endframe(int imgs);
  void set_exposure_delta(int delta);
  void set_local_intensity(float i);
  void set_global_intensity(float i);

private:
  void ready_to_work(); //tell the mother to work!

  int           m_interpretation_mode;
  std::string   m_file;   //maybe not necessary to store this?
  VideoCapture  m_video;
  int           m_img_type;
  bool          m_work_done=true;  //change to "int status"
  //Definition of BBOX:
  Point         m_pnt_min;
  Point         m_pnt_max;
  int           m_frame_start_destin;
  int           m_frame_last_destin;
  int           m_frame_start_actual;
  int           m_frame_last_actual;
  //int           m_work_size= 100;  //frames to compute per work routine

  float         m_intensity_local;    // not in relation to others
  float         m_intensity_global;   // in relation to other segments

  //local values
  Base*         m_mother;
  Mat           m_values_abs;
  Mat           m_values_fac;
  double        m_uni_fac;

  //global values       //maybe a dirty-way
  Mat           m_m_values_abs;
  Mat           m_m_values_fac;
  double&       m_m_uni_fac;
};
#endif
