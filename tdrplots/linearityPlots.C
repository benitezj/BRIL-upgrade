#include "tdrstyle.C"
#include "CMS_lumi.C"
#include "TH1.h"
#include "TH1F.h"

TLatex text;
TLine line;
TF1 Fit("Fit","[0]+[1]*x", 0, 205);
TCanvas* canv = NULL;
float residual_range = 5;//%

void generateCanvas(TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title);
void printCanvas(TString canvName);
void plotLuminometer(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2);


void linearityPlots()
{
  setTDRStyle();
  
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";    
  plotLuminometer("OT_TDR.root", "ghBarrelL6", "Outer Tracker Layer 6 track stubs", 0.5, 210, "pileup", 0, 1200, "mean number of stubs / bx");
  plotLuminometer("TDRplotscluster.root", "cluster_TEPX", "TEPX clusters", 0.5, 210, "pileup", 0, 60000, "mean number of clusters / bx");
  plotLuminometer("TDRplotscluster.root", "cluster_D4R1", "TEPX Disk 4 Ring 1 clusters", 0.5, 210, "pileup", 0, 5000, "mean number of clusters / bx");
  plotLuminometer("TDRplots2xtotal_phi_R.root", "2xCoincidences_TEPX", "TEPX coincidences", 0.5, 210, "pileup", 0, 6000, "mean number of coincidences / bx");
  plotLuminometer("TDRplots2xtotal_phi_R.root", "2xCoincidences_D4R1", "TEPX Disk 4 Ring 1 coincidences", 0.5, 210, "pileup", 0, 600, "mean number of coincidences / bx");
  
}



/////////////////////////////////////////////////
/// auxiliary functions
////////////////////////////////////////////////
void plotLuminometer(TString filename, TString graphname, TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title, float fitmin=0, float fitmax=2){
  
  TString outfile=LuminometerName;
  outfile.ReplaceAll(" ","_");

   TFile F(filename,"read");
  TGraphErrors* G=(TGraphErrors*)F.Get(graphname);
  if(!G){ cout<<"Wrong graph name: "<<graphname<<endl; return;}
  
  //fit original graph otherwise fits stas appear on plot
  G->Fit(&Fit,"","N",fitmin,fitmax);

  ///linear graph
  TGraphErrors Counts;
  for(int i=0;i<G->GetN();i++){
    float x=G->GetX()[i];
    float y=G->GetY()[i];
    float ye=G->GetEY()[i];
    Counts.SetPoint(i,x,y);
    Counts.SetPointError(i,0,ye);
    //Counts.SetPointError(i,0,y/200);//FIX
  }
  
  generateCanvas(LuminometerName,x_min, x_max, x_title, y_min, y_max, y_title);
  Counts.Draw("pesame");
  Fit.Draw("lsame");
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity");
  delete canv;
  
  //residuals
  TGraphErrors Residuals;
  for(int i=0;i<Counts.GetN();i++){
    float x=Counts.GetX()[i];
    float y=Counts.GetY()[i];
    float ye=Counts.GetEY()[i];
    Residuals.SetPoint(i,x,100*(y-Fit.Eval(x))/Fit.Eval(x));
    Residuals.SetPointError(i,0,100*ye/Fit.Eval(x));
  }
  
  generateCanvas(LuminometerName,x_min, x_max, x_title, -residual_range, residual_range, "linearity residuals (%) ");
  Residuals.Draw("pesame");
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(0,1,210,1);
  line.DrawLine(0,-1,210,-1);
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity_residuals");
  delete canv;
}


void generateCanvas(TString LuminometerName, float x_min, float x_max, TString x_title, float y_min, float y_max, TString y_title){
  int iPeriod=0;// uses the lumi_sqrtS string
  int iPos=0;//postion of CMS Preliminary
  
  int W = 800;
  int H = 600;
  int H_ref = 600; 
  int W_ref = 800; 
  
  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.12*H_ref; 
  float L = 0.12*W_ref;
  float R = 0.04*W_ref;
  
  
  canv = new TCanvas(LuminometerName+"_"+x_title+"_"+y_title,"",50,50,W,H);
  canv->SetFillColor(0);
  canv->SetBorderMode(0);
  canv->SetFrameFillStyle(0);
  canv->SetFrameBorderMode(0);
  canv->SetLeftMargin( L/W );
  canv->SetRightMargin( R/W );
  canv->SetTopMargin( T/H );
  canv->SetBottomMargin( B/H );
  canv->SetTickx(0);
  canv->SetTicky(0);
  //canv->SetLogx(1);
  
  TH1F* h = new TH1F(LuminometerName+x_title+"_"+y_title,"",1,x_min,x_max);
  h->GetXaxis()->SetNdivisions(6,5,0);
  h->GetXaxis()->SetTitle(x_title);
  h->GetXaxis()->SetRangeUser(x_min,x_max);
  h->GetYaxis()->SetNdivisions(6,5,0);
  h->GetYaxis()->SetTitleOffset(1);
  h->GetYaxis()->SetTitle(y_title);
  h->GetYaxis()->SetMaxDigits(3);
  h->GetYaxis()->SetRangeUser(y_min,y_max);
  h->Draw();
  
  
  CMS_lumi( canv, iPeriod, iPos );
}


void printCanvas(TString canvName){
  
  canv->Update();
  canv->RedrawAxis();
  canv->GetFrame()->Draw();
  //canv->Print(canvName+".pdf",".pdf");
  canv->Print(canvName+".png",".png");
}


