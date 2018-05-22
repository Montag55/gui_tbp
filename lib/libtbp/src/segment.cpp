#include <lib/libtbp/include/segment.hpp>
#include <lib/libtbp/include/base.hpp>

#include <string.h>
#include <math.h>
using namespace cv;
using namespace std;
#include <chrono>;

int           m_frame_start_destin;
int           m_frame_last_destin;
int           m_frame_start_actual;
int           m_frame_last_actual;

Segment::Segment(std::string file, int img_type, Point min, Point max, int start_frame, int last_frame, double intensity_local, double intensity_global,Base* mother, Mat& mother_val,  Mat& mother_fac, double& mother_uni):
m_file {file},
m_video{VideoCapture(m_file)},
m_img_type{img_type},
m_pnt_min{min},
m_pnt_max{max},
m_frame_start_destin{start_frame},
m_frame_last_destin{last_frame},
m_frame_start_actual{-1}, //no comp yet
m_frame_last_actual{-1},  //no comp yet
m_intensity_local{intensity_local},
m_intensity_global{intensity_global},
m_mother{mother},
m_values_abs{Mat(m_pnt_max.y, m_pnt_max.x, m_img_type, cv::Scalar(0,0,0))},
m_values_fac{Mat(m_pnt_max.y, m_pnt_max.x, CV_64FC1, cv::Scalar(0))},
m_uni_fac{0.0f},
m_interpretation_mode{0}, //average
m_m_values_abs{mother_val},
m_m_values_fac{mother_fac},
m_m_uni_fac{mother_uni}{
  //update itself:
  //kann sich selbst anmelden!

  ready_to_work();

  /*
  std::cout<<"NEW Segment\n";
  std::cout<<"video:"       <<m_file<<"\n";
  std::cout<<"pnt_min:"     <<m_pnt_min<<"\n";
  std::cout<<"pnt_max:"     <<m_pnt_max<<"\n";
  std::cout<<"frame_start:" <<m_frame_start_destin<<"\n";
  std::cout<<"frame_last:"  <<m_frame_last_destin<<"\n";
  std::cout<<"intensity_l:" <<m_intensity_local<<"\n";
  std::cout<<"intensity_g:" <<m_intensity_global<<"\n";
  */
}



Segment::~Segment(){
  std::cout<<"delete segment\n";
}

void Segment::ready_to_work()
{//adds itself to the mothers work-que
  if(m_work_done) //change status
  {
    m_work_done=false;
    m_mother->add_work(this);
  }//otherwise already in calculation
}

bool Segment::work(int work_size){
  //ist soll gleich ist stand?
  //it works work_size much and returns, wether it is done!
  //choose interpretations-mode:

  if(m_interpretation_mode==0)
  {
    m_work_done =average(work_size);
  }//..other interpolations...?

  //if work is done return true
  return m_work_done;
}

