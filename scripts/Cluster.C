void Cluster() {

  TFile*f10 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42noPU.root");
  TFile*f = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU0p5.root");
  TFile*f1 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU1.root");
  TFile*f2 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU1p5.root");
  TFile*f3 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU2.root");
  TFile*f4 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU10.root");
  TFile*f5 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU30.root");
  TFile*f6 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU50.root");
  TFile*f7 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU100.root");
  TFile*f8 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU140.root");
  TFile*f9 = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU200.root");
  
  TCanvas * C = new TCanvas("Clusters","");
  C->SetLogy();

  TH2F * H = NULL;
  TH2F * H1 = NULL;
  TH2F * H2 = NULL;
  TH2F * H3 = NULL;
  TH2F * H4 = NULL;
  TH2F * H5 = NULL;
  TH2F * H6 = NULL;
  TH2F * H7 = NULL;
  TH2F * H8 = NULL;
  TH2F * H9 = NULL;
  
   H = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  if (H==NULL){
  return;
   }
  
  H1 = (TH2F*)f1->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H2 = (TH2F*)f2->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H3 = (TH2F*)f3->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H4 = (TH2F*)f4->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H5 = (TH2F*)f5->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H6 = (TH2F*)f6->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H7 = (TH2F*)f7->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H8 = (TH2F*)f8->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");
  H9 = (TH2F*)f9->Get("BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk 4");


  TH1D* H10 = H->ProjectionY("H10",1,1);
  H10->GetYaxis()->SetRangeUser(0,5000); 
  H10->GetXaxis()->SetRangeUser(0,4);
  H10->SetLineColor(28);
  H10->Scale(1./H10->Integral());
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0); 

  TH1D* H11 = H1->ProjectionY("H11",1,1);
  H11->GetXaxis()->SetRangeUser(0,250);
  H11->SetLineColor(1);
  H11->Scale(1./H11->Integral());

  TH1D* H12 = H2->ProjectionY("H12",1,1);
  H12->GetXaxis()->SetRangeUser(0,500);
  H12->SetLineColor(2);
  H12->Scale(1./H12->Integral());

  TH1D* H13 = H3->ProjectionY("H13",1,1);
  H13->GetXaxis()->SetRangeUser(0,500);
  H13->SetLineColor(3);
  H13->Scale(1./H13->Integral());

  TH1D* H14 = H4->ProjectionY("H14",1,1);
  H14->GetXaxis()->SetRangeUser(0,500);
  H14->SetLineColor(4);
  H14->Scale(1./H14->Integral());  

  TH1D* H15 = H5->ProjectionY("H15",1,1);
  H15->GetXaxis()->SetRangeUser(0,500);
  H15->SetLineColor(32);
  H15->Scale(1./H15->Integral());

  TH1D* H16 = H6->ProjectionY("H16",1,1);
  H16->GetXaxis()->SetRangeUser(0,500);
  H16->SetLineColor(6);
  H16->Scale(1./H16->Integral());

  TH1D* H17 = H7->ProjectionY("H17",1,1);
  H17->GetXaxis()->SetRangeUser(0,500);
  H17->SetLineColor(41);
  H17->Scale(1./H17->Integral());

  TH1D* H18 = H8->ProjectionY("H18",1,1);
  H18->GetXaxis()->SetRangeUser(0,500);
  H18->SetLineColor(8);
  H18->Scale(1./H18->Integral());

  TH1D* H19 = H9->ProjectionY("H19",1,1);
  H19->GetXaxis()->SetRangeUser(0,500);
  H19->SetLineColor(46);
  H19->Scale(1./H19->Integral());

  H10->Draw();
  H11->Draw("same");
  H12->Draw("same");
  H13->Draw("same");
  H14->Draw("same");
  H15->Draw("same");
  H16->Draw("same");
  H17->Draw("same");
  H18->Draw("same");
  H19->Draw("same");

  auto legend = new TLegend(0.65,0.65,0.88,0.88);
  legend->SetHeader("Pileup","C"); // option "C" allows to center the header
  legend->AddEntry(H10,"0.5","l");
  legend->AddEntry(H11,"1","l");
  legend->AddEntry(H12,"1.5","l");
  legend->AddEntry(H13,"2","l");
  legend->AddEntry(H14,"10","l");
  legend->AddEntry(H15,"30","l");
  legend->AddEntry(H16,"50","l");
  legend->AddEntry(H17,"100","l");
  legend->AddEntry(H18,"140","l");
  legend->AddEntry(H19,"200","l");
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);

  legend->Draw();
 
  C->Print("/eos/user/a/asehrawa/1beta.gif");
}

