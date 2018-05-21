// gcc img.c `pkg-config --cflags gtk+-3.0 --libs gtk+-3.0` -o img
/*
todo:
-0
button changes image writing random segment value
simple imwrite
-1
draw/scale image in gtk
-2
change parameter of segment with gtk
*/

#include <gtk/gtk.h>
#include <iostream>
#include <string.h>
#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include "test.hpp"
#include "base.hpp"


using namespace cv;
using namespace std;
Base* test_base;
int number=0;
void print_hello (GtkWidget *widget, gpointer   data){
  g_print ("doitXXXX\n");
  imwrite( "./test.jpg", test_base->get_result());
  test_base->upd_rand();
}

/*
seems to not allow multiple events like this.. so no long calculations pls!
*/
static gboolean timer_(gpointer data){
  g_print ("doit\n");
  test_base->continue_work();
  imwrite( "./test1.jpg", test_base->get_result());
  number++;
  int n_numb=number;
  return true;//keep ontimer
}

static void activate (GtkApplication *app, gpointer user_data){
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;


  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);

  button = gtk_button_new_with_label ("Hello World");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  //g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);

  gtk_widget_show_all (window);
  g_timeout_add_seconds(1, timer_, button);

}



int main (int    argc, char **argv){
  GtkApplication *app;
  test_base = new Base("./../../time/0_basic_vid.MP4");
  std::cout << "done!" << endl;


  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
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
