#include<stdio.h>
#include<math.h>
#include<vector>
#include<stdlib.h>
#include<string.h>

TString outputpath1 = "/home/ashish/TEPX_plot/Clusters/";
TString outputpath2 = "/home/ashish/TEPX_plot/2x Coincidences/";
TString outputpath3 = "/home/ashish/TEPX_plot/3x Coincidences/";

TString inpath = "/home/ashish/Desktop/TEPX_0.05new/samples_17Feb2020/";

//gROOT->ProcessLine(".x /home/ashish/rootlogon.C");

//string containing names of input sample files
std::vector<std::string> pulist = { "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
std::map<std::string, float> pumap = { { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
std::vector<std::string> disklist = { "-4", "-3", "-2", "-1", "1", "2", "3", "4" };


//create the profiles to be filled below.
TGraphErrors* TEPXClustersPerEvent[20][20]; //number of clusters vs pu
TGraphErrors* NonLinearity_TEPXClustersPerEvent[20][4]; //number of clusters vs pu
TProfile* Prof_TEPXClustersPerEvent[20][20]; //array pu,disk
TH2F* Histogram2D[20][20];
TH2F* Histogram12D[20][20];
TH1D* ProjectionY[20][20][20];
TF1* FitTEPXClustersPerEvent[20][4];

void initialize(int option){
  
  for (int d = 0; d < disklist.size(); d++){
    for (int r = 0; r < 5; r++){
      TEPXClustersPerEvent[d][r] = new TGraphErrors();
      NonLinearity_TEPXClustersPerEvent[d][r] = new TGraphErrors();
    }
  }

  //read the histograms
  for (int pu = 0; pu < pulist.size(); pu++) {
    TFile F(inpath + pulist[pu].c_str() + ".root", "read");
    gROOT->cd();
    
    for (int d = 0; d < disklist.size(); d++) { 
      for (int r = 0; r < 5; r++){
	//draw the 2D Cluster distributions for all PU
	if(option == 1){
	  
          
	  TString histoname = "BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";
	  TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	  Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));

          TString histoname1 = "BRIL_IT_Analysis/TEPX/Hits/Number of hits for Disk ";
	  TH2F* H1 = (TH2F*)F.Get(histoname1 + disklist[d].c_str());
	  Histogram12D[pu][d] = (TH2F*)H1->Clone(TString(H1->GetName()));


	  ProjectionY[pu][d][r] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, r, r)->Clone(TString(H->GetName()) +             "Projection");
	  ProjectionY[pu][d][r] ->Rebin(10);

	  Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile"); //number of clusters vs ring
	  TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1));
	  TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1));
        
	  FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 200);
	  FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
	  TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);


	  float x = pumap[pulist[pu]];
	  float y = (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	  float yerr = (Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1)) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);

             
	  if (pu > 2) {


	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x -(r-2), y);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);

	  } else {


	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	  
              
	  }
	}

	if(option == 2){

	  TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ";
	  TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	  Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));

	  ProjectionY[pu][d][r] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, r, r)->Clone(TString(H->GetName()) +             "Projection");
	  ProjectionY[pu][d][r] ->Rebin(10);

	  Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile"); //number of clusters vs ring
	  TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1));
	  TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1));

	  FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 200);
	  FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
	  TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);

	  float x = pumap[pulist[pu]];
	  float y = (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	  float yerr = (Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1)) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);

             
	  if (pu > 2) {


	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x -(r-2), y);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	    
	  } else {


	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	    
	  }
	}

	if(option == 3){

	

	  TString histoname = "BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk ";
	  TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	  Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));

	  ProjectionY[pu][d][r] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, r, r)->Clone(TString(H->GetName()) +             "Projection");
	  ProjectionY[pu][d][r] ->Rebin(10);

	  Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile"); //number of clusters vs ring
	  TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1));
	  TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1));
	  
	  FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 200);
	  FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
	  TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);

	  float x = pumap[pulist[pu]];
	  float y = (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	  float yerr = (Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1)) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	  
             
	  if (pu > 2) {


	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x -(r-2), y);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);

	  } else {


	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);

	  }     
	}
      }
    }
  }
}


	

