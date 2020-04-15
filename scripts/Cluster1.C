void Cluster1() {

  TFile*f = new TFile("/eos/user/a/asehrawa/TEPX/samples_17Feb2020/2023D42PU10.root");

  TCanvas*C = new TCanvas("Clusters","");


  TH2F * H1 = NULL;
  TH2F * H2 = NULL;
  TH2F * H3 = NULL;
  TH2F * H4 = NULL;
  TH2F * H5 = NULL;
  TH2F * H6 = NULL;
  TH2F * H7 = NULL;
  TH2F * H8 = NULL;
  TH2F * H9 = NULL;

  H1 = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk 4");
  
  if (H1==NULL){
    return;
  }

  TH1 * P1 = H1->ProjectionY("P1",1,1);
  P1->SetLineColor(1);
  P1->GetXaxis()->SetRangeUser(0,300);
  P1->GetYaxis()->SetRangeUser(0,500);
  gStyle->SetOptStat(0);

  TH1 * P2 = H1->ProjectionY("P2",2,2);


  P2->SetLineColor(2);

 
  TH1 * P3 = H1->ProjectionY("P3",3,3);

  P3->SetLineColor(3);
 
  TH1 * P4 = H1->ProjectionY("P4",4,4);
  P4->SetLineColor(4);
  

  TH1 * P5 = H1->ProjectionY("P5",5,5);
  P5->SetLineColor(6);

  P1->Draw("same");
  P2->Draw("same");
  P3->Draw("same");
  P4->Draw("same");
  P5->Draw("same");



  auto legend = new TLegend(0.6,0.6,0.6,0.6);
  legend->SetHeader("1D Histograms of Number of Clusters","C"); // option "C" allows to center the header                                                                  
  legend->AddEntry(P1,"Ring 1","l");
  legend->AddEntry(P2,"Ring 2","l");
  legend->AddEntry(P3,"Ring 3","l");
  legend->AddEntry(P4,"Ring 4","l");
  legend->AddEntry(P5,"Ring 5","l");
  legend->SetFillColor(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);

  legend->Draw();

  C->Print("/eos/user/a/asehrawa/1alpha.gif");
}

