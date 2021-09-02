#include "linearityPlots.C"


void linearityPlots_OT()
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 13 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";  


  TString LuminometerName="Outer Tracker Layers 1-6";
  TString outfile=LuminometerName;
  outfile.ReplaceAll(" ","_");


  TFile Finput("OT_TDR.root","read");
  TString graphname="ghBarrelL";
  
  TGraphErrors* Counts[6];
  TF1* F[6];

  int firstl=0;

  
  TLegend leg(0.2,0.5,0.4,0.8);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetBorderSize(0);
 

  ///Extract the graphs and apply fit
  for(long l=firstl;l<6;l++){
    TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+(l+1));
    if(!G){ cout<<"Wrong graph name: "<<graphname<<endl; return;}

    ///copy for linear graph
    Counts[l] = new TGraphErrors();
    for(int i=0;i<G->GetN();i++){
      float x=G->GetX()[i];
      float y=G->GetY()[i];
      float ye=G->GetEY()[i];
      Counts[l]->SetPoint(i,x,y);
      Counts[l]->SetPointError(i,0,ye);
    }

    F[l]=(TF1*)Fit.Clone(Fit.GetName()+graphname+(l+1));
    G->Fit(F[l],"","QN",0,2);
  }
  

  ////////////////////////
  ////Linearity graph
  generateCanvas(LuminometerName, 0.5, 210, "pile-up", 0, 2000, "# of track stubs");
  for(long l=firstl;l<6;l++){
    Counts[l]->SetMarkerColor(6-l);
    Counts[l]->SetLineColor(6-l);
    Counts[l]->Draw("pesame");
    F[l]->SetLineColor(6-l);
    F[l]->Draw("lsame");
    leg.AddEntry(Counts[l],TString("Layer ")+(l+1),"pl");
  }
  leg.Draw();
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity");    



  ///////////////////
  //residuals graph
  TGraphErrors Residuals[6];
  generateCanvas(LuminometerName,0.5, 210, "pile-up", -50, 50, "linearity residuals (%) ");
  
  for(long l=firstl;l<6;l++){
    for(int i=0;i<Counts[l]->GetN();i++){
      float x=Counts[l]->GetX()[i];
      float y=Counts[l]->GetY()[i];
      float ye=Counts[l]->GetEY()[i];
      Residuals[l].SetPoint(i,x,100*(y-F[l]->Eval(x))/F[l]->Eval(x));
      Residuals[l].SetPointError(i,0,100*ye/F[l]->Eval(x));
    }
    Residuals[l].SetMarkerColor(6-l);
    Residuals[l].SetLineColor(6-l);
    Residuals[l].Draw("pesame");
  }
  
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(0,1,210,1);
  line.DrawLine(0,-1,210,-1);
  text.DrawLatexNDC(0.2,0.85,LuminometerName);

  leg.SetX1NDC(0.2);
  leg.SetY1NDC(0.15);
  leg.SetX2NDC(0.4);
  leg.SetY2NDC(0.45);
  leg.Draw();
  printCanvas(outfile+"_Linearity_residuals");
 
  
}