//averages the whole subdomain in time
//does not use smaller xy subdomain
//we need to switch between interpretations here!
//already uses a kind of clever working
bool Segment::average(int work_size){
  //substract old influence here!
  m_m_values_abs-=m_values_abs*m_intensity_local*m_intensity_global;
  m_m_uni_fac   -=m_uni_fac*m_intensity_global;

  Mat tmp_frame;
  Mat tmp_frame_d;

  //correct updating to master!!
  int moves     = abs(m_frame_start_destin-m_frame_start_actual)+abs(m_frame_last_destin-m_frame_last_actual);
  int alt_moves = m_frame_last_destin-m_frame_start_destin;
  if(alt_moves<=moves){
    std::cout<<"shortcut\n";
    m_frame_start_actual=m_frame_start_destin;
    m_frame_last_actual=m_frame_start_destin;
    m_values_abs-=m_values_abs;
  }

  //startingpoint:
  if(m_frame_start_actual==-1){//not yet computed!
    m_frame_start_actual=m_frame_start_destin;

  }else if(m_frame_start_actual<m_frame_start_destin){
    double frameRate = m_video.get(CV_CAP_PROP_FPS);
    double frameTime = 1000.0 * m_frame_start_actual / frameRate;
    m_video.set(CV_CAP_PROP_POS_MSEC, frameTime);

    int endpoint=m_frame_start_actual+work_size;
    if(endpoint>m_frame_start_destin){
      endpoint=m_frame_start_destin;
    }

    for(int i= m_frame_start_actual; i<endpoint; i++)
    {
      m_video.read(tmp_frame);
      if(tmp_frame.empty())
      {
        std::cout<<"empty\n";
      }
      tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?
      m_values_abs-=tmp_frame_d;
    }
    m_frame_start_actual=endpoint;

  }else if(m_frame_start_actual>m_frame_start_destin){
    //we need to read the video in orginal direction!
    int startpoint=m_frame_start_actual-work_size;
    if(startpoint<m_frame_start_destin)
    {
      startpoint=m_frame_start_destin;
    }

    if(!m_video.set(CV_CAP_PROP_POS_FRAMES,startpoint))  //start frame
    {
      std::cout<<"fail!\n";
    }

    for(int i=startpoint; i<m_frame_start_actual; i++)
    {
      m_video.read(tmp_frame);
      tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?
      m_values_abs+=tmp_frame_d;
    }
    m_frame_start_actual=startpoint;
  }

  //endpoint:
  if(m_frame_last_actual==-1){//not yet computed!
    m_frame_last_actual=m_frame_start_destin;

  }else if(m_frame_last_actual<m_frame_last_destin){
    double frameRate = m_video.get(CV_CAP_PROP_FPS);
    double frameTime = 1000.0 * m_frame_last_actual / frameRate;
    m_video.set(CV_CAP_PROP_POS_MSEC, frameTime);

    int endpoint=m_frame_last_actual+work_size;
    if(endpoint>m_frame_last_destin){
      endpoint=m_frame_last_destin;
    }

    for(int i=m_frame_last_actual; i<endpoint; i++)
    {
      //calc
      bool success= m_video.read(tmp_frame);
      if (!success){
        cout << "problems............\n";
      }
      tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?
      m_values_abs+=tmp_frame_d;
    }
    m_frame_last_actual=endpoint;

  }else if(m_frame_last_actual>m_frame_last_destin){
    int startpoint=m_frame_last_actual-work_size;
    if(startpoint<m_frame_last_destin)
    {
      startpoint=m_frame_last_destin;
    }

    if(!m_video.set(CV_CAP_PROP_POS_FRAMES,startpoint))  //start frame
    {
      std::cout<<"fail!\n";
    }

    for(int i=startpoint; i<m_frame_last_actual; i++)
    {
      m_video.read(tmp_frame);
      tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?
      m_values_abs-=tmp_frame_d;
    }
    m_frame_last_actual=startpoint;
  }
/*
  std::cout<<m_frame_start_actual<<"start ac\n";
  std::cout<<m_frame_start_destin<<"start de\n";

  std::cout<<m_frame_last_actual<<"last ac\n";
  std::cout<<m_frame_last_destin<<"last dec\n";
*/

  m_uni_fac=        m_frame_last_actual-m_frame_start_actual;
  m_m_values_abs    +=m_values_abs*m_intensity_local*m_intensity_global;
  //m_m_values_fac  +=m_values_fac; //unnec
  m_m_uni_fac       +=m_uni_fac*m_intensity_global;

  if((m_frame_start_destin==m_frame_start_actual) && (m_frame_last_destin==m_frame_last_actual))
  {
    return true;  //ist = soll
  }else{
    return false; //ist != soll
  }
}

//it boosts extraordinary influences in an image
//void Segment::boost_diff()
//{
  //some image sectors look like they are negativ.. should that happen?
  /*another not to extreme  smoother boost function, might be nice*/
