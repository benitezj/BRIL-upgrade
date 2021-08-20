#include "stat_precision_globals.h"
#include <fstream>



void print_sigma_visible(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     float trigger_rate = 0  //Hz
		     ){

  myfile<<DETECTOR
      <<setprecision(3);

	float sigma_vis=(total_pp_crossection)*((count_per_event/200)*trigger_rate*second/NBX);
    //pu=200, 1bx, 1s
     myfile<<"&"<<trigger_rate/1000<<"&"<<sigma_vis<<"\\\\"<<endl;
  
  myfile<<"\\hline"<<endl;
}




void sigma_visible(){
  /**/
  TEPX_Counts();


  myfile.open("sigma_vis.txt");
  
  myfile<<ctime(&mytime)<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;

  myfile<<"/////////////////////////////////////////////////////////////"<<endl;
  myfile<<"///Stat pecision per bx and per  2500 bx for physics PU 200//"<<endl;
  myfile<<"0////////////////////////////////////////////////////////////"<<endl;
  
  myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l | c | c |}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<" & Readout Rate (kHz)& $\\sigma_{vis}$  \\\\"<<endl;
  myfile<<"\\hline"<<endl;
  print_sigma_visible("TEPXD4R1 Clusters",TEPXDR_C[0][3][0]+TEPXDR_C[1][3][0],825e3);
  print_sigma_visible("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][3][0]+TEPXDR_2x[1][3][0],825e3);
  print_sigma_visible("TEPX Clusters",TEPX_C,75e3);
  print_sigma_visible("TEPX 2x Coincidences",TEPX_2x,75e3);
  print_sigma_visible("OT Layer 6 track stubs",OTL6,40e6);
  print_sigma_visible("DT Trigger Primitives",DTTP,40e6);
  print_sigma_visible("BMTF",BMTF,40e6);
  print_sigma_visible("EMTF",EMTF,40e6);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  myfile.close();


}

