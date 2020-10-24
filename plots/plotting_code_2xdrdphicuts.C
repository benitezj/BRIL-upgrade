void plotting_code_2xdrdphicuts(){
  
  
  TString outputpath1 = "/home/ashish/TEPX_plot/2x Coincidences/2xCoincidences_Fit/";
  TString outputpath2 = "/home/ashish/TEPX_plot/2x Coincidences/Extrapolation/";
  TString outputpath3 = "/home/ashish/TEPX_plot/2x Coincidences/AllPU_residuals/";
  
  TString inpath = "/home/ashish/Desktop/23rdOct2020/TEPX/samples_23rdOctober2020_drdphicuts/";
  
  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
  
  //string containing names of input sample files
  std::vector<std::string> pulist = {"2023D42noPU" , "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {{ "2023D42noPU", 0 }, { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  std::vector<std::string> disklist = { "1", "2", "3", "4" };
  std::vector<std::string> sidelist = { "1", "2" };
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent[20][20][20]; //number of clusters vs pu
  TH2F* Histogram2D[20][20][20];
  
  for (int pu = 0; pu < pulist.size(); pu++) {
    for (int s = 0; s < sidelist.size(); s++){
      for (int d = 0; d < disklist.size(); d++){
	for (int r = 0; r < 5; r++){
	  
	  TEPXClustersPerEvent[s][d][r] = new TGraphErrors();
	}
      }
    }
  }
  
  //Non-linearity graphs
  TGraphErrors* NonLinearity_TEPXClustersPerEvent[20][20][20]; //number of clusters vs pu
  
  for (int s = 0; s < sidelist.size(); s++) {
    for (int d = 0; d < disklist.size(); d++) {
      for (int r = 0; r < 5; r++) {
	
	NonLinearity_TEPXClustersPerEvent[s][d][r] = new TGraphErrors();
	
      }
    }
  }
  
  
  //read the histograms
  TProfile* Prof_TEPXClustersPerEvent[20][20][20]; //array pu,disk
  for (int pu = 0; pu < pulist.size(); pu++) {
    TFile F(inpath + pulist[pu].c_str() + ".root", "read");
    gROOT->cd();
    
    for (int s = 0; s < sidelist.size(); s++) {
      for (int d = 0; d < disklist.size(); d++) {
	
	TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_side";
	
	TH2F* H = (TH2F*)F.Get(histoname + sidelist[s].c_str() + "_Disk" + disklist[d].c_str());
	Histogram2D[s][pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
	Prof_TEPXClustersPerEvent[s][pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	
	for (int r = 0; r < 5; r++) {
	  
	  TEPXClustersPerEvent[s][d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[s][pu][d]->GetBinContent(r + 1));
	  TEPXClustersPerEvent[s][d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[s][pu][d]->GetBinError(r + 1));
	  
	}
      }
    }
  }
  
  
  
  //Make the fit graphs for all Rings and Disks
  TLatex label;
  label.SetTextSize(0.2);
  TF1* FitTEPXClustersPerEvent[20][20][20];
  
  for (long s = 0; s < sidelist.size(); s++) {
    for (long d = 0; d < disklist.size(); d++) {
      for (long r = 0; r < 5; r++) {
	
	//fix the pads
	Int_t l = s * 20 + d * 5 + r + 1;
	TCanvas C("C");
	C.cd();
      
	//fit
	FitTEPXClustersPerEvent[s][d][r] = new TF1(TString("Fit_") + s + "_"+ d + "_" + r, "[0]+[1]*x", 0.5, 200);
	FitTEPXClustersPerEvent[s][d][r]->SetLineColor(4);
	TEPXClustersPerEvent[s][d][r]->Fit(FitTEPXClustersPerEvent[s][d][r], "", "", 0.5, 2);
	
	
	
	//draw the fit graphs for all disks and rings
	TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetNdivisions(12);
	TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetLabelSize(0.03);
	TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetLabelSize(0.03);
	TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetTitle("Pileup");
	TEPXClustersPerEvent[s][d][r]->SetMarkerStyle(21);
	TEPXClustersPerEvent[s][d][r]->SetMarkerSize(1);
	TEPXClustersPerEvent[s][d][r]->SetMarkerColor(2);
	gStyle->SetOptStat(1111);
	gStyle->SetOptFit(1111);
	gPad->SetGrid(1, 1);
	
	
	TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetTitle("Mean Number of 2x Coincidences");
	TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetRangeUser(0, 300);
	TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetRangeUser(0, 210);
	TEPXClustersPerEvent[s][d][r]->Draw("ape");
	FitTEPXClustersPerEvent[s][d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d + 1) + ",  R=" + (long)(r + 1) + ", S=" + long(s + 1));
	char* histname = new char[40];
	sprintf(histname, "histo%d_linearity.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath2 + histname);
	
	
	FitTEPXClustersPerEvent[s][d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[s][d][r]->SetLineColor(4);
        TEPXClustersPerEvent[s][d][r]->Fit(FitTEPXClustersPerEvent[s][d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetRangeUser(0, 5);
        TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetRangeUser(0, 2);
        char* histname1 = new char[40];
	sprintf(histname1, "histo%d_linearity1.gif", l);
        C.Update();
        C.Print(outputpath1 + histname1);
	
      }
    }
  }
  
for (int s = 0; s < sidelist.size(); s++) {
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++) {
      for (int pu = 0; pu < pulist.size(); pu++) {
	
	
	float x = pumap[pulist[pu]];
	float y = (Prof_TEPXClustersPerEvent[s][pu][d]->GetBinContent(r + 1) - FitTEPXClustersPerEvent[s][d][r]->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent[s][d][r]->Eval(pumap[pulist[pu]]);
	float yerr = (Prof_TEPXClustersPerEvent[s][pu][d]->GetBinError(r + 1)) / FitTEPXClustersPerEvent[s][d][r]->Eval(pumap[pulist[pu]]);
	
        
	if (pu > 2) {
	  
	  
	  NonLinearity_TEPXClustersPerEvent[s][d][r]->SetPoint(pu, x -(r-2), y);
	  NonLinearity_TEPXClustersPerEvent[s][d][r]->SetPointError(pu, 0, yerr);
	} else {
	  
	  
	  NonLinearity_TEPXClustersPerEvent[s][d][r]->SetPoint(pu, x, y);
	  NonLinearity_TEPXClustersPerEvent[s][d][r]->SetPointError(pu, 0, yerr);
	  
	}
      }
    }
  }
 }
 
 
 TCanvas C1("C1");
 C1.cd();
 
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetYaxis()->SetNdivisions(10);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetYaxis()->SetLabelSize(0.03);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetYaxis()->SetMaxDigits(4);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetXaxis()->SetNdivisions(12);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetXaxis()->SetLabelSize(0.04);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetXaxis()->SetRangeUser(0, 210);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->GetXaxis()->SetTitle("Pileup");
 NonLinearity_TEPXClustersPerEvent[1][3][0]->SetMarkerStyle(21);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->SetMarkerColor(2);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->SetMarkerSize(1);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->SetTitle("Side 2 Disk 4 Ring 1");
 TLine* line1 = new TLine(0, 0, 210, 0);
 line1->SetLineColor(kBlack);
 
 gPad->SetGrid(1, 1);
 NonLinearity_TEPXClustersPerEvent[1][3][0]->Draw("ape");
 line1->Draw("same");
 
 C1.Print(outputpath3 + "NS2Brane.gif");
 C1.Clear();
 
 
 TCanvas C2("C2");
 C2.cd();
 
 for (int s = 0; s < sidelist.size(); s++) {
   for (int d = 0; d < disklist.size(); d++) {
     
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetYaxis()->SetNdivisions(10);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetYaxis()->SetLabelSize(0.02);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
     
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetXaxis()->SetNdivisions(12);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetXaxis()->SetLabelSize(0.04);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetXaxis()->SetRangeUser(0, 210);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetXaxis()->SetTitle("Pileup");
     
     NonLinearity_TEPXClustersPerEvent[s][d][0]->SetMarkerStyle(20);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->SetLineColor(1);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->SetMarkerSize(0);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->SetTitle(TString("Disk ") + (d + 1) + TString(" Side ") + (s + 1));
     
     auto legend = new TLegend(0.8, 0.2, 0.9, 0.4);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->Draw("ape");
     legend->AddEntry(NonLinearity_TEPXClustersPerEvent[s][d][0], TString(" Ring ") + 1, "l");
     
     for (int r = 1; r < 5; r++) {
       
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetMarkerStyle(20);
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetLineColor(r + 1);
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetMarkerSize(0);
       NonLinearity_TEPXClustersPerEvent[s][d][r]->Draw("pesame");
       legend->AddEntry(NonLinearity_TEPXClustersPerEvent[s][d][r], TString(" Ring ") + (r + 1), "l");
       
     }
     
     TLine* line = new TLine(0, 0, 220, 0);
     line->SetLineColor(kBlack);
     line->Draw("same");
     gPad->SetGrid(1, 1);
     legend->SetFillColor(0);
     legend->SetLineColor(0);
     legend->SetFillColor(0);
     legend->Draw("same");
     
     C2.Print(outputpath3 + TString("2xCoincidencesdisk_") + d + s + ".gif");
     
   }
 }
}
