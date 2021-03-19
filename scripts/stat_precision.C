#include "stat_precision_globals.h"

void print_precision_funtion(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     int trigger_rate = 0  //Hz
		     ){

  cout<<DETECTOR
      <<setprecision(3)


    //pu=200, 1bx, 1s
      <<"&"<<trigger_rate/1000<<"&"<<100/sqrt(count_per_event*trigger_rate*second/NBX)
     
   // pu+200, 2500 bx, 1s
      <<"&"<<100/sqrt(NCOLLIDING*count_per_event*trigger_rate*second/NBX)




      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}


void print_precisionvdm(TString DETECTOR_vdm = "TEPX",
		     float count_per_event_vdm=0,
		     int trigger_rate_vdm = 0  //Hz
		     ){


  cout<<DETECTOR_vdm
      //<<setprecision(5)
    //<<" & "<<trigger_rate/1000

      <<setprecision(3)

    ///Vdm 1 bx, 1s
      <<"&"<<trigger_rate_vdm/1000<<"&"<< 100/sqrt((count_per_event_vdm/400)*trigger_rate_vdm*second/NBX)<<"&"
      //1 bx, 30s
      <<100/sqrt((count_per_event_vdm/400)*trigger_rate_vdm*VDM/NBX)  // pu 0.5 VDM
      //Vdm 100 bx, 30s
      <<" & "<<100/sqrt(150*(count_per_event_vdm/400)*trigger_rate_vdm*VDM/NBX)// pu 0.5 VDM

      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}


void stat_precision(){

  TEPX_Counts();


  /////////////////////////////////////
  ///create table per bx
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c |}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<" & Readout Rate (kHz)& 1 bx, 1s &2500 bx, 1s   \\\\"<<endl;
  cout<<"\\hline"<<endl;
  print_precision_funtion("TEPXD4R1 Clusters",TEPXDR_C[0][0][0]+TEPXDR_C[0][3][0],825e3);
  print_precision_funtion("TEPXD4R1 2x Coincidences",2*TEPXDR_2x[3][0],825e3);
  print_precision_funtion("TEPX Clusters",TEPX_C,75e3);
  print_precision_funtion("TEPX 2x Coincidences",2*TEPX_2x,75e3);
  print_precision_funtion("OT Layer 6 track stubs",OTL6,40e6);
  print_precision_funtion("DT Trigger Primitives",DTTP,40e6);
  print_precision_funtion("BMTF",BMTF,40e6);
  print_precision_funtion("EMTF",EMTF,40e6);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;
  
  cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  
  /////////////////////////////////////
  ///create table per bx for Vdm
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c |c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<"  & Readout Rate (kHz) &1 bx, 1s & 1 bx, 30s & 150 bx, 30s\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  print_precisionvdm("TEPXD4R1 Clusters",TEPXDR_C[0][3][0]+TEPXDR_C[0][3][0],825e3);  
  print_precisionvdm("TEPXD4R1 2x Coincidences",2*TEPXDR_2x[3][0],825e3);
  print_precisionvdm("TEPX Clusters",TEPX_C,500e3);
  print_precisionvdm("TEPX 2x Coincidences",2*TEPX_2x,500e3);
  print_precisionvdm("OT Layer 6 track stubs",OTL6,40e6);
  print_precisionvdm("DT Trigger Primitives",DTTP,40e6);
  print_precisionvdm("BMTF",BMTF,40e6);
  print_precisionvdm("EMTF",EMTF,40e6);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;
  
    cout<<TEPXDR_2x[3][0] <<endl;

}


