#include "linearityPlots.C"

void linearityPlots_perringclusters()
{
  setTDRStyle();
  lumi_sqrtS = "#sqrt{s} = 14 TeV";
  writeExtraText = true;
  extraText  = "       Phase-2 Simulation Preliminary";  


  TString LuminometerName="TEPX clusters per ring, Disk 4";
  TString outfile=LuminometerName;
  outfile.ReplaceAll(", ","_");
  outfile.ReplaceAll("+","p");

  TFile Finput("TDRplotscluster.root","read");
  TString graphname="Clusters";
  
  TGraphErrors* Counts[50][50];
  TF1* F[50][50];
 
  int firstl=0;
  int firstm=0;
 
  TLegend leg(0.2,0.6,0.4,0.8);
  leg.SetFillColor(0);
  leg.SetLineColor(0);
  leg.SetBorderSize(0);
 

  ///Extract the graphs and apply fit
  for(long l=firstl;l<8;l++){
    for(long m=firstm;m<5;m++){

    TGraphErrors* G=(TGraphErrors*)Finput.Get(graphname+"D"+l+"R"+m);
    if(!G){ cout<<"Wrong graph name: "<<graphname+"D"+l+"R"+m<<endl; return;}

    ///copy for linear graph
    Counts[l][m] = new TGraphErrors();
    for(int i=0;i<G->GetN();i++){
      float x=G->GetX()[i];
      float y=G->GetY()[i];
      float ye=G->GetEY()[i];
      Counts[l][m]->SetPoint(i,x,y);
      Counts[l][m]->SetPointError(i,0,ye);
    
}
    F[l][m]=(TF1*)Fit.Clone(Fit.GetName()+graphname+"D"+l+"R"+m);
    G->Fit(F[l][m],"","QN",0,2);
  }
 } 

  ////////////////////////
  ////Linearity graph
  generateCanvas(LuminometerName, 0.5, 210, "pileup", 0, 3000, "mean number of clusters / bx");
  for(long l=firstl;l<8;l++){
    for(long m=firstm;m<5;m++){
    if(l==7){

    Counts[l][m]->SetMarkerColor(5-m);
    Counts[l][m]->SetLineColor(5-m);
    Counts[l][m]->Draw("pesame");
    F[l][m]->SetLineColor(5-m);
    F[l][m]->Draw("lsame");
    leg.AddEntry(Counts[l][m],TString("ring ")+(m+1),"pl");
} 
}
}
  leg.Draw();
  text.DrawLatexNDC(0.2,0.85,LuminometerName);
  printCanvas(outfile+"_Linearity");    



  ///////////////////
  //residuals graph
  TGraphErrors Residuals[50][50];
  generateCanvas(LuminometerName,0.5, 210, "pileup", -5, 5, "linearity residuals (%) ");
  
  for(long l=firstl;l<8;l++){
       for(long m=firstm;m<5;m++){
          for(int i=0;i<Counts[l][m]->GetN();i++){
       if(l==7){
      float x=Counts[l][m]->GetX()[i];
      float y=Counts[l][m]->GetY()[i];
      float ye=Counts[l][m]->GetEY()[i];
      Residuals[l][m].SetPoint(i,x-m,100*(y-F[l][m]->Eval(x))/F[l][m]->Eval(x));
      Residuals[l][m].SetPointError(i,0,100*ye/F[l][m]->Eval(x));
    }


    Residuals[l][m].SetMarkerColor(5-m);
    Residuals[l][m].SetLineColor(5-m);
    Residuals[l][m].Draw("pesame");

  }
 } 
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
