#include "stat_precision_globals.h"




void vdm_stat_precision_function(TString DETECTOR = "TEPX", 
                                 float count_per_event_vdm=0,
                                 float trigger_rate_vdm=0,
                                 float Number_BX=0){

	/* defining variables*/ 
	float x_axis=0;/*values for the x axis*/
	float Gaus_dist=0;/*Values of the Gaussian distribution*/
	int center=0;/*center of the normal distribution*/
	float st_div= 0.120;/*standard deviation*/
	float x_lim=0.6;/*X axis limits*/
	float mean_counts=((count_per_event_vdm/400)*trigger_rate_vdm*VDM)/Number_BX;/*Mean counts/30s/bx*/

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
	TF1 * F=new TF1("F","[0]*exp((-0.5*(x-[1])**2)/([2]**2))", -x_lim, x_lim );
	F->SetParLimits(0,0, 100000000);
	F->FixParameter(1,0);
	F->SetParLimits(2,0, 1);
	F->SetLineColor(8);
	F->Draw();


	/*Extracting covariance and correlation matrices */
	TFitResultPtr r = H->Fit(F,"S");
	TMatrixD cor = r->GetCorrelationMatrix();
	TMatrixD cov = r->GetCovarianceMatrix();
   //cov.Print();
   cout<<DETECTOR<<" .......... "<<cov[0][2]<<endl;


	/*extracting parameters and parameter errors*/
	float Norm = F->GetParameter(0);
	float Norm_Error = F->GetParError(0);
	float CapSigma = F->GetParameter(2);
	float CapSigma_Error = F->GetParError(2);
	float sigma_vis=sqrt((pow(1/Norm,2)*cov[0][0])+2*(pow(1/CapSigma,2)*cov[2][2])+(4*cov[0][2]/(Norm*CapSigma)));


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

  myfile<<DETECTOR
      
      //amplitude and amplitude uncertainty
      <<"&"<<toPrecision(Norm,3)<<"&"<<toPrecision(Norm_Error,2)


   
      //Beam Width 
      <<"&"<<toPrecision(CapSigma,2)

      //Beam Width and sigma visual uncertainty
      <<"&"<<fixed<<setprecision(5)<<CapSigma_Error
      <<"&"<<toPrecision(sigma_vis*100,2)
      <<"&"<<toPrecision((sigma_vis/sqrt(150))*100,2)

      <<"\\\\"<<endl;
  myfile<<"\\hline"<<endl;
}



void vdm_stat_precision(){

 gErrorIgnoreLevel = kFatal;
 
  
  /*open txt file*/
  myfile.open("vdm_stat_precision_LATEX_tables.txt");	  
  /*call TEPX variables*/
  TEPX_Counts();
  float TEPX_2X=TEPX_2x;
  float TEPXD4R1_2X=TEPXDR_2x[0][3][0]+TEPXDR_2x[1][3][0];
  
  myfile<<ctime(&mytime)<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;
  myfile<<" "<<endl;
  myfile<<"//////////////////////////////////////"<<endl;
  myfile<<"//create table and plots for toy Vdm//"<<endl;
  myfile<<"//////////////////////////////////////"<<endl;
  myfile<<"\\begin{center}"<<endl;
  myfile<< "\\scalebox{.8}{"<<endl;
  myfile<<"\\begin{tabular}{|l | c | c | c |c|c|c|c}"<<endl;
  myfile<<"\\hline"<<endl;
  myfile<<" & $N_0$ &$\\delta N_0$&$ \\Sigma$&$ \\delta\\Sigma$&$\\delta\\sigma_{vis}/\\sigma_{vis}(\\\%)$&$\\delta\\sigma_{vis}/\\sigma_{vis}(\\\%)$, 150 bx\\\\"<<endl;
  myfile<<"\\hline"<<endl;  
  vdm_stat_precision_function("TEPXD4R1 Clusters",TEPXDR_C[0][3][0]+TEPXDR_C[1][3][0],1000e3,NBX_TEPX_VDM);
  vdm_stat_precision_function("TEPXD4R1 2x Coincidences",TEPXD4R1_2X,1000e3,NBX_TEPX_VDM);
  vdm_stat_precision_function("TEPX Clusters",TEPX_C,500e3,NBX_TEPX_VDM);
  vdm_stat_precision_function("TEPX 2x Coincidences",TEPX_2X,500e3,NBX_TEPX_VDM);  
  vdm_stat_precision_function("OT Layer 6",OTL6,40e6,NBX);
  vdm_stat_precision_function("DT",DTTP,40e6,NBX);
  vdm_stat_precision_function("BMTF",BMTF,40e6,NBX);
  vdm_stat_precision_function("EMTF",EMTF,40e6,NBX);
  myfile<<"\\end{tabular}}"<<endl;
  myfile<< "\\end{center}"<<endl;
  myfile.close();


}

