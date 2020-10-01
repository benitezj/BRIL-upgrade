void PU200trueVsfake2x() {
  
  
  TFile * f = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  TFile * f1 = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  TFile * f2 = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  
  TCanvas * C = new TCanvas("2xCoincidencestrueVsfake","");
  
  TH2F * H1=NULL;    
  TH2F * H2=NULL;   
  TH2F * H3=NULL;
  
  
  H1 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring1_sametrack");
  H1->Rebin(10);
  if (H1==NULL){
    return;
  }
  
  H2 = (TH2F*)f1->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring1_notsametrack");
  H2->Rebin(10);
  if (H2==NULL){
    return;
  }
  
  H3 = (TH2F*)f2->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring1");
  H3->Rebin(10);
  if (H3==NULL){
    return;
  }
  
  
  H1->SetLineColor(1);
  H2->SetLineColor(2);
  H3->SetLineColor(3);
  
  H1->GetXaxis()->SetRangeUser(-0.2, 0.2);
  H2->GetYaxis()->SetRangeUser(-0.2, 0.2);
  H3->GetYaxis()->SetRangeUser(-0.2, 0.2);
  
  
  H1->Scale(1./H1->Integral());
  H2->Scale(1./H2->Integral());
  H3->Scale(1./H3->Integral());
  
  gPad->SetGrid(1,1);
  
  H1->Draw("same");
  H2->Draw("same");
  H3->Draw("same");
  
  auto legend = new TLegend(0.6,0.6,0.9,0.9);
  legend->AddEntry(H1,"PU 200 true 2x in phi Ring 1 ","l");
  legend->AddEntry(H2,"PU 200 fake 2x in phi Ring 1","l");
  legend->AddEntry(H3,"PU 200 true 2x in phi Ring 1","l");
  
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->Draw("same");
  
  
  
  C->Print("/home/ashish/sphaleron.gif");
  
}
