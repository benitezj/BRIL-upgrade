#include "stat_precision_globals.h"
#include <fstream>



void print_precision_funtion(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     float trigger_rate = 0  //Hz
		     ){

  myfile<<DETECTOR
      <<setprecision(3)


    //pu=200, 1bx, 1s
      <<"&"<<trigger_rate/1000<<"&"<<100/sqrt(count_per_event*trigger_rate*second/NBX)
     
   // pu+200, 2500 bx, 1s
      <<"&"<<100/sqrt(NCOLLIDING*count_per_event*trigger_rate*second/NBX)




      <<"\\\\"<<endl;
  
  myfile<<"\\hline"<<endl;
}


void print_precisionvdm(TString DETECTOR_vdm = "TEPX",
		     float count_per_event_vdm=0,
		     int trigger_rate_vdm = 0,  //Hz
		     int Number_BX=0
		     ){


  myfile<<DETECTOR_vdm
      //<<setprecision(5)
    //<<" & "<<trigger_rate/1000

      <<setprecision(3)
      <<"&"<<trigger_rate_vdm/1000
    ///Vdm 1 bx, 1s
      <<"&"<< 100/sqrt((count_per_event_vdm/400)*trigger_rate_vdm*second/Number_BX)<<"&"
      //1 bx, 30s
      <<100/sqrt((count_per_event_vdm/400)*trigger_rate_vdm*VDM/Number_BX)  // pu 0.5 VDM
      //Vdm 150 bx, 30s
      <<" & "<<100/sqrt(150*(count_per_event_vdm/400)*trigger_rate_vdm*VDM/Number_BX)// pu 0.5 VDM

      <<"\\\\"<<endl;
  
  myfile<<"\\hline"<<endl;
}


void stat_precision(){
  /**/
  TEPX_Counts();


  myfile.open("Stat_Precision_tables_LATEX.txt");
  
  myfile<<ctime(&mytime)<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;

  myfile<<"/////////////////////////////////////////////////////////////"<<endl;
  myfile<<"///Stat pecision per bx and per  2500 bx for physics PU 200//"<<endl;
  myfile<<"0////////////////////////////////////////////////////////////"<<endl;
  
  myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l | c | c | c |}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<" & Readout Rate (kHz)& 1 bx, 1s &2500 bx, 1s   \\\\"<<endl;
  myfile<<"\\hline"<<endl;
  print_precision_funtion("TEPXD4R1 Clusters",TEPXDR_C[0][3][0]+TEPXDR_C[1][3][0],825e3);
  print_precision_funtion("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][3][0]+TEPXDR_2x[1][3][0],825e3);
  print_precision_funtion("TEPX Clusters",TEPX_C,75e3);
  print_precision_funtion("TEPX 2x Coincidences",TEPX_2x,75e3);
  print_precision_funtion("OT Layer 6 track stubs",OTL6,40e6);
  print_precision_funtion("DT Trigger Primitives",DTTP,40e6);
  print_precision_funtion("BMTF",BMTF,40e6);
  print_precision_funtion("EMTF",EMTF,40e6);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  
  myfile<<"////////////////////////////////////////////////////////////"<<endl;
  myfile<<"///Stat pecision per bx and per 150 bx for Vdm scan PU 0.5//"<<endl;
  myfile<<"////////////////////////////////////////////////////////////"<<endl;
  
  /////////////////////////////////////
  ///create table per bx for Vdm
  /////////////////////////////////////
  myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l | c | c | c |c|}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<"  & Readout Rate (kHz) &1 bx, 1s & 1 bx, 30s & 150 bx, 30s\\\\"<<endl;
  myfile<<"\\hline"<<endl;  
  print_precisionvdm("TEPXD4R1 Clusters",TEPXDR_C[0][3][0]+TEPXDR_C[1][3][0],1000e3,NBX_TEPX_VDM);  
  print_precisionvdm("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][3][0]+TEPXDR_2x[1][3][0],1000e3,NBX_TEPX_VDM);
  print_precisionvdm("TEPX Clusters",TEPX_C,500e3,NBX_TEPX_VDM);
  print_precisionvdm("TEPX 2x Coincidences",TEPX_2x,500e3,NBX_TEPX_VDM);
  print_precisionvdm("OT Layer 6 track stubs",OTL6,40e6,NBX);
  print_precisionvdm("DT Trigger Primitives",DTTP,40e6,NBX);
  print_precisionvdm("BMTF",BMTF,40e6,NBX);
  print_precisionvdm("EMTF",EMTF,40e6,NBX);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  myfile.close();


}