/*
  double treshhold=10;
  //reset influence :
  m_m_values_abs-m_values_abs;
  m_m_values_fac-m_values_fac;
  for(unsigned int i = m_frame_start; i <= m_frame_last; i++) {

    std::cout<<"frame:"<< i <<"\n";
    m_video >> tmp_frame;
    tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?

    m_values_abs += tmp_frame_d * m_intensity_local * m_intensity_global;
  }

  m_m_values_abs  += m_values_abs;
  m_m_uni_fac     += m_uni_fac;
  //auto end=std::chrono::high_resolution_clock::now();
  //auto duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-st).count();
  //std::cout<<duration<<"\n";

  //search for differences:
  std::cout<<"search for diff\n";
  m_video.set(CV_CAP_PROP_POS_FRAMES,m_frame_start);  //start frame
  m_values_abs+=avg_mat;    //set simpl clr
  for(int i=m_frame_start; i<=m_frame_last;i++)
  {
    //std::cout<<"frame:"<<i<<"\n";
    m_video.read(tmp_frame);

    tmp_frame.convertTo(tmp_frame_d, m_img_type);
      for (int row = m_pnt_min.y; row < m_pnt_max.y; ++row){
          //ptr:
          const float *ptr_tmp =        (float*)tmp_frame_d.ptr(row);
          const float *ptr_avg =        (float*)avg_mat.ptr(row);
          float *ptr_abs =  (float*)m_values_abs.ptr(row);
          //const float *ptr_fac =  (float*)m_values_fac.ptr(row);
          for (int col = m_pnt_min.x; col < m_pnt_max.x; col++)
          {
              //ptr:
              const float *uc_pixel_tmp = ptr_tmp;
              const float *uc_pixel_avg = ptr_avg;
              float *uc_pixel_abs = ptr_abs;

              double distance_old=abs(uc_pixel_abs[0]-uc_pixel_avg[0])+abs(uc_pixel_abs[1]-uc_pixel_avg[1])+abs(uc_pixel_abs[2]-uc_pixel_avg[2]);
              double distance_new=abs(uc_pixel_tmp[0]-uc_pixel_avg[0])+abs(uc_pixel_tmp[1]-uc_pixel_avg[1])+abs(uc_pixel_tmp[2]-uc_pixel_avg[2]);
              if(distance_new>treshhold && distance_old<distance_new)
              {
                for(int c=0; c<3; c++) //allow more channel!?
                {
                  uc_pixel_abs[c]=uc_pixel_tmp[c];
                }
              }

              ptr_tmp += 3;
              ptr_avg += 3;
              ptr_abs += 3;
          }
      }
  }
  m_m_uni_fac+=1;
  m_m_values_abs+=m_values_abs;
  */
//}

