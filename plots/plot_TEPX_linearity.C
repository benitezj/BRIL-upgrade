#include "/home/ashish/BRIL-upgrade/plots/linearity_globals.h"
#include "/home/ashish/BRIL-upgrade/plots/linearity_2D.C"
//#include "/home/ashish/Projection.C"
#include "/home/ashish/BRIL-upgrade/plots/linearity_fit.C"

void plot_TEPX_linearity(){
  
  int option = 2;

  //call functions
  initialize(option);
  linearity_2D(option);
  //Projection(option);
  linearity_fit(option);
 
}
