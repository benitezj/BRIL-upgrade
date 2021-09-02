#include "stat_precision_globals.h"
#include <fstream>



void print_sigma_visible(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     float trigger_rate = 0,  //Hz
		     float pileup=0,
		     float pp_crossection=0){

  myfile<<DETECTOR
      <<setprecision(3);
   float count_per_event_PU_1=(count_per_event/pileup);
	float sigma_vis=((pp_crossection)*count_per_event_PU_1)/pow(10,-27);
    //pu=200, 1bx, 1s
     myfile<<"&"<<count_per_event_PU_1<<"&"<<sigma_vis<<"\\\\"<<endl;
  
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
  myfile<<"/////////////////////sigma visible///////////////////////////"<<endl;
  myfile<<"0////////////////////////////////////////////////////////////"<<endl;
  
  myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l | c | c |}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<" & $\\left\\langle N_{\\text {observables/interaction }}\\right\\rangle $& $\\sigma_{vis}$ mb  \\\\"<<endl;
  myfile<<"\\hline"<<endl;
  print_sigma_visible("TEPXD4R1 Clusters",TEPXDR_C[0][3][0]+TEPXDR_C[1][3][0],825e3,200,total_pp_crossection_14);
  print_sigma_visible("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][3][0]+TEPXDR_2x[1][3][0],825e3,200,total_pp_crossection_14);
  print_sigma_visible("TEPX Clusters",TEPX_C,75e3,200,total_pp_crossection_14);
  print_sigma_visible("TEPX 2x Coincidences",TEPX_2x,75e3,200,total_pp_crossection_14);
  print_sigma_visible("OT Layer 6 track stubs",OTL6,40e6,200,total_pp_crossection_14);
  print_sigma_visible("DT Trigger Primitives",DTTP,40e6,200,total_pp_crossection_13);
  print_sigma_visible("BMTF",BMTF,40e6,200,total_pp_crossection_13);
  print_sigma_visible("EMTF",EMTF,40e6,200,total_pp_crossection_13);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  myfile.close();
  cout<< TEPX_C<<endl;
  cout<< TEPX_2x<<endl;


}

