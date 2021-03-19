#include "linearityPlots.C"

void linearityPlots_perringclustersdiskcombined()
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";  
  
  
  TString LuminometerName="TEPX clusters per ring, Disk ";
  TString outfile=LuminometerName;
  
  outfile.ReplaceAll(" ","_");
  outfile.ReplaceAll(",","_");
  outfile.ReplaceAll("-","n");
  
  TFile Finput("TDRplotscluster.root","read");
  TString graphname="cluster_disk";
  
  TGraphErrors* Counts[50][50];
  TF1* F[50][50];
  
  int firstl=0;
  int firstm=0;
  
  ///Extract the graphs and apply fit
  for(long l=firstl;l<4;l++){
    for(long m=firstm;m<5;m++){
      
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
    generateCanvas(LuminometerName+l, 0.5, 210, "pileup", 0, 6000, "mean number of clusters / bx");
    TLegend leg(0.2,0.6,0.4,0.8);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);	
    for(long m=firstm;m<5;m++){
      
      Counts[l][m]->SetMarkerColor(5-m);
      Counts[l][m]->SetLineColor(5-m);
      Counts[l][m]->Draw("pesame");
      F[l][m]->SetLineColor(5-m);
      F[l][m]->Draw("lsame");
      
      leg.AddEntry(Counts[l][m],TString("ring ")+(m+1),"pl");
      leg.Draw(); 
      
      
    }
    
    text.DrawLatexNDC(0.2,0.85,LuminometerName+(l+1));
    printCanvas(outfile+(l+1)+"combined_Linearity");
  }
  
  
  
  ///////////////////
  //residuals graph
  TGraphErrors Residuals[50][50];
  
  for(long l=firstl;l<4;l++){
    generateCanvas(LuminometerName+l,0.5, 210, "pileup", -5, 5, "linearity residuals (%) ");
    TLegend leg(0.75,0.72,0.95,0.9);
    leg.SetFillColor(0);
    leg.SetLineColor(0);
    leg.SetBorderSize(0);    
    for(long m=firstm;m<5;m++){
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
      
      leg.SetX1NDC(0.75);
      leg.SetY1NDC(0.72);
      leg.SetX2NDC(0.95);
      leg.SetY2NDC(0.9);
      leg.Draw();
    }
    
    line.SetLineStyle(2);
    line.SetLineWidth(2);
    line.DrawLine(0,1,210,1);
    line.DrawLine(0,-1,210,-1);
    
    text.DrawLatexNDC(0.2,0.85,LuminometerName+(l+1));
    printCanvas(outfile+(l+1)+"combined_Linearity_residuals");
    
  }
}
