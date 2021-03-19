#include "linearityPlots.C"

void linearityPlots_perringcoincidencesdiskcombined(int option=1)
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";  
  
  
  TString LuminometerName="TEPX coincidences per ring, Disk ";
  
  if(option==2) {
    LuminometerName="TEPX coincidences in phi per ring, Disk ";
  }
  if(option==3) {
    LuminometerName="TEPX coincidences in R per ring, Disk ";
  }
  
  
  TString outfile=LuminometerName;
  
  outfile.ReplaceAll(" ","_");
  outfile.ReplaceAll(",","_");
  outfile.ReplaceAll("-","n");
  
  
  TString filename = "TDRplots_2x_phi_R.root";
  TString graphname = "2xCoincidencesinphi_disk";
  
  if(option==2) {
    
    filename = "TDRplots_2xinphi.root";
    graphname = "2xCoincidencesinR_disk";
    
  }
  
  if(option==3) {
    
    filename = "TDRplots2xinR.root";
    graphname = "2xCoincidences_disk";
    
  }
  
  
  TFile Finput(filename,"read");
  
  TGraphErrors* Counts[20][20];
  TF1* F[20][20];
  
  int firstl=0;
  int firstm=0;
  
  //Extract the graphs and apply fit
  
  for(long l=firstl;l<4;l++){
    for(long m=firstm;m<4;m++){
      
      TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+(l+1)+"combinedring"+(m+1));
      if(!G){ cout<<"Wrong graph name: "<<graphname+(l+1)+"combinedring"+(m+1)<<endl; return;}
      
      
	///copy for linear graph
      Counts[l][m] = new TGraphErrors();
      for(int i=0;i<G->GetN();i++){
	float x=G->GetX()[i];
	float y=G->GetY()[i];
	float ye=G->GetEY()[i];
	Counts[l][m]->SetPoint(i,x,y);
	Counts[l][m]->SetPointError(i,0,ye);
	
      }
      
      F[l][m]=(TF1*)Fit.Clone(Fit.GetName()+graphname+(l+1)+"combinedring"+(m+1));
      G->Fit(F[l][m],"","QN",0,2);
    }
  } 
  
  ////////////////////////
  ////Linearity graph
  
  for(long l=firstl;l<4;l++){
    
    if(option==1) {
      generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 600, "mean number of coincidences / bx");
    }
    if(option==2) {
      generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 300, "mean number of coincidences / bx");
    }
    
    if(option==3) {
      generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 100, "mean number of coincidences / bx");
    }
    //generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 200, "mean number of coincidences / bx");
    TLegend leg(0.2,0.6,0.4,0.8);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);
    for(long m=firstm;m<4;m++){
      Counts[l][m]->SetMarkerColor(5-m);
      Counts[l][m]->SetLineColor(5-m);
      Counts[l][m]->Draw("pesame");
      F[l][m]->SetLineColor(5-m);
      F[l][m]->Draw("lsame");	
      leg.AddEntry(Counts[l][m],TString("ring ")+(m+1),"pl");
      
    }
    
    leg.Draw();
    
    text.DrawLatexNDC(0.2,0.85,LuminometerName+(l+1));
    printCanvas(outfile+(l+1)+"combined_Linearity");
    
  }
  
  
  ///////////////////
  //residuals graph
  TGraphErrors Residuals[20][20];
  
  
  for(long l=firstl;l<4;l++){
    generateCanvas(LuminometerName,0.5, 210, "pileup", -5, 5, "linearity residuals (%) ");
    TLegend leg(0.7,0.2,0.9,0.4);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);
    for(long m=firstm;m<4;m++){
      for(int i=0;i<Counts[l][m]->GetN();i++){
	
	float x=Counts[l][m]->GetX()[i];
	float y=Counts[l][m]->GetY()[i];
	float ye=Counts[l][m]->GetEY()[i];
	Residuals[l][m].SetPoint(i,x-m,100*(y-F[l][m]->Eval(x))/F[l][m]->Eval(x));
	Residuals[l][m].SetPointError(i,0,100*ye/F[l][m]->Eval(x));
	
      }
      
      leg.AddEntry(Counts[l][m],TString("ring ")+(m+1),"pl");
      Residuals[l][m].SetMarkerColor(5-m);
      Residuals[l][m].SetLineColor(5-m);
      Residuals[l][m].Draw("pesame");
      
      line.SetLineStyle(2);
      line.SetLineWidth(2);
      line.DrawLine(0,1,210,1);
      line.DrawLine(0,-1,210,-1);
      
      text.DrawLatexNDC(0.2,0.85,LuminometerName+(l+1));
      
    }
    
    leg.Draw();
    printCanvas(outfile+(l+1)+"combined_Linearity_residuals");
    
  } 
}
