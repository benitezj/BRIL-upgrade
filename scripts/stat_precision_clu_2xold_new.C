float NBX=3564; /// number bunches per orbit
float NORB = 11223; //Hz ,  = orbits per second  =  1/(3564 * 25 ns )
float LN4 = 4*0.365; //s
float LS = 64*0.365; //s
float VDM = 30; //s 


void print_precision(TString DETECTOR = "TEPX",
		     float count_per_event=0,
		     float trigger_rate = 0  //Hz
		     ){

  float totcount = count_per_event * trigger_rate; 


  cout<<DETECTOR
      <<setprecision(5)
    //<<" & "<<trigger_rate/1000

      <<setprecision(2)

    ///Vdm
      <<" & "<<100./sqrt(VDM*totcount/400)   // pu 0.5 VDM
      <<" & "<<100./sqrt(100*VDM*totcount/400)   // pu 0.5 VDM

    //pu=200, 1bx
      <<" & "<<100./sqrt(LN4*totcount)        // pu 200  4LN
      <<" & "<<100./sqrt(LS*totcount)  // pu 200  1LS

    //pu=200, 1 orbit
      <<" & "<<100./sqrt(NBX*LN4*totcount)        // pu 200  4LN
      <<" & "<<100./sqrt(NBX*LS*totcount)  // pu 200  1LS


      <<"\\\\"<<endl;
  
  cout<<"\\hline"<<endl;
}




void stat_precision_clu_2xold_new(){


///READ TEPX number of Clusters per event for pu=200
  float TEPX_clu=0;
  float TEPXDR_clu[8][5];
  TFile FTEPX_clu("/home/ashish/Desktop/TEPX_0.1/samples_17Feb2020/2023D42PU200.root","r");
  std::vector<string> disk_clu={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
    TH2F* H1 = (TH2F*)FTEPX_clu.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ")+disk_clu[d].c_str());
    TProfile* P=H1->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_clu[d][r-1] = P->GetBinContent(r);
      TEPX_clu += P->GetBinContent(r);
}
}


  ///READ TEPX number of 2x Coincidences per event for pu=200
  float TEPX_2x=0;
  float TEPXDR_2x[8][5];
  TFile FTEPX_2x("/home/ashish/Desktop/TEPX_0.1/samples_17Feb2020/2023D42PU200.root","r");
  std::vector<string> disk_2x={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
    TH2F* H2 = (TH2F*)FTEPX_2x.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ")+disk_2x[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2x[d][r-1] = P->GetBinContent(r);
      TEPX_2x += P->GetBinContent(r);
}
}


///READ TEPX number of new 2x Coincidences per event for pu=200
  float TEPX_2xnew=0;
  float TEPXDR_2xnew[8][5];
  TFile FTEPX_2xnew("/home/ashish/Desktop/TEPX_0.02/samples_17Feb2020/2023D42PU200.root","r");
  std::vector<string> disk_2xnew={"-4","-3","-2","-1","1","2","3","4"};
  for(long d=0;d<8;d++){
    TH2F* H3 = (TH2F*)FTEPX_2xnew.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ")+disk_2xnew[d].c_str());
    TProfile* P=H3->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2xnew[d][r-1] = P->GetBinContent(r);
      TEPX_2xnew += P->GetBinContent(r);
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
  cout<<"\\begin{tabular}{l | c | c | c | c | c | c |}"<<endl;
  cout<<"\\hline\\hline"<<endl;
  cout<<"  & \\multicolumn{2}{c|}{ vdM  (pu=0.5) }    &  \\multicolumn{4}{c|}{ Physics (pu = 200)} \\\\"<<endl;
  cout<<"  & 1 bx, 30 s     & 100 bx, 30 s        &  1 bx, 4 LN     & 1 bx, 1 LS      & 1 orbit, 4 LN & 1 orbit, 1 LS \\\\"<<endl;
  cout<<"\\hline"<<endl;
  
  print_precision("TEPX Clusters",TEPX_clu,75e3);
  //print_precision("TEPX 2x Coincidences",TEPX,500e3);
  print_precision("TEPXD4R1 Clusters",TEPXDR_clu[0][0]+TEPXDR_clu[7][0],800e3);
  print_precision("TEPX 2x Coincidences",TEPX_2x,75e3);
  print_precision("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][0]+TEPXDR_2x[7][0],800e3);
  print_precision("TEPX new 2x Coincidences",TEPX_2xnew,75e3);
  print_precision("TEPXD4R1 new 2x Coincidences",TEPXDR_2xnew[0][0]+TEPXDR_2xnew[7][0],800e3);
  print_precision("OT Layer6 stubs",OTL6,40e6);
  print_precision("DT Primitives",DTTP,40e6);
  print_precision("BMTF",BMTF,40e6);
  print_precision("OMTF",OMTF,40e6);
  print_precision("EMTF",EMTF,40e6);
 

  cout<<"\\end{tabular}"<<endl;




}
