#include "stat_precision_globals.h"




void vdm_stat_precision_function(TString DETECTOR = "TEPX", 
                                 float count_per_event_vdm=0,
                                 float trigger_rate_vdm=0 ){

/* defining variables*/ 
float x_axis=0;/*values for the x axis*/
float Gaus_dist=0;/*Values of the Gaussian distribution*/
int center=0;/*center of the normal distribution*/
float st_div= 0.1322;/*standard deviation*/
float x_lim=0.6;/*X axis limits*/
float mean_counts=(count_per_event_vdm/400)*trigger_rate_vdm*VDM/NBX;/*Mean counts/30s/bx*/

/*Defining the Gaussian distribution*/
TF1  G("G","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -x_lim,x_lim );
G.FixParameter(0,mean_counts);
G.FixParameter(1,center);
G.FixParameter(2,st_div);


/*Histogram fill */
TH1F * H=new TH1F("Van der Meer Scan",DETECTOR,25, -x_lim, x_lim); 
    
    for (int i=0;i<25;i++){
        x_axis=H->GetXaxis()->GetBinCenter(i+1);
        Gaus_dist=G.Eval(x_axis);
        H->SetBinContent(i+1,Gaus_dist);
        H->SetBinError(i+1,sqrt(Gaus_dist));
        }
        
/*Fitting normal distribution to Histogram*/
TF1 * F=new TF1("F","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -x_lim, x_lim );
F->SetParLimits(0,0, 1000000);
F->FixParameter(1,0);
F->SetParLimits(2,0, 2);
F->SetLineColor(8);
H->Fit(F,"Q","");

/*extracting parameters and parameter errors*/
float Norm = F->GetParameter(0);
float Norm_Error = F->GetParError(0);
float CapSigma = F->GetParameter(2);
float CapSigma_Error = F->GetParError(2);
float sigma_vis=sqrt(pow(Norm_Error/Norm,2)+(2*pow(CapSigma_Error/CapSigma,2)));

/*plot histogram*/
TCanvas *c1=new TCanvas("c1","",1);
int Max=H->GetBinContent( H->GetMaximumBin());
H->GetXaxis()->SetTitle("#Delta x(mm)");
H->GetXaxis()->CenterTitle(true);
H->GetXaxis()->SetRangeUser(-1.2*x_lim, 1.2*x_lim);
H->GetYaxis()->SetTitle("counts/30s/bx");
H->GetYaxis()->CenterTitle(true);
H->GetYaxis()->SetTitleOffset(1);
gPad->SetLogy(1);
gStyle->SetOptStat(0);
H->Draw();

/*Print parameters on plot*/
TLatex latex;
latex.SetTextFont(42);
latex.SetTextSize(0.04);
latex.SetTextAlign(13);  
latex.DrawLatex(-.1,.005*Max,TString::Format("a= %g", Norm));
latex.DrawLatex(-.1,.003*Max,TString::Format("#deltaa= %g", Norm_Error));
latex.DrawLatex(-.1,.0018*Max,TString::Format("#Sigma= %g", CapSigma));
latex.DrawLatex(-.1,.001*Max,TString::Format("#delta#Sigma=%g", CapSigma_Error));
latex.DrawLatex(-.1,.0006*Max,TString::Format("#delta#sigma_{vis}/#sigma_{vis}= %g",  sigma_vis));

/*Legends*/
TLegend * legend = new TLegend(0.75,0.7,0.9,.9);
legend->AddEntry(H,"Toy Data","le");
legend->AddEntry(F," Fit result","l");
legend->SetMargin(0.2);
legend->SetTextFont(42);
legend->SetTextSize(0.04);
legend->Draw();

/*print a gif file*/
c1->Print("/home/hedwin/plots/Stat_Precision_VdM_"+ DETECTOR +".png");

  cout<<DETECTOR
      
      //amplitude and amplitude uncertainty
      <<"&"<<Norm<<"&"<<Norm_Error

   <<fixed<<setprecision(4)
   
      //Beam Width 
      <<"&"<<CapSigma

      //Beam Width and sigma visual uncertainty
      <<"&"<<CapSigma_Error
      <<"&"<<sigma_vis*100
      <<"\\\\"<<endl;
  cout<<"\\hline"<<endl;
}



void vdm_stat_precision(){

  gErrorIgnoreLevel = kFatal;
  
  /*call TEPX variables*/
  TEPX_Counts();

  /////////////////////////////////////
  ///create table and plots for toy Vdm
  /////////////////////////////////////
  cout<<"\\begin{center}"<<endl;
  cout<< "\\scalebox{.8}{"<<endl;
  cout<<"\\begin{tabular}{|l | c | c | c |c|c|}"<<endl;
  cout<<"\\hline"<<endl;
  cout<<"Detector & a &$\\Delta a$&$ \\Sigma$&$ \\delta\\Sigma$&$\\delta\\sigma_{vis}/\\sigma_{vis}$\\\\"<<endl;
  cout<<"\\hline"<<endl;  
  vdm_stat_precision_function("TEPXD4R1 Clusters",TEPXDR_C[0][0]+TEPXDR_C[7][0],800e3);
  vdm_stat_precision_function("TEPXD4R1 2x Coincidences",TEPXDR_2x[0][0]+TEPXDR_2x[7][0],800e3);
  vdm_stat_precision_function("TEPX Clusters",TEPX_C,500e3);
  vdm_stat_precision_function("TEPX 2x Coincidences",TEPX_2x,500e3);  
  vdm_stat_precision_function("OT Layer 6",OTL6,40e6);
  vdm_stat_precision_function("DT",DTTP,40e6);
  vdm_stat_precision_function("BMTF",BMTF,40e6);
  vdm_stat_precision_function("EMTF",EMTF,40e6);
  cout<<"\\end{tabular}}"<<endl;
  cout<< "\\end{center}"<<endl;


  
  
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
  cout<< "\\end{center}"<<endl;
}

