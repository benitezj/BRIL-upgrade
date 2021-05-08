#include "linearityPlots.C"

void linearityPlots_perringcoincidences()
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";  
  
  TString LuminometerName="TEPX coincidences in R per ring, Disk ";
  TString outfile=LuminometerName;
  
  outfile.ReplaceAll(" ","_");
  outfile.ReplaceAll(",","_");
  outfile.ReplaceAll("-","n");
  outfile.ReplaceAll("+","p");

  
  //TFile Finput("TDRplots_2xinphi.root","read");
  TFile Finput("TDRplots_2xinR.root","read");
  //TFile Finput("TDRplots2x_phi_R.root","read");
  TString graphname="2xCoincidences";
  
  TGraphErrors* Counts[20][20][20];
  TF1* F[20][20][20];
  
  int firstl=0;
  int firstm=0;
  int firstn=0;
  
  //Extract the graphs and apply fit
  for(long n=firstn;n<2;n++){
    for(long l=firstl;l<4;l++){
      for(long m=firstm;m<4;m++){
	
	TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+"S"+(n+1)+"D"+(l+1)+"R"+(m+1));
	if(!G){ cout<<"Wrong graph name: "<<graphname+"S"+(n+1)+"D"+(l+1)+"R"+(m+1)<<endl; return;}
	
	///copy for linear graph
	Counts[n][l][m] = new TGraphErrors();
	for(int i=0;i<G->GetN();i++){
	  float x=G->GetX()[i];
	  float y=G->GetY()[i];
	  float ye=G->GetEY()[i];
	  Counts[n][l][m]->SetPoint(i,x,y);
	  Counts[n][l][m]->SetPointError(i,0,ye);
	  
	}
	
	F[n][l][m]=(TF1*)Fit.Clone(Fit.GetName()+graphname+"S"+n+"D"+l+"R"+m);
	G->Fit(F[n][l][m],"","QN",0,2);
      }
    } 
  }
  ////////////////////////
  ////Linearity graph
  
  
  for(long n=firstn;n<2;n++){
    for(long l=firstl;l<4;l++){
      generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 100, "mean number of coincidences / bx");
      TLegend leg(0.2,0.6,0.4,0.8);
      leg.SetFillColor(0);
      leg.SetLineColor(0);
      leg.SetBorderSize(0);
      for(long m=firstm;m<4;m++){
	Counts[n][l][m]->SetMarkerColor(5-m);
	Counts[n][l][m]->SetLineColor(5-m);
	Counts[n][l][m]->Draw("pesame");
	F[n][l][m]->SetLineColor(5-m);
	F[n][l][m]->Draw("lsame");	
	leg.AddEntry(Counts[n][l][m],TString("ring ")+(m+1),"pl");
	
      }
      
      leg.Draw();
      
      if(n==0) {
	text.DrawLatexNDC(0.2,0.85,LuminometerName+(l-4));
      } else {
	text.DrawLatexNDC(0.2,0.85,LuminometerName+(l+1));
      } 
 
    if(n==0) {
      printCanvas(outfile+(l-4)+"_Linearity");
    } else {

     printCanvas(outfile+(l+1)+"_Linearity");
}
    }
  }
  
  ///////////////////
  //residuals graph
  TGraphErrors Residuals[20][20][20];
  
  for(long n=firstn;n<2;n++){
    for(long l=firstl;l<4;l++){
      generateCanvas(LuminometerName,0.5, 210, "pileup", -5, 5, "linearity residuals (%) ");
      TLegend leg(0.7,0.2,0.9,0.4);
      leg.SetFillColor(0);
      leg.SetLineColor(0);
      leg.SetBorderSize(0);
      for(long m=firstm;m<4;m++){
	for(int i=0;i<Counts[n][l][m]->GetN();i++){
	  
	  float x=Counts[n][l][m]->GetX()[i];
	  float y=Counts[n][l][m]->GetY()[i];
	  float ye=Counts[n][l][m]->GetEY()[i];
	  Residuals[n][l][m].SetPoint(i,x-m,100*(y-F[n][l][m]->Eval(x))/F[n][l][m]->Eval(x));
	  Residuals[n][l][m].SetPointError(i,0,100*ye/F[n][l][m]->Eval(x));
	  
	}
	leg.AddEntry(Counts[n][l][m],TString("ring ")+(m+1),"pl");
	Residuals[n][l][m].SetMarkerColor(5-m);
	Residuals[n][l][m].SetLineColor(5-m);
	Residuals[n][l][m].Draw("pesame");
	
	line.SetLineStyle(2);
	line.SetLineWidth(2);
	line.DrawLine(0,1,210,1);
	line.DrawLine(0,-1,210,-1);
	
	if(n==0) {
	  text.DrawLatexNDC(0.2,0.85,LuminometerName+(l-4));
	} else {
	  text.DrawLatexNDC(0.2,0.85,LuminometerName+(l+1));
	}
	
      }
      leg.Draw();

  if(n==0) {
      printCanvas(outfile+(l-4)+"_Linearity_residuals");
} else {

     printCanvas(outfile+(l+1)+"_Linearity_residuals");
}
    
     
    }    
  }
}
