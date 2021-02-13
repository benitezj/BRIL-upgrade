
float NBX=3564; /// number bunches per orbit
float NORB = 11223; //Hz ,  = orbits per second  =  1/(3564 * 25 ns )
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float LS = 64*0.365; //s (Lumi section)
float VDM = 30; //s 
float NCOLLIDING = 2500;//number of colliding bunches
int second=1;//one second 

/*Counts for detectors*/

float TEPX_C=0;
float TEPXDR_C[8][5];
float TEPX_2x=0;
float TEPXDR_2x[8][5];
// OT layer 6
float OTL6=902; //Layer 6, N modules * stubs per module from CDR histogram
// DT's
float DTTP = 0.61;        // 17MHz is total DT primitive rate from extrapolation study
//https://indico.cern.ch/event/896820/contributions/3781668/attachments/2001707/3341677/DT_Meeting_2020_03_11.pdf
// BMTF/EMTF
float BMTF = 0.042;
float EMTF = 0.24;  





/*This function is used to extract the clusters per event for TEPX*/
void TEPX_Counts(){ 


///READ TEPX number of Clusters per event for pu=200

  TFile FTEPX("/home/hedwin/2023D42PU200.root","r");
  std::vector<string> disk={"-4","-3","-2","-1","1","2","3","4"};
  for(int d=0;d<8;d++){
   TH2F* H1 = (TH2F*)FTEPX.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ")+disk[d].c_str());
    TProfile* P=H1->ProfileX();
    for(int r=1;r<=5;r++){
      TEPXDR_C[d][r-1] = P->GetBinContent(r);
      TEPX_C += P->GetBinContent(r);

}
}

///READ TEPX number of real 2x coincidences  per event for pu=200

  for(long d=0;d<8;d++){
   TH2F* H2 = (TH2F*)FTEPX.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ")+disk[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2x[d][r-1] = P->GetBinContent(r);
      TEPX_2x += P->GetBinContent(r);
}
}

}











































/*This function is used to extract the 2x coincidences per event for TEPX*/
void TEPX_Coincidences( ){ 





}
