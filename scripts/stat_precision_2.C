
float NBX=3564; /// number bunches per orbit
float NORB = 11223; //Hz ,  = orbits per second  =  1/(3564 * 25 ns )
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float LS = 64*0.365; //s (Lumi section)
float VDM = 30; //s 
float NCOLLIDING = 2500;//number of colliding bunches
/// OT layer 6
float OTL6=902; //Layer 6, N modules * stubs per module from CDR histogram
/// DT's
float DTTP = 0.61;        // 17MHz is total DT primitive rate from extrapolation study
//https://indico.cern.ch/event/896820/contributions/3781668/attachments/2001707/3341677/DT_Meeting_2020_03_11.pdf
/// BMTF/EMTF
float BMTF = 0.042;
float EMTF = 0.24;  

void print_precision2(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     int trigger_rate = 0  //Hz
		     ){

  cout<<DETECTOR
      <<setprecision(3)


    //pu=200, 1bx, 4LN
      <<"&"<<trigger_rate/1000<<"&"<<100/sqrt(count_per_event*trigger_rate*LN4/NBX)
     
   // pu+200, 2500 bx, 4LN
      <<"&"<<100/sqrt(NCOLLIDING*count_per_event*trigger_rate*LN4/NBX)

    //pu=200,2500 bx, 1LS

      <<"&"<<100/sqrt(NCOLLIDING*count_per_event*trigger_rate*LS/NBX)


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

    ///Vdm 1 bx, 4 LN
      <<"&"<<trigger_rate_vdm/1000<<"&"<< 100/sqrt((count_per_event_vdm/400)*trigger_rate_vdm*LN4/NBX)<<"&"
      //1 bx, 30s
      <<100/sqrt((count_per_event_vdm/400)*trigger_rate_vdm*VDM/NBX)  // pu 0.5 VDM
      //Vdm 100 bx, 30s
      <<" & "<<100/sqrt(100*(count_per_event_vdm/400)*trigger_rate_vdm*VDM/NBX)// pu 0.5 VDM

      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}


void stat_precision_2(){


///READ TEPX number of Clusters per event for pu=200
  float TEPX_C=0;
  float TEPXDR_C[8][5];
  TFile FTEPX_C("/home/hedwin/2023D42PU200.root","r");
  std::vector<string> disk_C={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
   TH2F* H1 = (TH2F*)FTEPX_C.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ")+disk_C[d].c_str());
    TProfile* P=H1->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_C[d][r-1] = P->GetBinContent(r);
      TEPX_C += P->GetBinContent(r);
}
}

///READ TEPX number of real 2x coincidences  per event for pu=200
  float TEPX_2x=0;
  float TEPXDR_2x[8][5];
  TFile FTEPX_2x("/home/hedwin/2023D42PU200.root","r");
  std::vector<string> disk_2x={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
   TH2F* H2 = (TH2F*)FTEPX_2x.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ")+disk_2x[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2x[d][r-1] = P->GetBinContent(r);
      TEPX_2x += P->GetBinContent(r);
}
}




  /////////////////////////////////////
  ///create table per bx
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c |c |}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<" & Readout Rate (kHz)& 1 bx, 4LN &2500 bx, 4LN   & 2500 bx, 1 LS \\\\"<<endl;
  cout<<"\\hline"<<endl;
  print_precision2("TEPXD4R1 Clusters",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);
  print_precision2("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][0]+TEPXDR_2x[7][0],800e3);
  print_precision2("TEPX Clusters",TEPX_C,75e3);
  print_precision2("TEPX 2x Coincidences",TEPX_2x,75e3);
  print_precision2("OT Layer 6 track stubs",OTL6,40e6);
  print_precision2("DT Trigger Primitives",DTTP,40e6);
  print_precision2("BMTF",BMTF,40e6);
  print_precision2("EMTF",EMTF,40e6);
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
  cout<<"  & Readout Rate (kHz) &1 bx, 4LN & 1 bx, 30s & 100 bx, 30s\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  print_precisionvdm("TEPXD4R1 Clusters",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);  
  print_precisionvdm("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][0]+TEPXDR_2x[7][0],800e3);
  print_precisionvdm("TEPX Clusters",TEPX_C,500e3);
  print_precisionvdm("TEPX 2x Coincidences",TEPX_2x,500e3);
  print_precisionvdm("OT Layer 6 track stubs",OTL6,40e6);
  print_precisionvdm("DT Trigger Primitives",DTTP,40e6);
  print_precisionvdm("BMTF",BMTF,40e6);
  print_precisionvdm("EMTF",EMTF,40e6);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;

    cout<<TEPX_2x<<endl;
  cout<< TEPXDR_C[0][0]+TEPXDR_C[7][0] <<endl;

}