//it boosts extraordinary influences in an image
/*
void Segment::boost_diff() {
  /*
  /*another not to extreme  smoother boost function, might be nice*/
  /*
  double treshhold = 10;
  //reset influence :
  m_m_values_abs - m_values_abs;
  m_m_values_fac - m_values_fac;

  //vid
  Mat tmp_frame;
  Mat tmp_frame_d;


  Mat avg_mat = Mat(m_pnt_max.y, m_pnt_max.x, m_img_type, cv::Scalar(0,0,0));

  //get avg
  m_uni_fac = 1;             //simply the number of frames
  m_video.set(CV_CAP_PROP_POS_FRAMES, m_frame_start);  //start frame

  for(unsigned int i = m_frame_start; i <= m_frame_last; i++) {
    std::cout<<"frame:"<<i<<"\n";
    m_video.read(tmp_frame);

    tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?

    avg_mat += tmp_frame_d / (m_frame_last - m_frame_start+1);
  }

  //search for differences:
  std::cout<<"search for diff\n";
  m_video.set(CV_CAP_PROP_POS_FRAMES, m_frame_start);  //start frame
  m_values_abs += avg_mat;    //set simpl clr

  for(int i = m_frame_start; i <= m_frame_last; i++) {
    //std::cout<<"frame:"<<i<<"\n";
    m_video.read(tmp_frame);

    tmp_frame.convertTo(tmp_frame_d, m_img_type);
      for (unsigned int row = m_pnt_min.y; row < m_pnt_max.y; ++row){
          //ptr:
          const float *ptr_tmp =        (float*)tmp_frame_d.ptr(row);
          const float *ptr_avg =        (float*)avg_mat.ptr(row);
          float *ptr_abs =  (float*)m_values_abs.ptr(row);
          float *ptr_fac =  (float*)m_values_fac.ptr(row);
          //const float *ptr_fac =  (float*)m_values_fac.ptr(row);
          for (unsigned int col = m_pnt_min.x; col < m_pnt_max.x; col++) {
              //ptr:
              const float *uc_pixel_tmp = ptr_tmp;
              const float *uc_pixel_avg = ptr_avg;
              float *uc_pixel_abs = ptr_abs;
              float *uc_pixel_fac = ptr_fac;

              //double distance_old=abs(uc_pixel_abs[0]-uc_pixel_avg[0])+abs(uc_pixel_abs[1]-uc_pixel_avg[1])+abs(uc_pixel_abs[2]-uc_pixel_avg[2]);
              double distance_new=pow(abs(uc_pixel_tmp[0]-uc_pixel_avg[0])+abs(uc_pixel_tmp[1]-uc_pixel_avg[1])+abs(uc_pixel_tmp[2]-uc_pixel_avg[2]),power);
              if(distance_new>treshhold)
              {
                for(int c=0; c<3; c++) //allow more channel!
                {
                  uc_pixel_abs[c]+=uc_pixel_tmp[c]*distance_new;
                }

                uc_pixel_fac[0]+=distance_new;
              }


              ptr_tmp += 3;
              ptr_avg += 3;
              ptr_abs += 3;
              ptr_fac += 1;
          }
      }
  }
  m_m_uni_fac+=1;
  m_m_values_abs+=m_values_abs;
  m_m_values_fac+=m_values_fac;

}*/

//EDIT THE SEGMENT:
  void Segment::move_in_time(int delta){
    m_frame_start_destin+=delta;
    m_frame_last_destin+=delta;
    ready_to_work();
  }

  void Segment::set_exposure(int new_exposure){
    m_frame_last_destin=m_frame_start_destin+new_exposure;
    ready_to_work();
  }

  void Segment::set_startframe(int imgs){
    std::cout<<"set_new_frame"<<std::endl;
    m_frame_start_destin=imgs;
    ready_to_work();
  }

  void Segment::set_endframe(int imgs){
    m_frame_last_destin=imgs;
    ready_to_work();
  }

  void Segment::set_exposure_delta(int delta){
    m_frame_last_destin+=delta;
    ready_to_work();
  }

  void Segment::set_local_intensity(float i){
    m_m_values_abs-=m_values_abs*m_intensity_local*m_intensity_global;

  //set
    m_intensity_local=i;
    m_m_values_abs    +=m_values_abs*m_intensity_local*m_intensity_global;
    ready_to_work();//to apply changes
  }

  void Segment::set_global_intensity(float i){
    m_m_values_abs    -=m_values_abs*m_intensity_local*m_intensity_global;
    m_m_uni_fac       -=m_uni_fac*m_intensity_global;

  //set
    m_intensity_global=i;
    m_m_values_abs    +=m_values_abs*m_intensity_local*m_intensity_global;
    m_m_uni_fac       +=m_uni_fac*m_intensity_global;
    ready_to_work();//to apply changes
  }

  int Segment::maximum(){
      return m_video.get(CV_CAP_PROP_FRAME_COUNT)-1;
  }

