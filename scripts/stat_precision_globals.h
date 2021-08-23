#include <string>
#include <sstream>
#include <cmath>
#include <iostream>


float total_pp_crossection_14= 78.4*pow(10,-27);// for 14 Tev
float total_pp_crossection_13= 77.6*pow(10,-27);// for 13 Tev
float NBX=3564; /// number bunches per orbit
float NBX_TEPX_VDM=150;
float NORB = 11246; //Hz ,  = orbits per second  =  1/(3564 * 25 ns )
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float LS = 64*0.365; //s (Lumi section)
float VDM = 30; //s 
float P_count=1.15*pow(10,11);
//float Norbit_NB4= 16417.7;// number of orbits per LN4
float NCOLLIDING = 2748;//number of colliding bunches
int second=1;//one second 

/*initiate output file*/
ofstream myfile;  

/*Counts for detectors*/
float TEPX_C=0;
float TEPXDR_C[2][4][5];
float TEPX_2x=0;
float TEPXDR_2x[2][4][5];
// OT layer 6
float OTL6=1078; //Layer 6, N modules * stubs per module from CDR histogram
// DT's
float DTTP = 0.61;        // 17MHz is total DT primitive rate from extrapolation study
//https://indico.cern.ch/event/896820/contributions/3781668/attachments/2001707/3341677/DT_Meeting_2020_03_11.pdf
// BMTF/EMTF
float BMTF = 0.042;
float EMTF = 0.24;  

/*time variable*/
time_t mytime= time(NULL);





/*This function is used to extract the clusters per event for TEPX*/
void TEPX_Counts(){ 



///READ TEPX number of Clusters per event for pu=200

  TFile FTEPX("2023D42PU200.root","r");
  std::vector<string> disk={"1","2","3","4"};
  std::vector<string> side={"1","2"};
  for (int s=0;s<2;s++ ){
  for(int d=0;d<4;d++){
   TH2F* H1 = (TH2F*)FTEPX.Get(TString("BRIL_IT_Analysis/TEPX/Clusters/Numberofclusters_side")+side[s].c_str()+TString("_Disk") +disk[d].c_str());
       TProfile* P=H1->ProfileX();
    for(int r=1;r<=5;r++){
      TEPXDR_C[s][d][r-1] = P->GetBinContent(r);
      if ( d==3 && r== 1){
          continue;
       }
      TEPX_C += P->GetBinContent(r);
}
}
}

///READ TEPX number of real 2x coincidences  per event for pu=200
  for (int s=0;s<2;s++ ){
  for(long d=0;d<4;d++){
   TH2F* H2 = (TH2F*)FTEPX.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_Inphi_side")+side[s].c_str()+TString("_Disk")+disk[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2x[s][d][r-1] = P->GetBinContent(r);
      if ( d==3 && r== 1){
          continue;
       }      
      TEPX_2x += P->GetBinContent(r);
}
}
}

}

/*number precision function*/


std::string toPrecision(double num, int n) {
    https://stackoverflow.com/questions/202302/rounding-to-an-arbitrary-number-of-significant-digits

    if(num == 0) {
      return "0";
    }

    double d = std::ceil(std::log10(num < 0 ? -num : num));
    int power = n - (int)d;
    double magnitude = std::pow(10., power);
    long shifted = ::round(num*magnitude);

    std::ostringstream oss;
    oss << shifted/magnitude;
    return oss.str();
}





























































