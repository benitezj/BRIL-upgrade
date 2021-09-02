void plotting_code_2xinR(){

  TFile *f = new TFile("/home/ashish/BRIL-upgrade/tdrplots/TDRplots2xinR.root","RECREATE");

  f->cd();
  gDirectory->pwd();
  f->ls();
  
  TString outputpath1 = "/2xinRCoincidences/Extrapolation/";
  TString outputpath2 = "./2xinRCoincidences/2xCoincidences_Fit/";  
  TString outputpath3 = "./2xinRCoincidences/AllPU_residuals/";
  
     TString inpath = "/eos/user/a/asehrawa/TEPX/2xresults_all";
  //TString inpath = "/home/ashish/Desktop/2xresults_all/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/24thOct2020/TEPX/samples_24thOctober2020_drdphicuts/";
  ///TString inpath = "/home/ashish/Desktop/30thNov2020_drdphicuts_1sigma/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/2xcombined_3dphi_2dr/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/2xinR_2sigmadr_2sigmadphi/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/1stDec2020_drdphicuts_3sigma/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/3sigma_new/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/1sigma_lxbatch-new/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/3sigma_lxbatch-new/TEPX/samples_17Feb2020/";
  
  
  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
  
  //string containing names of input sample files
  std::vector<std::string> pulist = {//"2023D42noPU" , 
    "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {//{ "2023D42noPU", 0 },
    { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
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
	
        //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_Inphi_side";
	//TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_InR_side";
        //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencess_InR_side";        
        TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_InR_side";
        //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_side";
	
	TH2F* H = (TH2F*)F.Get(histoname + sidelist[s].c_str() + "_Disk" + disklist[d].c_str());
	Histogram2D[s][pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
	Prof_TEPXClustersPerEvent[s][pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	
	for (int r = 0; r < 5; r++) {
	  
	  TEPXClustersPerEvent[s][d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[s][pu][d]->GetBinContent(r + 1));
          TEPXClustersPerEvent[s][d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[s][pu][d]->GetBinError(r + 1));
	  

	  //cout << "side " << s <<" pileup " << pu << " disk " << d << " ring " << r << " " << " Bin Content "<< Prof_TEPXClustersPerEvent[s][pu][d]->GetBinContent(r + 1) << endl;
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
	TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetRangeUser(0, 100);
	TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetRangeUser(0, 210);
        TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetNdivisions(10);
        TEPXClustersPerEvent[s][d][r]->SetName(TString("TGraphErrorExtrapolation") + "S" + s + "D" + d + "R" + r + 1);
	TEPXClustersPerEvent[s][d][r]->Draw("ape");
	FitTEPXClustersPerEvent[s][d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d + 1) + ",  R=" + (long)(r + 1) + ", S=" + long(s + 1));
	char* histname = new char[40];
	sprintf(histname, "histo%d_linearity2xinR.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath1 + histname);
	f->WriteTObject(TEPXClustersPerEvent[s][d][r]);
	
	FitTEPXClustersPerEvent[s][d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[s][d][r]->SetLineColor(4);
        TEPXClustersPerEvent[s][d][r]->Fit(FitTEPXClustersPerEvent[s][d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[s][d][r]->GetYaxis()->SetRangeUser(0, 5);
        TEPXClustersPerEvent[s][d][r]->GetXaxis()->SetRangeUser(0, 2);
        TEPXClustersPerEvent[s][d][r]->SetName(TString("TGraphErrorFit") + "S" + s + "D" + d + "R" + r + 1);
        char* histname1 = new char[40];
	sprintf(histname1, "histo%d_linearity12xinR.gif", l);
        C.Update();
        C.Print(outputpath2 + histname1);
	f->WriteTObject(TEPXClustersPerEvent[s][d][r]);

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
	    
	    
	    //NonLinearity_TEPXClustersPerEvent[s][d][r]->SetPoint(pu, x -(r-2), y);
	    NonLinearity_TEPXClustersPerEvent[s][d][r]->SetPoint(pu, x, y);
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
  
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetYaxis()->SetNdivisions(10);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetYaxis()->SetLabelSize(0.03);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetYaxis()->SetMaxDigits(4);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetYaxis()->SetRangeUser(-0.05, 0.05);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetXaxis()->SetNdivisions(12);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetXaxis()->SetLabelSize(0.04);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetXaxis()->SetRangeUser(0, 210);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->GetXaxis()->SetTitle("Pileup");
  NonLinearity_TEPXClustersPerEvent[0][3][0]->SetMarkerStyle(21);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->SetMarkerColor(0);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->SetLineColor(2);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->SetMarkerSize(0);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->SetName("Disk4Ring1(-Z)");
  NonLinearity_TEPXClustersPerEvent[0][3][0]->SetTitle("Disk4Ring1(-Z)");
  TLine* line1 = new TLine(0, 0, 210, 0);
  line1->SetLineColor(kBlack);
  
  gPad->SetGrid(1, 1);
  NonLinearity_TEPXClustersPerEvent[0][3][0]->Draw("ape");
  line1->Draw("same");
  
  TLine* line = new TLine(0, -0.01, 210, -0.01);
  line->SetLineColor(kBlack);
  line->SetLineStyle(9);
  line->Draw("same");
  
  TLine* line2 = new TLine(0, 0.01, 210, 0.01);
  line2->SetLineColor(kBlack);
  line2->SetLineStyle(9);
  line2->Draw("same");
  
  C1.Print(outputpath3 + "2xinR_D4R1 (-Z).gif");
  f->WriteTObject(NonLinearity_TEPXClustersPerEvent[0][3][0]);
  C1.Clear();



  TCanvas C4("C4");
  C4.cd();
  
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
  NonLinearity_TEPXClustersPerEvent[1][3][0]->SetMarkerColor(0);
  NonLinearity_TEPXClustersPerEvent[1][3][0]->SetLineColor(2);
  NonLinearity_TEPXClustersPerEvent[1][3][0]->SetMarkerSize(0);
  NonLinearity_TEPXClustersPerEvent[1][3][0]->SetName("Disk4Ring1(+Z)");
  NonLinearity_TEPXClustersPerEvent[1][3][0]->SetTitle("Disk4Ring1(+Z)");
  TLine* line3 = new TLine(0, 0, 210, 0);
  line3->SetLineColor(kBlack);
  
  gPad->SetGrid(1, 1);
  NonLinearity_TEPXClustersPerEvent[1][3][0]->Draw("ape");
  line3->Draw("same");
  
  TLine* line4 = new TLine(0, -0.01, 210, -0.01);
  line4->SetLineColor(kBlack);
  line4->SetLineStyle(9);
  line4->Draw("same");
  
  TLine* line5 = new TLine(0, 0.01, 210, 0.01);
  line5->SetLineColor(kBlack);
  line5->SetLineStyle(9);
  line5->Draw("same");
  
  C1.Print(outputpath3 + "2xinR_D4R1 (+Z).gif");
  f->WriteTObject(NonLinearity_TEPXClustersPerEvent[1][3][0]);
  C1.Clear();



  
  
  TCanvas C2("C2");
  C2.cd();
  
 for (int s = 0; s < sidelist.size(); s++) {
   for (int d = 0; d < disklist.size(); d++) {
     
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetYaxis()->SetNdivisions(10);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->GetYaxis()->SetLabelSize(0.04);
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
     //NonLinearity_TEPXClustersPerEvent[s][d][0]->SetTitle(TString("Disk ") + (d + 1) + TString(" Side ") + (s + 1) + TString(" (2xinphi & 2xinR)"));

     
     auto legend = new TLegend(0.7, 0.7, 0.9, 0.9);
     NonLinearity_TEPXClustersPerEvent[s][d][0]->Draw("ape");
     legend->AddEntry(NonLinearity_TEPXClustersPerEvent[s][d][0], TString(" Ring ") + 1, "l");
     
     for (int r = 1; r < 4; r++) {
       
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetMarkerStyle(20);
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetLineColor(r + 1);
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetMarkerSize(0);
       NonLinearity_TEPXClustersPerEvent[s][d][r]->SetName(TString("TGraphErrorResidual") + "S" + s + "D" + d + "R" + (r + 1));
       NonLinearity_TEPXClustersPerEvent[s][d][r]->Draw("pesame");
       legend->AddEntry(NonLinearity_TEPXClustersPerEvent[s][d][r], TString(" Ring ") + (r + 1), "l");
       f->WriteTObject(NonLinearity_TEPXClustersPerEvent[s][d][r]);

     }
     
     TLine* line = new TLine(0, 0, 210, 0);
     line->SetLineColor(kBlack);
     line->Draw("same");
     
     TLine* line1 = new TLine(0, -0.01, 210, -0.01);
     line1->SetLineColor(kBlack);
     line1->SetLineStyle(9);
     line1->Draw("same");
     
     TLine* line2 = new TLine(0, 0.01, 210, 0.01);
     line2->SetLineColor(kBlack);
     line2->SetLineStyle(9);
     line2->Draw("same");
     
     
     gPad->SetGrid(1, 1);
     legend->SetFillColor(0);
     legend->SetLineColor(0);
     legend->SetFillColor(0);
     legend->Draw("same");
     
     C2.Print(outputpath3 + TString("2xCoincidencesdisk_2xinR") + d + s + ".gif");
     
   }
 }
}
