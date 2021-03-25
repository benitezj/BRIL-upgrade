#include <string>
#include <sstream>
#include <cmath>
#include <iostream>



float NBX=3564; /// number bunches per orbit
float NORB = 11246; //Hz ,  = orbits per second  =  1/(3564 * 25 ns )
float LN4 = 4*0.365; //s (4 Lumi Nibles)
float LS = 64*0.365; //s (Lumi section)
float VDM = 30; //s 
float P_count=1.15*pow(10,11);
//float Norbit_NB4= 16417.7;// number of orbits per LN4
float NCOLLIDING = 2500;//number of colliding bunches
int second=1;//one second 

/*initiate output file*/
ofstream myfile;  

/*Counts for detectors*/
float TEPX_C=0;
float TEPXDR_C[2][4][5];
float TEPX_2x=0;
float TEPXDR_2x[4][5];
// OT layer 6
float OTL6=1078; //Layer 6, N modules * stubs per module from CDR histogram
// DT's
float DTTP = 0.61;        // 17MHz is total DT primitive rate from extrapolation study
//https://indico.cern.ch/event/896820/contributions/3781668/attachments/2001707/3341677/DT_Meeting_2020_03_11.pdf
// BMTF/EMTF
float BMTF = 0.042;
float EMTF = 0.24;  

/*time varianle*/
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
      TEPX_C += P->GetBinContent(r);
   }
}
}



