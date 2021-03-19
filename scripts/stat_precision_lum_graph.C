#include "stat_precision_globals.h"
float lum_unc[8][21];
float sigma_vis[8];
float PU[21]={1,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
float PU_L[21];
float stat_unc[8][21];





void stat_precision_lum_function(){

    TEPX_Counts();
    float count_per_events[8]={TEPXDR_C[0][0][0]+TEPXDR_C[0][3][0],2*TEPXDR_2x[3][0],TEPX_C,2*TEPX_2x,OTL6,DTTP,BMTF,EMTF};
    float trigger_rates[8]={825e3,825e3,75e3,75e3,40e6,40e6,40e6,40e6};

    // float stat_unc_pup5[8]={2.1/100,4.92/100,0.709/100,2.02/100,0.629/100,24.2/100,92.1/100,38.5/100};



	/* defining variables*/ 
	float x_axis=0;/*values for the x axis*/
	float Gaus_dist=0;/*Values of the Gaussian distribution*/
	int center=0;/*center of the normal distribution*/
	float st_div= 0.120;/*standard deviation*/
	float x_lim=0.6;/*X axis limits*/
	float mean_counts[8];
	TF1  G("G","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -x_lim,x_lim );
	TH1F * H=new TH1F("Van der Meer Scan","",25, -x_lim, x_lim); 
	TF1 * F=new TF1("F","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -x_lim, x_lim );





	for(int m=0;m<8;m++){

	 mean_counts[m]=(count_per_events[m]/400)*trigger_rates[m]*VDM/NBX;/*Mean counts/30s/bx*/


	/*Defining the Gaussian distribution*/
	G.FixParameter(0,mean_counts[m]);
	G.FixParameter(1,center);
	G.FixParameter(2,st_div);


	/*Histogram fill */

		 
		 for (int i=0;i<25;i++){
		     x_axis=H->GetXaxis()->GetBinCenter(i+1);
		     Gaus_dist=G.Eval(x_axis);
		     H->SetBinContent(i+1,Gaus_dist);
		     H->SetBinError(i+1,sqrt(Gaus_dist));
		     }
		     
	/*Fitting normal distribution to Histogram*/

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
	/*Extracting covariance and correlation matrices */
	TFitResultPtr r = H->Fit(F,"SQ");
	TMatrixD cor = r->GetCorrelationMatrix();
	TMatrixD cov = r->GetCovarianceMatrix();
   sigma_vis[m]=sqrt((pow(1/Norm,2)*cov[0][0])+2*(pow(1/CapSigma,2)*cov[2][2])+(4/(Norm*CapSigma))*cov[0][2]);


	 for(int n=0;n<21;n++){
		        PU_L[n]=200/PU[n];
		        stat_unc[m][n]=1/sqrt((count_per_events[m]/PU_L[n])*trigger_rates[m]*second/NBX);
		         lum_unc[m][n]=100*sqrt(pow(sigma_vis[m],2)+(pow(stat_unc[m][n],2)));

	}



 }

}


void stat_precision_lum_graph(){





int n=21;

stat_precision_lum_function();

TH1F * H1=new TH1F("","",1, 0.01, 200.1); 
TCanvas *c1=new TCanvas("c1","");

TMultiGraph *MG = new TMultiGraph();



   TGraph *TEPXDRC = new TGraph(n,PU,lum_unc[0]);
   TEPXDRC->SetMarkerColor(kRed);
   TEPXDRC->SetMarkerStyle(20);
   TEPXDRC->SetLineColor(kRed);
   MG->Add(TEPXDRC);
   
   TGraph *TEPXDR2x = new TGraph(n,PU,lum_unc[1]);
   TEPXDR2x->SetMarkerColor(kBlue);
   TEPXDR2x->SetMarkerStyle(21);
   TEPXDR2x->SetLineColor(kBlue);
   MG->Add(TEPXDR2x);
   
   TGraph *TEPXC = new TGraph(n,PU,lum_unc[2]);
   TEPXC->SetMarkerColor(kOrange);
   TEPXC->SetMarkerStyle(22);
   TEPXC->SetLineColor(kOrange);
   MG->Add(TEPXC);
   
   TGraph *TEPX2x = new TGraph(n,PU,lum_unc[3]);
   TEPX2x->SetMarkerColor(kYellow);
   TEPX2x->SetMarkerStyle(23);
   TEPX2x->SetLineColor(kYellow);
   MG->Add(TEPX2x);
   
   TGraph *OT6 = new TGraph(n,PU,lum_unc[4]);
   OT6->SetMarkerColor(kBlack);
   OT6->SetMarkerStyle(33);
   OT6->SetLineColor(kBlack);
   MG->Add(OT6);
   
   TGraph *DTS = new TGraph(n,PU,lum_unc[5]);
   DTS->SetMarkerColor(kGreen);
   DTS->SetMarkerStyle(34);
   DTS->SetLineColor(kGreen);
   MG->Add(DTS);
   
   TGraph *BMTFT = new TGraph(n,PU,lum_unc[6]);
   BMTFT->SetMarkerColor(kViolet);
   BMTFT->SetMarkerStyle(43);
   BMTFT->SetLineColor(kViolet);
   MG->Add(BMTFT);
   
   TGraph *EMTFT = new TGraph(n,PU,lum_unc[7]);
   EMTFT->SetMarkerColor(kCyan);
   EMTFT->SetMarkerStyle(47);
   EMTFT->SetLineColor(kCyan);
   MG->Add(EMTFT);
   


  
  MG->GetYaxis()->SetRangeUser(0.01, 10000);
  MG->GetXaxis()->SetLimits(0.7, 250);
  MG->GetYaxis()->CenterTitle(true);
  MG->GetYaxis()->SetTitleOffset(1);
  MG->GetYaxis()->SetTitle(" Statistical Uncertainty on #sigma_{vis} * N  / bx / 1s (%)");
  MG->GetXaxis()->SetTitle("Pile-up");
  gPad->SetLogy();
  gPad->SetLogx();
  MG->Draw("lpsame");
   
  TLegend * legend = new TLegend(0.75,0.58,.97,.98);
  legend->AddEntry(TEPXDRC,"TEPXD4R1 Clusters","lep");
  legend->AddEntry(TEPXDR2x," TEPXD4R1 2x Coincidences","lep");
  legend->AddEntry(TEPXC,"TEPX Clusters","lep");
  legend->AddEntry(TEPX2x,"TEPX 2x Coincidences","lep");
  legend->AddEntry(OT6,"OT Layer 6 track stubs","lep");
  legend->AddEntry(DTS,"DT Trigger Primitives","lep");
  legend->AddEntry(BMTFT,"BMTF","lep");
  legend->AddEntry(EMTFT,"EMTF","lep");
  legend->SetMargin(0.2);
  legend->SetTextFont(42);
  legend->SetTextSize(0.02);
  legend->Draw();
 
 c1->Print("/home/hedwin/plots/stat_plots/Stat_uncertainty_for_lum_Physics_log.png");
}
