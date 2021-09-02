void linearity_fit(int option){

  //Make the fit graphs for all Rings and Disks
  TLatex label;
  label.SetTextSize(0.2);
  TF1* FitTEPXClustersPerEvent[20][4];
 


  for (int d = 0; d < disklist.size(); d++){
    for (int r = 0; r < 5; r++) {
      
      //fix the pads
      Int_t l = d * 5 + r + 1;
      
     TCanvas C("C");
     C.cd();

      //fit
      FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 200);
      FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
      TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
      
      
      
      //draw the fit graphs for all disks and rings
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetNdivisions(12);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetLabelSize(0.03);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetLabelSize(0.03);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetTitle("Pileup");
      TEPXClustersPerEvent[d][r]->SetMarkerStyle(21);
      TEPXClustersPerEvent[d][r]->SetMarkerSize(1);
      TEPXClustersPerEvent[d][r]->SetMarkerColor(2);
      gStyle->SetOptStat(1111);
      gStyle->SetOptFit(1111);
      gPad->SetGrid(1, 1);

      if (option == 1){
	

	TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of Clusters");
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 30);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetNdivisions(10);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
	TEPXClustersPerEvent[d][r]->Draw("ape");
	FitTEPXClustersPerEvent[d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r+ 1));
	char* histname = new char[10];
	sprintf(histname, "histo%d_linearity1.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath1 + "clusters_Fit/" + histname);
	
	
        FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
        TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 3000);
        TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
        char* histname1 = new char[10];
	sprintf(histname1, "histo%d_linearity4.gif", l);
        C.Update();
        C.Print(outputpath1 + "Extrapolation/" + histname1);


        TCanvas C1("C1");
	C1.cd();
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetNdivisions(10);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetLabelSize(0.03);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetMaxDigits(4);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetLineColor(2);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetRangeUser(-0.015, 0.015);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetNdivisions(12);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetLabelSize(0.04);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetRangeUser(0, 210);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetTitle("Pileup");
	NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerStyle(21);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerColor(2);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerSize(0.001);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetTitle("Disk 4 Ring 1");
	TLine* line1 = new TLine(0, 0, 210, 0);
	line1->SetLineColor(kBlack);

	gPad->SetGrid(1, 1);
	NonLinearity_TEPXClustersPerEvent[7][0]->Draw("ape");
	line1->Draw("same");
	
	C1.Print(outputpath1 + "AllPU_residuals/" + "NS1Brane.gif");
	C1.Clear();

	
        TCanvas C2("C");
        C2.cd();
	  for (int d = 0; d < disklist.size(); d++) {

	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetNdivisions(10);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetLabelSize(0.02);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetRangeUser(-0.015, 0.015);
	  
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetNdivisions(12);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetLabelSize(0.04);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetRangeUser(0, 210);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetTitle("Pileup");
      
	  NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerStyle(20);
	  NonLinearity_TEPXClustersPerEvent[d][0]->SetLineColor(1);
	  NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerSize(0);
	  if (d <= 3) {
            NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 4));
	  } else {
	    NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 3));
	  }

	  auto legend = new TLegend(0.7, 0.2, 0.8, 0.4);
	  NonLinearity_TEPXClustersPerEvent[d][0]->Draw("ape");
	  legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][0], TString(" Ring ") + 1, "l");
	  
	    for (int r = 1; r < 5; r++) {

	    NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
	    NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
	    legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1), "l");
	    }
      
	  TLine* line = new TLine(0, 0, 220, 0);
	  line->SetLineColor(kBlack);
	  line->Draw("same");
	  gPad->SetGrid(1, 1);
	  legend->SetFillColor(0);
	  legend->SetLineColor(0);
	  legend->SetFillColor(0);
	  legend->Draw("same");

	  C2.Print(outputpath1 + "AllPU_residuals/" + TString("Clusterdisk_") + d + ".gif");
	 }
        
      }
	

      if (option == 2){

	
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of 2x Coincidences");
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 500);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
	TEPXClustersPerEvent[d][r]->Draw("ape");
	FitTEPXClustersPerEvent[d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r + 1));
	char* histname = new char[10];
	sprintf(histname, "histo%d_linearity2.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath2 + "2xCoincidences_Fit/" + histname);
	
	
	FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
        TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 8);
        TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
        char* histname1 = new char[10];
	sprintf(histname1, "histo%d_linearity5.gif", l);
        C.Update();
        C.Print(outputpath2 + "Extrapolation/" + histname1);

	TCanvas C1("C1");
	C1.cd();
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetNdivisions(10);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetLabelSize(0.03);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetMaxDigits(4);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetRangeUser(-0.15, 0.15);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetNdivisions(12);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetLabelSize(0.04);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetRangeUser(0, 210);
	NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetTitle("Pileup");
	NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerStyle(21);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerColor(2);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerSize(0.6);
	NonLinearity_TEPXClustersPerEvent[7][0]->SetTitle("Disk 4 Ring 1");
	TLine* line1 = new TLine(0, 0, 210, 0);
	line1->SetLineColor(kBlack);

	gPad->SetGrid(1, 1);
	NonLinearity_TEPXClustersPerEvent[7][0]->Draw("ape");
	line1->Draw("same");

	C1.Print(outputpath2 + "AllPU_residuals/" + "NS2Brane.gif");
	C1.Clear();
	

	for (int d = 0; d < disklist.size(); d++) {

	  TCanvas C2("C2");
	  C2.cd();
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetNdivisions(10);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetLabelSize(0.02);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetRangeUser(-0.15, 0.15);
	  
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetNdivisions(12);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetLabelSize(0.04);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetRangeUser(0, 210);
	  NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetTitle("Pileup");
	  
	  NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerStyle(20);
	  NonLinearity_TEPXClustersPerEvent[d][0]->SetLineColor(1);
	  NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerSize(0);
	  
	  if (d <= 3) {
	    NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 4));
	  } else {
	    NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 3));
	  }

	  auto legend = new TLegend(0.7, 0.2, 0.8, 0.4);
	  NonLinearity_TEPXClustersPerEvent[d][0]->Draw("ape");
	  legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][0], TString(" Ring ") + 1, "l");
	  
	  for (int r = 1; r < 5; r++) {
	    
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
	    NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
	    legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1), "l");
	
	  }

	  TLine* line = new TLine(0, 0, 220, 0);
	  line->SetLineColor(kBlack);
	  line->Draw("same");
	  gPad->SetGrid(1, 1);
	  legend->SetFillColor(0);
	  legend->SetLineColor(0);
	  legend->SetFillColor(0);
	  legend->Draw("same");

	  C2.Print(outputpath2 + "AllPU_residuals/" + TString("2xCoincidencesdisk_") + d + ".gif");
	  
	}
      }
            
      if (option == 3){

	
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of 3x Coincidences");
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 80);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
	TEPXClustersPerEvent[d][r]->Draw("ape");
	FitTEPXClustersPerEvent[d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r + 1));
	char* histname = new char[10];
	sprintf(histname, "histo%d_linearity3.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath3 + "3xCoincidences_Fit/" + histname);
	
	
        FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
        TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 1.5);
        TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
        char* histname1 = new char[10];
	sprintf(histname1, "histo%d_linearity6.gif", l);
        C.Update();
        C.Print(outputpath3 + "Extrapolation/" + histname1);

	TCanvas C1("C1");
	C1.cd();
	NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetNdivisions(10);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetLabelSize(0.03);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
	NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetMaxDigits(4);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetRangeUser(-5, 5);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetNdivisions(12);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetLabelSize(0.04);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetRangeUser(0, 210);
	NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetTitle("Pileup");
	NonLinearity_TEPXClustersPerEvent[7][1]->SetMarkerStyle(21);
	NonLinearity_TEPXClustersPerEvent[7][1]->SetMarkerColor(2);
	NonLinearity_TEPXClustersPerEvent[7][1]->SetMarkerSize(0.6);
	NonLinearity_TEPXClustersPerEvent[7][1]->SetTitle("Disk 4 Ring 2");
	TLine* line1 = new TLine(0, 0, 210, 0);
	line1->SetLineColor(kBlack);

	gPad->SetGrid(1, 1);
	NonLinearity_TEPXClustersPerEvent[7][1]->Draw("ape");
	line1->Draw("same");

	C1.Print(outputpath3 + "AllPU_residuals/" + "NS3Brane.gif");
	C1.Clear();
	
	TCanvas C2("C2");
	C2.cd();
	
	for (int d = 0; d < disklist.size(); d++) {
	  
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetNdivisions(10);
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetLabelSize(0.02);
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetRangeUser(-50, 50);
	  
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetNdivisions(12);
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetLabelSize(0.04);
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetRangeUser(0, 210);
	  NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetTitle("Pileup");
	  
	  NonLinearity_TEPXClustersPerEvent[d][1]->SetMarkerStyle(20);
	  NonLinearity_TEPXClustersPerEvent[d][1]->SetLineColor(1);
	  NonLinearity_TEPXClustersPerEvent[d][1]->SetMarkerSize(0);
	  if (d <= 3) {
	    NonLinearity_TEPXClustersPerEvent[d][1]->SetTitle(TString("Disk ") + (d - 4));
	  } else {
	    NonLinearity_TEPXClustersPerEvent[d][1]->SetTitle(TString("Disk ") + (d - 3));
	  }
	  
	  auto legend = new TLegend(0.7, 0.2, 0.8, 0.4);
	  NonLinearity_TEPXClustersPerEvent[d][1]->Draw("ape");
	  legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][1], TString(" Ring ") + 2, "l");
      
	  for (int r = 2; r < 5; r++) {
	    
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
	    NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
	    legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1) , "l");
	  }
	  
	  TLine* line = new TLine(0, 0, 220, 0);
	  line->SetLineColor(kBlack);
	  line->Draw("same");
	  gPad->SetGrid(1, 1);
	  legend->SetFillColor(0);
	  legend->SetLineColor(0);
	  legend->SetFillColor(0);
	  legend->Draw("same");
	  
	  C2.Print(outputpath3 + "AllPU_residuals/" + TString("3xCoincidencesdisk_") + d + ".gif");

	}
      }              
    }
  }
}



