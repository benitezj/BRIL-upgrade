float NBX=3564; /// number bunches per orbit
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float Norbit_NB4= 16417.7;// number of orbits per LN4



void print_data_rates(TString DETECTOR= "TEPX",
                      float number_of_histo=0, 
                      float mean_counts_bx=0
		     ){
		

    //bits per bin
    float bits_per_bin=ceil(log2(mean_counts_bx));
          
     //bit per histogram
     float bits_per_histo=NBX*bits_per_bin;
     cout<< DETECTOR
     <<setprecision(3)
     //Number of Histograms
     <<"&"<<number_of_histo
     
     <<"&"<<bits_per_bin
     
     // Bits per Histogram
     <<"&"<< (bits_per_histo)/1000
     
     //Data Transfer Rates
     <<"&"<< (number_of_histo*bits_per_histo)/(LN4*1000000)
     <<"\\\\"<<endl;
  
    cout<<"\\hline"<<endl;     

}


void Data_Rates(){
     


/////////////////////////////////////
//TEPX Clusters                    // 
/////////////////////////////////////
  float TEPX_C=0;
  TFile FTEPX_C("2023D42PU200.root","r");
   TH2F * H1 = (TH2F*)FTEPX_C.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk 4"));
    TProfile* P=H1->ProfileX();
     TEPX_C += P->GetBinContent(1);

float Ncluster_QuarterRing=TEPX_C/4;
float Ncluster_QuarterRing_bx_NB4  = (Ncluster_QuarterRing * LN4*(75e3))/2500;  // number of clusters per quarter ring per bx per NB4 integration period          
float Nhistogram_C  =  4*5*4*2  ;

/////////////////////////////////////
//TEPX 2x Coincidences             // 
/////////////////////////////////////

  float TEPX_2x=0;
   TH2F * H2 = (TH2F*)FTEPX_C.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk 4"));
    TProfile* J=H2->ProfileX();
     TEPX_2x += J->GetBinContent(1);
  
  float N2x_QuarterRing=TEPX_2x/4;
  float N2x_QuarterRing_bx_NB4  = (N2x_QuarterRing * LN4*(75e3))/2500 ;  // number of clusters per quarter ring per bx per NB4 integration period          
  float Nhistogram_2x =  4*5*4*2  ;


/////////////////////////////////////
//OT                               // 
/////////////////////////////////////

float Nladder= 78;
float Nmodule_ladder = 12; //number of modules per ladder 
float Nmodule =  Nmodule_ladder * Nladder * 2 ;  //total number of modules
float Nstub_module  = 0.8; //  number of stubs per module per event 
float Nstubs_bx_NB4= Nstub_module * Nmodule_ladder  * Norbit_NB4;
float Nhistogram_OT = 156;



/////////////////////////////////////
//DT                               // 
/////////////////////////////////////

float Ntp_chamber = 0.0125;  //trigger primitives per chamber per event for pu=200
float Ntp_bx_NB4  =  Ntp_chamber * Norbit_NB4;  
float Nhistogram_DT = 250;

     
  /////////////////////////////////////
  ///create table 
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l  |c |c |c|c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<"&  Number of Histograms&Bits/bin & Memory per histogram (Kb) & Data Transfer Rates (Mbps)\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  print_data_rates("TEPX Clusters",Nhistogram_C,Ncluster_QuarterRing_bx_NB4);
  print_data_rates("TEPX 2x Coincidences",Nhistogram_2x,N2x_QuarterRing_bx_NB4);
  print_data_rates("OT Layer 6 track stubs",Nhistogram_OT,Nstubs_bx_NB4);
  print_data_rates("DT Trigger Primitives",Nhistogram_DT,Ntp_bx_NB4);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;
  
  

}






