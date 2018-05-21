/*
a simple terminal interface:
-input video via parameter
##
addsegment       [int]startframe [int] exposure //makes a new segment

% delete segment [int]id
startframe      [int]id   [int]frame
%endframe       [int]id   [int]frame
move            [int]id   [int]delta
exposure        [int]id   [int]imgs
exposure_delta  [int]id   [int]delta
##
-always copmpute full segment
-erstmal nur avg
*/

#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
#include <opencv2/opencv.hpp>
#include "base.hpp"
using namespace cv;
using namespace std;
/*
seems to not allow multiple events like this.. so no long calculations pls!
*/
size_t split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find( ch );
    size_t initialPos = 0;
    strs.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        strs.push_back( txt.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = txt.find( ch, initialPos );
    }

    // Add the last one
    strs.push_back( txt.substr( initialPos, std::min( pos, txt.size() ) - initialPos +1 ) );

    return strs.size();
}

int main (int    argc, char **argv){

  //store segments:
  std::vector<Segment*>   segments;

  if(argc==2)   //file parameter
  {
    Mat image;
    //std::cout<<"starts time reinterpretation application\n";
    std::string file=argv[1];
    Base* base = new Base(file);
    bool fin=false;
    std::cout<<"expecting a segment definition:\n";
    int i=0;
    while(!fin)
    {
        string command;
        std::cout<<"expecting input\n";
        getline (cin,command);
        std::vector<std::string> v;
        split( command, v, ' ' );
        if(v[0]=="addsegment")
        {
          //seems to work
          std::cout<<"addsegment\n";
          int startframe  =std::stoi (v[1]);
          int exposure    =std::stoi (v[2]);
          //std::cout<<"startframe: "<<startframe<<", exposure: "<<exposure<<"\n";
          //add avg segment
           segments.push_back(base->add_segment(startframe, startframe+exposure));
          //check definition of start und endframe..?
        }else if(v[0]=="move"){
          //seems to work with delta + & -
          int id        =std::stoi (v[1]);
          int delta     =std::stoi (v[2]);
          //std::cout<<"move, id:"<<id<<", delta: "<<delta<<"\n";
          //add avg segment
           segments[id]->move_in_time(delta);
           //m_segments.push_back(Segment(m_file,m_img_type,m_pnt_min,m_pnt_max, start, end,inten_loc, inten_glo,m_values_abs,m_values_fac,m_uni_fac));
           //set soll wert
        }else if(v[0]=="exposure"){
          //seems to work
          int id        =std::stoi (v[1]);
          int imgs      =std::stoi (v[2]);
          //std::cout<<"move, id:"<<id<<", delta: "<<delta<<"\n";
          //add avg segment
           //base->set_exposure(id, imgs);

         }else if(v[0]=="startframe"){
           //seems to work
           int id        =std::stoi (v[1]);
           int frame      =std::stoi (v[2]);
           //std::cout<<"move, id:"<<id<<", delta: "<<delta<<"\n";
           //add avg segment
            //base->set_startframe(id, frame);
          }else if(v[0]=="endframe"){
            //seems to work
            int id          =std::stoi (v[1]);
            int frame      =std::stoi (v[2]);
            //std::cout<<"move, id:"<<id<<", delta: "<<delta<<"\n";
            //add avg segment
             //base->set_endframe(id, frame);
           }else if(v[0]=="exposure_delta"){
             //seems to work
             int id        =std::stoi (v[1]);
             int delta      =std::stoi (v[2]);
             //std::cout<<"move, id:"<<id<<", delta: "<<delta<<"\n";
             //add avg segment
              //base->set_exposure_delta(id, delta);
            }else if(v[0]=="inten_local"){
              //seems to work
              int id        =std::stoi (v[1]);
              float i      =std::stof (v[2]);
              segments[id]->set_local_intensity(i);

            }else if(v[0]=="inten_global"){
               //does not work
               int id        =std::stoi (v[1]);
               float i      =std::stof (v[2]);
               segments[id]->set_global_intensity(i);
            }else if(v[0]=="work_size"){
                 //does not work
                 int i      =std::stoi (v[1]);
                 base->set_work_size(i);
            }

        while(base->work_to_do())
        {
          base->continue_work();  //set work size to everything
        }
        std::cout<<"save\n";
        base->save("state"+std::to_string(i)+"out.jpg");
        i++;
    }
    std::cout << "done!" << endl;
    imwrite( "./final.jpg", base->get_result());
  }else{
    std::cout<<"videopfad angeben?\n";
  }

  return 0;
}


/*simple draw img:
#include <gtk/gtk.h>

#define ROWS 500//1080
#define COLS 500//1920
#define BYTES_PER_PIXEL 3

//MAT TO RGB
void bw_to_rgb(guchar *rgb, guchar *bw, size_t sz) {
  for (size_t i = 0; i < sz; i++)
    for (size_t j = 0; j < BYTES_PER_PIXEL; j++)
      rgb[i * BYTES_PER_PIXEL + j] = bw[i];
}


int main(int argc, char** argv ) {

//Mat:
  // grayscale data array
  guchar bw[ROWS * COLS] = { 0 }; // start all black

  // draw a design
  for (int color = 0, i = 20; i < ROWS; i += 20) {
    color = (color == 0) ? 255 : 0;
    for (int r = i; r < ROWS - i; r++)
      for (int c = i; c < COLS - i; c++)
        bw[r * COLS + c] = color;
  }
//
  // convert to rgb (by tripling the values)
  guchar rgb[sizeof bw * BYTES_PER_PIXEL];
  bw_to_rgb(rgb, bw, ROWS * COLS);

  gtk_init(&argc, &argv);

  GdkPixbuf *pb = gdk_pixbuf_new_from_data(
    rgb,
    GDK_COLORSPACE_RGB,     // colorspace (must be RGB)
    0,                      // has_alpha (0 for no alpha)
    8,                      // bits-per-sample (must be 8)
    COLS, ROWS,             // cols, rows
    COLS * BYTES_PER_PIXEL, // rowstride
    NULL, NULL              // destroy_fn, destroy_fn_data
  );
  GtkWidget *image = gtk_image_new_from_pixbuf(pb);

  GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window), "TimeBasedImage");
  gtk_window_set_default_size(GTK_WINDOW(window), COLS+20, ROWS+20);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_container_add(GTK_CONTAINER(window), image);
  g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all(window);

  gtk_main();

  return 0;
}*/
