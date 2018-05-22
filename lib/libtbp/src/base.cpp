#include <lib/libtbp/include/base.hpp>
#include <lib/libtbp/include/segment.hpp>

#include <chrono>
#include <thread> //thread sleep

#include <string.h>
#include <vector>

using namespace cv;

//a default base with a file, without any segment
//we could talk about the img_type!?
Base::Base(std::string const& video_name) :
m_in_calculation{false},
m_file {video_name},
m_work_size{5},//defualt
m_video{VideoCapture(m_file, cv::CAP_FFMPEG)},
m_img_type{CV_32FC3},//http://ninghang.blogspot.de/2012/11/list-of-mat-type-in-opencv.html
m_pnt_min{Point(0, 0)},
m_pnt_max{Point(m_video.get(CV_CAP_PROP_FRAME_WIDTH), m_video.get(CV_CAP_PROP_FRAME_HEIGHT))},
m_frame_start{0},
m_frame_last{m_video.get(CV_CAP_PROP_FRAME_COUNT)-1},
m_values_abs{Mat(m_pnt_max.y, m_pnt_max.x, m_img_type, cv::Scalar(0,0,0))},
m_values_fac{Mat(m_pnt_max.y, m_pnt_max.x, CV_64FC1, cv::Scalar(0))},
m_result{Mat(m_pnt_max.y, m_pnt_max.x, m_img_type, cv::Scalar(0,0,0))},
m_intensity{1.0f},
m_uni_fac{0.0f}{
  std::cout<<"NEW BASE\n";
  std::cout<<"video:"<<m_file<<"\n";
  std::cout<<"pnt_min:"<<m_pnt_min<<"\n";
  std::cout<<"pnt_max:"<<m_pnt_max<<"\n";
  std::cout<<"frame_start:"<<m_frame_start<<"\n";
  std::cout<<"frame_last:"<<m_frame_last<<"\n";
  std::cout<<"intensity:"<<m_intensity<<"\n";
}

Base::~Base(){
  std::cout << "Base-Destruction: \n";
}
//ORGA::::::::::::::::::::::::::::::::::::::::::::::::

Segment*           Base::add_segment(){
  //Default Segment: average, exposure: 1
  return add_segment(0,1);
}

Segment*                Base::add_segment(int start, int end){
  double inten_loc=1.0;
  double inten_glo=1.0;
  Segment* new_seg= new Segment(m_file,m_img_type,m_pnt_min,m_pnt_max, start, end,inten_loc, inten_glo,this, m_values_abs,m_values_fac,m_uni_fac);
  return new_seg;
}

void                Base::save(std::string file){
  //expects file-ending! example: file="output.jpg"
  imwrite( file,m_result);
}


//WORK::::::::::::::::::::::::::::::::::::::::::::::::
bool                Base::work_to_do(){
  //tells, wether there are still segments wiht unfinnished work
  return m_in_calculation;
}

void Base::continue_work(){
  //let all segments work and delete if finnished:
  int work_size=m_work_size;
  m_seg_in_calc.erase(std::remove_if(m_seg_in_calc.begin(), m_seg_in_calc.end(), [work_size](Segment*& o) { return o->work(work_size); }),m_seg_in_calc.end());
  update_result();  //update the colour values to the result
  if(!m_seg_in_calc.size()) //no work left
  {
    std::cout<<"work done\n";
    m_in_calculation=false;
  }
}

void                Base::set_work_size(int i){
  //setts the working sizes
  m_work_size=i;
}

Mat const& Base::get_result() const{
  //could be changed to a frame buffer, lucas?
  return m_result;
}

Mat const& Base::get_frame(int i){
  //could be changed to a frame buffer, lucas?
  //we could always have a preview-frame-provider, that is
  //faster.. it could simply shift the frames?
  m_video.set(CV_CAP_PROP_POS_FRAMES,i); //is always not in comput
  Mat output;
  m_video.read(output);
  return output;//!watchout, output is not a special mat typ!
}

//PROT?:::::::::::::::::::::::::::::::::::::::::::::::
/*
  we might set the following functions protected?
*/
void                Base::add_work(Segment* new_seg){
  //it is intended that a segments uses this functions
  //to tell the base, that it has work to do...
  m_seg_in_calc.push_back(new_seg);
  m_in_calculation=true;
}

