void linearity(){

  TString inpath="/eos/user/a/asehrawa/TEPX/samples1_17Feb2020/";
  //TString inpath="";

  TString histoname="BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";

  std::vector<std::string> pulist={"2023D42PU0p5","2023D42PU1","2023D42PU1p5","2023D42PU2","2023D42PU10","2023D42PU30","2023D42PU50","2023D42PU100","2023D42PU140"};
  std::map<std::string,float> pumap={{"2023D42PU0p5",0.5},{"2023D42PU1",1},{"2023D42PU1p5",1.5},{"2023D42PU2",2},{"2023D42PU10",10},{"2023D42PU30",30},{"2023D42PU50",50},{"2023D42PU100",100},{"2023D42PU140",140}};
  std::vector<std::string> disklist={"-4","-3","-2","-1","1","2","3","4"};

  ///create the profiles to be filled below.
  TGraphErrors * TEPXClustersPerEvent[20][4];//number of clusters vs pu
  for(int d=0; d<disklist.size(); d++)
    for(int r=0 ; r<5; r++)
      TEPXClustersPerEvent[d][r] = new TGraphErrors();


  ///Non-linearity graphs
  TGraphErrors * NonLinearity_TEPXClustersPerEvent[20][4];//number of clusters vs pu
  for(int d=0; d<disklist.size(); d++){
    for(int r=0 ; r<5; r++){
      NonLinearity_TEPXClustersPerEvent[d][r] = new TGraphErrors();
    }
  }


  ///read the histograms
  TProfile * Prof_TEPXClustersPerEvent[20][20];//array pu,disk
  for(int pu=0;pu<pulist.size();pu++){
    TFile F(inpath+pulist[pu]+".root","read");
    //TFile F(inpath+pulist[pu]+".root","read");
    F.ls();
    gROOT->cd();

    for(int d=0;d<disklist.size();d++){
      TH2F* H=(TH2F*)F.Get(histoname+disklist[d]);
      cout<<H<< endl;
      cout<<histoname+disklist[d]<<endl;
      Prof_TEPXClustersPerEvent[pu][d] = (TProfile*) H->ProfileX()->Clone(TString(H->GetName())+"Profile");  //number of cluster vs ring
      
      for(int r=0;r<5;r++){
	TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1));
	TEPXClustersPerEvent[d][r]->SetPointError(pu, 0 , Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r+1));

	//NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1));
      }

    }
  }
  

  //Make the graphs
  TLatex label; 
  label.SetTextSize(0.2);
  TF1 * FitTEPXClustersPerEvent[20][4];
  //TCanvas C("C");
  //C.Divide(5,8);
  //for(long d=0;d<disklist.size();d++)
  //for(long r=0;r<5;r++){

      TCanvas C("C");

      //fix the pads
      TVirtualPad* pad = C.cd();
      pad->SetBottomMargin(0.3);
      pad->SetLeftMargin(0.3);
      
      //fit
      FitTEPXClustersPerEvent[4][1]=new TF1(TString("Fit_")+4+"_"+1,"[0]+[1]*x",0,200);
      FitTEPXClustersPerEvent[4][1]->SetLineColor(4);
      TEPXClustersPerEvent[4][1]->Fit(FitTEPXClustersPerEvent[4][1],"","",0,200);
    
      //draw
      
     
      TEPXClustersPerEvent[4][1]->GetYaxis()->SetNdivisions(2);
      TEPXClustersPerEvent[4][1]->GetYaxis()->SetLabelSize(0.15);
      TEPXClustersPerEvent[4][1]->GetYaxis()->SetMaxDigits(4);
      // TEPXClustersPerEvent[4][1]->GetYaxis()->SetRangeUser(0,2500);
      TEPXClustersPerEvent[4][1]->GetXaxis()->SetNdivisions(3);
      TEPXClustersPerEvent[4][1]->GetXaxis()->SetLabelSize(0.2);
      TEPXClustersPerEvent[4][1]->SetMarkerStyle(8);
      TEPXClustersPerEvent[4][1]->SetMarkerSize(0.5);
      
      TEPXClustersPerEvent[4][1]->Draw("ape");
      FitTEPXClustersPerEvent[4][1]->Draw("lsame");
      
      //label.DrawLatexNDC(0.33,0.7,TString("D=")+(long)(d<=3?d-4:d+1-4)+",  R="+(long)(r+1));
      //label.DrawLatexNDC(0.33,0.7,TString("D=")+(long)(d<=3?d-4:d+1-4)+",  R="+(long)(r+1));
    
    
  //C.Print("/afs/cern.ch/user/b/benitezj/www/BRIL/TEPX/linearity.gif");

  C.Print("/eos/user/a/asehrawa/TEPX/linearity1.gif");
    


//for(int d=0; d<disklist.size(); d++){
//for(int r=0 ; r<5; r++){
//for(int pu=0;pu<pulist.size();pu++){
//	NonLinearity_TEPXClustersPerEvent[4][1]->SetPoint(pu, pumap[pulist[pu]], 
//(Prof_TEPXClustersPerEvent[pu][4]->GetBinContent(0+1) - FitTEPXClustersPerEvent[4][1]->Eval(pumap[pulist[pu]]))/FitTEPXClustersPerEvent[4][1]->Eval(pumap[pulist[pu]]));
  //  } 
  //}
//}


  // C.Clear();
  //C.Divide(4,8);
  //for(long d=0;d<disklist.size();d++)
//for(long r=0;r<5;r++){
      TCanvas C1("C1");
      //fix the pads
      TVirtualPad* pad1 = C1.cd();
      pad1->SetBottomMargin(0.3);
      pad1->SetLeftMargin(0.3);
      
      //draw
      NonLinearity_TEPXClustersPerEvent[4][1]->GetYaxis()->SetNdivisions(2);
      NonLinearity_TEPXClustersPerEvent[4][1]->GetYaxis()->SetLabelSize(0.15);
      NonLinearity_TEPXClustersPerEvent[4][1]->GetYaxis()->SetMaxDigits(4);
      NonLinearity_TEPXClustersPerEvent[4][1]->GetYaxis()->SetRangeUser(0,2500);
      NonLinearity_TEPXClustersPerEvent[4][1]->GetYaxis()->SetRangeUser(-0.2,0.2);
      NonLinearity_TEPXClustersPerEvent[4][1]->GetXaxis()->SetNdivisions(3);
      NonLinearity_TEPXClustersPerEvent[4][1]->GetXaxis()->SetLabelSize(0.2);
      NonLinearity_TEPXClustersPerEvent[4][1]->SetMarkerStyle(8);
      NonLinearity_TEPXClustersPerEvent[4][1]->SetMarkerSize(0.5);
      NonLinearity_TEPXClustersPerEvent[4][1]->Draw("ape");
    
C1.Print("/eos/user/a/asehrawa/TEPX/linearity_residual1.gif");
    
  
}
