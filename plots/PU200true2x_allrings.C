void PU200true2x_allrings() {
  

  TFile * f = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  TFile * f1 = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  TFile * f2 = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  TFile * f3 = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  TFile * f4 = new TFile("/home/ashish/Desktop/TEPX/2023D42PU200.root");
  
  
  TCanvas * C = new TCanvas("2xCoincidencestrueallrings","");
  
  
  TH2F * H1=NULL;                                                                                                                           
  TH2F * H2=NULL; 
  TH2F * H3=NULL;
  TH2F * H4=NULL; 
  TH2F * H5=NULL;
  
  
  H1 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR_Ring1_sametrack");
  //H1 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR1_Ring1_sametrack");
  //H1 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring1_sametrack");
  H1->Rebin(10);
  if (H1==NULL){
    return;
  }
  
  H2 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR_Ring2_sametrack");
  //H2 = (TH2F*)f1->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR1_Ring2_sametrack");
  //H2 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring2_sametrack");
  H2->Rebin(10);
  if (H2==NULL){
    return;
  }
  
  H3 = (TH2F*)f2->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR_Ring3_sametrack");
  //H3 = (TH2F*)f2->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR1_Ring3_sametrack");
  //H3 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring3_sametrack");
  H3->Rebin(10);
  if (H3==NULL){
    return;
  }
  
  H4 = (TH2F*)f3->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR_Ring4_sametrack");
  //H4 = (TH2F*)f3->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR1_Ring4_sametrack");
  //H4 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring4_sametrack");
  H4->Rebin(10);
  if (H4==NULL){
    return;
  }
 
  H5 = (TH2F*)f4->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR_Ring5_sametrack");
  //H5 = (TH2F*)f4->Get("BRIL_IT_Analysis/TEPX/Residuals/ResidualsR1_Ring5_sametrack");
  //H5 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Residuals/Deltaphi_Ring5_sametrack");
  H5->Rebin(10);
  if (H5==NULL){
    return;
 }
  
  
  //H1->GetXaxis()->SetRangeUser(-1, 1);
  //H2->GetXaxis()->SetRangeUser(-1, 1);
  //H3->GetXaxis()->SetRangeUser(-1, 1);
  //H4->GetXaxis()->SetRangeUser(-1, 1);
  //H5->GetXaxis()->SetRangeUser(-1, 1);
  
  
  //H1->GetXaxis()->SetRangeUser(-0.2, 0.2);
  //H2->GetXaxis()->SetRangeUser(-0.2, 0.2);
  //H3->GetXaxis()->SetRangeUser(-0.2, 0.2);
  //H4->GetXaxis()->SetRangeUser(-0.2, 0.2);
  //H5->GetXaxis()->SetRangeUser(-0.2, 0.2);
  //H1->GetYaxis()->SetRangeUser(0, 3500);
  
  
  H1->Scale(1./H1->Integral());
  H2->Scale(1./H2->Integral());
  H3->Scale(1./H3->Integral());
  H4->Scale(1./H4->Integral());
  H5->Scale(1./H5->Integral());
  
  H1->SetLineColor(1);
  H2->SetLineColor(2);
  H3->SetLineColor(3);
  H4->SetLineColor(4);
  H5->SetLineColor(5);
  
  
  gPad->SetGrid(1,1);
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(1111);
  
  H1->Draw("same");
  H2->Draw("same");
  H3->Draw("same");
  H4->Draw("same");
  H5->Draw("same");
  
  auto legend = new TLegend(0.6,0.6,0.9,0.9);
  
  legend->AddEntry(H1,"PU 200 true 2x in phi Ring 1","l");
  legend->AddEntry(H2,"PU 200 true 2x in phi Ring 2","l");
  legend->AddEntry(H3,"PU 200 true 2x in phi Ring 3","l");
  legend->AddEntry(H4,"PU 200 true 2x in phi Ring 4","l");
  legend->AddEntry(H5,"PU 200 true 2x in phi Ring 5","l");
  
  
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->Draw("same");
  
  
  C->Print("/home/ashish/thatwasepic.gif");
  
}


