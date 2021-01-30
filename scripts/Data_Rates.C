float NBX=3564; /// number bunches per orbit
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float Norbit_NB4= 16417.7;// number of orbits per LN4
int   N_header=9*32;
int   N_mask=0;
int   N_err= 0;


void print_data_rates(TString DETECTOR= "TEPX",
                      float number_of_histo=0, 
                      float mean_counts=0,
                      float trigger_rate=0){

    //mean counst per event perbx/4LN
    int mean_counts_bx=(mean_counts* LN4 * trigger_rate)/(3564);
    //bits per bin
    int bits_per_bin=ceil(log2(mean_counts_bx));
    if ( bits_per_bin <=32 && bits_per_bin>16 ) {
       bits_per_bin=32;

}
    else if (bits_per_bin<=16 && bits_per_bin>8 ){

            bits_per_bin=16;

}          

     //bit per histogram
     int bits_per_histo=(NBX*bits_per_bin)+N_header;
     cout<< DETECTOR
     <<setprecision(3)
     //Number of Histograms
     <<"&"<<number_of_histo
     
     // Bits per Histogram
     <<"&"<< (bits_per_histo)
     
     //Data Transfer Rates
     <<"&"<< (number_of_histo*bits_per_histo)/(LN4*1000000)

     <<"\\\\"<<endl;
  
    cout<<"\\hline"<<endl;     

}
void data_used(TString DETECTOR_d= "TEPX",
                      float number_of_histo_d=0, 
                      float mean_counts_d=0,
                      int trigger_rate_d=0){
                          //mean counst per event perbx/4LN
    float mean_counts_bx_d=(mean_counts_d* LN4 *trigger_rate_d)/(3564);
    //bits per bin
    float bits_per_bin_d=ceil(log2(mean_counts_bx_d));
          
     //bit per histogram
     float bits_per_histo_d=NBX*bits_per_bin_d;
     cout<< DETECTOR_d
     <<setprecision(3)
     <<"&"<<trigger_rate_d/1000
     <<"&"<<mean_counts_d
     <<"&"<<mean_counts_bx_d
     <<"&"<< bits_per_bin_d
     <<"\\\\"<<endl;
  
    cout<<"\\hline"<<endl;     


}

void Data_Rates(){
     


/////////////////////////////////////
//TEPX Clusters                    // 
/////////////////////////////////////
  float TEPX_C=0;
  TFile FTEPX_C("/home/hedwin/2023D42PU200.root","r");
   TH2F * H1 = (TH2F*)FTEPX_C.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk 4"));
    TProfile* P=H1->ProfileX();
     TEPX_C += P->GetBinContent(1);//mean number of clusters 

float Ncluster_QuarterRing=TEPX_C/4;        
float Nhistogram_C  =  4*5*4*2  ;
/////////////////////////////////////
//TEPXD4R1 Clusters                // 
/////////////////////////////////////


     
        
float D4R1_Nhistogram_C  =  2*4;

/////////////////////////////////////
//TEPX 2x Coincidences             // 
/////////////////////////////////////

  float TEPX_2x=0;
   TH2F * H3 = (TH2F*)FTEPX_C.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk 4"));
    TProfile* J=H3->ProfileX();
     TEPX_2x += J->GetBinContent(1);//mean number of 2x Coincidences
  
  float N2x_QuarterRing=TEPX_2x/4;
  float Nhistogram_2x =  4*5*4*2  ;

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
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l  |c |c |c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<"&  Number of Histograms & Memory per histogram (Kb) & Data Transfer Rates (Mbps)\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  
  print_data_rates("TEPXD4R1 Clusters",D4R1_Nhistogram_C,Ncluster_QuarterRing,825e3);
  print_data_rates("TEPXD4R1 2x Coincidences",D4R1_Nhistogram_2x,N2x_QuarterRing,825e3);
  print_data_rates("TEPX Clusters",Nhistogram_C,Ncluster_QuarterRing,75e3);
  print_data_rates("TEPX 2x Coincidences",Nhistogram_2x,N2x_QuarterRing,75e3);
  print_data_rates("OT Layer 6 track stubs",Nhistogram_OT,Nstub_module,40e6);
  print_data_rates("DT Trigger Primitives",Nhistogram_DT,Ntp_chamber,40e6);
  print_data_rates("BMTF Track",NHisto_BMTF,Ntr_BMTF,40e6);
  print_data_rates("EMTF Tracks",NHisto_EMTF,Ntr_EMTF,40e6);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;
  
  
    cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l |c |c |c |c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<"&  Trigger rate (KHz) & Counts per event & Counts/bx/4LN&Bits/bin\\\\"<<endl;
  cout<<"\\hline"<<endl;
 data_used("TEPXD4R1 Clusters",D4R1_Nhistogram_C,Ncluster_QuarterRing,825e3);
  data_used("TEPXD4R1 2x Coincidences",D4R1_Nhistogram_2x,N2x_QuarterRing,825e3);
  data_used("TEPX Clusters",Nhistogram_C,Ncluster_QuarterRing,75e3);
  data_used("TEPX 2x Coincidences",Nhistogram_2x,N2x_QuarterRing,75e3);
  data_used("OT Layer 6 track stubs",Nhistogram_OT,Nstub_module,40e6);
  data_used("DT Trigger Primitives",Nhistogram_DT,Ntp_chamber,40e6);
  data_used("BMTF Track",NHisto_BMTF,Ntr_BMTF,40e6);
  data_used("EMTF Tracks",NHisto_EMTF,Ntr_EMTF,40e6);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;
  

}