void Base::update_result(){
  /*
  calculates the outputimage using the sum and its factors
  the pixel acces is already a bit performance.. using ptrs!
  */
  bool divzero=false;
  int m_img_delta=3;  //might be dependend on image mat typ

  for (unsigned int row = m_pnt_min.y; row < m_pnt_max.y; ++row) {
      //ptr:
      float *ptr_res        =  (float*)m_result.ptr(row);
      const float *ptr_abs  =  (float*)m_values_abs.ptr(row);
      const float *ptr_fac  =  (float*)m_values_fac.ptr(row);

      for (unsigned int col = m_pnt_min.x; col < m_pnt_max.x; col++) {
          //ptr:
          float *uc_pixel_res       = ptr_res;
          const float *uc_pixel_abs = ptr_abs;
          const float *uc_pixel_fac = ptr_fac;
          double factor             = uc_pixel_fac[0] + m_uni_fac;

          if(factor==0.0f)
          {
            divzero=true;
            for(int c=0; c<3; c++) //allow more channel!?
            {
              uc_pixel_res[c]=0;
            }
          }else{
            for(int c=0; c<3; c++) //allow more channel!?
            {
              uc_pixel_res[c]=uc_pixel_abs[c]/factor;
            }
          }
          //shift ptr:
          ptr_res += m_img_delta;
          ptr_abs += m_img_delta;
          ptr_fac += 1;
      }
  }

  if(divzero) {
    std::cout<<"WARNING: facwaszero\n";
  }
}

int                Base::get_video_size()
{
    std::cout<<"inbase:"<< m_video.get(CV_CAP_PROP_FRAME_COUNT)-1<<"\n";
    return m_video.get(CV_CAP_PROP_FRAME_COUNT)-1;
}


/*  some getter...
std::string const& Base::get_file() const{
  return m_file;
}

int const& Base::get_img_type() const{
  return m_img_type;
}

Point const& Base::get_pnt_min() const{
  return m_pnt_min;
}

Point const& Base::get_pnt_max() const{
  return m_pnt_max;
}

int const Base::get_frame_start() const{
    return m_frame_start;
}

int const Base::get_frame_last() const{
  return m_frame_last;
}

float const Base::get_intensity() const{
  return m_intensity;
}

Mat& Base::get_values_abs(){
    return m_values_abs;
}

Mat& Base::get_values_fac(){
  return m_values_fac;
}

double& Base::get_uni_fac(){
  return m_uni_fac;
}



void                Base::add_segment(int start, int end){
  double inten_loc=1.0;
  double inten_glo=1.0;
  m_segments.push_back(Segment(m_file,m_img_type,m_pnt_min,m_pnt_max, start, end,inten_loc, inten_glo,m_values_abs,m_values_fac,m_uni_fac));
  m_seg_in_calc.push_back(&m_segments.back());
  m_segments.back().in_work=true;
  m_in_calculation=true;
}
void                Base::move_segment(int id, int delta){
  //m_segments.push_back(Segment(m_file,m_img_type,m_pnt_min,m_pnt_max, start, end,inten_loc, inten_glo,m_values_abs,m_values_fac,m_uni_fac));
  //set soll wert
  m_segments[id].move_in_time(delta);
  m_seg_in_calc.push_back(&m_segments[id]);
  m_segments[id].in_work=true;
  m_in_calculation=true;
}

void                Base::set_exposure(int id, int imgs){
  //set soll wert von für end
  m_segments[id].set_exposure(imgs);
  m_seg_in_calc.push_back(&m_segments[id]);
  m_segments[id].in_work=true;
  m_in_calculation=true;
}

void                Base::set_startframe(int id, int frame){
  m_segments[id].set_startframe(frame);
  m_seg_in_calc.push_back(&m_segments[id]);
  m_segments[id].in_work=true;
  m_in_calculation=true;
}

void                Base::set_endframe(int id, int frame){
  m_segments[id].set_endframe(frame);
  m_seg_in_calc.push_back(&m_segments[id]);
  m_segments[id].in_work=true;
  m_in_calculation=true;
}

void                Base::set_exposure_delta(int id, int delta){
  m_segments[id].set_exposure_delta(delta);
  m_seg_in_calc.push_back(&m_segments[id]);
  m_segments[id].in_work=true;
  m_in_calculation=true;
}

void                Base::delete_segment(){  //id
  //delete a segment:
  //-> m_segments
  //-> m_in_calc_seg
  //free mem!!
}

void                Base::run(){             //routine
  bool lucas_is_clever=false;
  int sleep_time=100;

  while(!lucas_is_clever)
  {
    //any changes?
    if(!m_in_calculation)
    {//no calculation available
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }else{
      //calculation
      //forloop with that deletes elements if calc done
      //https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
      //rechange to vec!

    }
  }
}
*/
