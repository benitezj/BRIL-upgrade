
float NBX=3564; /// number bunches per orbit
float NORB = 11223; //Hz ,  = orbits per second  =  1/(3564 * 25 ns )
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float LS = 64*0.365; //s (Lumi section)
float VDM = 30; //s 


void print_precision2(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     int trigger_rate = 0  //Hz
		     ){

  float totcount = count_per_event * trigger_rate; 


  cout<<DETECTOR
      //<<setprecision(5)
    //<<" & "<<trigger_rate/1000

      <<setprecision(3)

    ///Vdm
     // <<" & "<<100./sqrt(VDM*totcount/400)   // pu 0.5 VDM
//      <<" & "<<100./sqrt(100*VDM*totcount/400)   // pu 0.5 VDM

    //pu=200, 1bx
      <<"&"<<trigger_rate/1000<<"&"<<100./sqrt(LN4*totcount)        // pu 200  4LN
      //<<" & "<<100./sqrt(LS*totcount)  // pu 200  1LS

    //pu=200, 1 orbit
      //<<" & "<<100./sqrt(NBX*LN4*totcount)        // pu 200  4LN
      <<" & "<<100./sqrt(NBX*LS*totcount)  // pu 200  1LS


      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}


void print_precisionvdm(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     int trigger_rate = 0  //Hz
		     ){

  float totcount = count_per_event * trigger_rate; 


  cout<<DETECTOR
      //<<setprecision(5)
    //<<" & "<<trigger_rate/1000

      <<setprecision(2)

    ///Vdm
      <<"&"<<trigger_rate/1000<<"&"<<100./sqrt(LN4*totcount/400)<<" & "<<100./sqrt(VDM*totcount/400)   // pu 0.5 VDM
      <<" & "<<100./sqrt(100*VDM*totcount/400)   // pu 0.5 VDM

      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}


void stat_precision_2(){


///READ TEPX number of Clusters per event for pu=200
  float TEPX_C=0;
  float TEPXDR_C[8][5];
  TFile FTEPX_C("2023D42PU200.root","r");
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
  TFile FTEPX_2x("2023D42PU200.root","r");
  std::vector<string> disk_2x={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
   TH2F* H2 = (TH2F*)FTEPX_2x.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of real 2x Coincidences for Disk ")+disk_2x[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2x[d][r-1] = P->GetBinContent(r);
      TEPX_2x += P->GetBinContent(r);
}
}

///READ TEPX number of 3x coincidences per event for pu=200
  float TEPX_3x=0;
  float TEPXDR_3x[8][5];
  TFile FTEPX_3x("2023D42PU200.root","r");
  std::vector<string> disk_3x={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
   TH2F* H3 = (TH2F*)FTEPX_3x.Get(TString("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of real 3x Coincidences for Disk ")+disk_3x[d].c_str());
    TProfile* P=H3->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_3x[d][r-1] = P->GetBinContent(r);
      TEPX_3x += P->GetBinContent(r);
}
}
  /// OT layer 6
  float OTL6=1827*6000/(LN4*40e6); //Layer 6, N modules * stubs per module from CDR histogram
  
  
  /// DT's
  float DTTP = 17e6 / 40e6;        // 17MHz is total DT primitive rate from extrapolation study
  //https://indico.cern.ch/event/896820/contributions/3781668/attachments/2001707/3341677/DT_Meeting_2020_03_11.pdf


  /// BMTF/OMTF/EMTF
  float BMTF = 456 / NORB;
  float OMTF = 306 / NORB;
  float EMTF = 2633 / NORB;  


  /////////////////////////////////////
  ///create table per bx
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c | }"<<endl;
  cout<<"\\hline"<<endl;
  cout<<" &Triger rate (kHz)& 1 bx, 4LN    & 1 orbit, 1 LS \\\\"<<endl;
  cout<<"\\hline"<<endl;
  
  print_precision2("TEPXD4R1 Clusters",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);
  print_precision2("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][0]+TEPXDR_2x[7][0],800e3);
  print_precision2("TEPXD4R1 3x Coincidences ",TEPXDR_3x[0][0]+TEPXDR_3x[7][0],800e3);
  print_precision2("TEPX Clusters",TEPX_C,75e3);
  //print_precision2("TEPX 2x Coincidences",TEPX,500e3);
  print_precision2("TEPX 2x Coincidences",TEPX_2x,75e3);
  print_precision2("TEPX 3x Coincidences ",TEPX_3x,75e3);
  print_precision2("OT stubs Layer6",OTL6,40e6);
  print_precision2("DT Primitives",DTTP,40e6);
  print_precision2("BMTF",BMTF,40e6);
  //print_precision2("OMTF",OMTF,40e6);
  print_precision2("EMTF",EMTF,40e6);
  
  
  cout<<"\\end{tabular}}\\\\"<<endl;
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
  cout<<"  & Trigger rate (kHz) &1 bx, 4LN & 1 bx, 30 s     & 100 bx, 30 s\\\\"<<endl;
  cout<<"\\hline"<<endl;
  print_precisionvdm("TEPXD4R1 3x Coincidences ",TEPXDR_3x[0][0]+TEPXDR_3x[7][0],800e3);
  print_precisionvdm("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][0]+TEPXDR_2x[7][0],800e3);
  print_precisionvdm("TEPXD4R1 Clusters",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);  
  print_precisionvdm("TEPX Clusters",TEPX_C,75e3);
  //print_precision2("TEPX 2x Coincidences",TEPX,500e3);
  print_precisionvdm("TEPX 2x Coincidences",TEPX_2x,75e3);
  print_precisionvdm("TEPX 3x Coincidences ",TEPX_3x,75e3);
  print_precisionvdm("OT stubs Layer6",OTL6,40e6);
  print_precisionvdm("DT Primitives",DTTP,40e6);
  print_precisionvdm("BMTF",BMTF,40e6);
  //print_precision2("OMTF",OMTF,40e6);
  print_precisionvdm("EMTF",EMTF,40e6);


  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;

  
}


