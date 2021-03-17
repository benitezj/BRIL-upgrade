#include "linearityPlots.C"


void linearityPlots_perdiskclusters()
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";  


  TString LuminometerName="TEPX clusters per disk";
  //TString LuminometerName="TEPX coincidences per disk";
  TString outfile=LuminometerName;
  outfile.ReplaceAll(" ","_");


  TFile Finput("TDRplotscluster.root","read");
  TString graphname="cluster_disk";
  

  //TFile Finput("TDRplots2xtotal_phi_R.root","read");
  //TString graphname="2xCoincidences_disk";
  
  TGraphErrors* Counts[6];
  TF1* F[6];
 
  int firstl=1;
 
  TLegend leg(0.2,0.6,0.4,0.8);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetBorderSize(0);
 

  ///Extract the graphs and apply fit
  for(long l=firstl;l<5;l++){

    TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+l);
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

    F[l]=(TF1*)Fit.Clone(Fit.GetName()+graphname+l);
    G->Fit(F[l],"","QN",0,2);
  }
  

  ////////////////////////
  ////Linearity graph
  generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 20000, "mean number of clusters / bx");
  //generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 2000, "mean number of Coincidences / bx");
  for(long l=firstl;l<5;l++){
    Counts[l]->SetMarkerColor(5-l);
    Counts[l]->SetLineColor(5-l);
    Counts[l]->Draw("pesame");
    F[l]->SetLineColor(5-l);
    F[l]->Draw("lsame");
    leg.AddEntry(Counts[l],TString("Disk ")+l,"pl");
  }
  leg.Draw();
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity");    



  ///////////////////
  //residuals graph
  TGraphErrors Residuals[6];
  generateCanvas(LuminometerName,0.5, 210, "pileup", -5, 5, "linearity residuals (%) ");
  
  for(long l=firstl;l<5;l++){
    for(int i=0;i<Counts[l]->GetN();i++){
      float x=Counts[l]->GetX()[i];
      float y=Counts[l]->GetY()[i];
      float ye=Counts[l]->GetEY()[i];
      Residuals[l].SetPoint(i,x-l,100*(y-F[l]->Eval(x))/F[l]->Eval(x));
      Residuals[l].SetPointError(i,0,100*ye/F[l]->Eval(x));
    }
    Residuals[l].SetMarkerColor(5-l);
    //Residuals[l].SetMarkerSize(0);
    Residuals[l].SetLineColor(5-l);
    Residuals[l].Draw("pesame");
  }
  
  line.SetLineStyle(2);
  line.SetLineWidth(2);
  line.DrawLine(0,1,210,1);
  line.DrawLine(0,-1,210,-1);
  text.DrawLatexNDC(0.2,0.85,LuminometerName);

  leg.SetX1NDC(0.75);
  leg.SetY1NDC(0.72);
  leg.SetX2NDC(0.95);
  leg.SetY2NDC(0.9);
  leg.Draw();
  printCanvas(outfile+"_Linearity_residuals");
 
  
}
