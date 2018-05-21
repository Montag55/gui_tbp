#ifndef BASE_HPP
#define BASE_HPP

/*
The BASE is our main C++ Interface to load videos and interpret them as images.
We will use a QT-GUI and a Terminal Interface...

the base basically contains the reference video, organizes all segments and
provides the resulting image. you cann add segments, but you have to store
and edit them yourself...
*/

class Segment;                  //forward declaration
#include <opencv2/opencv.hpp>   //to acces images & videos
#include <string.h>             //<3 string
#include <vector>
#include <lib/libtbp/include/segment.hpp>

using namespace cv;
using namespace std;

class Base {
public:
        Base(std::string const& video_name);
        ~Base();
        //ORGA::::::::::::::::::::::::::::::::::::::::::::::::
/*NY*/  //void              add_video();              //add another video to the Base
        Segment*            add_segment();            //type, id change with reference
        Segment*            add_segment(int start, int end);            //type, id change with reference
        void                save(std::string file);   //saves output image

        //WORK::::::::::::::::::::::::::::::::::::::::::::::::
        bool                work_to_do();
        void                continue_work();   //routine fct to continue work in segm
        void                set_work_size(int i);
        Mat const&          get_result()     const;
        Mat const&          get_frame(int i);  //preview

        //PROT?:::::::::::::::::::::::::::::::::::::::::::::::
        void                add_work(Segment* new_seg); //maybe protected?

private:
        void                update_result();  //whenever values_abs and values_fac
                                              //are edited, we need to update the
                                              //resulting image
        //performance boost-> whenever we only edit a few pixels, we could use a
        //update-mask in order ot not have to always update all pixels.
        //so we should probably have to update functions!

private:
  bool                    m_in_calculation;  //in_calculation?

  //origin:
  std::string             m_file;             //vector..
  VideoCapture            m_video;            //vector..
  int                     m_img_type;         //colour resolution
  int                     m_work_size;    //work-size

  //domain:
  Point                   m_pnt_min;
  Point                   m_pnt_max;
  int                     m_frame_start;
  int                     m_frame_last;

  //daat:
  std::vector<Segment>    m_segments;           //in order to delete
  std::vector<Segment*>   m_seg_in_calc;        //stores currently edited segments
  Mat                     m_values_abs;
  Mat                     m_values_fac;
  double                  m_uni_fac;
  float                   m_intensity;           //overall intensity: default: 1.0f
  Mat                     m_result;
};

#endif
