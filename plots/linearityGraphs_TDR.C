
void totalcountcluster1(){
  
  TFile *f = new TFile("./TDRplotscluster.root","RECREATE");
  
  f->cd();
  gDirectory->pwd();
  f->ls();
  
  //TString inpath = "/home/ashish/TEPX_rootfiles/samples_17Feb2020/";
  TString inpath = "/eos/user/a/asehrawa/TEPX/samples_for_clusters_old_CMSSW_code/";

  TString histoname = "BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";

  std::vector<std::string> pulist = {"2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {{ "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  //std::vector<std::string> disklist = {"-4", "-3", "-2", "-1", "1", "2", "3", "4"};
  std::vector<std::string> disklist = {"-1", "-2", "-3", "-4", "1", "2", "3", "4"};//swap disks in negative side , apparently histograms are wrongly labeled in the input file, clusters should be increasing with disk number
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent; //number of clusters vs pu
  TGraphErrors* TEPXClustersPerEvent_D4R1;
  TEPXClustersPerEvent = new TGraphErrors();
  TEPXClustersPerEvent_D4R1 = new TGraphErrors();
  
  
  TGraphErrors* TEPXClustersPerEvent_disk[8];
  TGraphErrors* TEPXClustersPerEvent_ring[8][5];
  for (int d = 0; d < 8; d++){
    TEPXClustersPerEvent_disk[d] = new TGraphErrors();	
    for (int r = 0; r < 5; r++){
      TEPXClustersPerEvent_ring[d][r] = new TGraphErrors();	
    }
  }
  

  TH2D PerRing2DMap("PerRing2DMap","",9,-4.5,4.5,5,0.5,5.5);//Counts vs (disk,ring)

  
  //read the histograms
  for (int pu = 0; pu < pulist.size(); pu++) {
    
    TFile F(inpath + pulist[pu].c_str() + ".root", "read");
    if(F.IsZombie()) return;
    F.Print();
    gROOT->cd();
    
    float totalcount=0;
    float totalcounterror=0;
    
    float totalcount_D4R1=0;
    float totalcounterror_D4R1=0;
    
    float totalcount_disk[8];
    float totalcounterror_disk[8];
            
    for (int d = 0; d < 8; d++) {
      int disk = (d<=3 ? d-4 : d-3 );

      TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
      TProfile* Prof_TEPXClustersPerEvent = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
      
      totalcount_disk[d]=0;
      totalcounterror_disk[d]=0;
      
      for (int r = 0; r < 5; r++) {
	
	float count = Prof_TEPXClustersPerEvent->GetBinContent(r + 1);
	float counterror = Prof_TEPXClustersPerEvent->GetBinError(r + 1);
	
	if(!((d == 0 || d == 7) && r == 0)){//TEPX - D4R1
	  totalcount+=count;
	  totalcounterror+= counterror * counterror;
	}
	
	if((d == 0 || d == 7) && r == 0){//D4R1
	  totalcount_D4R1+=count;
	  cout<<"THERE WAS A BUG IN NEXT LINE"<<endl;
	  //totalcounterror_D4R1 = counterror * counterror;/////<<<--- BUG
	  totalcounterror_D4R1 += counterror * counterror;/////<<<--- BUG
	}
	
	totalcount_disk[d] += count;
	totalcounterror_disk[d] += counterror * counterror;
	


	if(pumap[pulist[pu]]==200.) 
	  PerRing2DMap.Fill(disk,r+1,count);
	
	TEPXClustersPerEvent_ring[d][r]->SetPoint(pu, pumap[pulist[pu]], count);
	TEPXClustersPerEvent_ring[d][r]->SetPointError(pu, 0, counterror);
      }	

      TEPXClustersPerEvent_D4R1->SetPoint(pu, pumap[pulist[pu]], totalcount_disk[d]);
      TEPXClustersPerEvent_D4R1->SetPointError(pu, 0, sqrt(totalcounterror_disk[d]));      
    }
    
    
    TEPXClustersPerEvent->SetPoint(pu, pumap[pulist[pu]], totalcount);
    TEPXClustersPerEvent->SetPointError(pu, 0, sqrt(totalcounterror));
    
    TEPXClustersPerEvent_D4R1->SetPoint(pu, pumap[pulist[pu]], totalcount_D4R1);
    TEPXClustersPerEvent_D4R1->SetPointError(pu, 0, sqrt(totalcounterror_D4R1));
  }
  
  
  f->WriteTObject(&PerRing2DMap);

  TEPXClustersPerEvent->SetName(TString("clusters_TEPX"));  
  f->WriteTObject(TEPXClustersPerEvent);
  
  TEPXClustersPerEvent_D4R1->SetName(TString("clusters_TEPXD4R1"));  
  f->WriteTObject(TEPXClustersPerEvent_D4R1);



  for (int d = 0; d < 8; d++) {
    int disk = (d<=3 ? d-4 : d-3 );

    if (disk < 0 ) {
      TEPXClustersPerEvent_disk[d]->SetName(TString("clusters_") + "Dm" + (-disk));
    } else {
      TEPXClustersPerEvent_disk[d]->SetName(TString("clusters_") + "Dp" + (disk));
    }
    f->WriteTObject(TEPXClustersPerEvent_disk[d]);
    

    for (int r = 0; r < 5; r++){
      if (disk < 0) {
	TEPXClustersPerEvent_ring[d][r]->SetName(TString("clusters_") + "Dm" + (-disk) + "R" + (r+1));
      } else {
	TEPXClustersPerEvent_ring[d][r]->SetName(TString("clusters_") + "Dp" + (disk) + "R" + (r+1));
      }
      f->WriteTObject(TEPXClustersPerEvent_ring[d][r]);
    }

  }

}





void totalcount2x1(){
  
  TFile *f = new TFile("./TDRplots_2xinphi.root","RECREATE");
  if(f->IsZombie()) return;
  //TFile *f = new TFile("./TDRplots_2xinR.root","RECREATE");
  //TFile *f = new TFile("./TDRplots2x_phi_R.root","RECREATE");


  TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_Inphi_side";
  //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_InR_side";
  //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_side";
  
  
  f->cd();
  gDirectory->cd();
  f->ls();
  
  TString inpath = "/eos/user/a/asehrawa/TEPX/2xresults_all/";
  
  //string containing names of input sample files
  std::vector<std::string> pulist = {"2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {{ "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent; //number of clusters vs pu
  TEPXClustersPerEvent = new TGraphErrors();

  TGraphErrors* TEPXClustersPerEvent_D4R1;
  TEPXClustersPerEvent_D4R1 = new TGraphErrors();

  TGraphErrors* TEPXClustersPerEvent_disk[2][4];  
  for (int s = 0; s < 2; s++)
    for (int d = 0; d < 4; d++)
	TEPXClustersPerEvent_disk[s][d] = new TGraphErrors();

  TGraphErrors* TEPXClustersPerEvent_ring[2][4][5];   
  for (int s = 0; s < 2; s++)
    for (int d = 0; d < 4; d++)
      for (int r = 0; r < 5; r++)
	TEPXClustersPerEvent_ring[s][d][r] = new TGraphErrors();
    

  TH2D Coincidences2DMap("Coincidences2DMap","",9,-4.5,4.5,5,0.5,5.5);//Counts vs (disk,ring)


  //read the histograms
  for (int pu = 0; pu < pulist.size(); pu++) {
    
    TFile F(inpath + pulist[pu].c_str() + ".root", "read");
    if(F.IsZombie()) return;
    F.Print();

    gROOT->cd();
    
    float totalcount=0;
    float totalcounterror=0;
    
    float totalcount_D4R1=0;
    float totalcounterror_D4R1=0;
    
    float totalcount_disk[2][4];
    float totalcounterror_disk[2][4];
      
    for (long s = 0; s < 2; s++) {
      for (long d = 0; d < 4; d++) {

	int disk = (s==0 ? -(d+1) : d+1 );

	TString hname=histoname + (s+1) + "_Disk" + (d+1);
	TH2F* H = (TH2F*)F.Get(hname);
	if(!H){cout<<hname<<" not found in input"<<endl; return;}
	TProfile* Prof_TEPXClustersPerEvent = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	
	totalcount_disk[s][d]=0;
	totalcounterror_disk[s][d]=0;
	
	for (int r = 0; r < 5; r++) {
	  
	  float count = Prof_TEPXClustersPerEvent->GetBinContent(r + 1); //per ring
	  float counterror = Prof_TEPXClustersPerEvent->GetBinError(r + 1);
	  
	  totalcount_disk[s][d]+=count; //per disk
	  totalcounterror_disk[s][d]+= counterror * counterror;

	  if(!(d == 0 && r == 0)){//TEPX  - D4R1
	    totalcount+=count;
	    totalcounterror+= counterror * counterror;
	  }	
	  
	  if((d == 0) && r == 0){//D4R1
	    totalcount_D4R1+=count;
	    totalcounterror_D4R1 = counterror * counterror;
	  }    
	  

	  if(pumap[pulist[pu]]==200.) Coincidences2DMap.Fill(disk,r+1,count);
	  
	  TEPXClustersPerEvent_ring[s][d][r]->SetPoint(pu, pumap[pulist[pu]], count);
	  TEPXClustersPerEvent_ring[s][d][r]->SetPointError(pu, 0, counterror);
	}   
	
	TEPXClustersPerEvent_disk[s][d]->SetPoint(pu, pumap[pulist[pu]], totalcount_disk[s][d]);
	TEPXClustersPerEvent_disk[s][d]->SetPointError(pu, 0, sqrt(totalcounterror_disk[s][d]));
      }
    }
    
    TEPXClustersPerEvent->SetPoint(pu, pumap[pulist[pu]], totalcount);
    TEPXClustersPerEvent->SetPointError(pu, 0, sqrt(totalcounterror));
    TEPXClustersPerEvent_D4R1->SetPoint(pu, pumap[pulist[pu]], totalcount_D4R1);
    TEPXClustersPerEvent_D4R1->SetPointError(pu, 0, sqrt(totalcounterror_D4R1));
  }

  

  f->WriteTObject(&Coincidences2DMap);
  

  TEPXClustersPerEvent->SetMarkerSize(2);
  TEPXClustersPerEvent->SetMarkerColor(2);
  TEPXClustersPerEvent->SetName(TString("Coincidences2x_TEPX"));  
  f->WriteTObject(TEPXClustersPerEvent);
  
  
  TEPXClustersPerEvent_D4R1->SetMarkerSize(2);
  TEPXClustersPerEvent_D4R1->SetMarkerColor(2);
  TEPXClustersPerEvent_D4R1->SetName(TString("Coincidences2x_TEPXD4R1"));  
  f->WriteTObject(TEPXClustersPerEvent_D4R1);


  for (int s = 0; s < 2; s++) {
    for (int d = 0; d < 4; d++) {
      TEPXClustersPerEvent_disk[s][d]->SetMarkerSize(2);
      TEPXClustersPerEvent_disk[s][d]->SetMarkerColor(2);
      if(s==0) TEPXClustersPerEvent_disk[s][d]->SetName(TString("Coincidences2x_Dm")+(d+1));  
      if(s==1) TEPXClustersPerEvent_disk[s][d]->SetName(TString("Coincidences2x_Dp")+(d+1));  
      f->WriteTObject(TEPXClustersPerEvent_disk[s][d]);
    }
  }


   
  for (int s = 0; s < 2; s++){
    for (int d = 0; d < 4; d++) {
      for (int r = 0; r < 5; r++){
	TEPXClustersPerEvent_ring[s][d][r]->SetMarkerSize(2);
	TEPXClustersPerEvent_ring[s][d][r]->SetMarkerColor(2);
	
	if(s==0)
	  TEPXClustersPerEvent_ring[s][d][r]->SetName(TString("Coincidences2x_") + "Dm" + (d+1) + "R" + (r+1));
	if(s==1)
	  TEPXClustersPerEvent_ring[s][d][r]->SetName(TString("Coincidences2x_") + "Dp" + (d+1) + "R" + (r+1));
	
	f->WriteTObject(TEPXClustersPerEvent_ring[s][d][r]);
      }
    }
  }  

  f->ls();
  f->Close();

}
      
