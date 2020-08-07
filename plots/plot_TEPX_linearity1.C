#include "/home/ashish/linearity_globals.h"
#include "/home/ashish/linearity_2D.C"
//#include "/home/ashish/Projection.C"
//#include "/home/ashish/linearity_fit.C"

void plot_TEPX_linearity1(){
  
  int option = 1;
 
  //call functions
  initialize(option);
  linearity_2D(option);
  //Projection(option);
  //linearity_fit(option);
 
}
