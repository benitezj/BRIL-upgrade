void totalcountcluster1(){
  
  TFile *f = new TFile("./TDRplotscluster_testing.root","RECREATE");
  
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
  //std::vector<std::string> disklist = {"-1", "-2", "-3", "-4", "1", "2", "3", "4"};
  //std::cout << "disklist " << disklist << std::endl;
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent; //number of clusters vs pu
  TGraphErrors* TEPXClustersPerEvent1[20][20];
  
  TGraphErrors* TEPXClustersPerEvent_disk1;
  TGraphErrors* TEPXClustersPerEvent_disk2;
  TGraphErrors* TEPXClustersPerEvent_disk3;
  TGraphErrors* TEPXClustersPerEvent_disk4;
  TGraphErrors* TEPXClustersPerEvent_disk5;
  TGraphErrors* TEPXClustersPerEvent_disk6;
  TGraphErrors* TEPXClustersPerEvent_disk7;
  TGraphErrors* TEPXClustersPerEvent_disk8;
  
  TGraphErrors* TEPXClustersPerEvent_disk1combined;
  TGraphErrors* TEPXClustersPerEvent_disk2combined;
  TGraphErrors* TEPXClustersPerEvent_disk3combined;
  TGraphErrors* TEPXClustersPerEvent_disk4combined;
  
  TGraphErrors* TEPXClustersPerEvent_disk1combinedring1;
  TGraphErrors* TEPXClustersPerEvent_disk1combinedring2;
  TGraphErrors* TEPXClustersPerEvent_disk1combinedring3;
  TGraphErrors* TEPXClustersPerEvent_disk1combinedring4;
  TGraphErrors* TEPXClustersPerEvent_disk1combinedring5;
  
  TGraphErrors* TEPXClustersPerEvent_disk2combinedring1;
  TGraphErrors* TEPXClustersPerEvent_disk2combinedring2;
  TGraphErrors* TEPXClustersPerEvent_disk2combinedring3;
  TGraphErrors* TEPXClustersPerEvent_disk2combinedring4;
  TGraphErrors* TEPXClustersPerEvent_disk2combinedring5;
  
  TGraphErrors* TEPXClustersPerEvent_disk3combinedring1;
  TGraphErrors* TEPXClustersPerEvent_disk3combinedring2;
  TGraphErrors* TEPXClustersPerEvent_disk3combinedring3;
  TGraphErrors* TEPXClustersPerEvent_disk3combinedring4;
  TGraphErrors* TEPXClustersPerEvent_disk3combinedring5;
  
  TGraphErrors* TEPXClustersPerEvent_disk4combinedring1;
  TGraphErrors* TEPXClustersPerEvent_disk4combinedring2;
  TGraphErrors* TEPXClustersPerEvent_disk4combinedring3;
  TGraphErrors* TEPXClustersPerEvent_disk4combinedring4;
  TGraphErrors* TEPXClustersPerEvent_disk4combinedring5;
  
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
        TEPXClustersPerEvent_disk5 = new TGraphErrors();
	TEPXClustersPerEvent_disk6 = new TGraphErrors();
	TEPXClustersPerEvent_disk7 = new TGraphErrors();
	TEPXClustersPerEvent_disk8 = new TGraphErrors();
	
        TEPXClustersPerEvent_disk1combined = new TGraphErrors();
	TEPXClustersPerEvent_disk2combined = new TGraphErrors();
	TEPXClustersPerEvent_disk3combined = new TGraphErrors();
	TEPXClustersPerEvent_disk4combined = new TGraphErrors();
	
	TEPXClustersPerEvent_D4R1 = new TGraphErrors();
	TEPXClustersPerEvent1[d][r] = new TGraphErrors();
	
	TEPXClustersPerEvent_disk1combinedring1= new TGraphErrors();
	TEPXClustersPerEvent_disk1combinedring2= new TGraphErrors();
	TEPXClustersPerEvent_disk1combinedring3= new TGraphErrors();
	TEPXClustersPerEvent_disk1combinedring4= new TGraphErrors();
	TEPXClustersPerEvent_disk1combinedring5= new TGraphErrors();
	
	TEPXClustersPerEvent_disk2combinedring1= new TGraphErrors();
	TEPXClustersPerEvent_disk2combinedring2= new TGraphErrors();
	TEPXClustersPerEvent_disk2combinedring3= new TGraphErrors();
	TEPXClustersPerEvent_disk2combinedring4= new TGraphErrors();
	TEPXClustersPerEvent_disk2combinedring5= new TGraphErrors();
	
	TEPXClustersPerEvent_disk3combinedring1= new TGraphErrors();
	TEPXClustersPerEvent_disk3combinedring2= new TGraphErrors();
	TEPXClustersPerEvent_disk3combinedring3= new TGraphErrors();
	TEPXClustersPerEvent_disk3combinedring4= new TGraphErrors();
	TEPXClustersPerEvent_disk3combinedring5= new TGraphErrors();
	
	TEPXClustersPerEvent_disk4combinedring1= new TGraphErrors();
	TEPXClustersPerEvent_disk4combinedring2= new TGraphErrors();
	TEPXClustersPerEvent_disk4combinedring3= new TGraphErrors();
	TEPXClustersPerEvent_disk4combinedring4= new TGraphErrors();
	TEPXClustersPerEvent_disk4combinedring5= new TGraphErrors();
  	
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
      
      float totalcount_disk5=0;
      float totalcounterror_disk5=0;
      
      float totalcount_disk6=0;
      float totalcounterror_disk6=0;
      
      float totalcount_disk7=0;
      float totalcounterror_disk7=0;
      
      float totalcount_disk8=0;
      float totalcounterror_disk8=0;
      
      
      float totalcount_disk1combined=0;
      float totalcounterror_disk1combined=0;
      
      float totalcount_disk2combined=0;
      float totalcounterror_disk2combined=0;
      
      float totalcount_disk3combined=0;
      float totalcounterror_disk3combined=0;
      
      float totalcount_disk4combined=0;
      float totalcounterror_disk4combined=0;
      
      
      float totalcount_disk1combinedring1=0;
      float totalcounterror_disk1combinedring1=0;
      
      float totalcount_disk1combinedring2=0;
      float totalcounterror_disk1combinedring2=0;
      
      float totalcount_disk1combinedring3=0;
      float totalcounterror_disk1combinedring3=0;
      
      float totalcount_disk1combinedring4=0;
      float totalcounterror_disk1combinedring4=0;
      
      float totalcount_disk1combinedring5=0;
      float totalcounterror_disk1combinedring5=0;
      
      
      float totalcount_disk2combinedring1=0;
      float totalcounterror_disk2combinedring1=0;
      
      float totalcount_disk2combinedring2=0;
      float totalcounterror_disk2combinedring2=0;
      
      float totalcount_disk2combinedring3=0;
      float totalcounterror_disk2combinedring3=0;
      
      float totalcount_disk2combinedring4=0;
      float totalcounterror_disk2combinedring4=0;
      
      float totalcount_disk2combinedring5=0;
      float totalcounterror_disk2combinedring5=0;
      
      
      float totalcount_disk3combinedring1=0;
      float totalcounterror_disk3combinedring1=0;
      
      float totalcount_disk3combinedring2=0;
      float totalcounterror_disk3combinedring2=0;
      
      float totalcount_disk3combinedring3=0;
      float totalcounterror_disk3combinedring3=0;
      
      float totalcount_disk3combinedring4=0;
      float totalcounterror_disk3combinedring4=0;
      
      float totalcount_disk3combinedring5=0;
      float totalcounterror_disk3combinedring5=0;
      
      
      float totalcount_disk4combinedring1=0;
      float totalcounterror_disk4combinedring1=0;
      
      float totalcount_disk4combinedring2=0;
      float totalcounterror_disk4combinedring2=0;
      
      float totalcount_disk4combinedring3=0;
      float totalcounterror_disk4combinedring3=0;
      
      float totalcount_disk4combinedring4=0;
      float totalcounterror_disk4combinedring4=0;
      
      float totalcount_disk4combinedring5=0;
      float totalcounterror_disk4combinedring5=0;
      
      
      for (int d = 0; d < disklist.size(); d++) {
	
	TString histoname = "BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";
	
	TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
        std::cout << "Value of d "<< d << " disklist " << disklist[d].c_str() << std::endl;
	Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
	Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	
	for (int r = 0; r < 5; r++) {
	  
	  float count = Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1);
	  float counterror = Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1);
	  
	  TEPXClustersPerEvent1[d][r]->SetPoint(pu, pumap[pulist[pu]], count);
	  TEPXClustersPerEvent1[d][r]->SetPointError(pu, 0, counterror);
	  
	  
          
	  if ((d == 3 || d == 4) && r == 0) {
	    
	    totalcount_disk1combinedring1+=count;
	    totalcounterror_disk1combinedring1+= counterror * counterror;
            
	    
	  }
	  
	  
	  if ((d == 3 || d == 4) && r == 1) {
	    
	    totalcount_disk1combinedring2+=count;
	    totalcounterror_disk1combinedring2+= counterror * counterror;
	    
	  }
	  
	  
	  
	  if ((d == 3 || d == 4) && r == 2) {
	    
	    
	    totalcount_disk1combinedring3+=count;
	    totalcounterror_disk1combinedring3+= counterror * counterror;
	  }
	  
	  
	  if ((d == 3 || d == 4) && r == 3) {
	    
	    totalcount_disk1combinedring4+=count;
	    totalcounterror_disk1combinedring4+= counterror * counterror;
	    
	  }
	  
	  
	  if ((d == 3 || d == 4) && r == 4) {
	    
	    totalcount_disk1combinedring5+=count;
	    totalcounterror_disk1combinedring5+= counterror * counterror;
	    
	  }
	  
	  
	  if((d == 2 || d == 5) && r == 0) {
	    
	    
	    totalcount_disk2combinedring1+=count;
	    totalcounterror_disk2combinedring1+= counterror * counterror;
	  }
	  
	  
	  if((d == 2 || d == 5) && r == 1) {
	    
	    totalcount_disk2combinedring2+=count;
	    totalcounterror_disk2combinedring2+= counterror * counterror;
	    
	  }
	  
	  
	  if((d == 2 || d == 5) && r == 2) {
	    
	    totalcount_disk2combinedring3+=count;
	    totalcounterror_disk2combinedring3+= counterror * counterror;
	  }
	  
	  
	  if((d == 2 || d == 5) && r == 3) {
	    
	    totalcount_disk2combinedring4+=count;
	    totalcounterror_disk2combinedring4+= counterror * counterror;
	  }
	  
	  
	  if((d == 2 || d == 5) && r == 4) {
	    
	    totalcount_disk2combinedring5+=count;
	    totalcounterror_disk2combinedring5+= counterror * counterror;
	  }
	  
	  
	  
	  if((d == 1 || d == 6) && r == 0) {
	    
	    totalcount_disk3combinedring1+=count;
	    totalcounterror_disk3combinedring1+= counterror * counterror;
	    
	  }
	  
	  
	  if((d == 1 || d == 6) && r == 1) {
	    
	    totalcount_disk3combinedring2+=count;
	    totalcounterror_disk3combinedring2+= counterror * counterror;
	    
	    
	  }
	  
	  if((d == 1 || d == 6) && r == 2) {
	    
	    totalcount_disk3combinedring3+=count;
	    totalcounterror_disk3combinedring3+= counterror * counterror;
	    
	    
	  }
	  
	  
	  if((d == 1 || d == 6) && r == 3) {
	    
	    totalcount_disk3combinedring4+=count;
	    totalcounterror_disk3combinedring4+= counterror * counterror;
	    
	    
	  }
	  
	  
	  if((d == 1 || d == 6) && r == 4) {
	    
	    totalcount_disk3combinedring5+=count;
	    totalcounterror_disk3combinedring5+= counterror * counterror;
	    
	    
	  }
	  
	  
	  if((d == 0 || d == 7) && r == 0) {
	    
	    totalcount_disk4combinedring1+=count;
	    totalcounterror_disk4combinedring1+= counterror * counterror;
	    
	  }
	  
	  
	  if((d == 0 || d == 7) && r == 1) {
	    
	    totalcount_disk4combinedring2+=count;
	    totalcounterror_disk4combinedring2+= counterror * counterror;
	    
	  }
	  
	  
	  
	  if((d == 0 || d == 7) && r == 2) {
	    
	    totalcount_disk4combinedring3+=count;
	    totalcounterror_disk4combinedring3+= counterror * counterror;
	    
	  }
	  
	  
	  
	  if((d == 0 || d == 7) && r == 3) {
	    
	    totalcount_disk4combinedring4+=count;
	    totalcounterror_disk4combinedring4+= counterror * counterror;
	    
	  }
	  
	  
	  if((d == 0 || d == 7) && r == 4) {
	    
	    totalcount_disk4combinedring5+=count;
	    totalcounterror_disk4combinedring5+= counterror * counterror;
	    
	  }
	  
	  
	  if (d == 3) {
	    
	    totalcount_disk1+=count;
	    totalcounterror_disk1+= counterror * counterror;
	    
	  }
	  
          //cout << "disk1(-Z) count "<<totalcount_disk1 << endl;	  
	  
	  if(d == 4) {
	    
	    totalcount_disk5+=count;
	    totalcounterror_disk5+= counterror * counterror;
	    
	  }
	  
          //cout << "disk1(+Z) count "<<totalcount_disk5 << endl;
	  
	  if (d == 3 || d == 4) {
	    
	    totalcount_disk1combined+=count;
	    totalcounterror_disk1combined+= counterror * counterror;
	    
	  }
	  
          //cout <<"disk1 combined count "<< totalcount_disk1combined << endl;
	  
	  
	  if (d == 2) {
	    
	    totalcount_disk2+=count;
	    totalcounterror_disk2+= counterror * counterror;
	    
	  }
	  
          //cout << "disk2(-Z) count "<<totalcount_disk2 << endl;
	  
	  if(d == 5) {
	    
	    totalcount_disk6+=count;
	    totalcounterror_disk6+= counterror * counterror;
	    
	  }
	  
          //cout << "disk2(+Z) count "<<totalcount_disk6 << endl;
	  
	  if(d == 2 || d == 5) {
	    
            totalcount_disk2combined+=count;
	    totalcounterror_disk2combined+= counterror * counterror;
	  }
	  
	  //cout <<"disk2 combined count "<< totalcount_disk2combined << endl;
	  
	  if (d == 1) {
	    
	    totalcount_disk3+=count;
	    totalcounterror_disk3+= counterror * counterror;
	    
	  }
	  
          //cout << "disk3(-Z) count "<<totalcount_disk3 << endl;
	  
	  
	  if(d == 6) {
	    
	    totalcount_disk7+=count;
	    totalcounterror_disk7+= counterror * counterror;
	    
	  }
	  
	  //cout << "disk3(+Z) count "<<totalcount_disk7 << endl;
	  
	  if(d == 1 || d == 6) {
	    
            totalcount_disk3combined+=count;
	    totalcounterror_disk3combined+= counterror * counterror;
	    
	  }
	  
          //cout <<"disk3 combined count "<< totalcount_disk3combined << endl;
	  
	  
	  if (d == 0) {
	    
	    totalcount_disk4+=count;
	    totalcounterror_disk4+= counterror * counterror;
	    
	  }
	  
	  //cout << "disk4(-Z) count "<<totalcount_disk4 << endl;
	  
	  
	  if (d == 7) {
	    
	    totalcount_disk8+=count;
	    totalcounterror_disk8+= counterror * counterror;
	    
	  }
	  
	  //cout << "disk4(+Z) count "<<totalcount_disk8 << endl;  
	  
          if(d == 0 || d == 7) {
	    
            totalcount_disk4combined+=count;
	    totalcounterror_disk4combined+= counterror * counterror;
	    
	    
	  }
	  
	  //cout <<"disk4 combined count "<< totalcount_disk4combined << endl;
	  
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
      

      TEPXClustersPerEvent_disk5->SetPoint(pu, pumap[pulist[pu]], totalcount_disk5);
      TEPXClustersPerEvent_disk5->SetPointError(pu, 0, sqrt(totalcounterror_disk5));
      
      TEPXClustersPerEvent_disk6->SetPoint(pu, pumap[pulist[pu]], totalcount_disk6);
      TEPXClustersPerEvent_disk6->SetPointError(pu, 0, sqrt(totalcounterror_disk6));
      
      TEPXClustersPerEvent_disk7->SetPoint(pu, pumap[pulist[pu]], totalcount_disk7);
      TEPXClustersPerEvent_disk7->SetPointError(pu, 0, sqrt(totalcounterror_disk7));
      
      TEPXClustersPerEvent_disk8->SetPoint(pu, pumap[pulist[pu]], totalcount_disk8);
      TEPXClustersPerEvent_disk8->SetPointError(pu, 0, sqrt(totalcounterror_disk8));
      
      
      TEPXClustersPerEvent_D4R1->SetPoint(pu, pumap[pulist[pu]], totalcount_D4R1);
      TEPXClustersPerEvent_D4R1->SetPointError(pu, 0, sqrt(totalcounterror_D4R1));
      
      
      TEPXClustersPerEvent_disk1combined->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1combined);
      TEPXClustersPerEvent_disk1combined->SetPointError(pu, 0, sqrt(totalcounterror_disk1combined));
      
      TEPXClustersPerEvent_disk2combined->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2combined);
      TEPXClustersPerEvent_disk2combined->SetPointError(pu, 0, sqrt(totalcounterror_disk2combined));
      
      TEPXClustersPerEvent_disk3combined->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3combined);
      TEPXClustersPerEvent_disk3combined->SetPointError(pu, 0, sqrt(totalcounterror_disk3combined));
      
      TEPXClustersPerEvent_disk4combined->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4combined);
      TEPXClustersPerEvent_disk4combined->SetPointError(pu, 0, sqrt(totalcounterror_disk4combined));
      
      
      TEPXClustersPerEvent_disk1combinedring1->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1combinedring1);
      TEPXClustersPerEvent_disk1combinedring1->SetPointError(pu, 0, sqrt(totalcounterror_disk1combinedring1));
      
      TEPXClustersPerEvent_disk1combinedring2->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1combinedring2);
      TEPXClustersPerEvent_disk1combinedring2->SetPointError(pu, 0, sqrt(totalcounterror_disk1combinedring2));
      
      TEPXClustersPerEvent_disk1combinedring3->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1combinedring3);
      TEPXClustersPerEvent_disk1combinedring3->SetPointError(pu, 0, sqrt(totalcounterror_disk1combinedring3));
      
      TEPXClustersPerEvent_disk1combinedring4->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1combinedring4);
      TEPXClustersPerEvent_disk1combinedring4->SetPointError(pu, 0, sqrt(totalcounterror_disk1combinedring4));
      
      TEPXClustersPerEvent_disk1combinedring5->SetPoint(pu, pumap[pulist[pu]], totalcount_disk1combinedring5);
      TEPXClustersPerEvent_disk1combinedring5->SetPointError(pu, 0, sqrt(totalcounterror_disk1combinedring5));
      
      
      TEPXClustersPerEvent_disk2combinedring1->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2combinedring1);
      TEPXClustersPerEvent_disk2combinedring1->SetPointError(pu, 0, sqrt(totalcounterror_disk2combinedring1));
      
      TEPXClustersPerEvent_disk2combinedring2->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2combinedring2);
      TEPXClustersPerEvent_disk2combinedring2->SetPointError(pu, 0, sqrt(totalcounterror_disk2combinedring2));
      
      TEPXClustersPerEvent_disk2combinedring3->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2combinedring3);
      TEPXClustersPerEvent_disk2combinedring3->SetPointError(pu, 0, sqrt(totalcounterror_disk2combinedring3));
      
      TEPXClustersPerEvent_disk2combinedring4->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2combinedring4);
      TEPXClustersPerEvent_disk2combinedring4->SetPointError(pu, 0, sqrt(totalcounterror_disk2combinedring4));
      
      TEPXClustersPerEvent_disk2combinedring5->SetPoint(pu, pumap[pulist[pu]], totalcount_disk2combinedring5);
      TEPXClustersPerEvent_disk2combinedring5->SetPointError(pu, 0, sqrt(totalcounterror_disk2combinedring5));

      
      TEPXClustersPerEvent_disk3combinedring1->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3combinedring1);
      TEPXClustersPerEvent_disk3combinedring1->SetPointError(pu, 0, sqrt(totalcounterror_disk3combinedring1));
      
      TEPXClustersPerEvent_disk3combinedring2->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3combinedring2);
      TEPXClustersPerEvent_disk3combinedring2->SetPointError(pu, 0, sqrt(totalcounterror_disk3combinedring2));
      
      TEPXClustersPerEvent_disk3combinedring3->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3combinedring3);
      TEPXClustersPerEvent_disk3combinedring3->SetPointError(pu, 0, sqrt(totalcounterror_disk3combinedring3));
      
      TEPXClustersPerEvent_disk3combinedring4->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3combinedring4);
      TEPXClustersPerEvent_disk3combinedring4->SetPointError(pu, 0, sqrt(totalcounterror_disk3combinedring4));
      
      TEPXClustersPerEvent_disk3combinedring5->SetPoint(pu, pumap[pulist[pu]], totalcount_disk3combinedring5);
      TEPXClustersPerEvent_disk3combinedring5->SetPointError(pu, 0, sqrt(totalcounterror_disk3combinedring5));
      

      TEPXClustersPerEvent_disk4combinedring1->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4combinedring1);
      TEPXClustersPerEvent_disk4combinedring1->SetPointError(pu, 0, sqrt(totalcounterror_disk4combinedring1));
      
      TEPXClustersPerEvent_disk4combinedring2->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4combinedring2);
      TEPXClustersPerEvent_disk4combinedring2->SetPointError(pu, 0, sqrt(totalcounterror_disk4combinedring2));
      
      TEPXClustersPerEvent_disk4combinedring3->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4combinedring3);
      TEPXClustersPerEvent_disk4combinedring3->SetPointError(pu, 0, sqrt(totalcounterror_disk4combinedring3));
      
      TEPXClustersPerEvent_disk4combinedring4->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4combinedring4);
      TEPXClustersPerEvent_disk4combinedring4->SetPointError(pu, 0, sqrt(totalcounterror_disk4combinedring4));
      
      TEPXClustersPerEvent_disk4combinedring5->SetPoint(pu, pumap[pulist[pu]], totalcount_disk4combinedring5);
      TEPXClustersPerEvent_disk4combinedring5->SetPointError(pu, 0, sqrt(totalcounterror_disk4combinedring5));
      
    }
  }
  
  
  TEPXClustersPerEvent->SetMarkerSize(2);
  TEPXClustersPerEvent->SetMarkerColor(2);
  TEPXClustersPerEvent->SetName(TString("clusters_TEPX"));  
  f->WriteTObject(TEPXClustersPerEvent);
  
  TEPXClustersPerEvent_D4R1->SetMarkerSize(2);
  TEPXClustersPerEvent_D4R1->SetMarkerColor(2);
  TEPXClustersPerEvent_D4R1->SetName(TString("clusters_TEPXD4R1"));  
  f->WriteTObject(TEPXClustersPerEvent_D4R1);
  
  TEPXClustersPerEvent_disk1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1->SetName(TString("clusters_D-4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1);
  
  TEPXClustersPerEvent_disk2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2->SetName(TString("clusters_D-3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2);
  
  TEPXClustersPerEvent_disk3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3->SetName(TString("clusters_D-2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3);
  
  TEPXClustersPerEvent_disk4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4->SetName(TString("clusters_D-1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4);
  
  
  TEPXClustersPerEvent_disk5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk5->SetName(TString("clusters_D1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk5);
  
  TEPXClustersPerEvent_disk6->SetMarkerSize(2);
  TEPXClustersPerEvent_disk6->SetMarkerColor(2);
  TEPXClustersPerEvent_disk6->SetName(TString("clusters_D2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk6);
  
  TEPXClustersPerEvent_disk7->SetMarkerSize(2);
  TEPXClustersPerEvent_disk7->SetMarkerColor(2);
  TEPXClustersPerEvent_disk7->SetName(TString("clusters_D3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk7);
  
  TEPXClustersPerEvent_disk8->SetMarkerSize(2);
  TEPXClustersPerEvent_disk8->SetMarkerColor(2);
  TEPXClustersPerEvent_disk8->SetName(TString("clusters_D4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk8);
  

  TEPXClustersPerEvent_disk1combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combined->SetName(TString("clusters_combinedD1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combined);
  
  TEPXClustersPerEvent_disk2combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combined->SetName(TString("clusters_combinedD2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combined);
  
  TEPXClustersPerEvent_disk3combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combined->SetName(TString("clusters_combinedD3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combined);
  
  TEPXClustersPerEvent_disk4combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combined->SetName(TString("clusters_combinedD4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combined);
  
  
  TEPXClustersPerEvent_disk1combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring1->SetName(TString("clusters_combinedD1R1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring1);
  
  TEPXClustersPerEvent_disk1combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring2->SetName(TString("clusters_combinedD1R2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring2);
  
  TEPXClustersPerEvent_disk1combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring3->SetName(TString("clusters_combinedD1R3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring3);
  
  TEPXClustersPerEvent_disk1combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring4->SetName(TString("clusters_combinedD1R4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring4);
  
  TEPXClustersPerEvent_disk1combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring5->SetName(TString("clusters_combinedD1R5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring5);
  
 
  TEPXClustersPerEvent_disk2combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring1->SetName(TString("clusters_combinedD2R1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring1);
  
  TEPXClustersPerEvent_disk2combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring2->SetName(TString("clusters_combinedD2R2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring2);
  
  TEPXClustersPerEvent_disk2combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring3->SetName(TString("clusters_combinedD2R3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring3);
  
  TEPXClustersPerEvent_disk2combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring4->SetName(TString("clusters_combinedD2R4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring4);
  
  TEPXClustersPerEvent_disk2combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring5->SetName(TString("clusters_combinedD2R5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring5);

 
  TEPXClustersPerEvent_disk3combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring1->SetName(TString("clusters_combinedD3R1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring1);
  
  TEPXClustersPerEvent_disk3combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring2->SetName(TString("clusters_combinedD3R2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring2);
  
  TEPXClustersPerEvent_disk3combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring3->SetName(TString("clusters_combinedD3R3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring3);
  
  TEPXClustersPerEvent_disk3combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring4->SetName(TString("clusters_combinedD3R4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring4);
  
  TEPXClustersPerEvent_disk3combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring5->SetName(TString("clusters_combinedD3R5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring5);
  
  
  TEPXClustersPerEvent_disk4combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring1->SetName(TString("clusters_combinedD4R1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring1);
  
  TEPXClustersPerEvent_disk4combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring2->SetName(TString("clusters_combinedD4R2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring2);
  
  TEPXClustersPerEvent_disk4combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring3->SetName(TString("clusters_combinedD4R3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring3);
  
  TEPXClustersPerEvent_disk4combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring4->SetName(TString("clusters_combinedD4R4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring4);
  
  TEPXClustersPerEvent_disk4combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring5->SetName(TString("clusters_combinedD4R5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring5);
  
  
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++){
      
      TEPXClustersPerEvent1[d][r]->SetMarkerSize(2);
      TEPXClustersPerEvent1[d][r]->SetMarkerColor(2);
      
      if (d <= 3) {
	TEPXClustersPerEvent1[d][r]->SetName(TString("clusters_") + "D" + (d-4) + "R" + (r+1));
      } else {
	
	TEPXClustersPerEvent1[d][r]->SetName(TString("clusters_") + "D" + (d-3) + "R" + (r+1));
      }
      
      f->WriteTObject(TEPXClustersPerEvent1[d][r]);
      
    }
  }
}






