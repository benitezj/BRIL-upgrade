#include "stat_precision_globals.h"




void print_data_rates(TString DETECTOR= "TEPX",
                      float number_of_histo=0, 
                      float mean_counts=0,
                      float trigger_rate=0,
                      int N_header=0,
                      int N_mask=0,
                      int N_err= 0){

    //mean counst per event perbx/4LN
    int mean_counts_bx=(mean_counts* second * trigger_rate)/(NBX);
    //bits per bin
    int bits_per_bin=ceil(log2(mean_counts_bx));
    if ( bits_per_bin <=32 && bits_per_bin>16 ) {
       bits_per_bin=32;

}
    else if (bits_per_bin<=16 && bits_per_bin>8 ){

            bits_per_bin=16;

}          

     //bit per histogram
     int bits_per_histo=(NBX*bits_per_bin)+(N_header+N_mask+N_err)*32;
     myfile<< DETECTOR
     <<setprecision(3)
     //Number of Histograms
     <<"&"<<number_of_histo
     
     // Bits per Histogram
     <<"&"<< (bits_per_histo)/1000
     
     //Data Transfer Rates
     <<"&"<< (number_of_histo*bits_per_histo)/(second*1000000)

     <<"\\\\"<<endl;
  
    myfile<<"\\hline"<<endl;     

}
void data_used(TString DETECTOR_d= "TEPX",
                      float number_of_histo_d=0, 
                      float mean_counts_d=0,
                      int trigger_rate_d=0){
                          //mean counst per event perbx/4LN
    float mean_counts_bx_d=(mean_counts_d* second *trigger_rate_d)/(3564);
    //bits per bin
    float bits_per_bin_d=ceil(log2(mean_counts_bx_d));
          
     //bit per histogram

     myfile<< DETECTOR_d
     <<setprecision(3)
     <<"&"<<trigger_rate_d/1000
     <<"&"<<mean_counts_d
     <<"&"<<mean_counts_bx_d
     <<"&"<< bits_per_bin_d
     <<"\\\\"<<endl;
  
    myfile<<"\\hline"<<endl;     


}

void Data_Rates(){
     
TEPX_Counts();

myfile.open("Data_Rate_tables_LATEX.txt");


/////////////////////////////////////
//TEPX Clusters                    // 
/////////////////////////////////////


float Ncluster_QuarterRing=TEPXDR_C[1][3][0]*0.25;        
float Nhistogram_C  =  152  ;
/////////////////////////////////////
//TEPXD4R1 Clusters                // 
/////////////////////////////////////
        
float D4R1_Nhistogram_C  =  2*4;

/////////////////////////////////////
//TEPX 2x Coincidences             // 
/////////////////////////////////////
  
  float N2x_QuarterRing=2*TEPXDR_2x[3][0]*0.25;
  float Nhistogram_2x =  152  ;

/////////////////////////////////////
//TEPXD4R1 2x Coincidences         // 
/////////////////////////////////////


  float D4R1_Nhistogram_2x =  2*4;
  
/////////////////////////////////////
//OT                               // 
/////////////////////////////////////

float Nladder= 78;
float Nmodule_ladder = 12; //number of modules per ladder 
float Nmodule =  Nmodule_ladder * Nladder * 2 ;  //total number of modules
float Nstub_module  = 8; //  number of stubs per module per event 

float Nhistogram_OT = 156;



/////////////////////////////////////
//DT                               // 
/////////////////////////////////////

float Ntp_chamber = 0.0125;  //trigger primitives per chamber per event for pu=200

float Nhistogram_DT = 250;

/////////////////////////////////////
//BMTF                             // 
/////////////////////////////////////
float Ntr_BMTF=0.041;

float NHisto_BMTF=1;
/////////////////////////////////////
//EMTF                             // 
/////////////////////////////////////
     
float Ntr_EMTF=0.234;

float NHisto_EMTF=1;
  /////////////////////////////////////
  ///create table 
  /////////////////////////////////////
    myfile<<ctime(&mytime)<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;
  myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l  |c |c |c|}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<"&  Number of Histograms & Memory per histogram (Kb) & Data Transfer Rates (Mbps)\\\\"<<endl;
  myfile<<"\\hline"<<endl;  
  
  print_data_rates("TEPXD4R1 Clusters",D4R1_Nhistogram_C,Ncluster_QuarterRing,825e3,9,4,320);
  print_data_rates("TEPXD4R1 2x Coincidences",D4R1_Nhistogram_2x,N2x_QuarterRing,825e3,9,4,320);
  print_data_rates("TEPX Clusters",Nhistogram_C,Ncluster_QuarterRing,75e3,9,4,768);
  print_data_rates("TEPX 2x Coincidences",Nhistogram_2x,N2x_QuarterRing,75e3,9,4,768);
  print_data_rates("OT Layer 6 track stubs",Nhistogram_OT,Nstub_module,40e6,9,4,192);
  print_data_rates("DT Trigger Primitives",Nhistogram_DT,Ntp_chamber,40e6,0,0,0);
  print_data_rates("BMTF Track",NHisto_BMTF,Ntr_BMTF,40e6,0,0,0);
  print_data_rates("EMTF Tracks",NHisto_EMTF,Ntr_EMTF,40e6,0,0,0);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  
  
    myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l |c |c |c |c|}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<"&  Trigger rate (KHz) & Counts per event & Counts/bx/1s&Bits/bin\\\\"<<endl;
  myfile<<"\\hline"<<endl;
 data_used("TEPXD4R1 Clusters",D4R1_Nhistogram_C,Ncluster_QuarterRing,825e3);
  data_used("TEPXD4R1 2x Coincidences",D4R1_Nhistogram_2x,N2x_QuarterRing,825e3);
  data_used("TEPX Clusters",Nhistogram_C,Ncluster_QuarterRing,75e3);
  data_used("TEPX 2x Coincidences",Nhistogram_2x,N2x_QuarterRing,75e3);
  data_used("OT Layer 6 track stubs",Nhistogram_OT,Nstub_module,40e6);
  data_used("DT Trigger Primitives",Nhistogram_DT,Ntp_chamber,40e6);
  data_used("BMTF Track",NHisto_BMTF,Ntr_BMTF,40e6);
  data_used("EMTF Tracks",NHisto_EMTF,Ntr_EMTF,40e6);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  myfile.close();


}






