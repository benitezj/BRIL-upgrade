void merge() {
  
  TFile *f = new TFile("./TDRplots_2xcoincidences.root","RECREATE");
  
  f->cd();
  gDirectory->pwd();
  f->ls();
  
  std::vector<std::string> disklist = { "1", "2", "3", "4" };
  std::vector<std::string> ringlist = { "1", "2", "3", "4" ,"5"};
  std::vector<std::string> ringlist1 = { "1", "2", "3", "4"};
  std::vector<std::string> sidelist = { "1", "2" };
  
  TGraphErrors* G[50][50][50];
  TGraphErrors* G1[50][50][50];
  TGraphErrors* G2[50][50][50];
  
  TGraphErrors* J[50];
  TGraphErrors* J1[50];
  TGraphErrors* J2[50];
  
  TGraphErrors* K[50];
  TGraphErrors* K1[50];
  TGraphErrors* K2[50];
  
  TGraphErrors* L[50];
  TGraphErrors* L1[50];
  TGraphErrors* L2[50];
  
  
  TGraphErrors* A;
  TGraphErrors* B;
  TGraphErrors* C;
  
  TFile F("./TDRplots_2xinphi.root", "read");
  gROOT->cd();
  
  TFile F1("./TDRplots_2xinR.root", "read");
  gROOT->cd();
  
  
  TFile F2("./TDRplots2x_phi_R.root", "read");
  gROOT->cd();
  
  A=(TGraphErrors*)F.Get("2xCoincidencesinphi_TEPX");
  B=(TGraphErrors*)F1.Get("2xCoincidencesinR_TEPX");
  C=(TGraphErrors*)F2.Get("2xCoincidences_TEPX");
  
  A->SetName("2xCoincidencesinphi_TEPX");
  B->SetName("2xCoincidencesinR_TEPX");
  C->SetName("2xCoincidences_TEPX"); 
  
  f->WriteTObject(A);
  f->WriteTObject(B);
  f->WriteTObject(C);
  
  
  for (int s = 0; s < sidelist.size(); s++){
    for (int d = 0; d < disklist.size(); d++){
      for (int r = 0; r < ringlist.size(); r++){
	
	G[s][d][r]=(TGraphErrors*)F.Get(TString("2xCoincidencesinphi") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1));
	if(!G[s][d][r]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinphi") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1)<<endl; return;}
	
	G[s][d][r]->SetName(TString("2xCoincidencesinphi") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1));  
	f->WriteTObject(G[s][d][r]);
	
	
	G2[s][d][r]=(TGraphErrors*)F2.Get(TString("2xCoincidences") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1));
	if(!G2[s][d][r]){ cout<<"Wrong graph name: "<<TString("2xCoincidences") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1)<<endl; return;}
	
	G2[s][d][r]->SetName(TString("2xCoincidences") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1));  
	f->WriteTObject(G2[s][d][r]);
	
      }
    }
  }
  
  
  for (int s = 0; s < sidelist.size(); s++){
    for (int d = 0; d < disklist.size(); d++){
      for (int r = 0; r < ringlist1.size(); r++){
	
	G1[s][d][r]=(TGraphErrors*)F1.Get(TString("2xCoincidencesinR") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1));
	if(!G1[s][d][r]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinR") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1)<<endl; return;}
	
	G1[s][d][r]->SetName(TString("2xCoincidencesinR") +"S"+(s+1)+"D" +(d+1) +"R"+(r+1));  
	f->WriteTObject(G1[s][d][r]);
	
      }
    }
  }
  
  for (int d = -4; d < 5; d++){
    if(d!=0) {
      
      J[d]=(TGraphErrors*)F.Get(TString("2xCoincidencesinphi_disk")+d);
      if(!J[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinphi_disk")+d<<endl; return;}
      
      J[d]->SetName(TString("2xCoincidencesinphi_disk")+d);  
      f->WriteTObject(J[d]);
      
      J1[d]=(TGraphErrors*)F1.Get(TString("2xCoincidencesinR_disk")+d);
      if(!J1[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinR_disk")+d<<endl; return;}
      
      J1[d]->SetName(TString("2xCoincidencesinR_disk")+d);  
      f->WriteTObject(J1[d]);
      
      J2[d]=(TGraphErrors*)F2.Get(TString("2xCoincidences_disk")+d);
      if(!J2[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidences_disk")+d<<endl; return;}
      
      J2[d]->SetName(TString("2xCoincidences_disk")+d);  
      f->WriteTObject(J2[d]);
    }
  }
  
  
  
  for (int d = 1; d < 5; d++){
    
    K[d]=(TGraphErrors*)F.Get(TString("2xCoincidencesinphi_disk")+d+"combined");
    if(!K[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinphi_disk")+d+"combined"<<endl; return;}
    
    K[d]->SetName(TString("2xCoincidencesinphi_disk")+d+"combined");  
    f->WriteTObject(K[d]);
    
    K1[d]=(TGraphErrors*)F1.Get(TString("2xCoincidencesinR_disk")+d+"combined");
    if(!K1[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinR_disk")+d+"combined"<<endl; return;}
    
    K1[d]->SetName(TString("2xCoincidencesinR_disk")+d+"combined");  
    f->WriteTObject(K1[d]);
    
    K2[d]=(TGraphErrors*)F2.Get(TString("2xCoincidences_disk")+d+"combined");
    if(!K2[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidences_disk")+d+"combined"<<endl; return;}
    
    K2[d]->SetName(TString("2xCoincidences_disk")+d+"combined");  
    f->WriteTObject(K2[d]);
    
  }
  
  
  for (int d = 1; d < 5; d++){
    for (int r = 0; r < ringlist.size(); r++){
      
      L[d]=(TGraphErrors*)F.Get(TString("2xCoincidencesinphi_disk")+d+"combinedring"+(r+1));
      if(!L[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinphi_disk")+d+"combinedring"+(r+1)<<endl; return;}
      
      L[d]->SetName(TString("2xCoincidencesinphi_disk")+d+"combinedring"+(r+1));  
      f->WriteTObject(L[d]);
      
      L2[d]=(TGraphErrors*)F2.Get(TString("2xCoincidences_disk")+d+"combinedring"+(r+1));
      if(!L2[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidences_disk")+d+"combinedring"+(r+1)<<endl; return;}
      
      L2[d]->SetName(TString("2xCoincidences_disk")+d+"combinedring"+(r+1));  
      f->WriteTObject(L2[d]);
      
    }
  }
  
  
  for (int d = 1; d < 5; d++){
    for (int r = 0; r < ringlist1.size(); r++){
      
      L1[d]=(TGraphErrors*)F1.Get(TString("2xCoincidencesinR_disk")+d+"combinedring"+(r+1));
      if(!L1[d]){ cout<<"Wrong graph name: "<<TString("2xCoincidencesinR_disk")+d+"combinedring"+(r+1)<<endl; return;}
      
      L1[d]->SetName(TString("2xCoincidencesinR_disk")+d+"combinedring"+(r+1));  
      f->WriteTObject(L1[d]);
    }
  }    
}
