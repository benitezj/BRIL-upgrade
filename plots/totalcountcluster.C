void totalcountcluster(){

 TFile *f = new TFile("/home/ashish/BRIL-upgrade/tdrplots/TDRplotsclustertotal.root","RECREATE");

  f->cd();
  gDirectory->pwd();
  f->ls();
  
  TString outputpath1 = "/home/ashish/TEPX_plot/Clusters/Extrapolation/";
  TString outputpath2 = "/home/ashish/TEPX_plot/Clusters/clusters_Fit/";  
  TString outputpath3 = "/home/ashish/TEPX_plot/Clusters/AllPU_residuals/";
  
  TString inpath = "/home/ashish/TEPX_rootfiles/samples_17Feb2020/";
  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
  
  //string containing names of input sample files
  std::vector<std::string> pulist = {//"2023D42noPU" , 
    "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {//{ "2023D42noPU", 0 },
    { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  std::vector<std::string> disklist = { "-4", "-3", "-2", "-1", "1", "2", "3", "4" };
  //std::vector<std::string> sidelist = { "1", "2" };
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent; //number of clusters vs pu
  TGraphErrors* TEPXClustersPerEvent1[20][20]; 
  TH2F* Histogram2D[20][20];
  
  //Non-linearity graphs
  TGraphErrors* NonLinearity_TEPXClustersPerEvent; //number of clusters vs pu 
  NonLinearity_TEPXClustersPerEvent = new TGraphErrors();
  
  for (int pu = 0; pu < pulist.size(); pu++) {
      for (int d = 0; d < disklist.size(); d++){
	for (int r = 0; r < 5; r++){
	  
	  TEPXClustersPerEvent = new TGraphErrors();
          TEPXClustersPerEvent1[d][r] = new TGraphErrors();
	}
      }
    
    
    //read the histograms
    TProfile* Prof_TEPXClustersPerEvent[20][20]; //array pu,disk
    for (int pu = 0; pu < pulist.size(); pu++) {
      
      TFile F(inpath + pulist[pu].c_str() + ".root", "read");
      gROOT->cd();
      
      float totalcount=0;
      float totalcounterror=0;
      float totalcounterror1=0;
      
      
	for (int d = 0; d < disklist.size(); d++) {
	  
	  TString histoname = "BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";
	  
	  TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	  Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
	  Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	  
	  for (int r = 0; r < 5; r++) {
	    
	    float count = Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1);
	    float counterror = Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1);
	    
	    TEPXClustersPerEvent1[d][r]->SetPoint(pu, pumap[pulist[pu]], count);
	    TEPXClustersPerEvent1[d][r]->SetPointError(pu, 0, counterror);
	    
	    totalcount+=count;
	    totalcounterror+= counterror * counterror;
	    
	  }   
	}
      
      
      totalcounterror1 = sqrt(totalcounterror);
      //cout << totalcounterror1 << endl;
      
      TCanvas C("C");
      C.cd();
      
      TEPXClustersPerEvent->SetPoint(pu, pumap[pulist[pu]], totalcount);
      TEPXClustersPerEvent->SetPointError(pu, 0, totalcounterror1);
      
      //cout << totalcount << endl;
      
      Int_t l = 1;
      
      TF1* FitTEPXClustersPerEvent;
      
      FitTEPXClustersPerEvent = new TF1(TString("Fit_"), "[0]+[1]*x", 0.5, 200);
      
      FitTEPXClustersPerEvent->SetLineColor(4);
      TEPXClustersPerEvent->Fit(FitTEPXClustersPerEvent, "", "", 0.5, 2);
      
      TEPXClustersPerEvent->GetXaxis()->SetNdivisions(12);
      TEPXClustersPerEvent->GetYaxis()->SetNdivisions(12);
      TEPXClustersPerEvent->GetYaxis()->SetLabelSize(0.03);
      TEPXClustersPerEvent->GetXaxis()->SetLabelSize(0.03);
      TEPXClustersPerEvent->GetXaxis()->SetTitle("Pileup");
      TEPXClustersPerEvent->SetMarkerStyle(21);
      TEPXClustersPerEvent->SetMarkerSize(1);
      TEPXClustersPerEvent->SetMarkerColor(2);
      gStyle->SetOptStat(1111);
      gStyle->SetOptFit(1111);
      gPad->SetGrid(1, 1);
      
      
      TEPXClustersPerEvent->GetYaxis()->SetTitle("Mean Number of clusters");
      TEPXClustersPerEvent->GetYaxis()->SetRangeUser(0, 100000);
      TEPXClustersPerEvent->GetXaxis()->SetRangeUser(0, 210);
      TEPXClustersPerEvent->SetName(TString("TGraphErrorExtrapolation"));
      TEPXClustersPerEvent->Draw("ape");
      FitTEPXClustersPerEvent->Draw("lsame");
      char* histname1 = new char[2];
      sprintf(histname1, "histo%d_linearity1.gif", l);
      C.Print(outputpath1 + histname1);
      f->WriteTObject(TEPXClustersPerEvent);
	
      FitTEPXClustersPerEvent = new TF1(TString("Fit_"), "[0]+[1]*x", 0.5, 2);
      FitTEPXClustersPerEvent->SetLineColor(4);
      TEPXClustersPerEvent->Fit(FitTEPXClustersPerEvent, "", "", 0.5, 2);
      TEPXClustersPerEvent->GetYaxis()->SetRangeUser(0, 1000);
      TEPXClustersPerEvent->GetXaxis()->SetRangeUser(0, 2);
      TEPXClustersPerEvent->SetName(TString("TGraphErrorFit"));
      char* histname2 = new char[2];
      sprintf(histname2, "histo%d_linearity2.gif", l);
      C.Update();
      C.Print(outputpath2 + histname2);
      f->WriteTObject(TEPXClustersPerEvent);     

      TCanvas c1("c1");
      c1.cd(); 
      
      TLatex label;
      label.SetTextSize(0.2);
      
      
      NonLinearity_TEPXClustersPerEvent->SetPoint(pu, pumap[pulist[pu]], (totalcount - FitTEPXClustersPerEvent->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent->Eval(pumap[pulist[pu]]));
      NonLinearity_TEPXClustersPerEvent->SetPointError(pu, 0, (totalcounterror1) / FitTEPXClustersPerEvent->Eval(pumap[pulist[pu]]));
      
      NonLinearity_TEPXClustersPerEvent->GetYaxis()->SetNdivisions(10);
      NonLinearity_TEPXClustersPerEvent->GetYaxis()->SetLabelSize(0.04);
      NonLinearity_TEPXClustersPerEvent->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
      NonLinearity_TEPXClustersPerEvent->GetYaxis()->SetRangeUser(-0.05, 0.05);
      
      NonLinearity_TEPXClustersPerEvent->GetXaxis()->SetNdivisions(12);
      NonLinearity_TEPXClustersPerEvent->GetXaxis()->SetLabelSize(0.04);
      NonLinearity_TEPXClustersPerEvent->GetXaxis()->SetRangeUser(0, 210);
      NonLinearity_TEPXClustersPerEvent->GetXaxis()->SetTitle("Pileup");
      
      NonLinearity_TEPXClustersPerEvent->SetMarkerStyle(20);
      NonLinearity_TEPXClustersPerEvent->SetLineColor(2);
      NonLinearity_TEPXClustersPerEvent->SetMarkerSize(0);
      NonLinearity_TEPXClustersPerEvent->SetTitle(TString("Cluster residuals"));
      NonLinearity_TEPXClustersPerEvent->SetName(TString("total cluster residual"));
      NonLinearity_TEPXClustersPerEvent->Draw("ape");
      
      gPad->SetGrid(1, 1);
      
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
      
      c1.Print(outputpath3 + TString("totalcount_clusterresidual") +  ".png");
      f->WriteTObject(NonLinearity_TEPXClustersPerEvent);
      
    }
  }  
}

//cout << "side " << s <<" pileup " << pu << " disk " << d << " ring " << r << " " << " Bin Content "<< Prof_TEPXClustersPerEvent[s][pu][d]->GetBinContent(r + 1) << endl;

