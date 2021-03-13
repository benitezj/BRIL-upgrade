void totalcountcluster1(){
  
  TFile *f = new TFile("./TDRplotscluster.root","RECREATE");
  
  f->cd();
  gDirectory->pwd();
  f->ls();
  
  TString inpath = "/home/ashish/TEPX_rootfiles/samples_17Feb2020/";
  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
  
  //string containing names of input sample files
  std::vector<std::string> pulist = {//"2023D42noPU" , 
    "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {//{ "2023D42noPU", 0 },
    { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  std::vector<std::string> disklist = {"-4", "-3", "-2", "-1", "1", "2", "3", "4"};
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent; //number of clusters vs pu
  TGraphErrors* TEPXClustersPerEvent1[20][20];
  TGraphErrors* TEPXClustersPerEvent_disk1;
  TGraphErrors* TEPXClustersPerEvent_disk2;
  TGraphErrors* TEPXClustersPerEvent_disk3;
  TGraphErrors* TEPXClustersPerEvent_disk4;
  TGraphErrors* TEPXClustersPerEvent_D4R1;
  
  TH2F* Histogram2D[20][20];
  
  //Non-linearity graphs
  TGraphErrors* NonLinearity_TEPXClustersPerEvent; //number of clusters vs pu 
  NonLinearity_TEPXClustersPerEvent = new TGraphErrors();
  
  for (int pu = 0; pu < pulist.size(); pu++) {
    for (int d = 0; d < disklist.size(); d++){
      for (int r = 0; r < 5; r++){
	
	TEPXClustersPerEvent = new TGraphErrors();
	TEPXClustersPerEvent_disk1 = new TGraphErrors();
	TEPXClustersPerEvent_disk2 = new TGraphErrors();
	TEPXClustersPerEvent_disk3 = new TGraphErrors();
	TEPXClustersPerEvent_disk4 = new TGraphErrors();
	TEPXClustersPerEvent_D4R1 = new TGraphErrors();
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
      
      float totalcount_D4R1=0;
      float totalcounterror_D4R1=0;
      
      float totalcount_disk1=0;
      float totalcounterror_disk1=0;
      
      float totalcount_disk2=0;
      float totalcounterror_disk2=0;
      
      float totalcount_disk3=0;
      float totalcounterror_disk3=0;
      
      float totalcount_disk4=0;
      float totalcounterror_disk4=0;
      
      
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
	  
	  if (d == 3 || d == 4) {
	    
	    totalcount_disk1+=count;
	    totalcounterror_disk1+= counterror * counterror;
	    
	  }
	   
	  if (d == 2 || d == 5) {
	    
	    totalcount_disk2+=count;
	    totalcounterror_disk2+= counterror * counterror;
	    
	  }
	  
	  if (d == 1 || d == 6) {
	    
	    totalcount_disk3+=count;
	    totalcounterror_disk3+= counterror * counterror;
	    
	  }
	  
	   if (d == 0 || d == 7) {
	     
	     totalcount_disk4+=count;
	     totalcounterror_disk4+= counterror * counterror;
	     
	   }
	   
	   
	   if(!((d == 0 || d == 7) && r == 0)){
	     
	     totalcount+=count;
	     totalcounterror+= counterror * counterror;
	     
	   }
	   
	   if((d == 0 || d == 7) && r == 0){
	     
	     totalcount_D4R1+=count;
	     totalcounterror_D4R1 = counterror * counterror;
	     
	   }
	}	
      }
      
      
      TEPXClustersPerEvent->SetPoint(pu, pumap[pulist[pu]], totalcount);
      TEPXClustersPerEvent->SetPointError(pu, 0, sqrt(totalcounterror));
      
      TEPXClustersPerEvent_disk1->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1);
      TEPXClustersPerEvent_disk1->SetPointError(pu, 0, sqrt(totalcounterror_disk1));
      
      TEPXClustersPerEvent_disk2->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2);
      TEPXClustersPerEvent_disk2->SetPointError(pu, 0, sqrt(totalcounterror_disk2));
      
      TEPXClustersPerEvent_disk3->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3);
      TEPXClustersPerEvent_disk3->SetPointError(pu, 0, sqrt(totalcounterror_disk3));
      
      TEPXClustersPerEvent_disk4->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4);
      TEPXClustersPerEvent_disk4->SetPointError(pu, 0, sqrt(totalcounterror_disk4));
      
      TEPXClustersPerEvent_D4R1->SetPoint(pu, pumap[pulist[pu]], totalcount_D4R1);
      TEPXClustersPerEvent_D4R1->SetPointError(pu, 0, sqrt(totalcounterror_D4R1));
      
    }
  }
  
  TEPXClustersPerEvent->SetMarkerSize(2);
  TEPXClustersPerEvent->SetMarkerColor(2);
  TEPXClustersPerEvent->SetName(TString("cluster_TEPX"));  
  f->WriteTObject(TEPXClustersPerEvent);
  
  TEPXClustersPerEvent_D4R1->SetMarkerSize(2);
  TEPXClustersPerEvent_D4R1->SetMarkerColor(2);
  TEPXClustersPerEvent_D4R1->SetName(TString("cluster_D4R1"));  
  f->WriteTObject(TEPXClustersPerEvent_D4R1);
  
  TEPXClustersPerEvent_disk1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1->SetName(TString("cluster_disk1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1);
  
  TEPXClustersPerEvent_disk2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2->SetName(TString("cluster_disk2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2);
  
  
  TEPXClustersPerEvent_disk3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3->SetName(TString("cluster_disk3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3);
  
  TEPXClustersPerEvent_disk4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4->SetName(TString("cluster_disk4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4);
  
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++){
      
      TEPXClustersPerEvent1[d][r]->SetMarkerSize(2);
      TEPXClustersPerEvent1[d][r]->SetMarkerColor(2);
      TEPXClustersPerEvent1[d][r]->SetName(TString("Clusters") + "D" + d + "R" + r);
      f->WriteTObject(TEPXClustersPerEvent1[d][r]);
      
      
    }
  }
}