/*
void Segment::boost_similarities(int power){
  //tries to kick everything out that is moving...
  //another ,but expensive, option might be a modal filter..in time?
  /*
  might be good to treshhold video errors.. litle bit shaking cam..
  and make effect stronger
  */
  /*
  double treshhold=3*255-300;
  /*another not to extreme  smoother boost function, might be nice*/
  //double treshhold=10;
  //reset influence :
  /*
  m_m_values_abs - m_values_abs;
  m_m_values_fac - m_values_fac;

  //vid
  Mat tmp_frame;
  Mat tmp_frame_d;

  /*
  Mat avg_mat=Mat(m_pnt_max.y, m_pnt_max.x, m_img_type, cv::Scalar(0,0,0));

  //get avg
  m_uni_fac = 1;             //simply the number of frames
  m_video.set(CV_CAP_PROP_POS_FRAMES,m_frame_start);  //start frame

  for(unsigned int i = m_frame_start; i <= m_frame_last; i++) {
    std::cout<<"frame:"<<i<<"\n";
    m_video.read(tmp_frame);

    tmp_frame.convertTo(tmp_frame_d, m_img_type);   //do this for the whole video right at the start!?

    avg_mat += tmp_frame_d / (m_frame_last - m_frame_start + 1);
  }

  //search for differences:
  std::cout<<"search for diff\n";
  m_video.set(CV_CAP_PROP_POS_FRAMES, m_frame_start);  //start frame
  m_values_abs += avg_mat;    //set simpl clr

  for(unsigned int i = m_frame_start; i <= m_frame_last; i++) {
    //std::cout<<"frame:"<<i<<"\n";
    m_video.read(tmp_frame);

    tmp_frame.convertTo(tmp_frame_d, m_img_type);
      for (unsigned int row = m_pnt_min.y; row < m_pnt_max.y; ++row){
          //ptr:
          const float *ptr_tmp  =  (float*)tmp_frame_d.ptr(row);
          const float *ptr_avg  =  (float*)avg_mat.ptr(row);
          float *ptr_abs        =  (float*)m_values_abs.ptr(row);
          float *ptr_fac        =  (float*)m_values_fac.ptr(row);
          //const float *ptr_fac =  (float*)m_values_fac.ptr(row);
          for (unsigned int col = m_pnt_min.x; col < m_pnt_max.x; col++) {
              //ptr:
              const float *uc_pixel_tmp = ptr_tmp;
              const float *uc_pixel_avg = ptr_avg;
              float *uc_pixel_abs       = ptr_abs;
              float *uc_pixel_fac       = ptr_fac;

              //double distance_old=abs(uc_pixel_abs[0]-uc_pixel_avg[0])+abs(uc_pixel_abs[1]-uc_pixel_avg[1])+abs(uc_pixel_abs[2]-uc_pixel_avg[2]);
              //maybe other fct?: double distance_new=exp(((3*255)-(abs(uc_pixel_tmp[0]-uc_pixel_avg[0])+abs(uc_pixel_tmp[1]-uc_pixel_avg[1])+abs(uc_pixel_tmp[2]-uc_pixel_avg[2])))-500);

              //maybe pythagoras dist?:
              double distance=(abs(uc_pixel_tmp[0]-uc_pixel_avg[0])+abs(uc_pixel_tmp[1]-uc_pixel_avg[1])+abs(uc_pixel_tmp[2]-uc_pixel_avg[2]));
              double value =pow(3*255-distance,power);
              if(distance<treshhold)
              {
                for(int c=0; c<3; c++) //allow more channel!
                {
                  uc_pixel_abs[c]+=uc_pixel_tmp[c]*value;
                }

                uc_pixel_fac[0]+=value;
              }else{
                //std::cout<<"cut\n";
              }


              ptr_tmp += 3;
              ptr_avg += 3;
              ptr_abs += 3;
              ptr_fac += 1;
          }
      }
  }
  m_m_uni_fac+=1;
  m_m_values_abs+=m_values_abs;
  m_m_values_fac+=m_values_fac;

}*/
