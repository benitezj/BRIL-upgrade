


void linearityGraphs_TDR_oldcode(){
  
  TFile *f = new TFile("./TEPXLinearityGraphs.root","RECREATE");
  if(f->IsZombie()) return;
  
  gROOT->cd();
  
  //** Input is a directory containing a list of root files with histograms produced by the ITCluserAnalyzer module in BRIL-ITSim package:
  // 2023D42noPU.root   2023D42PU100.root  2023D42PU140.root  2023D42PU1.root    2023D42PU2.root   2023D42PU50.root
  // 2023D42PU0p5.root  2023D42PU10.root   2023D42PU1p5.root  2023D42PU200.root  2023D42PU30.root
 

  //TString inpath = "/eos/user/a/asehrawa/TEPX/samples_for_clusters_old_CMSSW_code/"; // old low stats processing where log files were lost
  //TString inpath = "/eos/user/a/asehrawa/TEPX/2xresults_all/"; //high stats processing with new lxbatch script splitting to many jobs
  TString inpath = "/eos/user/a/asehrawa/TEPX/samples_7Sep2021/"; //new processing with only 50 root files per point to reproduce cluster plot in TDR

  //local laptop paths
  //TString inpath = "/home/ashish/TEPX_rootfiles/samples_17Feb2020/";
  //TString inpath = "/Users/josebenitez/analysis/";//high stats processsing

  
  std::map<std::string, float> pumap = {
    { "2023D42PU0p5", 0.5 },
    { "2023D42PU1", 1 },
    { "2023D42PU1p5", 1.5 },
    { "2023D42PU2", 2 },
    { "2023D42PU10", 10 },
    { "2023D42PU30", 30 },
    { "2023D42PU50", 50 },
    { "2023D42PU100", 100 },
    { "2023D42PU140", 140 },
    { "2023D42PU200", 200 }
  };
  
  
  
  std::map<std::string, std::string>  inputHistMap= {
    {"BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ","Clusters"}
    //,{"BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_Inphi_","Coincidences2x_Inphi"},
    //,{"BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_InR_","Coincidences2x_InR"},
    //,{"BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_","Coincidences2x_total"}
  };
  
    
  for(std::map<std::string, std::string >::iterator it_hist = inputHistMap.begin(); it_hist!=inputHistMap.end(); ++it_hist){ 
      
    //create the profiles to be filled below.
    TGraphErrors* TEPXClustersPerEvent  = new TGraphErrors();
    TGraphErrors* TEPXClustersPerEvent_D4R1 = new TGraphErrors();
    TGraphErrors* TEPXClustersPerEvent_disk[1][8];
    TGraphErrors* TEPXClustersPerEvent_ring[1][8][5];
    for (int s = 0; s < 1; s++) {
      for (int d = 0; d < 8; d++){
	TEPXClustersPerEvent_disk[s][d] = new TGraphErrors();	
	for (int r = 0; r < 5; r++){
	  TEPXClustersPerEvent_ring[s][d][r] = new TGraphErrors();	
	}
      }
    }
    

    TH2D PerRing2DMap("PerRing2DMap","",9,-4.5,4.5,5,0.5,5.5);//Counts vs (disk,ring)
    
  
    int pu=0;
    for(std::map<std::string, float >::iterator it = pumap.begin(); it!=pumap.end(); ++it){ 
      
      TFile F(inpath + (it->first).c_str() + ".root", "read");
      if(F.IsZombie()) return;
      //TDirectoryFile*  Dir = (TDirectoryFile*)F.Get(dirname);
      //Dir->ls();
      gROOT->cd();
      
      
      float totalcount=0;
      float totalcounterror=0;
      
      float totalcount_D4R1=0;
      float totalcounterror_D4R1=0;
      
      for (int s = 0; s < 1; s++) {
	for (int d = 0; d < 8; d++) {
	  
	  int disk = (d<4 ? d-4 : d-3 );
	  
	  //TString histname=TString(it_hist->first)+"side"+(s+1)+"_Disk"+(d+1);
	  TString histname=TString(it_hist->first)+disk;
	  TH2F* H = (TH2F*)F.Get(histname);
	  if(!H){ cout<<histname<<"  not found in "<<F.GetName()<<endl; }
	    
	  TProfile* Prof_TEPXClustersPerEvent = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	  

	  float totalcount_disk=0;
	  float totalcounterror_disk=0;

	  for (int r = 0; r < 5; r++) {
	    
	    float count = Prof_TEPXClustersPerEvent->GetBinContent(r + 1);
	    float counterror = Prof_TEPXClustersPerEvent->GetBinError(r + 1);
	    
	    if(!((d == 0 || d == 7) && r == 0)){//TEPX - D4R1
	      totalcount += count;
	      totalcounterror += counterror * counterror;
	    }
	    
	    if((d == 0 || d == 7) && r == 0){//D4R1
	      totalcount_D4R1 += count;
	      totalcounterror_D4R1 += counterror * counterror;
	    }
	    
	
	    totalcount_disk += count;
	    totalcounterror_disk += counterror * counterror;
	    

	    if(it->second==200.)  PerRing2DMap.Fill(disk,r+1,count);
	    
	    TEPXClustersPerEvent_ring[s][d][r]->SetPoint(pu, it->second, count);
	    TEPXClustersPerEvent_ring[s][d][r]->SetPointError(pu, 0, counterror);
	  }	
	  
	  TEPXClustersPerEvent_disk[s][d]->SetPoint(pu, it->second, totalcount_disk);
	  TEPXClustersPerEvent_disk[s][d]->SetPointError(pu, 0, sqrt(totalcounterror_disk));      
	}
      }
      
      
      TEPXClustersPerEvent->SetPoint(pu, it->second, totalcount);
      TEPXClustersPerEvent->SetPointError(pu, 0, sqrt(totalcounterror));
      
      TEPXClustersPerEvent_D4R1->SetPoint(pu, it->second, totalcount_D4R1);
      TEPXClustersPerEvent_D4R1->SetPointError(pu, 0, sqrt(totalcounterror_D4R1));
      
      pu++;
    }
    
    
    PerRing2DMap.SetName(TString(it_hist->second)+"_2DRingMap");  
    f->WriteTObject(&PerRing2DMap);
    
    TEPXClustersPerEvent->SetName(TString(it_hist->second)+"_TEPX");  
    f->WriteTObject(TEPXClustersPerEvent);
    
    TEPXClustersPerEvent_D4R1->SetName(TString(it_hist->second)+"_TEPXD4R1");  
    f->WriteTObject(TEPXClustersPerEvent_D4R1);
  

    for (int s = 0; s < 1; s++) {
      for (int d = 0; d < 8; d++) {
	//int disk = (s==0 ? -(d+1) : d+1 );
	int disk = (d<4 ? d-4 : d-3 );
	
	if (disk < 0 )
	  TEPXClustersPerEvent_disk[s][d]->SetName(TString(it_hist->second)+ "_Dm" + (-disk));
	else 
	  TEPXClustersPerEvent_disk[s][d]->SetName(TString(it_hist->second)+ "_Dp" + (disk));
	
	f->WriteTObject(TEPXClustersPerEvent_disk[s][d]);
	

	for (int r = 0; r < 5; r++){
	  if (disk < 0)
	    TEPXClustersPerEvent_ring[s][d][r]->SetName(TString(it_hist->second)+ "_Dm" + (-disk) + "R" + (r+1));
	  else 
	    TEPXClustersPerEvent_ring[s][d][r]->SetName(TString(it_hist->second)+ "_Dp" + (disk) + "R" + (r+1));
      
	  f->WriteTObject(TEPXClustersPerEvent_ring[s][d][r]);
	}

      }
    }


  }
  
  
  
  f->ls();
  f->Close();
}



