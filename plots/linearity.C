
void linearity(){

  TString inpath="/eos/user/b/benitezj/BRIL/UpgradeStudies/CMSSW_10_6_0_patch2-PU25ns_106X_upgrade2023";
  TString histoname="BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";

  std::vector<std::string> pulist={"0p5","1","1p5","2","10","50","100","140","200"};
  std::map<std::string,int> pumap={{"0p5",0.5},{"1",1},{"1p5",1.5},{"2",2},{"10",10},{"50",50},{"100",100},{"140",140},{"200",200}};
  std::vector<std::string> disklist={"-4","-3","-2","-1","1","2","3","4"};

  ///create the profiles to be filled below.
  TGraphErrors * TEPXClustersPerEvent[20][4];//number of clusters vs pu
  for(int d=0; d<disklist.size(); d++)
    for(int r=0 ; r<4; r++)
      TEPXClustersPerEvent[d][r] = new TGraphErrors();


  ///Non-linearity graphs
  TGraphErrors * NonLinearity_TEPXClustersPerEvent[20][4];//number of clusters vs pu
  for(int d=0; d<disklist.size(); d++){
    for(int r=0 ; r<4; r++){
      NonLinearity_TEPXClustersPerEvent[d][r] = new TGraphErrors();
    }
  }


  ///read the histograms
  TProfile * Prof_TEPXClustersPerEvent[20][20];//array pu,disk
  for(int pu=0;pu<pulist.size();pu++){
    TFile F(inpath+"/summary_PU"+pulist[pu]+".root","read");  
    gROOT->cd();

    for(int d=0;d<disklist.size();d++){
      TH2F* H=(TH2F*)F.Get(histoname+disklist[d]);
      Prof_TEPXClustersPerEvent[pu][d] = (TProfile*) H->ProfileX()->Clone(TString(H->GetName())+"Profile");//number of cluster vs ring
      
      for(int r=0;r<4;r++){
	TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1));
	TEPXClustersPerEvent[d][r]->SetPointError(pu, 0 , Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r+1));

	//NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1));
      }

    }
  }
  

  ///Make the graphs
  TLatex label; 
  label.SetTextSize(0.2);
  TF1 * FitTEPXClustersPerEvent[20][4];
  TCanvas C("C");
  C.Divide(4,8);
  for(long d=0;d<disklist.size();d++)
    for(long r=0;r<4;r++){

      //fix the pads
      TVirtualPad* pad = C.cd(d*4+r+1);
      pad->SetBottomMargin(0.3);
      pad->SetLeftMargin(0.3);
      
      //fit
      FitTEPXClustersPerEvent[d][r]=new TF1(TString("Fit_")+d+"_"+r,"[0]+[1]*x",0,200);
      FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
      TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r],"","",0,50);
      
      //draw
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetNdivisions(2);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetLabelSize(0.15);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetMaxDigits(4);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0,2500);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetNdivisions(3);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetLabelSize(0.2);
      TEPXClustersPerEvent[d][r]->SetMarkerStyle(8);
      TEPXClustersPerEvent[d][r]->SetMarkerSize(0.5);
      
      TEPXClustersPerEvent[d][r]->Draw("ape");
      FitTEPXClustersPerEvent[d][r]->Draw("lsame");
      label.DrawLatexNDC(0.33,0.7,TString("D=")+(long)(d<=3?d-4:d+1-4)+",  R="+(long)(r+1));
    }
  C.Print("/afs/cern.ch/user/b/benitezj/www/BRIL/TEPX/linearity.gif");
  


  for(int d=0; d<disklist.size(); d++){
    for(int r=0 ; r<4; r++){
      for(int pu=0;pu<pulist.size();pu++){
  	NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], 
							  (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]))/FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]));
      } 
    }
  }


  C.Clear();
  C.Divide(4,8);
  for(long d=0;d<disklist.size();d++)
    for(long r=0;r<4;r++){

      //fix the pads
      TVirtualPad* pad = C.cd(d*4+r+1);
      pad->SetBottomMargin(0.3);
      pad->SetLeftMargin(0.3);
      
      //draw
      NonLinearity_TEPXClustersPerEvent[d][r]->GetYaxis()->SetNdivisions(2);
      NonLinearity_TEPXClustersPerEvent[d][r]->GetYaxis()->SetLabelSize(0.15);
      NonLinearity_TEPXClustersPerEvent[d][r]->GetYaxis()->SetMaxDigits(4);
      //NonLinearity_TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0,2500);
      NonLinearity_TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(-0.2,0.2);
      NonLinearity_TEPXClustersPerEvent[d][r]->GetXaxis()->SetNdivisions(3);
      NonLinearity_TEPXClustersPerEvent[d][r]->GetXaxis()->SetLabelSize(0.2);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(8);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0.5);
      NonLinearity_TEPXClustersPerEvent[d][r]->Draw("ape");
    }
  C.Print("/afs/cern.ch/user/b/benitezj/www/BRIL/TEPX/linearity_residual.gif");
  
  



}
