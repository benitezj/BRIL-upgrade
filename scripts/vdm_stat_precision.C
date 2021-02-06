
void vdm_stat_precision(){

/* defining variables*/ 
float x_axis;/*values for the x axis*/
float Gaus_dist;/*Values of the Gaussian distribution*/
int center=0;/*center of the normal distribution*/
int mean_value=100;
float st_div= 50*pow(10, -6);/*standar deviation*/
float x_lim=200*pow(10, -6);/*X axis limits*/


/*Defining the Gaussian distribution*/
TF1  G("G","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -x_lim,x_lim );
G.FixParameter(0,mean_value);
G.FixParameter(1,center);
G.FixParameter(2,st_div);


/*Histogram fill */
auto H=new TH1F("Van der Meer Scan"," ",25, -x_lim, x_lim); 
    
    for (int i=0;i<25;i++){
        x_axis=H->GetXaxis()->GetBinCenter(i+1);
        Gaus_dist=G.Eval(x_axis);
        H->SetBinContent(i+1,Gaus_dist);
        H->SetBinError(i+1,sqrt(Gaus_dist));
        }
        
/*Fitting normal distribution to Histogram*/
TF1  F("F","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -x_lim, x_lim );
F.SetParLimits(0,0, 1000000);
F.FixParameter(1,0);
F.SetParLimits(2,0, 1);
F.SetLineColor(8);
H->Fit(&F);


/*plot histogram*/
TCanvas *c1=new TCanvas("c1");
int Max=H->GetBinContent( H->GetMaximumBin());
gStyle->SetOptStat(0);
H->GetXaxis()->SetTitle("x#Delta");
H->GetXaxis()->CenterTitle(true);
H->GetYaxis()->SetTitle("#lambda VdM");
H->GetYaxis()->CenterTitle(true);
H->GetYaxis()->SetTitleOffset(1);
H->GetYaxis()->SetRangeUser( 0 , 1.2*Max);
H->Draw();

/*print a gif file*/
c1->Print("/home/hedwin/plots/Stat_Precision_VdM.gif");

/*extracting parameters and parameter errors*/
float Norm = F.GetParameter(0);
float Norm_Error = F.GetParError(0);
float CapSigma = F.GetParameter(2);
float CapSigma_Error = F.GetParError(2);
cout<<"Mean value"<<"................ "<< Norm <<endl;
cout<<"Mean value error"<<".......... "<< Norm_Error<<endl;
cout<<"Standard deviation"<<"........ "<< CapSigma<<endl;
cout<<"Standard deviation error"<<".. "<< CapSigma_Error<<endl;
}



