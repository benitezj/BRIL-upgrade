

void OT_cabling_map(){

  TFile FInput("OT_L6Cabling.root","read"); //file from Georg with 2D histogram mapping module to DTC id

  TH2D * HInput = (TH2D*)FInput.Get("hist");

  TH1F HModulesPerDTC("HModulesPerDTC","",36,0.5,36.5);
  TH1F HLaddersPerDTC("HLaddersPerDTC","",36,0.5,36.5);

  TGraph GDTCvsLadder;
  int GDTCvsLadder_counter=0;
  
  for(Int_t i=1;i<=22;i++){
    for(Int_t j=1;j<=76;j++){
      //if(i==21) cout<<i<<" "<<j<<" "<<HInput->GetBinContent(i,j)<<endl;
      
      int dtc=HInput->GetBinContent(i,j);
      
      HModulesPerDTC.Fill(dtc);
      if(i==1||i==13) HLaddersPerDTC.Fill(dtc);

      if(i==22){
	GDTCvsLadder.SetPoint(GDTCvsLadder_counter,j,dtc);
	GDTCvsLadder_counter++;
      }
    }
  }


  TCanvas C("C");
  gStyle->SetOptStat(0);

  
  C.Clear();
  HModulesPerDTC.Draw("histp");
  C.Print("OT_cabling_map_HModulesPerDTC.pdf");

  C.Clear();
  HLaddersPerDTC.GetYaxis()->SetRangeUser(0,7);
  HLaddersPerDTC.GetYaxis()->SetTitle("Number of Ladders");
  HLaddersPerDTC.GetXaxis()->SetTitle("DTC id");
  HLaddersPerDTC.Draw("histtext");
  C.Print("OT_cabling_map_HLaddersPerDTC.pdf");

  C.Clear();
  GDTCvsLadder.SetMarkerStyle(8);
  GDTCvsLadder.SetMarkerSize(0.5);
  GDTCvsLadder.GetYaxis()->SetTitle("DTC id");
  GDTCvsLadder.GetXaxis()->SetTitle("Ladder id");
  GDTCvsLadder.Draw("ap");
  C.Print("OT_cabling_map_GDTCvsLadder.pdf");
}
