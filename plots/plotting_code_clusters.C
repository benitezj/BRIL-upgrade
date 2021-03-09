void plotting_code_clusters(){

TFile *f = new TFile("/home/ashish/BRIL-upgrade/tdrplots/TDRplotscluster.root","RECREATE");

  f->cd();
  gDirectory->pwd();
  f->ls();
  
  TString outputpath1 = "/home/ashish/TEPX_plot/Clusters/Extrapolation/";
  TString outputpath2 = "/home/ashish/TEPX_plot/Clusters/clusters_Fit/";  
  TString outputpath3 = "/home/ashish/TEPX_plot/Clusters/AllPU_residuals/";
  
  TString inpath = "/home/ashish/TEPX_rootfiles/samples_17Feb2020/";
  
  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
  
  //string containing names of input sample files
  std::vector<std::string> pulist = { "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {{ "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  std::vector<std::string> disklist = { "-4", "-3", "-2", "-1", "1", "2", "3", "4" };
  
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent[20][20]; //number of clusters vs pu
  TH2F* Histogram2D[20][20];
  
  for (int pu = 0; pu < pulist.size(); pu++) {
    for (int d = 0; d < disklist.size(); d++){
      for (int r = 0; r < 5; r++){
	
	TEPXClustersPerEvent[d][r] = new TGraphErrors();
      }
    }
  }
  
  //Non-linearity graphs
  TGraphErrors* NonLinearity_TEPXClustersPerEvent[20][20]; //number of clusters vs pu
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++) {
      NonLinearity_TEPXClustersPerEvent[d][r] = new TGraphErrors();
      
    }
  }
  
  
  
  //read the histograms
  TProfile* Prof_TEPXClustersPerEvent[20][20]; //array pu,disk
  for (int pu = 0; pu < pulist.size(); pu++) {
    TFile F(inpath + pulist[pu].c_str() + ".root", "read");
    gROOT->cd();
    
    
    for (int d = 0; d < disklist.size(); d++) {
      
      TString histoname = "BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";
      
      TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
      Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
      Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
      
      for (int r = 0; r < 5; r++) {
	
	TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1));
	TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1));
	
	
      }
    }
  }
  
  
  
  //Make the fit graphs for all Rings and Disks
  TLatex label;
  label.SetTextSize(0.2);
  TF1* FitTEPXClustersPerEvent[20][20];
  
  for (int d = 0; d < disklist.size(); d++) {
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
      
      
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of clusters");
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 3000);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetNdivisions(10);
      TEPXClustersPerEvent[d][r]->SetName(TString("TGraphErrorFit") + "D" + d + "R" + r + 1);
      TEPXClustersPerEvent[d][r]->Draw("ape");
      FitTEPXClustersPerEvent[d][r]->Draw("lsame");
      label.SetTextSize(0.1);
      label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r+ 1));
      char* histname = new char[40];
      sprintf(histname, "histo%d_linearity.png", l);
      cout << "==========================" << histname << endl;
      C.Print(outputpath1 + histname);
      f->WriteTObject(TEPXClustersPerEvent[d][r]);
      
      FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
      FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
      TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 30);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
      TEPXClustersPerEvent[d][r]->SetName(TString("TGraphErrorExtrapolation") + "D" + d + "R" + r + 1);
      char* histname1 = new char[40];
      sprintf(histname1, "histo%d_linearity1.gif", l);
      C.Update();
      C.Print(outputpath2 + histname1);
      f->WriteTObject(TEPXClustersPerEvent[d][r]);
    }
  }
  
  
  
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++) {
      for (int pu = 0; pu < pulist.size(); pu++) {
	
	
	float x = pumap[pulist[pu]];
	float y = (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	float yerr = (Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1)) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	
        
	if (pu > 2) {
	  
	  
	  //NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x -(r-2), y);
          NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	  NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	} else {
	  
	  
	  NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	  NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	  
	}
      }
    }
  }  
  
  
  
  TCanvas C1("C1");
  C1.cd();
  
  NonLinearity_TEPXClustersPerEvent[0][0]->GetYaxis()->SetNdivisions(10);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetYaxis()->SetLabelSize(0.03);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
  NonLinearity_TEPXClustersPerEvent[0][0]->GetYaxis()->SetMaxDigits(4);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetXaxis()->SetNdivisions(12);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetXaxis()->SetLabelSize(0.04);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetXaxis()->SetRangeUser(0, 210);
  NonLinearity_TEPXClustersPerEvent[0][0]->GetXaxis()->SetTitle("Pileup");
  NonLinearity_TEPXClustersPerEvent[0][0]->SetMarkerStyle(21);
  NonLinearity_TEPXClustersPerEvent[0][0]->SetMarkerColor(2);
  NonLinearity_TEPXClustersPerEvent[0][0]->SetMarkerSize(0);
  NonLinearity_TEPXClustersPerEvent[0][0]->SetLineColor(2);
  NonLinearity_TEPXClustersPerEvent[0][0]->SetTitle("Side 1 Disk 4 Ring 1");
  NonLinearity_TEPXClustersPerEvent[0][0]->SetName("Side 1 Disk 4 Ring 1");
  TLine* line1 = new TLine(0, 0, 210, 0);
  line1->SetLineColor(kBlack);
  
  gPad->SetGrid(1, 1);
  NonLinearity_TEPXClustersPerEvent[0][0]->Draw("ape");
  line1->Draw("same");
  
  TLine* line = new TLine(0, -0.01, 210, -0.01);
  line->SetLineColor(kBlack);
  line->SetLineStyle(9);
  line->Draw("same");
  
  TLine* line2 = new TLine(0, 0.01, 210, 0.01);
  line2->SetLineColor(kBlack);
  line2->SetLineStyle(9);
  line2->Draw("same");
  
  C1.Print(outputpath3 + "Cluster_residualD4R1(-Z).gif");
  C1.Clear();


  TCanvas C4("C4");
  C4.cd();
  
  NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetNdivisions(10);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetLabelSize(0.03);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
  NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetMaxDigits(4);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetNdivisions(12);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetLabelSize(0.04);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetRangeUser(0, 210);
  NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetTitle("Pileup");
  NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerStyle(21);
  NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerColor(2);
  NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerSize(0);
  NonLinearity_TEPXClustersPerEvent[7][0]->SetLineColor(2);
  NonLinearity_TEPXClustersPerEvent[7][0]->SetTitle("Side 2 Disk 4 Ring 1");
  NonLinearity_TEPXClustersPerEvent[7][0]->SetName("Side 2 Disk 4 Ring 1");
  TLine* line3 = new TLine(0, 0, 210, 0);
  line3->SetLineColor(kBlack);
  
  gPad->SetGrid(1, 1);
  NonLinearity_TEPXClustersPerEvent[7][0]->Draw("ape");
  line3->Draw("same");
  
  TLine* line4 = new TLine(0, -0.01, 210, -0.01);
  line4->SetLineColor(kBlack);
  line4->SetLineStyle(9);
  line4->Draw("same");
  
  TLine* line5 = new TLine(0, 0.01, 210, 0.01);
  line5->SetLineColor(kBlack);
  line5->SetLineStyle(9);
  line5->Draw("same");
  
  C4.Print(outputpath3 + "Cluster_residualD4R1(+Z).gif");
  C4.Clear();



  TCanvas C2("C2");
  C2.cd();
  
  
  for (int d = 0; d < disklist.size(); d++) {
    
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetNdivisions(10);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
    
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetNdivisions(12);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetRangeUser(0, 210);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetTitle("Pileup");
    
    NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerStyle(20);
    NonLinearity_TEPXClustersPerEvent[d][0]->SetLineColor(1);
    NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerSize(0);
    NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d + 1));
    
    if (d <= 3) {
      NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 4));
    } else {
      NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 3));
    }
    
    auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
    NonLinearity_TEPXClustersPerEvent[d][0]->Draw("ape");
    legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][0], TString(" Ring ") + 1, "l");
    
    for (int r = 1; r < 5; r++) {
      
      NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetName(TString("TGraphErrorResidual") + "D" + d + "R" + (r + 1));
      NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
      legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1), "l");
      
    
    

    TLine* line = new TLine(0, 0, 220, 0);
    line->SetLineColor(kBlack);
    
    
    TLine* line1 = new TLine(0, -0.01, 210, -0.01);
    line1->SetLineColor(kBlack);
    line1->SetLineStyle(9);
    

    TLine* line2 = new TLine(0, 0.01, 210, 0.01);
    line2->SetLineColor(kBlack);
    line2->SetLineStyle(9);

    line->Draw("same");
    line1->Draw("same");
    line2->Draw("same");
    
    gPad->SetGrid(1, 1);
    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetFillColor(0);
    legend->Draw("same");

    C2.Print(outputpath3 + TString("Cluster_residuals") + d + ".gif");
    f->WriteTObject(NonLinearity_TEPXClustersPerEvent[d][r]);

    }
  }
}

