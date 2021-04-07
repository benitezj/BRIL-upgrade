#include "stat_precision_globals.h"

float PU[21]={1,10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};
float PU_L[21];
float stat_unc[8][21];








void stat_precision_function(){

 TEPX_Counts();

  float count_per_event[8]={TEPXDR_C[0][3][0]+TEPXDR_C[1][3][0],TEPXDR_2x[0][3][0]+TEPXDR_2x[1][3][0],TEPX_C,TEPX_2x,OTL6,DTTP,BMTF,EMTF};
float trigger_rate[8]={825e3,825e3,75e3,75e3,40e6,40e6,40e6,40e6};

    for (int i=0;i<8;i++){

        for(int l=0;l<21;l++){

           PU_L[l]=200/PU[l];
           stat_unc[i][l]=100/sqrt((count_per_event[i]/PU_L[l])*trigger_rate[i]*second/NBX);


        }

    }
}


void stat_precision_graph(){

stat_precision_function();

TMultiGraph *MG = new TMultiGraph();
TCanvas *c1=new TCanvas("c1","");

   int n=21;



   TGraph *TEPXDRC = new TGraphErrors(n,PU,stat_unc[0]);
   TEPXDRC->SetMarkerColor(kRed);
   TEPXDRC->SetMarkerStyle(20);
   TEPXDRC->SetLineColor(kRed);
   MG->Add(TEPXDRC);
   
   TGraph *TEPXDR2x = new TGraphErrors(n,PU,stat_unc[1]);
   TEPXDR2x->SetMarkerColor(kBlue);
   TEPXDR2x->SetMarkerStyle(21);
   TEPXDR2x->SetLineColor(kBlue);
   MG->Add(TEPXDR2x);
   
   TGraph *TEPXC = new TGraphErrors(n,PU,stat_unc[2]);
   TEPXC->SetMarkerColor(kOrange);
   TEPXC->SetMarkerStyle(22);
   TEPXC->SetLineColor(kOrange);
   MG->Add(TEPXC);
   
   TGraph *TEPX2x = new TGraphErrors(n,PU,stat_unc[3]);
   TEPX2x->SetMarkerColor(kYellow);
   TEPX2x->SetMarkerStyle(23);
   TEPX2x->SetLineColor(kYellow);
   MG->Add(TEPX2x);
   
   TGraph *OT6 = new TGraphErrors(n,PU,stat_unc[4]);
   OT6->SetMarkerColor(kBlack);
   OT6->SetMarkerStyle(33);
   OT6->SetLineColor(kBlack);
   MG->Add(OT6);
   
   TGraph *DTS = new TGraph(n,PU,stat_unc[5]);
   DTS->SetMarkerColor(kGreen);
   DTS->SetMarkerStyle(34);
   DTS->SetLineColor(kGreen);
   MG->Add(DTS);
   
   TGraph *BMTFT = new TGraph(n,PU,stat_unc[6]);
   BMTFT->SetMarkerColor(kViolet);
   BMTFT->SetMarkerStyle(43);
   BMTFT->SetLineColor(kViolet);
   MG->Add(BMTFT);
   
   TGraph *EMTFT = new TGraph(n,PU,stat_unc[7]);
   EMTFT->SetMarkerColor(kCyan);
   EMTFT->SetMarkerStyle(47);
   EMTFT->SetLineColor(kCyan);
   MG->Add(EMTFT);
   


  MG->GetYaxis()->SetRangeUser(0.01, 1000);
  MG->GetXaxis()->SetLimits(0.8, 250);
  MG->GetYaxis()->CenterTitle(true);
  MG->GetYaxis()->SetTitleOffset(1.2);
  MG->GetYaxis()->SetTitle("Statistical Uncertainty on the counts N  /  bx / 1s  (%)  ");
  MG->GetXaxis()->SetTitle("Pileup");
  gPad->SetLogy();
  gPad->SetLogx();
  MG->Draw("apl");
   
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

 c1->Print("/home/hedwin/plots/stat_plots/Stat_uncertainty_for_Physics_log.png");
}
