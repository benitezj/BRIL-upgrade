float NBX=3564;
float LN4 = 4*0.365; //s
float LS = 64*0.365; //s
float VDM = 30; //s 


void print_precision(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     float trigger_rate = 0  //Hz
		     ){

  float totcount = count_per_event * trigger_rate  / NBX; 


  cout<<DETECTOR
      <<setprecision(5)
      <<" & "<<trigger_rate/1000
      <<setprecision(2)
    //<<" "<<100./sqrt(VDM*totcount/400/10)   // pu 0.5 VDM tail
      <<" & "<<100./sqrt(VDM*totcount/400)   // pu 0.5 VDM
      <<" & "<<100./sqrt(LN4*totcount)        // pu 200  4LN
      <<" & "<<100./sqrt(LS*totcount)  // pu 200  1LS
      <<" & "<<100./sqrt(50*LS*totcount)  // pu 200  50LS
      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}




void stat_precision(){

  ///READ TEPX number of clusters per event for pu=200
  float TEPX=0;
  float TEPXDR[8][5];
  TFile FTEPX("2023D42PU200.root","r");
  std::vector<string> disk={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
    TH2F* H2 = (TH2F*)FTEPX.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ")+disk[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR[d][r-1] = P->GetBinContent(r);
      TEPX += P->GetBinContent(r);
    }
  }


  /// OT layer 6
  float OTL6=1827*6000/(LN4*40e6); //Layer 6, N modules * stubs per module from CDR histogram
  
  
  /// DT's
  float DTTP = 17e6 / 40e6;        // 17MHz is total DT primitive rate from extrapolation study
  float DTTrk = 20e3*5*12 / 40e6;  // 20kHz is total DT primitive rate for MB3 , approximates track rate
  //https://indico.cern.ch/event/896820/contributions/3781668/attachments/2001707/3341677/DT_Meeting_2020_03_11.pdf
  


  /////////////////////////////////////
  ///create table per bx
  /////////////////////////////////////
  cout<<"\\begin{tabular}{l | c | c | c | c | c}"<<endl;
  cout<<"\\hline\\hline"<<endl;
  cout<<"  &  Trigger  & vdM  (pu=0.5)    & pu = 200  & pu = 200  & pu = 200\\\\"<<endl;
  cout<<"  &  (kHz)    & 30s              &  4 LN     & 1 LS      & 50 LS\\\\"<<endl;
  cout<<"\\hline"<<endl;
  
  print_precision("TEPX clusters",TEPX,75e3);
  print_precision("TEPX clusters",TEPX,500e3);
  print_precision("TEPXD4R1 clusters",TEPXDR[0][0]+TEPXDR[7][0],800e3);
  print_precision("OT Layer6 stubs",OTL6,40e6);
  print_precision("DT Primitives",DTTP,40e6);
  print_precision("BMTF",DTTrk,40e6);


  cout<<"\\end{tabular}"<<endl;
}