///READ TEPX number of real 2x coincidences  per event for pu=200

  for(long d=0;d<4;d++){
   TH2F* H2 = (TH2F*)FTEPX.Get(TString("BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_side2_Disk")+disk[d].c_str());
    TProfile* P=H2->ProfileX();
    for(long r=1;r<=5;r++){
      TEPXDR_2x[d][r-1] = P->GetBinContent(r);
      TEPX_2x += P->GetBinContent(r);
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






















/*  
  
   /////////////////////////////////////
  ///create table and plots for toy Vdm for all TEPX Disks for clsuters 
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c |c|c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<" & a &$\\Delta a$&$ \\Sigma$&$ \\delta\\Sigma$&$\\delta\\sigma_{vis}/\\sigma_{vis}$\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  vdm_stat_precision_function("TEPXD4R1 Clusters",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);
  vdm_stat_precision_function("TEPXD4R2 Clusters",TEPXDR_C[0][1]+TEPXDR_C[7][1],800e3);
  vdm_stat_precision_function("TEPXD4R3 Clusters",TEPXDR_C[0][2]+TEPXDR_C[7][2],800e3);
  vdm_stat_precision_function("TEPXD4R4 Clusters",TEPXDR_C[0][3]+TEPXDR_C[7][3],800e3);
  vdm_stat_precision_function("TEPXD4R5 Clusters",TEPXDR_C[0][4]+TEPXDR_C[7][4],800e3);
  vdm_stat_precision_function("TEPXD3R1 Clusters",TEPXDR_C[1][0]+TEPXDR_C[6][0],800e3);
  vdm_stat_precision_function("TEPXD3R2 Clusters",TEPXDR_C[1][1]+TEPXDR_C[6][1],800e3);
  vdm_stat_precision_function("TEPXD3R3 Clusters",TEPXDR_C[1][2]+TEPXDR_C[6][2],800e3);
  vdm_stat_precision_function("TEPXD3R4 Clusters",TEPXDR_C[1][3]+TEPXDR_C[6][3],800e3);
  vdm_stat_precision_function("TEPXD3R5 Clusters",TEPXDR_C[1][4]+TEPXDR_C[6][4],800e3);
  vdm_stat_precision_function("TEPXD2R1 Clusters",TEPXDR_C[2][0]+TEPXDR_C[5][0],800e3);
  vdm_stat_precision_function("TEPXD2R2 Clusters",TEPXDR_C[2][1]+TEPXDR_C[5][1],800e3);
  vdm_stat_precision_function("TEPXD2R3 Clusters",TEPXDR_C[2][2]+TEPXDR_C[5][2],800e3);
  vdm_stat_precision_function("TEPXD2R4 Clusters",TEPXDR_C[2][3]+TEPXDR_C[5][3],800e3);
  vdm_stat_precision_function("TEPXD2R5 Clusters",TEPXDR_C[2][4]+TEPXDR_C[5][4],800e3);
  vdm_stat_precision_function("TEPXD1R1 Clusters",TEPXDR_C[3][0]+TEPXDR_C[4][0],800e3);
  vdm_stat_precision_function("TEPXD1R2 Clusters",TEPXDR_C[3][1]+TEPXDR_C[4][1],800e3);
  vdm_stat_precision_function("TEPXD1R3 Clusters",TEPXDR_C[3][2]+TEPXDR_C[4][2],800e3);
  vdm_stat_precision_function("TEPXD1R4 Clusters",TEPXDR_C[3][3]+TEPXDR_C[4][3],800e3);
  vdm_stat_precision_function("TEPXD1R5 Clusters",TEPXDR_C[3][4]+TEPXDR_C[4][4],800e3);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;

     /////////////////////////////////////
  ///create table and plots for toy Vdm for all TEPX Disks for 2x Coincidences 
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c |c|c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<" & a &$\\Delta a$&$ \\Sigma$&$ \\delta\\Sigma$&$\\delta\\sigma_{vis}/\\sigma_{vis}$\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  vdm_stat_precision_function("TEPXD4R1 2x Coincidences",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);
  vdm_stat_precision_function("TEPXD4R2 2x Coincidences",TEPXDR_C[0][1]+TEPXDR_C[7][1],800e3);
  vdm_stat_precision_function("TEPXD4R3 2x Coincidences",TEPXDR_C[0][2]+TEPXDR_C[7][2],800e3);
  vdm_stat_precision_function("TEPXD4R4 2x Coincidences",TEPXDR_C[0][3]+TEPXDR_C[7][3],800e3);
  vdm_stat_precision_function("TEPXD4R5 2x Coincidences",TEPXDR_C[0][4]+TEPXDR_C[7][4],800e3);
  vdm_stat_precision_function("TEPXD3R1 2x Coincidences",TEPXDR_C[1][0]+TEPXDR_C[6][0],800e3);
  vdm_stat_precision_function("TEPXD3R2 2x Coincidences",TEPXDR_C[1][1]+TEPXDR_C[6][1],800e3);
  vdm_stat_precision_function("TEPXD3R3 2x Coincidences",TEPXDR_C[1][2]+TEPXDR_C[6][2],800e3);
  vdm_stat_precision_function("TEPXD3R4 2x Coincidences",TEPXDR_C[1][3]+TEPXDR_C[6][3],800e3);
  vdm_stat_precision_function("TEPXD3R5 2x Coincidences",TEPXDR_C[1][4]+TEPXDR_C[6][4],800e3);
  vdm_stat_precision_function("TEPXD2R1 2x Coincidences",TEPXDR_C[2][0]+TEPXDR_C[5][0],800e3);
  vdm_stat_precision_function("TEPXD2R2 2x Coincidences",TEPXDR_C[2][1]+TEPXDR_C[5][1],800e3);
  vdm_stat_precision_function("TEPXD2R3 2x Coincidences",TEPXDR_C[2][2]+TEPXDR_C[5][2],800e3);
  vdm_stat_precision_function("TEPXD2R4 2x Coincidences",TEPXDR_C[2][3]+TEPXDR_C[5][3],800e3);
  vdm_stat_precision_function("TEPXD2R5 2x Coincidences",TEPXDR_C[2][4]+TEPXDR_C[5][4],800e3);
  vdm_stat_precision_function("TEPXD1R1 2x Coincidences",TEPXDR_C[3][0]+TEPXDR_C[4][0],800e3);
  vdm_stat_precision_function("TEPXD1R2 2x Coincidences",TEPXDR_C[3][1]+TEPXDR_C[4][1],800e3);
  vdm_stat_precision_function("TEPXD1R3 2x Coincidences",TEPXDR_C[3][2]+TEPXDR_C[4][2],800e3);
  vdm_stat_precision_function("TEPXD1R4 2x Coincidences",TEPXDR_C[3][3]+TEPXDR_C[4][3],800e3);
  vdm_stat_precision_function("TEPXD1R5 2x Coincidences",TEPXDR_C[3][4]+TEPXDR_C[4][4],800e3);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;*/










































