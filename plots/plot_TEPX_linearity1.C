void plot_TEPX_linearity(){

  int option = 1;
  
  TString outputpath1 = "/home/ashish/TEPX_plot/Clusters/2D clusters Histograms/";
  TString outputpath2 = "/home/ashish/TEPX_plot/Clusters/Projection/";
  TString outputpath3 = "/home/ashish/TEPX_plot/Clusters/clusters_Fit/";
  TString outputpath4 = "/home/ashish/TEPX_plot/Clusters/Extrapolation/";
  TString outputpath5 = "/home/ashish/TEPX_plot/Clusters/AllPU_residuals/";

  TString outputpath6 = "/home/ashish/TEPX_plot/2x Coincidences/2x Coincidences 2D Histograms/";
  TString outputpath7 = "/home/ashish/TEPX_plot/2x Coincidences/Projection/";
  TString outputpath8 = "/home/ashish/TEPX_plot/2x Coincidences/2x Coincidences_Fit/";
  TString outputpath9 = "/home/ashish/TEPX_plot/2x Coincidences/Extrapolation/";
  TString outputpath10 = "/home/ashish/TEPX_plot/2x Coincidences/AllPU_residuals/";

  TString outputpath11 = "/home/ashish/TEPX_plot/3x Coincidences/3x Coincidences 2D Histograms/";
  TString outputpath12 = "/home/ashish/TEPX_plot/3x Coincidences/Projection/";
  TString outputpath13 = "/home/ashish/TEPX_plot/3x Coincidences/3x Coincidences_Fit/";
  TString outputpath14 = "/home/ashish/TEPX_plot/3x Coincidences/Extrapolation/";
  TString outputpath15 = "/home/ashish/TEPX_plot/3x Coincidences/AllPU_residuals/";

  TString inpath = "/home/ashish/TEPX/samples_17Feb2020/";

  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
    
  //string containing names of input sample files
  std::vector<std::string> pulist = { "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = { { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  std::vector<std::string> disklist = { "-4", "-3", "-2", "-1", "1", "2", "3", "4" };

  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent[20][4]; //number of clusters vs pu
  TH2F* Histogram2D[11][16];
  TH1D* ProjectionY[20][20];
  TH1D* ProjectionY1[20][20];
  TH1D* ProjectionY2[20][20];
  TH1D* ProjectionY3[20][20];
  TH1D* ProjectionY4[20][20];
    
    
  for (int pu = 0; pu < pulist.size(); pu++) {
    for (int d = 0; d < disklist.size(); d++){
      for (int r = 0; r <= 5; r++){
	TEPXClustersPerEvent[d][r] = new TGraphErrors();
	ProjectionY[pu][d] = new TH1D();
	ProjectionY1[pu][d] = new TH1D();
	ProjectionY2[pu][d] = new TH1D();
	ProjectionY3[pu][d] = new TH1D();
	ProjectionY4[pu][d] = new TH1D();
      }
    }
  }

  //Non-linearity graphs
  TGraphErrors* NonLinearity_TEPXClustersPerEvent[20][4]; //number of clusters vs pu
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++) {
      NonLinearity_TEPXClustersPerEvent[d][r] = new TGraphErrors();
           
    }
  }
    
    

  //read the histograms
  TProfile* Prof_TEPXClustersPerEvent[20][20]; //array pu,disk
  for (int pu = 0; pu < pulist.size(); pu++) {
    TFile F(inpath + pulist[pu].c_str() + ".root", "read");
    gROOT->cd();

	
    for (int d = 0; d < disklist.size(); d++) {
      if (option == 1){

	//draw the 2D Cluster distributions for all PU
	TString histoname = "BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";

	TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));

        //Define and Rebin ProjectionY for all Rings
	ProjectionY[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 1, 1)->Clone(TString(H->GetName()) +             "Projection");
        ProjectionY[pu][d] ->Rebin(10);

	ProjectionY1[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 2,2)->Clone(TString(H->GetName()) +             "Projection");
        ProjectionY1[pu][d] ->Rebin(10);

	ProjectionY2[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 3, 3)->Clone(TString(H->GetName()) +            "Projection");
        ProjectionY2[pu][d] ->Rebin(10);

	ProjectionY3[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 4, 4)->Clone(TString(H->GetName()) +            "Projection");
	ProjectionY3[pu][d] ->Rebin(10);

	ProjectionY4[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 5, 5)->Clone(TString(H->GetName()) +            "Projection");
        ProjectionY4[pu][d] ->Rebin(10);
            
	Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile"); //number of cluster vs ring

        //Draw 2D clusters histograms and ProjectionY for low PU
	if (pu < 4){
	  TCanvas *c1 = new TCanvas();
	  c1->cd();
	  Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, 350);
	  Histogram2D[pu][d]->Draw("colz");
	  char *hist2Dname = new char[10];
	  Int_t pud = pu * 8 + d + 1;
	  sprintf(hist2Dname,"histo2D_%d.gif",pud);
	  cout<<"=========================="<<hist2Dname<<endl;
	  c1->Print(outputpath1 + hist2Dname);
	  c1->Clear();
                
	  TCanvas *c2 = new TCanvas();
	  c2->cd();
	  ProjectionY[pu][d]->GetXaxis()->SetRangeUser(0, 60);
	  ProjectionY[pu][d]->GetYaxis()->SetRangeUser(0, 70000);
          ProjectionY[pu][d]->GetYaxis()->SetTitle("# of events");
	  ProjectionY[pu][d]->SetLineColor(5);
	  ProjectionY[pu][d]->Draw("same");
	  ProjectionY1[pu][d]->GetXaxis()->SetRangeUser(0, 60);
	  ProjectionY1[pu][d]->GetYaxis()->SetRangeUser(0, 70000);
	  ProjectionY1[pu][d]->SetLineColor(2);
	  ProjectionY1[pu][d]->Draw("same");
	  ProjectionY2[pu][d]->GetXaxis()->SetRangeUser(0, 60);
	  ProjectionY2[pu][d]->GetYaxis()->SetRangeUser(0, 70000);
	  ProjectionY2[pu][d]->SetLineColor(3);
	  ProjectionY2[pu][d]->Draw("same");
	  ProjectionY3[pu][d]->GetXaxis()->SetRangeUser(0, 60);
	  ProjectionY3[pu][d]->GetYaxis()->SetRangeUser(0, 70000);
	  ProjectionY3[pu][d]->SetLineColor(4);
	  ProjectionY3[pu][d]->Draw("same");
	  ProjectionY4[pu][d]->GetXaxis()->SetRangeUser(0, 60);
	  ProjectionY4[pu][d]->GetYaxis()->SetRangeUser(0, 70000);
	  ProjectionY4[pu][d]->SetLineColor(6);
	  ProjectionY4[pu][d]->Draw("same");
                
               

	  auto legend1 = new TLegend(0.7,0.7,0.88,0.88);
	  legend1->AddEntry(ProjectionY[pu][d], "Ring 1" ,"l");
	  legend1->AddEntry(ProjectionY1[pu][d], "Ring 2" ,"l");
	  legend1->AddEntry(ProjectionY2[pu][d], "Ring 3" ,"l");
	  legend1->AddEntry(ProjectionY3[pu][d], "Ring 4" ,"l");
	  legend1->AddEntry(ProjectionY4[pu][d], "Ring 5" ,"l");

	  legend1->SetFillColor(0);
	  legend1->SetLineColor(0);
	  legend1->SetFillColor(0);
	  legend1->Draw();
	  char *Projection = new char[12];
	  Int_t pro = pu * 8 + d + 1;
	  sprintf(Projection,"Projection_%d.gif",pro);
	  cout<<"=========================="<<Projection<<endl;
	  c2->Print(outputpath2 + Projection);
	  c2->Clear();
	}

        //Draw 2D clusters Histograms and ProjectionY for high PU
	if (pu >= 4){

	  TCanvas *c3 = new TCanvas();
	  c3->cd();
	  Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, 3500);
	  Histogram2D[pu][d]->Draw("colz");
	  char *hist2Dname = new char[10];
	  Int_t pud1 = pu * 8 + d + 1;
	  sprintf(hist2Dname,"histo2D_%d.gif",pud1);
	  cout<<"=========================="<<hist2Dname<<endl;
	  c3->Print(outputpath1 + hist2Dname);
	  c3->Clear();

                
	  TCanvas *c4 = new TCanvas();
	  c4->cd();
	  ProjectionY[pu][d]->GetXaxis()->SetRangeUser(0, 1500);
	  ProjectionY[pu][d]->GetYaxis()->SetRangeUser(0, 1000);
	  ProjectionY[pu][d]->GetYaxis()->SetTitle("# of events");
	  ProjectionY[pu][d]->SetLineColor(5);
	  ProjectionY[pu][d]->Draw("same");
	  ProjectionY1[pu][d]->GetXaxis()->SetRangeUser(0, 1500);
	  ProjectionY1[pu][d]->GetYaxis()->SetRangeUser(0, 1000);
	  ProjectionY1[pu][d]->SetLineColor(2);
	  ProjectionY1[pu][d]->Draw("same");
	  ProjectionY2[pu][d]->GetXaxis()->SetRangeUser(0, 1500);
	  ProjectionY2[pu][d]->GetYaxis()->SetRangeUser(0, 1000);
	  ProjectionY2[pu][d]->SetLineColor(3);
	  ProjectionY2[pu][d]->Draw("same");
	  ProjectionY3[pu][d]->GetXaxis()->SetRangeUser(0, 1500);
	  ProjectionY3[pu][d]->GetYaxis()->SetRangeUser(0, 1000);
	  ProjectionY3[pu][d]->SetLineColor(4);
	  ProjectionY3[pu][d]->Draw("same");
	  ProjectionY4[pu][d]->GetXaxis()->SetRangeUser(0, 1500);
	  ProjectionY4[pu][d]->GetYaxis()->SetRangeUser(0, 1000);
	  ProjectionY4[pu][d]->SetLineColor(6);
	  ProjectionY4[pu][d]->Draw("same");

	  auto legend2 = new TLegend(0.7,0.7,0.88,0.88);
	  legend2->AddEntry(ProjectionY[pu][d], "Ring 1" ,"l");
	  legend2->AddEntry(ProjectionY1[pu][d], "Ring 2" ,"l");
	  legend2->AddEntry(ProjectionY2[pu][d], "Ring 3" ,"l");
	  legend2->AddEntry(ProjectionY3[pu][d], "Ring 4" ,"l");
	  legend2->AddEntry(ProjectionY4[pu][d], "Ring 5" ,"l");

	  legend2->SetFillColor(0);
	  legend2->SetLineColor(0);
	  legend2->SetFillColor(0);
	  legend2->Draw();
	  char *Projection = new char[12];
	  Int_t pro = pu * 8 + d + 1;
	  sprintf(Projection,"Projection_%d.gif",pro);
	  cout<<"=========================="<<Projection<<endl;
	  c4->Print(outputpath2 + Projection);
	  c4->Clear();
	      
	}

        //Draw ProjectionY for each Ring and Disk for low PU
	if(pu < 4){

	  TCanvas *c5 = new TCanvas();
	  c5->cd();
	  c5->SetLogy();

	  
	  ProjectionY[0][d]->GetXaxis()->SetRangeUser(0, 100);
          ProjectionY[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
          if (d <=3){
          ProjectionY[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 4) + " Ring 1");
	  }else{
	  ProjectionY[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 3) + " Ring 1");
	  }
	  ProjectionY[0][d]->SetLineColor(1);
	  ProjectionY[0][d]->Scale(1./ProjectionY[0][d]->Integral());
	  ProjectionY[0][d]->Draw("same");
	  
	 
	  ProjectionY[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[1][d]->SetLineColor(2);
	  ProjectionY[1][d]->Scale(1./ProjectionY[1][d]->Integral());
	  ProjectionY[1][d]->Draw("same");
          
	  
	  ProjectionY[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[2][d]->SetLineColor(3);
	  ProjectionY[2][d]->Scale(1./ProjectionY[2][d]->Integral());
	  ProjectionY[2][d]->Draw("same");

	  
	  ProjectionY[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[3][d]->SetLineColor(4);
          ProjectionY[3][d]->Scale(1./ProjectionY[3][d]->Integral());
	  ProjectionY[3][d]->Draw("same");

		

	  auto legend3 = new TLegend(0.7,0.7,0.88,0.88);
	  legend3->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	  legend3->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	  legend3->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	  legend3->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");

	  legend3->SetFillColor(0);
	  legend3->SetLineColor(0);
	  legend3->SetFillColor(0);
	  legend3->Draw();

	  char *Projection11 = new char[10];
	  Int_t pro12 = d + 1;
	  sprintf(Projection11,"ProjectionRing1_%d.gif",pro12);
	  cout<<"=========================="<<Projection11<<endl;
	  c5->Print(outputpath2 + Projection11);
	  c5->Clear();

                
	  TCanvas *c6 = new TCanvas();
	  c6->cd();
	  c6->SetLogy();

	  ProjectionY1[0][d]->SetMinimum(0.011);
	  ProjectionY1[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY1[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 4) + " Ring 2");
	  }else{
	  ProjectionY1[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 3) + " Ring 2");
	  }
	  ProjectionY1[0][d]->SetLineColor(1);
	  ProjectionY1[0][d]->Scale(1./ProjectionY1[0][d]->Integral());
	  ProjectionY1[0][d]->Draw("same");

	  ProjectionY1[1][d]->SetMinimum(0.001);
	  ProjectionY1[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[1][d]->SetLineColor(2);
          ProjectionY1[1][d]->Scale(1./ProjectionY1[1][d]->Integral());
	  ProjectionY1[1][d]->Draw("same");
          
	  ProjectionY1[2][d]->SetMinimum(0.001);
	  ProjectionY1[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[2][d]->SetLineColor(3);
	  ProjectionY1[2][d]->Scale(1./ProjectionY1[2][d]->Integral());
	  ProjectionY1[2][d]->Draw("same");
	  
	  ProjectionY1[3][d]->SetMinimum(0.01);
	  ProjectionY1[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[3][d]->SetLineColor(4);
	  ProjectionY1[3][d]->Scale(1./ProjectionY1[3][d]->Integral());
	  ProjectionY1[3][d]->Draw("same");
	  
	  auto legend4 = new TLegend(0.7,0.7,0.88,0.88);
	  legend4->AddEntry(ProjectionY1[0][d], "pu = 0.5" ,"l");
	  legend4->AddEntry(ProjectionY1[1][d], "pu = 1" ,"l");
	  legend4->AddEntry(ProjectionY1[2][d], "pu = 1.5" ,"l");
	  legend4->AddEntry(ProjectionY1[3][d], "pu = 2" ,"l");

	  legend4->SetFillColor(0);
	  legend4->SetLineColor(0);
	  legend4->SetFillColor(0);
	  legend4->Draw();

	  char *Projection14 = new char[10];
	  Int_t pro14 = d + 1;
	  sprintf(Projection14,"ProjectionRing2_%d.gif",pro14);
	  cout<<"=========================="<<Projection14<<endl;
	  c6->Print(outputpath2 + Projection14);
	  c6->Clear();

	  TCanvas *c7 = new TCanvas();
	  c7->cd();
	  c7->SetLogy();
	  
	  ProjectionY2[0][d]->SetMinimum(0.001);
	  ProjectionY2[0][d]->GetXaxis()->SetRangeUser(0, 100);
          ProjectionY2[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY2[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 4) + " Ring 3");
	  }else{
	  ProjectionY2[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 3) + " Ring 3");
	  }
	  ProjectionY2[0][d]->SetLineColor(1);
	  ProjectionY2[0][d]->Scale(1./ProjectionY2[0][d]->Integral());
	  ProjectionY2[0][d]->Draw("same");
	  
	  ProjectionY2[1][d]->SetMinimum(0.001);
	  ProjectionY2[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[1][d]->SetLineColor(2);
          ProjectionY2[1][d]->Scale(1./ProjectionY2[1][d]->Integral());
	  ProjectionY2[1][d]->Draw("same");
               
	  ProjectionY2[2][d]->SetMinimum(0.001);
	  ProjectionY2[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[2][d]->SetLineColor(3);
	  ProjectionY2[2][d]->Scale(1./ProjectionY2[2][d]->Integral());
	  ProjectionY2[2][d]->Draw("same");

	  ProjectionY2[3][d]->SetMinimum(0.01);
	  ProjectionY2[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[3][d]->SetLineColor(4);
	  ProjectionY2[3][d]->Scale(1./ProjectionY2[3][d]->Integral());
	  ProjectionY2[3][d]->Draw("same");

	  auto legend5 = new TLegend(0.7,0.7,0.88,0.88);
	  legend5->AddEntry(ProjectionY1[0][d], "pu = 0.5" ,"l");
	  legend5->AddEntry(ProjectionY1[1][d], "pu = 1" ,"l");
	  legend5->AddEntry(ProjectionY1[2][d], "pu = 1.5" ,"l");
	  legend5->AddEntry(ProjectionY1[3][d], "pu = 2" ,"l");
	  
	  legend5->SetFillColor(0);
	  legend5->SetLineColor(0);
	  legend5->SetFillColor(0);
	  legend5->Draw();

	  char *Projection15 = new char[10];
	  Int_t pro15 = d + 1;
	  sprintf(Projection15,"ProjectionRing3_%d.gif",pro15);
	  cout<<"=========================="<<Projection15<<endl;
	  c7->Print(outputpath2 + Projection15);
	  c7->Clear();


	  TCanvas *c8 = new TCanvas();
	  c8->cd();
	  c8->SetLogy();
	  
	  ProjectionY3[0][d]->SetMinimum(0.011);
	  ProjectionY3[0][d]->GetXaxis()->SetRangeUser(0, 100);
          ProjectionY3[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY3[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 4) + " Ring 4");
	  }else{
	  ProjectionY3[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 3) + " Ring 4");
	  }
	  ProjectionY3[0][d]->SetLineColor(1);
          ProjectionY3[0][d]->Scale(1./ProjectionY3[0][d]->Integral());
	  ProjectionY3[0][d]->Draw("same");
	  
	  ProjectionY3[1][d]->SetMinimum(0.001);
	  ProjectionY3[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[1][d]->SetLineColor(2);
          ProjectionY3[1][d]->Scale(1./ProjectionY3[1][d]->Integral());
	  ProjectionY3[1][d]->Draw("same");
          
	  ProjectionY3[2][d]->SetMinimum(0.001);
	  ProjectionY3[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[2][d]->SetLineColor(3);
          ProjectionY3[2][d]->Scale(1./ProjectionY3[2][d]->Integral());
	  ProjectionY3[2][d]->Draw("same");

	  ProjectionY3[3][d]->SetMinimum(0.01);
	  ProjectionY3[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[3][d]->SetLineColor(4);
          ProjectionY3[3][d]->Scale(1./ProjectionY3[3][d]->Integral());
	  ProjectionY3[3][d]->Draw("same");

	  auto legend6 = new TLegend(0.7,0.7,0.88,0.88);
	  legend6->AddEntry(ProjectionY3[0][d], "pu = 0.5" ,"l");
	  legend6->AddEntry(ProjectionY3[1][d], "pu = 1" ,"l");
	  legend6->AddEntry(ProjectionY3[2][d], "pu = 1.5" ,"l");
	  legend6->AddEntry(ProjectionY3[3][d], "pu = 2" ,"l");

	  legend6->SetFillColor(0);
	  legend6->SetLineColor(0);
	  legend6->SetFillColor(0);
	  legend6->Draw();

	  char *Projection16 = new char[10];
	  Int_t pro16 = d + 1;
	  sprintf(Projection16,"ProjectionRing4_%d.gif",pro16);
	  cout<<"=========================="<<Projection16<<endl;
	  c8->Print(outputpath2 + Projection16);
	  c8->Clear();



	  TCanvas *c9 = new TCanvas();
	  c9->cd();
	  c9->SetLogy();
	  
	  ProjectionY4[0][d]->SetMinimum(0.011);
	  ProjectionY4[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY4[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 4) + " Ring 5");
	  }else{
	  ProjectionY4[0][d]->SetTitle(TString("Number of clusters for Disk ") + (d - 3) + " Ring 5");
	  }
	  ProjectionY4[0][d]->SetLineColor(1);
          ProjectionY4[0][d]->Scale(1./ProjectionY4[0][d]->Integral());
	  ProjectionY4[0][d]->Draw("same");
	  
	  ProjectionY4[1][d]->SetMinimum(0.001);
	  ProjectionY4[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[1][d]->SetLineColor(2);
          ProjectionY4[1][d]->Scale(1./ProjectionY4[1][d]->Integral());
	  ProjectionY4[1][d]->Draw("same");
          
	  ProjectionY4[2][d]->SetMinimum(0.001);
	  ProjectionY4[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[2][d]->SetLineColor(3);
          ProjectionY4[2][d]->Scale(1./ProjectionY4[2][d]->Integral());
	  ProjectionY4[2][d]->Draw("same");
	  
	  ProjectionY4[3][d]->SetMinimum(0.01);
	  ProjectionY4[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[3][d]->SetLineColor(4);
	  ProjectionY4[3][d]->Scale(1./ProjectionY4[3][d]->Integral());
	  ProjectionY4[3][d]->Draw("same");
	  
	  auto legend7 = new TLegend(0.7,0.7,0.88,0.88);
	  legend7->AddEntry(ProjectionY4[0][d], "pu = 0.5" ,"l");
	  legend7->AddEntry(ProjectionY4[1][d], "pu = 1" ,"l");
	  legend7->AddEntry(ProjectionY4[2][d], "pu = 1.5" ,"l");
	  legend7->AddEntry(ProjectionY4[3][d], "pu = 2" ,"l");
	  
	  legend7->SetFillColor(0);
	  legend7->SetLineColor(0);
	  legend7->SetFillColor(0);
	  legend7->Draw();
	  
	  char *Projection17 = new char[10];
	  Int_t pro17 = d + 1;
	  sprintf(Projection17,"ProjectionRing5_%d.gif",pro17);
	  cout<<"=========================="<<Projection17<<endl;
	  c9->Print(outputpath2 + Projection17);
	  c9->Clear();
	  
	}
	
        //Draw ProjectionY for each Ring and Disk for all PU
	TCanvas *c10 = new TCanvas();
	c10->cd();
	c10->SetLogy();
	
	ProjectionY[0][d]->SetMinimum(0.011);
	ProjectionY[0][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY[0][d]->SetLineColor(1);
        ProjectionY[0][d]->Scale(1./ProjectionY[0][d]->Integral());
        ProjectionY[0][d]->Draw("same");
	
	ProjectionY[1][d]->SetMinimum(0.001);
	ProjectionY[1][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[1][d]->SetLineColor(2);
        ProjectionY[1][d]->Scale(1./ProjectionY[1][d]->Integral());
	ProjectionY[1][d]->Draw("same");
        
	ProjectionY[2][d]->SetMinimum(0.001);
	ProjectionY[2][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[2][d]->SetLineColor(3);
        ProjectionY[2][d]->Scale(1./ProjectionY[2][d]->Integral());
	ProjectionY[2][d]->Draw("same");
	
	ProjectionY[3][d]->SetMinimum(0.01);
	ProjectionY[3][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[3][d]->SetLineColor(4);
        ProjectionY[3][d]->Scale(1./ProjectionY[3][d]->Integral());
	ProjectionY[3][d]->Draw("same");
	
	ProjectionY[4][d]->SetMinimum(0.01);
	ProjectionY[4][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[4][d]->SetLineColor(5);
        ProjectionY[4][d]->Scale(1./ProjectionY[4][d]->Integral());
	ProjectionY[4][d]->Draw("same");
	
	ProjectionY[5][d]->SetMinimum(0.01);
	ProjectionY[5][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[5][d]->SetLineColor(6);
	ProjectionY[5][d]->Scale(1./ProjectionY[5][d]->Integral());
	ProjectionY[5][d]->Draw("same");
	
	ProjectionY[6][d]->SetMinimum(0.01);
	ProjectionY[6][d]->GetXaxis()->SetRangeUser(0, 3000);
	
	ProjectionY[6][d]->SetLineColor(7);
        ProjectionY[6][d]->Scale(1./ProjectionY[6][d]->Integral());
	ProjectionY[6][d]->Draw("same");
	
	ProjectionY[7][d]->SetMinimum(0.01);
	ProjectionY[7][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[7][d]->SetLineColor(8);
        ProjectionY[7][d]->Scale(1./ProjectionY[7][d]->Integral());
	ProjectionY[7][d]->Draw("same");
	
	ProjectionY[8][d]->SetMinimum(0.01);
	ProjectionY[8][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[8][d]->SetLineColor(9);
	ProjectionY[8][d]->Scale(1./ProjectionY[8][d]->Integral());
	ProjectionY[8][d]->Draw("same");
	
	ProjectionY[9][d]->SetMinimum(0.01);
	ProjectionY[9][d]->GetXaxis()->SetRangeUser(0, 3000);
	ProjectionY[9][d]->SetLineColor(44);
	ProjectionY[9][d]->Scale(1./ProjectionY[9][d]->Integral());
	ProjectionY[9][d]->Draw("same");
	
	
	
	auto legend8 = new TLegend(0.7,0.7,0.88,0.88);
	legend8->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend8->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend8->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend8->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend8->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend8->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend8->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend8->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend8->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend8->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend8->SetFillColor(0);
	legend8->SetLineColor(0);
	legend8->SetFillColor(0);
	legend8->Draw();
	
	
	char *Projection12 = new char[10];
	Int_t pro13 = d + 1;
	sprintf(Projection12,"ProjectionsRing1_%d.gif",pro13);
	cout<<"=========================="<<Projection12<<endl;
	c10->Print(outputpath2 + Projection12);
	c10->Clear();
	
	
	
	
	
	TCanvas *c11 = new TCanvas();
	c11->cd();
	c11->SetLogy();
	
	ProjectionY1[0][d]->SetMinimum(0.011);
	ProjectionY1[0][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY1[0][d]->SetLineColor(1);
	ProjectionY1[0][d]->Scale(1./ProjectionY1[0][d]->Integral());
	ProjectionY1[0][d]->Draw("same");
	
	ProjectionY1[1][d]->SetMinimum(0.001);
	ProjectionY1[1][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[1][d]->SetLineColor(2);
	ProjectionY1[1][d]->Scale(1./ProjectionY1[1][d]->Integral());
	ProjectionY1[1][d]->Draw("same");
        
	ProjectionY1[2][d]->SetMinimum(0.001);
	ProjectionY1[2][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[2][d]->SetLineColor(3);
        ProjectionY1[2][d]->Scale(1./ProjectionY1[2][d]->Integral());
	ProjectionY1[2][d]->Draw("same");
	
	ProjectionY1[3][d]->SetMinimum(0.01);
	ProjectionY1[3][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[3][d]->SetLineColor(4);
	ProjectionY1[3][d]->Scale(1./ProjectionY1[3][d]->Integral());
	ProjectionY1[3][d]->Draw("same");
	
	ProjectionY1[4][d]->SetMinimum(0.01);
	ProjectionY1[4][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[4][d]->SetLineColor(5);
	ProjectionY1[4][d]->Scale(1./ProjectionY1[4][d]->Integral());
	ProjectionY1[4][d]->Draw("same");
	
	ProjectionY1[5][d]->SetMinimum(0.01);
	ProjectionY1[5][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[5][d]->SetLineColor(6);
	ProjectionY1[5][d]->Scale(1./ProjectionY1[5][d]->Integral());
	ProjectionY1[5][d]->Draw("same");
	
	ProjectionY1[6][d]->SetMinimum(0.01);
	ProjectionY1[6][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[6][d]->SetLineColor(7);
	ProjectionY1[6][d]->Scale(1./ProjectionY1[6][d]->Integral());
	ProjectionY1[6][d]->Draw("same");
	
	ProjectionY1[7][d]->SetMinimum(0.01);
	ProjectionY1[7][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[7][d]->SetLineColor(8);
	ProjectionY1[7][d]->Scale(1./ProjectionY1[7][d]->Integral());
	ProjectionY1[7][d]->Draw("same");
	
	ProjectionY1[8][d]->SetMinimum(0.01);
	ProjectionY1[8][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[8][d]->SetLineColor(9);
	ProjectionY1[8][d]->Scale(1./ProjectionY1[8][d]->Integral());
	ProjectionY1[8][d]->Draw("same");
	
	ProjectionY1[9][d]->SetMinimum(0.01);
	ProjectionY1[9][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY1[9][d]->SetLineColor(44);
	ProjectionY1[9][d]->Scale(1./ProjectionY1[9][d]->Integral());
	ProjectionY1[9][d]->Draw("same");
	
	
	
	auto legend9 = new TLegend(0.7,0.7,0.88,0.88);
	legend9->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend9->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend9->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend9->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend9->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend9->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend9->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend9->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend9->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend9->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend9->SetFillColor(0);
	legend9->SetLineColor(0);
	legend9->SetFillColor(0);
	legend9->Draw();
	
	
	char *Projection14 = new char[10];
	Int_t pro14 = d + 1;
	sprintf(Projection14,"ProjectionsRing2_%d.gif",pro14);
	cout<<"=========================="<<Projection14<<endl;
	c11->Print(outputpath2 + Projection14);
	c11->Clear();
	
	
	
	TCanvas *c12 = new TCanvas();
	c12->cd();
	c12->SetLogy();
	
	ProjectionY2[0][d]->SetMinimum(0.011);
	ProjectionY2[0][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY2[0][d]->SetLineColor(1);
        ProjectionY2[0][d]->Scale(1./ProjectionY2[0][d]->Integral());
	ProjectionY2[0][d]->Draw("same");
	
	ProjectionY2[1][d]->SetMinimum(0.001);
	ProjectionY2[1][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[1][d]->SetLineColor(2);
        ProjectionY2[1][d]->Scale(1./ProjectionY2[1][d]->Integral());
	ProjectionY2[1][d]->Draw("same");
        
	ProjectionY2[2][d]->SetMinimum(0.001);
	ProjectionY2[2][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[2][d]->SetLineColor(3);
        ProjectionY2[2][d]->Scale(1./ProjectionY2[2][d]->Integral());
	ProjectionY2[2][d]->Draw("same");
	
	ProjectionY2[3][d]->SetMinimum(0.01);
	ProjectionY2[3][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[3][d]->SetLineColor(4);
        ProjectionY2[3][d]->Scale(1./ProjectionY2[3][d]->Integral());
	ProjectionY2[3][d]->Draw("same");
	
	ProjectionY2[4][d]->SetMinimum(0.01);
	ProjectionY2[4][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[4][d]->SetLineColor(5);
	ProjectionY2[4][d]->Scale(1./ProjectionY2[4][d]->Integral());
	ProjectionY2[4][d]->Draw("same");
	
	ProjectionY2[5][d]->SetMinimum(0.01);
	ProjectionY2[5][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[5][d]->SetLineColor(6);
        ProjectionY2[5][d]->Scale(1./ProjectionY2[5][d]->Integral());
	ProjectionY2[5][d]->Draw("same");
	
	ProjectionY2[6][d]->SetMinimum(0.01);
	ProjectionY2[6][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[6][d]->SetLineColor(7);
        ProjectionY2[6][d]->Scale(1./ProjectionY2[6][d]->Integral());
	ProjectionY2[6][d]->Draw("same");
	
	ProjectionY2[7][d]->SetMinimum(0.01);
	ProjectionY2[7][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[7][d]->SetLineColor(8);
        ProjectionY2[7][d]->Scale(1./ProjectionY2[7][d]->Integral());
	ProjectionY2[7][d]->Draw("same");
	
	ProjectionY2[8][d]->SetMinimum(0.01);
	ProjectionY2[8][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[8][d]->SetLineColor(9);
        ProjectionY2[8][d]->Scale(1./ProjectionY2[8][d]->Integral());
	ProjectionY2[8][d]->Draw("same");
	
	ProjectionY2[9][d]->SetMinimum(0.01);
	ProjectionY2[9][d]->GetXaxis()->SetRangeUser(0, 2500);
	ProjectionY2[9][d]->SetLineColor(44);
        ProjectionY2[9][d]->Scale(1./ProjectionY2[9][d]->Integral());
	ProjectionY2[9][d]->Draw("same");
	
	
	
	auto legend10 = new TLegend(0.7,0.7,0.88,0.88);
	legend10->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend10->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend10->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend10->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend10->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend10->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend10->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend10->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend10->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend10->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend10->SetFillColor(0);
	legend10->SetLineColor(0);
	legend10->SetFillColor(0);
	legend10->Draw();
	
	
	char *Projection15 = new char[10];
	Int_t pro15 = d + 1;
	sprintf(Projection15,"ProjectionsRing3_%d.gif",pro15);
	cout<<"=========================="<<Projection15<<endl;
	c12->Print(outputpath2 + Projection15);
	c12->Clear();
	
	
	
	TCanvas *c13 = new TCanvas();
	c13->cd();
	c13->SetLogy();
	
	ProjectionY3[0][d]->SetMinimum(0.011);
	ProjectionY3[0][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY3[0][d]->SetLineColor(1);
	ProjectionY3[0][d]->Scale(1./ProjectionY3[0][d]->Integral());
	ProjectionY3[0][d]->Draw("same");
	
	ProjectionY3[1][d]->SetMinimum(0.001);
	ProjectionY3[1][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[1][d]->SetLineColor(2);
        ProjectionY3[1][d]->Scale(1./ProjectionY3[0][d]->Integral());
	ProjectionY3[1][d]->Draw("same");
        
	ProjectionY3[2][d]->SetMinimum(0.001);
	ProjectionY3[2][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[2][d]->SetLineColor(3);
	ProjectionY3[2][d]->Scale(1./ProjectionY3[2][d]->Integral());
	ProjectionY3[2][d]->Draw("same");
	
	ProjectionY3[3][d]->SetMinimum(0.01);
	ProjectionY3[3][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[3][d]->SetLineColor(4);
	ProjectionY3[3][d]->Scale(1./ProjectionY3[3][d]->Integral());
	ProjectionY3[3][d]->Draw("same");
	
	ProjectionY3[4][d]->SetMinimum(0.01);
	ProjectionY3[4][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[4][d]->SetLineColor(5);
	ProjectionY3[4][d]->Scale(1./ProjectionY3[4][d]->Integral());
	ProjectionY3[4][d]->Draw("same");
	
	ProjectionY3[5][d]->SetMinimum(0.01);
	ProjectionY3[5][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[5][d]->SetLineColor(6);
	ProjectionY3[5][d]->Scale(1./ProjectionY3[5][d]->Integral());
	ProjectionY3[5][d]->Draw("same");
	
	ProjectionY3[6][d]->SetMinimum(0.01);
	ProjectionY3[6][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[6][d]->SetLineColor(7);
	ProjectionY3[6][d]->Scale(1./ProjectionY3[6][d]->Integral());
	ProjectionY3[6][d]->Draw("same");
	
	ProjectionY3[7][d]->SetMinimum(0.01);
	ProjectionY3[7][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[7][d]->SetLineColor(8);
	ProjectionY3[7][d]->Scale(1./ProjectionY3[7][d]->Integral());
	ProjectionY3[7][d]->Draw("same");
	
	ProjectionY3[8][d]->SetMinimum(0.01);
	ProjectionY3[8][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[8][d]->SetLineColor(9);
	ProjectionY3[8][d]->Scale(1./ProjectionY3[8][d]->Integral());
	ProjectionY3[8][d]->Draw("same");

	ProjectionY3[9][d]->SetMinimum(0.01);
	ProjectionY3[9][d]->GetXaxis()->SetRangeUser(0, 2000);
	ProjectionY3[9][d]->SetLineColor(44);
	ProjectionY3[9][d]->Scale(1./ProjectionY3[9][d]->Integral());
	ProjectionY3[9][d]->Draw("same");
	
 

	auto legend11 = new TLegend(0.7,0.7,0.88,0.88);
	legend11->AddEntry(ProjectionY3[0][d], "pu = 0.5" ,"l");
	legend11->AddEntry(ProjectionY3[1][d], "pu = 1" ,"l");
	legend11->AddEntry(ProjectionY3[2][d], "pu = 1.5" ,"l");
	legend11->AddEntry(ProjectionY3[3][d], "pu = 2" ,"l");
	legend11->AddEntry(ProjectionY3[4][d], "pu = 10" ,"l");
	legend11->AddEntry(ProjectionY3[5][d], "pu = 30" ,"l");
	legend11->AddEntry(ProjectionY3[6][d], "pu = 50" ,"l");
	legend11->AddEntry(ProjectionY3[7][d], "pu = 100" ,"l");
	legend11->AddEntry(ProjectionY3[8][d], "pu = 140" ,"l");
	legend11->AddEntry(ProjectionY3[9][d], "pu = 200" ,"l");
	legend11->SetFillColor(0);
	legend11->SetLineColor(0);
	legend11->SetFillColor(0);
	legend11->Draw();
	
	char *Projection16 = new char[10];
	Int_t pro16 = d + 1;
	sprintf(Projection16,"ProjectionsRing4_%d.gif",pro16);
	cout<<"=========================="<<Projection16<<endl;
	c13->Print(outputpath2 + Projection16);
	c13->Clear();
		
		

	TCanvas *c14 = new TCanvas();
	c14->cd();
	c14->SetLogy();
	
	ProjectionY4[0][d]->SetMinimum(0.011);
	ProjectionY4[0][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY4[0][d]->SetLineColor(1);
	ProjectionY4[0][d]->Scale(1./ProjectionY4[0][d]->Integral());
	ProjectionY4[0][d]->Draw("same");
	
	ProjectionY4[1][d]->SetMinimum(0.001);
	ProjectionY4[1][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[1][d]->SetLineColor(2);
	ProjectionY4[1][d]->Scale(1./ProjectionY4[1][d]->Integral());
	ProjectionY4[1][d]->Draw("same");
        
	ProjectionY4[2][d]->SetMinimum(0.001);
	ProjectionY4[2][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[2][d]->SetLineColor(3);
	ProjectionY4[2][d]->Scale(1./ProjectionY4[2][d]->Integral());
	ProjectionY4[2][d]->Draw("same");
	
	ProjectionY4[3][d]->SetMinimum(0.01);
	ProjectionY4[3][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[3][d]->SetLineColor(4);
	ProjectionY4[3][d]->Scale(1./ProjectionY4[3][d]->Integral());
	ProjectionY4[3][d]->Draw("same");
	
	ProjectionY4[4][d]->SetMinimum(0.01);
	ProjectionY4[4][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[4][d]->SetLineColor(5);
	ProjectionY4[4][d]->Scale(1./ProjectionY4[4][d]->Integral());
	ProjectionY4[4][d]->Draw("same");
	
	ProjectionY4[5][d]->SetMinimum(0.01);
	ProjectionY4[5][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[5][d]->SetLineColor(6);
	ProjectionY4[5][d]->Scale(1./ProjectionY4[5][d]->Integral());
	ProjectionY4[5][d]->Draw("same");
	
	ProjectionY4[6][d]->SetMinimum(0.01);
	ProjectionY4[6][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[6][d]->SetLineColor(7);
	ProjectionY4[6][d]->Scale(1./ProjectionY4[6][d]->Integral());
	ProjectionY4[6][d]->Draw("same");
	
	ProjectionY4[7][d]->SetMinimum(0.01);
	ProjectionY4[7][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[7][d]->SetLineColor(8);
	ProjectionY4[7][d]->Scale(1./ProjectionY4[7][d]->Integral());
	ProjectionY4[7][d]->Draw("same");
	
	ProjectionY4[8][d]->SetMinimum(0.01);
	ProjectionY4[8][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[8][d]->SetLineColor(9);
	ProjectionY4[8][d]->Scale(1./ProjectionY4[8][d]->Integral());
	ProjectionY4[8][d]->Draw("same");
	
	ProjectionY4[9][d]->SetMinimum(0.01);
	ProjectionY4[9][d]->GetXaxis()->SetRangeUser(0, 1500);
	ProjectionY4[9][d]->SetLineColor(44);
	ProjectionY4[9][d]->Scale(1./ProjectionY4[9][d]->Integral());
	ProjectionY4[9][d]->Draw("same");
	
	
	
	auto legend12 = new TLegend(0.7,0.7,0.88,0.88);
	legend12->AddEntry(ProjectionY4[0][d], "pu = 0.5" ,"l");
	legend12->AddEntry(ProjectionY4[1][d], "pu = 1" ,"l");
	legend12->AddEntry(ProjectionY4[2][d], "pu = 1.5" ,"l");
	legend12->AddEntry(ProjectionY4[3][d], "pu = 2" ,"l");
	legend12->AddEntry(ProjectionY4[4][d], "pu = 10" ,"l");
	legend12->AddEntry(ProjectionY4[5][d], "pu = 30" ,"l");
	legend12->AddEntry(ProjectionY4[6][d], "pu = 50" ,"l");
	legend12->AddEntry(ProjectionY4[7][d], "pu = 100" ,"l");
	legend12->AddEntry(ProjectionY4[8][d], "pu = 140" ,"l");
	legend12->AddEntry(ProjectionY4[9][d], "pu = 200" ,"l");
	legend12->SetFillColor(0);
	legend12->SetLineColor(0);
	legend12->SetFillColor(0);
	legend12->Draw();
	
	
	char *Projection17 = new char[10];
	Int_t pro17 = d + 1;
	sprintf(Projection17,"ProjectionsRing5_%d.gif",pro17);
	cout<<"=========================="<<Projection17<<endl;
	c14->Print(outputpath2 + Projection17);
	c14->Clear();
      }
      
      
      
      if (option == 2){
	
	//draw the 2D 2x Coincidences distributions for all PU
	TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ";
	
	TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
	
	ProjectionY[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 1, 1)->Clone(TString(H->GetName()) +             "Projection");
        ProjectionY[pu][d] ->Rebin(5);
	ProjectionY1[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 2,2)->Clone(TString(H->GetName()) +             "Projection");
	ProjectionY1[pu][d] ->Rebin(5);
	ProjectionY2[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 3, 3)->Clone(TString(H->GetName()) +            "Projection");
	ProjectionY2[pu][d] ->Rebin(5);
	ProjectionY3[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 4, 4)->Clone(TString(H->GetName()) +            "Projection");
	ProjectionY3[pu][d] ->Rebin(5);
	ProjectionY4[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 5, 5)->Clone(TString(H->GetName()) +            "Projection");
        ProjectionY4[pu][d] ->Rebin(5);
        
	Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile"); //number of cluster vs ring
	
	if (pu < 4){
	  TCanvas *c15 = new TCanvas();
	  c15->cd();
	  Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, 100);
	  Histogram2D[pu][d]->Draw("colz");
	  char *hist2Dname = new char[10];
	  Int_t pud = pu * 8 + d + 1;
	  sprintf(hist2Dname,"histos2D_%d.gif",pud);
	  cout<<"=========================="<<hist2Dname<<endl;
	  c15->Print(outputpath6 + hist2Dname);
	  c15->Clear();
          
	  TCanvas *c16 = new TCanvas();
	  c16->cd();
	  ProjectionY[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY[pu][d]->GetYaxis()->SetRangeUser(0, 20000);
	  ProjectionY[pu][d]->GetYaxis()->SetTitle("# of events");
	  ProjectionY[pu][d]->SetLineColor(5);
	  ProjectionY[pu][d]->Draw("same");
	  ProjectionY1[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY1[pu][d]->GetYaxis()->SetRangeUser(0, 20000);
	  ProjectionY1[pu][d]->SetLineColor(2);
	  ProjectionY1[pu][d]->Draw("same");
	  ProjectionY2[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY2[pu][d]->GetYaxis()->SetRangeUser(0, 20000);
	  ProjectionY2[pu][d]->SetLineColor(3);
	  ProjectionY2[pu][d]->Draw("same");
	  ProjectionY3[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY3[pu][d]->GetYaxis()->SetRangeUser(0, 20000);
	  ProjectionY3[pu][d]->SetLineColor(4);
	  ProjectionY3[pu][d]->Draw("same");
	  ProjectionY4[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY4[pu][d]->GetYaxis()->SetRangeUser(0, 20000);
	  ProjectionY4[pu][d]->SetLineColor(6);
	  ProjectionY4[pu][d]->Draw("same");
          
          
	  
	  auto legend13 = new TLegend(0.7,0.7,0.88,0.88);
	  legend13->AddEntry(ProjectionY[pu][d], "Ring 1" ,"l");
	  legend13->AddEntry(ProjectionY1[pu][d], "Ring 2" ,"l");
	  legend13->AddEntry(ProjectionY2[pu][d], "Ring 3" ,"l");
	  legend13->AddEntry(ProjectionY3[pu][d], "Ring 4" ,"l");
	  legend13->AddEntry(ProjectionY4[pu][d], "Ring 5" ,"l");
	  
	  legend13->SetFillColor(0);
	  legend13->SetLineColor(0);
	  legend13->SetFillColor(0);
	  legend13->Draw();
	  char *Projection = new char[12];
	  Int_t pro = pu * 8 + d + 1;
	  sprintf(Projection,"Projection2x_%d.gif",pro);
	  cout<<"=========================="<<Projection<<endl;
	  c16->Print(outputpath7 + Projection);
	  c16->Clear();
	  
	}
	if (pu >= 4){
	  
	  TCanvas *c17 = new TCanvas();
	  c17->cd();
	  Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, 1000);
	  Histogram2D[pu][d]->Draw("colz");
	  char *hist2Dname = new char[10];
	  Int_t pud1 = pu * 8 + d + 1;
	  sprintf(hist2Dname,"histos2D_%d.gif",pud1);
	  cout<<"=========================="<<hist2Dname<<endl;
	  c17->Print(outputpath7 + hist2Dname);
	  c17->Clear();
	  
          
	  TCanvas *c18 = new TCanvas();
	  c18->cd();
	  ProjectionY[pu][d]->GetXaxis()->SetRangeUser(0, 500);
	  ProjectionY[pu][d]->GetYaxis()->SetRangeUser(0, 2500);
          ProjectionY[pu][d]->GetYaxis()->SetTitle("# of events");
	  ProjectionY[pu][d]->SetLineColor(5);
	  ProjectionY[pu][d]->Draw("same");
	  ProjectionY1[pu][d]->GetXaxis()->SetRangeUser(0, 500);
	  ProjectionY1[pu][d]->GetYaxis()->SetRangeUser(0, 2500);
	  ProjectionY1[pu][d]->SetLineColor(2);
	  ProjectionY1[pu][d]->Draw("same");
	  ProjectionY2[pu][d]->GetXaxis()->SetRangeUser(0, 500);
	  ProjectionY2[pu][d]->GetYaxis()->SetRangeUser(0, 2500);
	  ProjectionY2[pu][d]->SetLineColor(3);
	  ProjectionY2[pu][d]->Draw("same");
	  ProjectionY3[pu][d]->GetXaxis()->SetRangeUser(0, 500);
	  ProjectionY3[pu][d]->GetYaxis()->SetRangeUser(0, 2500);
	  ProjectionY3[pu][d]->SetLineColor(4);
	  ProjectionY3[pu][d]->Draw("same");
	  ProjectionY4[pu][d]->GetXaxis()->SetRangeUser(0, 500);
	  ProjectionY4[pu][d]->GetYaxis()->SetRangeUser(0, 2500);
	  ProjectionY4[pu][d]->SetLineColor(6);
	  ProjectionY4[pu][d]->Draw("same");
	  
	  auto legend14 = new TLegend(0.7,0.7,0.88,0.88);
	  legend14->AddEntry(ProjectionY[pu][d], "Ring 1" ,"l");
	  legend14->AddEntry(ProjectionY1[pu][d], "Ring 2" ,"l");
	  legend14->AddEntry(ProjectionY2[pu][d], "Ring 3" ,"l");
	  legend14->AddEntry(ProjectionY3[pu][d], "Ring 4" ,"l");
	  legend14->AddEntry(ProjectionY4[pu][d], "Ring 5" ,"l");
	  
	  legend14->SetFillColor(0);
	  legend14->SetLineColor(0);
	  legend14->SetFillColor(0);
	  legend14->Draw();
	  char *Projection = new char[12];
	  Int_t pro = pu * 8 + d + 1;
	  sprintf(Projection,"Projection2x_%d.gif",pro);
	  cout<<"=========================="<<Projection<<endl;
	  c18->Print(outputpath7 + Projection);
	  c18->Clear();
	  
	}
	
        
	if(pu < 4){
	  
	  TCanvas *c19 = new TCanvas();
	  c19->cd();
	  c19->SetLogy();
	  
	  ProjectionY[0][d]->SetMinimum(0.011);
	  ProjectionY[0][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 4) + " Ring 1");
	  }else{
	  ProjectionY[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 3) + " Ring 1");
	  }
	  ProjectionY[0][d]->SetLineColor(1);
	  ProjectionY[0][d]->Scale(1./ProjectionY[0][d]->Integral());
	  ProjectionY[0][d]->Draw("same");
	  
	  ProjectionY[1][d]->SetMinimum(0.001);
	  ProjectionY[1][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY[1][d]->SetLineColor(2);
	  ProjectionY[1][d]->Scale(1./ProjectionY[1][d]->Integral());
	  ProjectionY[1][d]->Draw("same");
          
	  ProjectionY[2][d]->SetMinimum(0.001);
	  ProjectionY[2][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY[2][d]->SetLineColor(3);
	  ProjectionY[2][d]->Scale(1./ProjectionY[2][d]->Integral());
	  ProjectionY[2][d]->Draw("same");
	  
	  ProjectionY[3][d]->SetMinimum(0.01);
	  ProjectionY[3][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY[3][d]->SetLineColor(4);
	  ProjectionY[3][d]->Scale(1./ProjectionY[3][d]->Integral());
	  ProjectionY[3][d]->Draw("same");
	  
	  
	  
	  auto legend15 = new TLegend(0.7,0.7,0.88,0.88);
	  legend15->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	  legend15->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	  legend15->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	  legend15->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	  
	  legend15->SetFillColor(0);
	  legend15->SetLineColor(0);
	  legend15->SetFillColor(0);
	  legend15->Draw();
	  
	  char *Projection11 = new char[10];
	  Int_t pro12 = d + 1;
	  sprintf(Projection11,"ProjectionasRing1_%d.gif",pro12);
	  cout<<"=========================="<<Projection11<<endl;
	  c19->Print(outputpath7 + Projection11);
	  c19->Clear();
	  
          
	  TCanvas *c20 = new TCanvas();
	  c20->cd();
	  c20->SetLogy();
	  
	  ProjectionY1[0][d]->SetMinimum(0.011);
	  ProjectionY1[0][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY1[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY1[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 4) + " Ring 2");
	  }else{
	  ProjectionY1[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 3) + " Ring 2");
	  }
	  ProjectionY1[0][d]->SetLineColor(1);
	  ProjectionY1[0][d]->Scale(1./ProjectionY1[0][d]->Integral());
	  ProjectionY1[0][d]->Draw("same");

	  ProjectionY1[1][d]->SetMinimum(0.001);
	  ProjectionY1[1][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY1[1][d]->SetLineColor(2);
	  ProjectionY1[1][d]->Scale(1./ProjectionY1[1][d]->Integral());
	  ProjectionY1[1][d]->Draw("same");
          
	  ProjectionY1[2][d]->SetMinimum(0.001);
	  ProjectionY1[2][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY1[2][d]->SetLineColor(3);
	  ProjectionY1[2][d]->Scale(1./ProjectionY1[2][d]->Integral());
	  ProjectionY1[2][d]->Draw("same");
	  
	  ProjectionY1[3][d]->SetMinimum(0.01);
	  ProjectionY1[3][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY1[3][d]->SetLineColor(4);
	  ProjectionY1[3][d]->Scale(1./ProjectionY1[3][d]->Integral());
	  ProjectionY1[3][d]->Draw("same");
	  
	  auto legend16 = new TLegend(0.7,0.7,0.88,0.88);
	  legend16->AddEntry(ProjectionY1[0][d], "pu = 0.5" ,"l");
	  legend16->AddEntry(ProjectionY1[1][d], "pu = 1" ,"l");
	  legend16->AddEntry(ProjectionY1[2][d], "pu = 1.5" ,"l");
	  legend16->AddEntry(ProjectionY1[3][d], "pu = 2" ,"l");
	  
	  legend16->SetFillColor(0);
	  legend16->SetLineColor(0);
	  legend16->SetFillColor(0);
	  legend16->Draw();
	  
	  char *Projection14 = new char[10];
	  Int_t pro14 = d + 1;
	  sprintf(Projection14,"ProjectionasRing2_%d.gif",pro14);
	  cout<<"=========================="<<Projection14<<endl;
	  c20->Print(outputpath7 + Projection14);
	  c20->Clear();
	  
	  TCanvas *c21 = new TCanvas();
	  c21->cd();
	  c21->SetLogy();
	  
	  ProjectionY2[0][d]->SetMinimum(0.011);
	  ProjectionY2[0][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY2[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY2[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 4) + " Ring 3");
	  }else{
	  ProjectionY2[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 3) + " Ring 3");
	  }
	  ProjectionY2[0][d]->SetLineColor(1);
	  ProjectionY2[0][d]->Scale(1./ProjectionY2[0][d]->Integral());
	  ProjectionY2[0][d]->Draw("same");
	  
	  ProjectionY2[1][d]->SetMinimum(0.001);
	  ProjectionY2[1][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY2[1][d]->SetLineColor(2);
	  ProjectionY2[1][d]->Scale(1./ProjectionY2[1][d]->Integral());
	  ProjectionY2[1][d]->Draw("same");
          
	  ProjectionY2[2][d]->SetMinimum(0.001);
	  ProjectionY2[2][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY2[2][d]->SetLineColor(3);
	  ProjectionY2[2][d]->Scale(1./ProjectionY2[2][d]->Integral());
	  ProjectionY2[2][d]->Draw("same");
	  
	  ProjectionY2[3][d]->SetMinimum(0.01);
	  ProjectionY2[3][d]->GetXaxis()->SetRangeUser(0, 50);
	  ProjectionY2[3][d]->SetLineColor(4);
	  ProjectionY2[3][d]->Scale(1./ProjectionY2[3][d]->Integral());
	  ProjectionY2[3][d]->Draw("same");
	  
	  auto legend17 = new TLegend(0.7,0.7,0.88,0.88);
	  legend17->AddEntry(ProjectionY1[0][d], "pu = 0.5" ,"l");
	  legend17->AddEntry(ProjectionY1[1][d], "pu = 1" ,"l");
	  legend17->AddEntry(ProjectionY1[2][d], "pu = 1.5" ,"l");
	  legend17->AddEntry(ProjectionY1[3][d], "pu = 2" ,"l");
	  
	  legend17->SetFillColor(0);
	  legend17->SetLineColor(0);
	  legend17->SetFillColor(0);
	  legend17->Draw();
	  
	  char *Projection15 = new char[10];
	  Int_t pro15 = d + 1;
	  sprintf(Projection15,"ProjectionasRing3_%d.gif",pro15);
	  cout<<"=========================="<<Projection15<<endl;
	  c21->Print(outputpath7 + Projection15);
	  c21->Clear();
	  
	  
	  TCanvas *c22 = new TCanvas();
	  c22->cd();
	  c22->SetLogy();
	  
	  ProjectionY3[0][d]->SetMinimum(0.011);
	  ProjectionY3[0][d]->GetXaxis()->SetRangeUser(0, 30);
	  ProjectionY3[0][d]->GetYaxis()->SetTitle("# of events");
	  if (d <=3){
          ProjectionY3[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 4) + " Ring 4");
	  }else{
	  ProjectionY3[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 3) + " Ring 4");
	  }
	  ProjectionY3[0][d]->SetLineColor(1);
	  ProjectionY3[0][d]->Scale(1./ProjectionY3[0][d]->Integral());
	  ProjectionY3[0][d]->Draw("same");
	  
	  ProjectionY3[1][d]->SetMinimum(0.001);
	  ProjectionY3[1][d]->GetXaxis()->SetRangeUser(0, 30);
	  ProjectionY3[1][d]->SetLineColor(2);
	  ProjectionY3[1][d]->Scale(1./ProjectionY3[1][d]->Integral());
	  ProjectionY3[1][d]->Draw("same");
          
	  ProjectionY3[2][d]->SetMinimum(0.001);
	  ProjectionY3[2][d]->GetXaxis()->SetRangeUser(0, 30);
	  ProjectionY3[2][d]->SetLineColor(3);
	  ProjectionY3[2][d]->Scale(1./ProjectionY3[2][d]->Integral());
	  ProjectionY3[2][d]->Draw("same");
	  
	  ProjectionY3[3][d]->SetMinimum(0.01);
	  ProjectionY3[3][d]->GetXaxis()->SetRangeUser(0, 30);
	  ProjectionY3[3][d]->SetLineColor(4);
	  ProjectionY3[3][d]->Scale(1./ProjectionY3[3][d]->Integral());
	  ProjectionY3[3][d]->Draw("same");
	  
	  auto legend18 = new TLegend(0.7,0.7,0.88,0.88);
	  legend18->AddEntry(ProjectionY3[0][d], "pu = 0.5" ,"l");
	  legend18->AddEntry(ProjectionY3[1][d], "pu = 1" ,"l");
	  legend18->AddEntry(ProjectionY3[2][d], "pu = 1.5" ,"l");
	  legend18->AddEntry(ProjectionY3[3][d], "pu = 2" ,"l");
	  
	  legend18->SetFillColor(0);
	  legend18->SetLineColor(0);
	  legend18->SetFillColor(0);
	  legend18->Draw();
	  
	  char *Projection16 = new char[10];
	  Int_t pro16 = d + 1;
	  sprintf(Projection16,"ProjectionasRing4_%d.gif",pro16);
	  cout<<"=========================="<<Projection16<<endl;
	  c22->Print(outputpath7 + Projection16);
	  c22->Clear();
	  
	  
	  
	  TCanvas *c23 = new TCanvas();
	  c23->cd();
	  c23->SetLogy();
	  
	  ProjectionY4[0][d]->SetMinimum(0.011);
	  ProjectionY4[0][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY4[0][d]->GetYaxis()->SetTitle("# of events");
	  if (d <=3){
          ProjectionY4[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 4) + " Ring 5");
	  }else{
	  ProjectionY4[0][d]->SetTitle(TString("Number of 2x Coincidences for Disk ") + (d - 3) + " Ring 5");
	  }
	  ProjectionY4[0][d]->SetLineColor(1);
	  ProjectionY4[0][d]->Scale(1./ProjectionY4[0][d]->Integral());
	  ProjectionY4[0][d]->Draw("same");
	  
	  ProjectionY4[1][d]->SetMinimum(0.001);
	  ProjectionY4[1][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY4[1][d]->SetLineColor(2);
	  ProjectionY4[1][d]->Scale(1./ProjectionY4[1][d]->Integral());
	  ProjectionY4[1][d]->Draw("same");
          
	  ProjectionY4[2][d]->SetMinimum(0.001);
	  ProjectionY4[2][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY4[2][d]->SetLineColor(3);
	  ProjectionY4[2][d]->Scale(1./ProjectionY4[2][d]->Integral());
	  ProjectionY4[2][d]->Draw("same");
	  
	  ProjectionY4[3][d]->SetMinimum(0.01);
	  ProjectionY4[3][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY4[3][d]->SetLineColor(4);
	  ProjectionY4[3][d]->Scale(1./ProjectionY4[3][d]->Integral());
	  ProjectionY4[3][d]->Draw("same");
	  
	  auto legend19 = new TLegend(0.7,0.7,0.88,0.88);
	  legend19->AddEntry(ProjectionY4[0][d], "pu = 0.5" ,"l");
	  legend19->AddEntry(ProjectionY4[1][d], "pu = 1" ,"l");
	  legend19->AddEntry(ProjectionY4[2][d], "pu = 1.5" ,"l");
	  legend19->AddEntry(ProjectionY4[3][d], "pu = 2" ,"l");
	  
	  legend19->SetFillColor(0);
	  legend19->SetLineColor(0);
	  legend19->SetFillColor(0);
	  legend19->Draw();
	  
	  char *Projection17 = new char[10];
	  Int_t pro17 = d + 1;
	  sprintf(Projection17,"ProjectionasRing5_%d.gif",pro17);
	  cout<<"=========================="<<Projection17<<endl;
	  c23->Print(outputpath7 + Projection17);
	  c23->Clear();
	  
	}
	
        
	TCanvas *c24 = new TCanvas();
	c24->cd();
	c24->SetLogy();
	
	ProjectionY[0][d]->SetMinimum(0.011);
	ProjectionY[0][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY[0][d]->SetLineColor(1);
        ProjectionY[0][d]->Scale(1./ProjectionY[0][d]->Integral());
	ProjectionY[0][d]->Draw("same");
	
	ProjectionY[1][d]->SetMinimum(0.001);
	ProjectionY[1][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[1][d]->SetLineColor(2);
	ProjectionY[1][d]->Scale(1./ProjectionY[1][d]->Integral());
	ProjectionY[1][d]->Draw("same");
        
	ProjectionY[2][d]->SetMinimum(0.001);
	ProjectionY[2][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[2][d]->SetLineColor(3);
	ProjectionY[2][d]->Scale(1./ProjectionY[2][d]->Integral());
	ProjectionY[2][d]->Draw("same");
	
	ProjectionY[3][d]->SetMinimum(0.01);
	ProjectionY[3][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[3][d]->SetLineColor(4);
	ProjectionY[3][d]->Scale(1./ProjectionY[3][d]->Integral());
	ProjectionY[3][d]->Draw("same");
	
	ProjectionY[4][d]->SetMinimum(0.01);
	ProjectionY[4][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[4][d]->SetLineColor(5);
	ProjectionY[4][d]->Scale(1./ProjectionY[4][d]->Integral());
	ProjectionY[4][d]->Draw("same");
	
	ProjectionY[5][d]->SetMinimum(0.01);
	ProjectionY[5][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[5][d]->SetLineColor(6);
	ProjectionY[5][d]->Scale(1./ProjectionY[5][d]->Integral());
	ProjectionY[5][d]->Draw("same");
	
	ProjectionY[6][d]->SetMinimum(0.01);
	ProjectionY[6][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[6][d]->SetLineColor(7);
	ProjectionY[6][d]->Scale(1./ProjectionY[6][d]->Integral());
	ProjectionY[6][d]->Draw("same");
	
	ProjectionY[7][d]->SetMinimum(0.01);
	ProjectionY[7][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[7][d]->SetLineColor(8);
	ProjectionY[7][d]->Scale(1./ProjectionY[7][d]->Integral());
	ProjectionY[7][d]->Draw("same");
	
	ProjectionY[8][d]->SetMinimum(0.01);
	ProjectionY[8][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[8][d]->SetLineColor(9);
	ProjectionY[8][d]->Scale(1./ProjectionY[8][d]->Integral());
	ProjectionY[8][d]->Draw("same");
	
	ProjectionY[9][d]->SetMinimum(0.01);
	ProjectionY[9][d]->GetXaxis()->SetRangeUser(0, 600);
	ProjectionY[9][d]->SetLineColor(44);
	ProjectionY[9][d]->Scale(1./ProjectionY[9][d]->Integral());
	ProjectionY[9][d]->Draw("same");
	
	
	
	auto legend20 = new TLegend(0.7,0.7,0.88,0.88);
	legend20->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend20->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend20->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend20->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend20->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend20->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend20->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend20->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend20->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend20->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend20->SetFillColor(0);
	legend20->SetLineColor(0);
	legend20->SetFillColor(0);
	legend20->Draw();
	
	
	char *Projection12 = new char[10];
	Int_t pro13 = d + 1;
	sprintf(Projection12,"ProjectionbsRing1_%d.gif",pro13);
	cout<<"=========================="<<Projection12<<endl;
	c24->Print(outputpath7 + Projection12);
	c24->Clear();
	
	
	
	
	
	TCanvas *c25 = new TCanvas();
	c25->cd();
	c25->SetLogy();
	
	ProjectionY1[0][d]->SetMinimum(0.011);
	ProjectionY1[0][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY1[0][d]->SetLineColor(1);
	ProjectionY1[0][d]->Scale(1./ProjectionY1[0][d]->Integral());
	ProjectionY1[0][d]->Draw("same");
	
	ProjectionY1[1][d]->SetMinimum(0.001);
	ProjectionY1[1][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[1][d]->SetLineColor(2);
	ProjectionY1[1][d]->Scale(1./ProjectionY1[1][d]->Integral());
	ProjectionY1[1][d]->Draw("same");
        
	ProjectionY1[2][d]->SetMinimum(0.001);
	ProjectionY1[2][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[2][d]->SetLineColor(3);
	ProjectionY1[2][d]->Scale(1./ProjectionY1[2][d]->Integral());
	ProjectionY1[2][d]->Draw("same");
	
	ProjectionY1[3][d]->SetMinimum(0.01);
	ProjectionY1[3][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[3][d]->SetLineColor(4);
	ProjectionY1[3][d]->Scale(1./ProjectionY1[3][d]->Integral());
	ProjectionY1[3][d]->Draw("same");

	ProjectionY1[4][d]->SetMinimum(0.01);
	ProjectionY1[4][d]->GetXaxis()->SetRangeUser(0,400);
	ProjectionY1[4][d]->SetLineColor(5);
	ProjectionY1[4][d]->Scale(1./ProjectionY1[4][d]->Integral());
	ProjectionY1[4][d]->Draw("same");

	ProjectionY1[5][d]->SetMinimum(0.01);
	ProjectionY1[5][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[5][d]->SetLineColor(6);
	ProjectionY1[5][d]->Scale(1./ProjectionY1[5][d]->Integral());
	ProjectionY1[5][d]->Draw("same");
	
	ProjectionY1[6][d]->SetMinimum(0.01);
	ProjectionY1[6][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[6][d]->SetLineColor(7);
	ProjectionY1[6][d]->Scale(1./ProjectionY1[6][d]->Integral());
	ProjectionY1[6][d]->Draw("same");
		
	ProjectionY1[7][d]->SetMinimum(0.01);
	ProjectionY1[7][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[7][d]->SetLineColor(8);
	ProjectionY1[7][d]->Scale(1./ProjectionY1[7][d]->Integral());
	ProjectionY1[7][d]->Draw("same");
	
	ProjectionY1[8][d]->SetMinimum(0.01);
	ProjectionY1[8][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[8][d]->SetLineColor(9);
	ProjectionY1[8][d]->Scale(1./ProjectionY1[8][d]->Integral());
	ProjectionY1[8][d]->Draw("same");
	
	ProjectionY1[9][d]->SetMinimum(0.01);
	ProjectionY1[9][d]->GetXaxis()->SetRangeUser(0, 400);
	ProjectionY1[9][d]->SetLineColor(44);
	ProjectionY1[9][d]->Scale(1./ProjectionY1[9][d]->Integral());
	ProjectionY1[9][d]->Draw("same");
	
 

	auto legend21 = new TLegend(0.7,0.7,0.88,0.88);
	legend21->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend21->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend21->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend21->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend21->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend21->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend21->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend21->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend21->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend21->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend21->SetFillColor(0);
	legend21->SetLineColor(0);
	legend21->SetFillColor(0);
	legend21->Draw();
	
	
	char *Projection14 = new char[10];
	Int_t pro14 = d + 1;
	sprintf(Projection14,"ProjectionbsRing2_%d.gif",pro14);
	cout<<"=========================="<<Projection14<<endl;
	c25->Print(outputpath7 + Projection14);
	c25->Clear();



	TCanvas *c26 = new TCanvas();
	c26->cd();
	c26->SetLogy();
	
	ProjectionY2[0][d]->SetMinimum(0.011);
	ProjectionY2[0][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY2[0][d]->SetLineColor(1);
	ProjectionY2[0][d]->Scale(1./ProjectionY2[0][d]->Integral());
	ProjectionY2[0][d]->Draw("same");
	
	ProjectionY2[1][d]->SetMinimum(0.001);
	ProjectionY2[1][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[1][d]->SetLineColor(2);
	ProjectionY2[1][d]->Scale(1./ProjectionY2[1][d]->Integral());
	ProjectionY2[1][d]->Draw("same");
               
	ProjectionY2[2][d]->SetMinimum(0.001);
	ProjectionY2[2][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[2][d]->SetLineColor(3);
	ProjectionY2[2][d]->Scale(1./ProjectionY2[2][d]->Integral());
	ProjectionY2[2][d]->Draw("same");
		
	ProjectionY2[3][d]->SetMinimum(0.01);
	ProjectionY2[3][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[3][d]->SetLineColor(4);
	ProjectionY2[3][d]->Scale(1./ProjectionY2[3][d]->Integral());
	ProjectionY2[3][d]->Draw("same");

	ProjectionY2[4][d]->SetMinimum(0.01);
	ProjectionY2[4][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[4][d]->SetLineColor(5);
	ProjectionY2[4][d]->Scale(1./ProjectionY2[4][d]->Integral());
	ProjectionY2[4][d]->Draw("same");

	ProjectionY2[5][d]->SetMinimum(0.01);
	ProjectionY2[5][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[5][d]->SetLineColor(6);
	ProjectionY2[5][d]->Scale(1./ProjectionY2[5][d]->Integral());
	ProjectionY2[5][d]->Draw("same");

	ProjectionY2[6][d]->SetMinimum(0.01);
	ProjectionY2[6][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[6][d]->SetLineColor(7);
	ProjectionY2[6][d]->Scale(1./ProjectionY2[6][d]->Integral());
	ProjectionY2[6][d]->Draw("same");

	ProjectionY2[7][d]->SetMinimum(0.01);
	ProjectionY2[7][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[7][d]->SetLineColor(8);
	ProjectionY2[7][d]->Scale(1./ProjectionY2[7][d]->Integral());
	ProjectionY2[7][d]->Draw("same");

	ProjectionY2[8][d]->SetMinimum(0.01);
	ProjectionY2[8][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[8][d]->SetLineColor(9);
	ProjectionY2[8][d]->Scale(1./ProjectionY2[8][d]->Integral());
	ProjectionY2[8][d]->Draw("same");
	
	ProjectionY2[9][d]->SetMinimum(0.01);
	ProjectionY2[9][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY2[9][d]->SetLineColor(44);
	ProjectionY2[9][d]->Scale(1./ProjectionY2[9][d]->Integral());
	ProjectionY2[9][d]->Draw("same");
	
	
	
	auto legend22 = new TLegend(0.7,0.7,0.88,0.88);
	legend22->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend22->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend22->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend22->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend22->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend22->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend22->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend22->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend22->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend22->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend22->SetFillColor(0);
	legend22->SetLineColor(0);
	legend22->SetFillColor(0);
	legend22->Draw();
	
	
	char *Projection15 = new char[10];
	Int_t pro15 = d + 1;
	sprintf(Projection15,"ProjectionbsRing3_%d.gif",pro15);
	cout<<"=========================="<<Projection15<<endl;
	c26->Print(outputpath7 + Projection15);
	c26->Clear();
	
	
	
	TCanvas *c27 = new TCanvas();
	c27->cd();
	c27->SetLogy();
	
	ProjectionY3[0][d]->SetMinimum(0.011);
	ProjectionY3[0][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY3[0][d]->SetLineColor(1);
	ProjectionY3[0][d]->Scale(1./ProjectionY3[0][d]->Integral());
	ProjectionY3[0][d]->Draw("same");
	
	ProjectionY3[1][d]->SetMinimum(0.001);
	ProjectionY3[1][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[1][d]->SetLineColor(2);
	ProjectionY3[1][d]->Scale(1./ProjectionY3[1][d]->Integral());
	ProjectionY3[1][d]->Draw("same");
        
	ProjectionY3[2][d]->SetMinimum(0.001);
	ProjectionY3[2][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[2][d]->SetLineColor(3);
	ProjectionY3[2][d]->Scale(1./ProjectionY3[2][d]->Integral());
	ProjectionY3[2][d]->Draw("same");
		
	ProjectionY3[3][d]->SetMinimum(0.01);
	ProjectionY3[3][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[3][d]->SetLineColor(4);
	ProjectionY3[3][d]->Scale(1./ProjectionY3[3][d]->Integral());
	ProjectionY3[3][d]->Draw("same");
	
	ProjectionY3[4][d]->SetMinimum(0.01);
	ProjectionY3[4][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[4][d]->SetLineColor(5);
	ProjectionY3[4][d]->Scale(1./ProjectionY3[4][d]->Integral());
	ProjectionY3[4][d]->Draw("same");
	
	ProjectionY3[5][d]->SetMinimum(0.01);
	ProjectionY3[5][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[5][d]->SetLineColor(6);
	ProjectionY3[5][d]->Scale(1./ProjectionY3[5][d]->Integral());
	ProjectionY3[5][d]->Draw("same");
	
	ProjectionY3[6][d]->SetMinimum(0.01);
	ProjectionY3[6][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[6][d]->SetLineColor(7);
	ProjectionY3[6][d]->Scale(1./ProjectionY3[6][d]->Integral());
	ProjectionY3[6][d]->Draw("same");
	
	ProjectionY3[7][d]->SetMinimum(0.01);
	ProjectionY3[7][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[7][d]->SetLineColor(8);
	ProjectionY3[7][d]->Scale(1./ProjectionY3[7][d]->Integral());
	ProjectionY3[7][d]->Draw("same");
		
	ProjectionY3[8][d]->SetMinimum(0.01);
	ProjectionY3[8][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[8][d]->SetLineColor(9);
	ProjectionY3[8][d]->Scale(1./ProjectionY3[8][d]->Integral());
	ProjectionY3[8][d]->Draw("same");
	
	ProjectionY3[9][d]->SetMinimum(0.01);
	ProjectionY3[9][d]->GetXaxis()->SetRangeUser(0, 250);
	ProjectionY3[9][d]->SetLineColor(44);
	ProjectionY3[9][d]->Scale(1./ProjectionY3[9][d]->Integral());
	ProjectionY3[9][d]->Draw("same");
	
	
	
	auto legend23 = new TLegend(0.7,0.7,0.88,0.88);
	legend23->AddEntry(ProjectionY3[0][d], "pu = 0.5" ,"l");
	legend23->AddEntry(ProjectionY3[1][d], "pu = 1" ,"l");
	legend23->AddEntry(ProjectionY3[2][d], "pu = 1.5" ,"l");
	legend23->AddEntry(ProjectionY3[3][d], "pu = 2" ,"l");
	legend23->AddEntry(ProjectionY3[4][d], "pu = 10" ,"l");
	legend23->AddEntry(ProjectionY3[5][d], "pu = 30" ,"l");
	legend23->AddEntry(ProjectionY3[6][d], "pu = 50" ,"l");
	legend23->AddEntry(ProjectionY3[7][d], "pu = 100" ,"l");
	legend23->AddEntry(ProjectionY3[8][d], "pu = 140" ,"l");
	legend23->AddEntry(ProjectionY3[9][d], "pu = 200" ,"l");
	legend23->SetFillColor(0);
	legend23->SetLineColor(0);
	legend23->SetFillColor(0);
	legend23->Draw();
	
	char *Projection16 = new char[10];
	Int_t pro16 = d + 1;
	sprintf(Projection16,"ProjectionbsRing4_%d.gif",pro16);
	cout<<"=========================="<<Projection16<<endl;
	c27->Print(outputpath7 + Projection16);
	c27->Clear();
		
		
		
	TCanvas *c28 = new TCanvas();
	c28->cd();
	c28->SetLogy();
	
	ProjectionY4[0][d]->SetMinimum(0.011);
	ProjectionY4[0][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY4[0][d]->SetLineColor(1);
	ProjectionY4[0][d]->Scale(1./ProjectionY4[0][d]->Integral());
	ProjectionY4[0][d]->Draw("same");
	
	ProjectionY4[1][d]->SetMinimum(0.001);
	ProjectionY4[1][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[1][d]->SetLineColor(2);
	ProjectionY4[1][d]->Scale(1./ProjectionY4[1][d]->Integral());
	ProjectionY4[1][d]->Draw("same");
        
	ProjectionY4[2][d]->SetMinimum(0.001);
	ProjectionY4[2][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[2][d]->SetLineColor(3);
	ProjectionY4[2][d]->Scale(1./ProjectionY4[2][d]->Integral());
	ProjectionY4[2][d]->Draw("same");
	
	ProjectionY4[3][d]->SetMinimum(0.01);
	ProjectionY4[3][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[3][d]->SetLineColor(4);
	ProjectionY4[3][d]->Scale(1./ProjectionY4[3][d]->Integral());
	ProjectionY4[3][d]->Draw("same");
	
	ProjectionY4[4][d]->SetMinimum(0.01);
	ProjectionY4[4][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[4][d]->SetLineColor(5);
	ProjectionY4[4][d]->Scale(1./ProjectionY4[4][d]->Integral());
	ProjectionY4[4][d]->Draw("same");
	
	ProjectionY4[5][d]->SetMinimum(0.01);
	ProjectionY4[5][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[5][d]->SetLineColor(6);
	ProjectionY4[5][d]->Scale(1./ProjectionY4[5][d]->Integral());
	ProjectionY4[5][d]->Draw("same");
	
	ProjectionY4[6][d]->SetMinimum(0.01);
	ProjectionY4[6][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[6][d]->SetLineColor(7);
	ProjectionY4[6][d]->Scale(1./ProjectionY4[6][d]->Integral());
	ProjectionY4[6][d]->Draw("same");
	
	ProjectionY4[7][d]->SetMinimum(0.01);
	ProjectionY4[7][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[7][d]->SetLineColor(8);
	ProjectionY4[7][d]->Scale(1./ProjectionY4[7][d]->Integral());
	ProjectionY4[7][d]->Draw("same");
	
	ProjectionY4[8][d]->SetMinimum(0.01);
	ProjectionY4[8][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[8][d]->SetLineColor(9);
	ProjectionY4[8][d]->Scale(1./ProjectionY4[8][d]->Integral());
	ProjectionY4[8][d]->Draw("same");
	
	ProjectionY4[9][d]->SetMinimum(0.01);
	ProjectionY4[9][d]->GetXaxis()->SetRangeUser(0, 150);
	ProjectionY4[9][d]->SetLineColor(44);
	ProjectionY4[9][d]->Scale(1./ProjectionY4[9][d]->Integral());
	ProjectionY4[9][d]->Draw("same");
	
	
	
	auto legend24 = new TLegend(0.7,0.7,0.88,0.88);
	legend24->AddEntry(ProjectionY4[0][d], "pu = 0.5" ,"l");
	legend24->AddEntry(ProjectionY4[1][d], "pu = 1" ,"l");
	legend24->AddEntry(ProjectionY4[2][d], "pu = 1.5" ,"l");
	legend24->AddEntry(ProjectionY4[3][d], "pu = 2" ,"l");
	legend24->AddEntry(ProjectionY4[4][d], "pu = 10" ,"l");
	legend24->AddEntry(ProjectionY4[5][d], "pu = 30" ,"l");
	legend24->AddEntry(ProjectionY4[6][d], "pu = 50" ,"l");
	legend24->AddEntry(ProjectionY4[7][d], "pu = 100" ,"l");
	legend24->AddEntry(ProjectionY4[8][d], "pu = 140" ,"l");
	legend24->AddEntry(ProjectionY4[9][d], "pu = 200" ,"l");
	legend24->SetFillColor(0);
	legend24->SetLineColor(0);
	legend24->SetFillColor(0);
	legend24->Draw();
	
	
	char *Projection17 = new char[10];
	Int_t pro17 = d + 1;
	sprintf(Projection17,"ProjectionbsRing5_%d.gif",pro17);
	cout<<"=========================="<<Projection17<<endl;
	c28->Print(outputpath7 + Projection17);
	c28->Clear();
      }
	    
            
      if (option == 3){
            
	//draw the 2D 2x Coincidences distributions for all PU
	TString histoname = "BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk ";

	TH2F* H = (TH2F*)F.Get(histoname + disklist[d].c_str());
	Histogram2D[pu][d] = (TH2F*)H->Clone(TString(H->GetName()));

	ProjectionY[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 1, 1)->Clone(TString(H->GetName()) +             "Projection");
	
	ProjectionY1[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 2,2)->Clone(TString(H->GetName()) +             "Projection");
	
	ProjectionY2[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 3, 3)->Clone(TString(H->GetName()) +            "Projection");
	
	ProjectionY3[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 4, 4)->Clone(TString(H->GetName()) +            "Projection");
	
	ProjectionY4[pu][d] = (TH1D*)H->ProjectionY(TString("ProjectionY_") + pu + "_" + d, 5, 5)->Clone(TString(H->GetName()) +            "Projection");
	
            
	Prof_TEPXClustersPerEvent[pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile"); //number of cluster vs ring

	if (pu < 4){
	  TCanvas *c29 = new TCanvas();
	  c29->cd();
	  Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, 50);
	  Histogram2D[pu][d]->Draw("colz");
	  char *hist2Dname = new char[10];
	  Int_t pud = pu * 8 + d + 1;
	  sprintf(hist2Dname,"histoss2D_%d.gif",pud);
	  cout<<"=========================="<<hist2Dname<<endl;
	  c29->Print(outputpath11 + hist2Dname);
	  c29->Clear();
          
	  TCanvas *c30 = new TCanvas();
	  c30->cd();
	  ProjectionY[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY[pu][d]->GetYaxis()->SetRangeUser(0, 2000);
          ProjectionY[pu][d]->GetYaxis()->SetTitle("# of events");
	  ProjectionY[pu][d]->SetLineColor(5);
	  ProjectionY[pu][d]->Draw("same");
	  ProjectionY1[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY1[pu][d]->GetYaxis()->SetRangeUser(0, 2000);
	  ProjectionY1[pu][d]->SetLineColor(2);
	  ProjectionY1[pu][d]->Draw("same");
	  ProjectionY2[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY2[pu][d]->GetYaxis()->SetRangeUser(0, 2000);
	  ProjectionY2[pu][d]->SetLineColor(3);
	  ProjectionY2[pu][d]->Draw("same");
	  ProjectionY3[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY3[pu][d]->GetYaxis()->SetRangeUser(0, 2000);
	  ProjectionY3[pu][d]->SetLineColor(4);
	  ProjectionY3[pu][d]->Draw("same");
	  ProjectionY4[pu][d]->GetXaxis()->SetRangeUser(0, 20);
	  ProjectionY4[pu][d]->GetYaxis()->SetRangeUser(0, 2000);
	  ProjectionY4[pu][d]->SetLineColor(6);
	  ProjectionY4[pu][d]->Draw("same");
          
          
	  
	  auto legend25 = new TLegend(0.7,0.7,0.88,0.88);
	  legend25->AddEntry(ProjectionY1[pu][d], "Ring 2" ,"l");
	  legend25->AddEntry(ProjectionY2[pu][d], "Ring 3" ,"l");
	  legend25->AddEntry(ProjectionY3[pu][d], "Ring 4" ,"l");
	  legend25->AddEntry(ProjectionY4[pu][d], "Ring 5" ,"l");
	  
	  legend25->SetFillColor(0);
	  legend25->SetLineColor(0);
	  legend25->SetFillColor(0);
	  legend25->Draw();
	  char *Projection = new char[12];
	  Int_t pro = pu * 8 + d + 1;
	  sprintf(Projection,"Projection3x_%d.gif",pro);
	  cout<<"=========================="<<Projection<<endl;
	  c30->Print(outputpath12 + Projection);
	  c30->Clear();
	}

	if (pu >= 4){
	  
	  TCanvas *c31 = new TCanvas();
	  c31->cd();
	  Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, 100);
	  Histogram2D[pu][d]->Draw("colz");
	  char *hist2Dname = new char[10];
	  Int_t pud1 = pu * 8 + d + 1;
	  sprintf(hist2Dname,"histoss2D_%d.gif",pud1);
	  cout<<"=========================="<<hist2Dname<<endl;
	  c31->Print(outputpath11 + hist2Dname);
	  c31->Clear();
		
                
	  TCanvas *c32 = new TCanvas();
	  c32->cd();
	  ProjectionY[pu][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[pu][d]->GetYaxis()->SetRangeUser(0, 1500);
	  ProjectionY[pu][d]->GetYaxis()->SetTitle("# of events");
	  ProjectionY[pu][d]->SetLineColor(5);
	  ProjectionY[pu][d]->Draw("same");
	  ProjectionY1[pu][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[pu][d]->GetYaxis()->SetRangeUser(0, 1500);
	  ProjectionY1[pu][d]->SetLineColor(2);
	  ProjectionY1[pu][d]->Draw("same");
	  ProjectionY2[pu][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[pu][d]->GetYaxis()->SetRangeUser(0, 1500);
	  ProjectionY2[pu][d]->SetLineColor(3);
	  ProjectionY2[pu][d]->Draw("same");
	  ProjectionY3[pu][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[pu][d]->GetYaxis()->SetRangeUser(0, 1500);
	  ProjectionY3[pu][d]->SetLineColor(4);
	  ProjectionY3[pu][d]->Draw("same");
	  ProjectionY4[pu][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[pu][d]->GetYaxis()->SetRangeUser(0, 1500);
	  ProjectionY4[pu][d]->SetLineColor(6);
	  ProjectionY4[pu][d]->Draw("same");
	  
	  auto legend26 = new TLegend(0.7,0.7,0.88,0.88);
	  legend26->AddEntry(ProjectionY1[pu][d], "Ring 2" ,"l");
	  legend26->AddEntry(ProjectionY2[pu][d], "Ring 3" ,"l");
	  legend26->AddEntry(ProjectionY3[pu][d], "Ring 4" ,"l");
	  legend26->AddEntry(ProjectionY4[pu][d], "Ring 5" ,"l");
	  
	  legend26->SetFillColor(0);
	  legend26->SetLineColor(0);
	  legend26->SetFillColor(0);
	  legend26->Draw();
	  char *Projection = new char[12];
	  Int_t pro = pu * 8 + d + 1;
	  sprintf(Projection,"Projection3x_%d.gif",pro);
	  cout<<"=========================="<<Projection<<endl;
	  c32->Print(outputpath12 + Projection);
	  c32->Clear();
	  
	}

                
	if(pu < 4){
	  
	  TCanvas *c33 = new TCanvas();
	  c33->cd();
	  c33->SetLogy();

	  ProjectionY[0][d]->SetMinimum(0.011);
	  ProjectionY[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 4) + " Ring 1");
	  }else{
	  ProjectionY[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 3) + " Ring 1");
	  }
	  ProjectionY[0][d]->SetLineColor(1);
	  ProjectionY[0][d]->Scale(1./ProjectionY[0][d]->Integral());
	  ProjectionY[0][d]->Draw("same");
	  
	  ProjectionY[1][d]->SetMinimum(0.001);
	  ProjectionY[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[1][d]->SetLineColor(2);
	  ProjectionY[1][d]->Scale(1./ProjectionY[1][d]->Integral());
	  ProjectionY[1][d]->Draw("same");
          
	  ProjectionY[2][d]->SetMinimum(0.001);
	  ProjectionY[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[2][d]->SetLineColor(3);
	  ProjectionY[2][d]->Scale(1./ProjectionY[2][d]->Integral());
	  ProjectionY[2][d]->Draw("same");
	  
	  ProjectionY[3][d]->SetMinimum(0.01);
	  ProjectionY[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY[3][d]->SetLineColor(4);
	  ProjectionY[3][d]->Scale(1./ProjectionY[3][d]->Integral());
	  ProjectionY[3][d]->Draw("same");
	  
	  
	  
	  auto legend27 = new TLegend(0.7,0.7,0.88,0.88);
	  legend27->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	  legend27->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	  legend27->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	  legend27->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
		
	  legend27->SetFillColor(0);
	  legend27->SetLineColor(0);
	  legend27->SetFillColor(0);
	  legend27->Draw();
	  
	  char *Projection11 = new char[10];
	  Int_t pro12 = d + 1;
	  sprintf(Projection11,"ProjectioncsRing1_%d.gif",pro12);
	  cout<<"=========================="<<Projection11<<endl;
	  c33->Print(outputpath12 + Projection11);
	  c33->Clear();
	  
          
	  TCanvas *c34 = new TCanvas();
	  c34->cd();
	  c34->SetLogy();
	  
	  ProjectionY1[0][d]->SetMinimum(0.011);
	  ProjectionY1[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY1[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 4) + " Ring 2");
	  }else{
	  ProjectionY1[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 3) + " Ring 2");
	  }
	  ProjectionY1[0][d]->SetLineColor(1);
	  ProjectionY1[0][d]->Scale(1./ProjectionY1[0][d]->Integral());
	  ProjectionY1[0][d]->Draw("same");
	  
	  ProjectionY1[1][d]->SetMinimum(0.001);
	  ProjectionY1[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[1][d]->SetLineColor(2);
	  ProjectionY1[1][d]->Scale(1./ProjectionY1[1][d]->Integral());
	  ProjectionY1[1][d]->Draw("same");
          
	  ProjectionY1[2][d]->SetMinimum(0.001);
	  ProjectionY1[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[2][d]->SetLineColor(3);
	  ProjectionY1[2][d]->Scale(1./ProjectionY1[2][d]->Integral());
	  ProjectionY1[2][d]->Draw("same");
	  
	  ProjectionY1[3][d]->SetMinimum(0.01);
	  ProjectionY1[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY1[3][d]->SetLineColor(4);
	  ProjectionY1[3][d]->Scale(1./ProjectionY1[3][d]->Integral());
	  ProjectionY1[3][d]->Draw("same");
	  
	  auto legend28 = new TLegend(0.7,0.7,0.88,0.88);
	  legend28->AddEntry(ProjectionY1[0][d], "pu = 0.5" ,"l");
	  legend28->AddEntry(ProjectionY1[1][d], "pu = 1" ,"l");
	  legend28->AddEntry(ProjectionY1[2][d], "pu = 1.5" ,"l");
	  legend28->AddEntry(ProjectionY1[3][d], "pu = 2" ,"l");
	  
	  legend28->SetFillColor(0);
	  legend28->SetLineColor(0);
	  legend28->SetFillColor(0);
	  legend28->Draw();
	  
	  char *Projection14 = new char[10];
	  Int_t pro14 = d + 1;
	  sprintf(Projection14,"ProjectioncsRing2_%d.gif",pro14);
	  cout<<"=========================="<<Projection14<<endl;
	  c34->Print(outputpath12 + Projection14);
	  c34->Clear();
		
	  TCanvas *c35 = new TCanvas();
	  c35->cd();
	  c35->SetLogy();
	  
	  ProjectionY2[0][d]->SetMinimum(0.011);
	  ProjectionY2[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
          if (d <=3){
          ProjectionY2[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 4) + " Ring 3");
	  }else{
	  ProjectionY2[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 3) + " Ring 3");
	  }
	  ProjectionY2[0][d]->SetLineColor(1);
	  ProjectionY2[0][d]->Scale(1./ProjectionY2[0][d]->Integral());
	  ProjectionY2[0][d]->Draw("same");
	  
	  ProjectionY2[1][d]->SetMinimum(0.001);
	  ProjectionY2[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[1][d]->SetLineColor(2);
	  ProjectionY2[1][d]->Scale(1./ProjectionY2[1][d]->Integral());
	  ProjectionY2[1][d]->Draw("same");
          
	  ProjectionY2[2][d]->SetMinimum(0.001);
	  ProjectionY2[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[2][d]->SetLineColor(3);
	  ProjectionY2[2][d]->Scale(1./ProjectionY2[2][d]->Integral());
	  ProjectionY2[2][d]->Draw("same");
	  
	  ProjectionY2[3][d]->SetMinimum(0.01);
	  ProjectionY2[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY2[3][d]->SetLineColor(4);
	  ProjectionY2[3][d]->Scale(1./ProjectionY2[3][d]->Integral());
	  ProjectionY2[3][d]->Draw("same");
	  
	  auto legend29 = new TLegend(0.7,0.7,0.88,0.88);
	  legend29->AddEntry(ProjectionY1[0][d], "pu = 0.5" ,"l");
	  legend29->AddEntry(ProjectionY1[1][d], "pu = 1" ,"l");
	  legend29->AddEntry(ProjectionY1[2][d], "pu = 1.5" ,"l");
	  legend29->AddEntry(ProjectionY1[3][d], "pu = 2" ,"l");
	  
	  legend29->SetFillColor(0);
	  legend29->SetLineColor(0);
	  legend29->SetFillColor(0);
	  legend29->Draw();
	  
	  char *Projection15 = new char[10];
	  Int_t pro15 = d + 1;
	  sprintf(Projection15,"ProjectioncsRing3_%d.gif",pro15);
	  cout<<"=========================="<<Projection15<<endl;
	  c35->Print(outputpath12 + Projection15);
	  c35->Clear();
	  
	  
	  TCanvas *c36 = new TCanvas();
	  c36->cd();
	  c36->SetLogy();

	  ProjectionY3[0][d]->SetMinimum(0.011);
	  ProjectionY3[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY3[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 4) + " Ring 4");
	  }else{
	  ProjectionY3[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 3) + " Ring 4");
	  }
	  ProjectionY3[0][d]->SetLineColor(1);
	  ProjectionY3[0][d]->Scale(1./ProjectionY3[0][d]->Integral());
	  ProjectionY3[0][d]->Draw("same");
	  
	  ProjectionY3[1][d]->SetMinimum(0.001);
	  ProjectionY3[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[1][d]->SetLineColor(2);
	  ProjectionY3[1][d]->Scale(1./ProjectionY3[1][d]->Integral());
	  ProjectionY3[1][d]->Draw("same");
	  
	  ProjectionY3[2][d]->SetMinimum(0.001);
	  ProjectionY3[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[2][d]->SetLineColor(3);
	  ProjectionY3[2][d]->Scale(1./ProjectionY3[2][d]->Integral());
	  ProjectionY3[2][d]->Draw("same");
	  
	  ProjectionY3[3][d]->SetMinimum(0.01);
	  ProjectionY3[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY3[3][d]->SetLineColor(4);
	  ProjectionY3[3][d]->Scale(1./ProjectionY3[3][d]->Integral());
	  ProjectionY3[3][d]->Draw("same");
	  
	  auto legend30 = new TLegend(0.7,0.7,0.88,0.88);
	  legend30->AddEntry(ProjectionY3[0][d], "pu = 0.5" ,"l");
	  legend30->AddEntry(ProjectionY3[1][d], "pu = 1" ,"l");
	  legend30->AddEntry(ProjectionY3[2][d], "pu = 1.5" ,"l");
	  legend30->AddEntry(ProjectionY3[3][d], "pu = 2" ,"l");
	  
	  legend30->SetFillColor(0);
	  legend30->SetLineColor(0);
	  legend30->SetFillColor(0);
	  legend30->Draw();
	  
	  char *Projection16 = new char[10];
	  Int_t pro16 = d + 1;
	  sprintf(Projection16,"ProjectioncsRing4_%d.gif",pro16);
	  cout<<"=========================="<<Projection16<<endl;
	  c36->Print(outputpath12 + Projection16);
	  c36->Clear();
	  
	  

	  TCanvas *c37 = new TCanvas();
	  c37->cd();
	  c37->SetLogy();
	  
	  ProjectionY4[0][d]->SetMinimum(0.011);
	  ProjectionY4[0][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	  if (d <=3){
          ProjectionY4[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 4) + " Ring 5");
	  }else{
	  ProjectionY4[0][d]->SetTitle(TString("Number of 3x Coincidences for Disk ") + (d - 3) + " Ring 5");
	  }
	  ProjectionY4[0][d]->SetLineColor(1);
	  ProjectionY4[0][d]->Scale(1./ProjectionY4[0][d]->Integral());
	  ProjectionY4[0][d]->Draw("same");

	  ProjectionY4[1][d]->SetMinimum(0.001);
	  ProjectionY4[1][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[1][d]->SetLineColor(2);
	  ProjectionY4[1][d]->Scale(1./ProjectionY4[1][d]->Integral());
	  ProjectionY4[1][d]->Draw("same");
          
	  ProjectionY4[2][d]->SetMinimum(0.001);
	  ProjectionY4[2][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[2][d]->SetLineColor(3);
	  ProjectionY4[2][d]->Scale(1./ProjectionY4[2][d]->Integral());
	  ProjectionY4[2][d]->Draw("same");
	  
	  ProjectionY4[3][d]->SetMinimum(0.01);
	  ProjectionY4[3][d]->GetXaxis()->SetRangeUser(0, 100);
	  ProjectionY4[3][d]->SetLineColor(4);
	  ProjectionY4[3][d]->Scale(1./ProjectionY4[3][d]->Integral());
	  ProjectionY4[3][d]->Draw("same");
	  
	  auto legend31 = new TLegend(0.7,0.7,0.88,0.88);
	  legend31->AddEntry(ProjectionY4[0][d], "pu = 0.5" ,"l");
	  legend31->AddEntry(ProjectionY4[1][d], "pu = 1" ,"l");
	  legend31->AddEntry(ProjectionY4[2][d], "pu = 1.5" ,"l");
	  legend31->AddEntry(ProjectionY4[3][d], "pu = 2" ,"l");
	  
	  legend31->SetFillColor(0);
	  legend31->SetLineColor(0);
	  legend31->SetFillColor(0);
	  legend31->Draw();
	  
	  char *Projection17 = new char[10];
	  Int_t pro17 = d + 1;
	  sprintf(Projection17,"ProjectioncsRing5_%d.gif",pro17);
	  cout<<"=========================="<<Projection17<<endl;
	  c37->Print(outputpath12 + Projection17);
	  c37->Clear();
	  
	}
	
        
	TCanvas *c38 = new TCanvas();
	c38->cd();
	c38->SetLogy();
	
	ProjectionY[0][d]->SetMinimum(0.011);
	ProjectionY[0][d]->GetXaxis()->SetRangeUser(0, 100);
        ProjectionY[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY[0][d]->SetLineColor(1);
	ProjectionY[0][d]->Scale(1./ProjectionY[0][d]->Integral());
	ProjectionY[0][d]->Draw("same");
	
	ProjectionY[1][d]->SetMinimum(0.001);
	ProjectionY[1][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[1][d]->SetLineColor(2);
	ProjectionY[1][d]->Scale(1./ProjectionY[1][d]->Integral());
	ProjectionY[1][d]->Draw("same");
               
	ProjectionY[2][d]->SetMinimum(0.001);
	ProjectionY[2][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[2][d]->SetLineColor(3);
	ProjectionY[2][d]->Scale(1./ProjectionY[2][d]->Integral());
	ProjectionY[2][d]->Draw("same");
	
	ProjectionY[3][d]->SetMinimum(0.01);
	ProjectionY[3][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[3][d]->SetLineColor(4);
	ProjectionY[3][d]->Scale(1./ProjectionY[3][d]->Integral());
	ProjectionY[3][d]->Draw("same");
	
	ProjectionY[4][d]->SetMinimum(0.01);
	ProjectionY[4][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[4][d]->SetLineColor(5);
	ProjectionY[4][d]->Scale(1./ProjectionY[4][d]->Integral());
	ProjectionY[4][d]->Draw("same");
	
	ProjectionY[5][d]->SetMinimum(0.01);
	ProjectionY[5][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[5][d]->SetLineColor(6);
	ProjectionY[5][d]->Scale(1./ProjectionY[5][d]->Integral());
	ProjectionY[5][d]->Draw("same");
	
	ProjectionY[6][d]->SetMinimum(0.01);
	ProjectionY[6][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[6][d]->SetLineColor(7);
	ProjectionY[6][d]->Scale(1./ProjectionY[6][d]->Integral());
	ProjectionY[6][d]->Draw("same");
	
	ProjectionY[7][d]->SetMinimum(0.01);
	ProjectionY[7][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[7][d]->SetLineColor(8);
	ProjectionY[7][d]->Scale(1./ProjectionY[7][d]->Integral());
	ProjectionY[7][d]->Draw("same");
	
	ProjectionY[8][d]->SetMinimum(0.01);
	ProjectionY[8][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[8][d]->SetLineColor(9);
	ProjectionY[8][d]->Scale(1./ProjectionY[8][d]->Integral());
	ProjectionY[8][d]->Draw("same");
	
	ProjectionY[9][d]->SetMinimum(0.01);
	ProjectionY[9][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY[9][d]->SetLineColor(44);
	ProjectionY[9][d]->Scale(1./ProjectionY[9][d]->Integral());
	ProjectionY[9][d]->Draw("same");
	
	

	auto legend32 = new TLegend(0.7,0.7,0.88,0.88);
	legend32->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend32->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend32->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend32->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend32->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend32->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend32->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend32->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend32->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend32->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend32->SetFillColor(0);
	legend32->SetLineColor(0);
	legend32->SetFillColor(0);
	legend32->Draw();
	
	
	char *Projection12 = new char[10];
	Int_t pro13 = d + 1;
	sprintf(Projection12,"ProjectiondsRing1_%d.gif",pro13);
	cout<<"=========================="<<Projection12<<endl;
	c38->Print(outputpath12 + Projection12);
	c38->Clear();
		
	
	

	
	TCanvas *c39 = new TCanvas();
	c39->cd();
	c39->SetLogy();
	
	ProjectionY1[0][d]->SetMinimum(0.011);
	ProjectionY1[0][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY1[0][d]->SetLineColor(1);
	ProjectionY1[0][d]->Scale(1./ProjectionY1[0][d]->Integral());
	ProjectionY1[0][d]->Draw("same");
	
	ProjectionY1[1][d]->SetMinimum(0.001);
	ProjectionY1[1][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[1][d]->SetLineColor(2);
	ProjectionY1[1][d]->Scale(1./ProjectionY1[1][d]->Integral());
	ProjectionY1[1][d]->Draw("same");
	
	ProjectionY1[2][d]->SetMinimum(0.001);
	ProjectionY1[2][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[2][d]->SetLineColor(3);
	ProjectionY1[2][d]->Scale(1./ProjectionY1[2][d]->Integral());
	ProjectionY1[2][d]->Draw("same");
	
	ProjectionY1[3][d]->SetMinimum(0.01);
	ProjectionY1[3][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[3][d]->SetLineColor(4);
	ProjectionY1[3][d]->Scale(1./ProjectionY1[3][d]->Integral());
	ProjectionY1[3][d]->Draw("same");
	
	ProjectionY1[4][d]->SetMinimum(0.01);
	ProjectionY1[4][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[4][d]->SetLineColor(5);
	ProjectionY1[4][d]->Scale(1./ProjectionY1[4][d]->Integral());
	ProjectionY1[4][d]->Draw("same");
	
	ProjectionY1[5][d]->SetMinimum(0.01);
	ProjectionY1[5][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[5][d]->SetLineColor(6);
	ProjectionY1[5][d]->Scale(1./ProjectionY1[5][d]->Integral());
	ProjectionY1[5][d]->Draw("same");
	
	ProjectionY1[6][d]->SetMinimum(0.01);
	ProjectionY1[6][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[6][d]->SetLineColor(7);
	ProjectionY1[6][d]->Scale(1./ProjectionY1[6][d]->Integral());
	ProjectionY1[6][d]->Draw("same");
	
	ProjectionY1[7][d]->SetMinimum(0.01);
	ProjectionY1[7][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[7][d]->SetLineColor(8);
	ProjectionY1[7][d]->Scale(1./ProjectionY1[7][d]->Integral());
	ProjectionY1[7][d]->Draw("same");
	
	ProjectionY1[8][d]->SetMinimum(0.01);
	ProjectionY1[8][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[8][d]->SetLineColor(9);
	ProjectionY1[8][d]->Scale(1./ProjectionY1[8][d]->Integral());
	ProjectionY1[8][d]->Draw("same");

	ProjectionY1[9][d]->SetMinimum(0.01);
	ProjectionY1[9][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY1[9][d]->SetLineColor(44);
	ProjectionY1[9][d]->Scale(1./ProjectionY1[9][d]->Integral());
	ProjectionY1[9][d]->Draw("same");
	
	
	
	auto legend33 = new TLegend(0.7,0.7,0.88,0.88);
	legend33->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend33->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend33->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend33->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend33->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend33->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend33->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend33->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend33->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend33->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend33->SetFillColor(0);
	legend33->SetLineColor(0);
	legend33->SetFillColor(0);
	legend33->Draw();
	
	
	char *Projection14 = new char[10];
	Int_t pro14 = d + 1;
	sprintf(Projection14,"ProjectiondsRing2_%d.gif",pro14);
	cout<<"=========================="<<Projection14<<endl;
	c39->Print(outputpath12 + Projection14);
	c39->Clear();
	
	
	
	TCanvas *c40 = new TCanvas();
	c40->cd();
	c40->SetLogy();
	
	ProjectionY2[0][d]->SetMinimum(0.011);
	ProjectionY2[0][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY2[0][d]->SetLineColor(1);
	ProjectionY2[0][d]->Scale(1./ProjectionY2[0][d]->Integral());
	ProjectionY2[0][d]->Draw("same");
	
	ProjectionY2[1][d]->SetMinimum(0.001);
	ProjectionY2[1][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[1][d]->SetLineColor(2);
	ProjectionY2[1][d]->Scale(1./ProjectionY2[1][d]->Integral());
	ProjectionY2[1][d]->Draw("same");
        
	ProjectionY2[2][d]->SetMinimum(0.001);
	ProjectionY2[2][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[2][d]->SetLineColor(3);
	ProjectionY2[2][d]->Scale(1./ProjectionY2[2][d]->Integral());
	ProjectionY2[2][d]->Draw("same");

	ProjectionY2[3][d]->SetMinimum(0.01);
	ProjectionY2[3][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[3][d]->SetLineColor(4);
	ProjectionY2[3][d]->Scale(1./ProjectionY2[3][d]->Integral());
	ProjectionY2[3][d]->Draw("same");
	
	ProjectionY2[4][d]->SetMinimum(0.01);
	ProjectionY2[4][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[4][d]->SetLineColor(5);
	ProjectionY2[4][d]->Scale(1./ProjectionY2[4][d]->Integral());
	ProjectionY2[4][d]->Draw("same");
	
	ProjectionY2[5][d]->SetMinimum(0.01);
	ProjectionY2[5][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[5][d]->SetLineColor(6);
	ProjectionY2[5][d]->Scale(1./ProjectionY2[5][d]->Integral());
	ProjectionY2[5][d]->Draw("same");
	
	ProjectionY2[6][d]->SetMinimum(0.01);
	ProjectionY2[6][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[6][d]->SetLineColor(7);
	ProjectionY2[6][d]->Scale(1./ProjectionY2[6][d]->Integral());
	ProjectionY2[6][d]->Draw("same");
		
	ProjectionY2[7][d]->SetMinimum(0.01);
	ProjectionY2[7][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[7][d]->SetLineColor(8);
	ProjectionY2[7][d]->Scale(1./ProjectionY2[7][d]->Integral());
	ProjectionY2[7][d]->Draw("same");
	
	ProjectionY2[8][d]->SetMinimum(0.01);
	ProjectionY2[8][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[8][d]->SetLineColor(9);
	ProjectionY2[8][d]->Scale(1./ProjectionY2[8][d]->Integral());
	ProjectionY2[8][d]->Draw("same");
	
	ProjectionY2[9][d]->SetMinimum(0.01);
	ProjectionY2[9][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY2[9][d]->SetLineColor(44);
	ProjectionY2[9][d]->Scale(1./ProjectionY2[9][d]->Integral());
	ProjectionY2[9][d]->Draw("same");
	
 
	
	auto legend34 = new TLegend(0.7,0.7,0.88,0.88);
	legend34->AddEntry(ProjectionY[0][d], "pu = 0.5" ,"l");
	legend34->AddEntry(ProjectionY[1][d], "pu = 1" ,"l");
	legend34->AddEntry(ProjectionY[2][d], "pu = 1.5" ,"l");
	legend34->AddEntry(ProjectionY[3][d], "pu = 2" ,"l");
	legend34->AddEntry(ProjectionY[4][d], "pu = 10" ,"l");
	legend34->AddEntry(ProjectionY[5][d], "pu = 30" ,"l");
	legend34->AddEntry(ProjectionY[6][d], "pu = 50" ,"l");
	legend34->AddEntry(ProjectionY[7][d], "pu = 100" ,"l");
	legend34->AddEntry(ProjectionY[8][d], "pu = 140" ,"l");
	legend34->AddEntry(ProjectionY[9][d], "pu = 200" ,"l");
	legend34->SetFillColor(0);
	legend34->SetLineColor(0);
	legend34->SetFillColor(0);
	legend34->Draw();
	
	
	char *Projection15 = new char[10];
	Int_t pro15 = d + 1;
	sprintf(Projection15,"ProjectiondsRing3_%d.gif",pro15);
	cout<<"=========================="<<Projection15<<endl;
	c40->Print(outputpath12 + Projection15);
	c40->Clear();
	
	
	
	TCanvas *c41 = new TCanvas();
	c41->cd();
	c41->SetLogy();
	
	ProjectionY3[0][d]->SetMinimum(0.011);
	ProjectionY3[0][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY3[0][d]->SetLineColor(1);
	ProjectionY3[0][d]->Scale(1./ProjectionY3[0][d]->Integral());
	ProjectionY3[0][d]->Draw("same");
	
	ProjectionY3[1][d]->SetMinimum(0.001);
	ProjectionY3[1][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[1][d]->SetLineColor(2);
	ProjectionY3[1][d]->Scale(1./ProjectionY3[1][d]->Integral());
	ProjectionY3[1][d]->Draw("same");
        
	ProjectionY3[2][d]->SetMinimum(0.001);
	ProjectionY3[2][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[2][d]->SetLineColor(3);
	ProjectionY3[2][d]->Scale(1./ProjectionY3[2][d]->Integral());
	ProjectionY3[2][d]->Draw("same");
	
	ProjectionY3[3][d]->SetMinimum(0.01);
	ProjectionY3[3][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[3][d]->SetLineColor(4);
	ProjectionY3[3][d]->Scale(1./ProjectionY3[3][d]->Integral());
	ProjectionY3[3][d]->Draw("same");
	
	ProjectionY3[4][d]->SetMinimum(0.01);
	ProjectionY3[4][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[4][d]->SetLineColor(5);
	ProjectionY3[4][d]->Scale(1./ProjectionY3[4][d]->Integral());
	ProjectionY3[4][d]->Draw("same");
	
	ProjectionY3[5][d]->SetMinimum(0.01);
	ProjectionY3[5][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[5][d]->SetLineColor(6);
	ProjectionY3[5][d]->Scale(1./ProjectionY3[5][d]->Integral());
	ProjectionY3[5][d]->Draw("same");
	
	ProjectionY3[6][d]->SetMinimum(0.01);
	ProjectionY3[6][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[6][d]->SetLineColor(7);
	ProjectionY3[6][d]->Scale(1./ProjectionY3[6][d]->Integral());
	ProjectionY3[6][d]->Draw("same");
	
	ProjectionY3[7][d]->SetMinimum(0.01);
	ProjectionY3[7][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[7][d]->SetLineColor(8);
	ProjectionY3[7][d]->Scale(1./ProjectionY3[7][d]->Integral());
	ProjectionY3[7][d]->Draw("same");
	
	ProjectionY3[8][d]->SetMinimum(0.01);
	ProjectionY3[8][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[8][d]->SetLineColor(9);
	ProjectionY3[8][d]->Scale(1./ProjectionY3[8][d]->Integral());
	ProjectionY3[8][d]->Draw("same");
	
	ProjectionY3[9][d]->SetMinimum(0.01);
	ProjectionY3[9][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY3[9][d]->SetLineColor(44);
	ProjectionY3[9][d]->Scale(1./ProjectionY3[9][d]->Integral());
	ProjectionY3[9][d]->Draw("same");
	
	
	
	auto legend35 = new TLegend(0.7,0.7,0.88,0.88);
	legend35->AddEntry(ProjectionY3[0][d], "pu = 0.5" ,"l");
	legend35->AddEntry(ProjectionY3[1][d], "pu = 1" ,"l");
	legend35->AddEntry(ProjectionY3[2][d], "pu = 1.5" ,"l");
	legend35->AddEntry(ProjectionY3[3][d], "pu = 2" ,"l");
	legend35->AddEntry(ProjectionY3[4][d], "pu = 10" ,"l");
	legend35->AddEntry(ProjectionY3[5][d], "pu = 30" ,"l");
	legend35->AddEntry(ProjectionY3[6][d], "pu = 50" ,"l");
	legend35->AddEntry(ProjectionY3[7][d], "pu = 100" ,"l");
	legend35->AddEntry(ProjectionY3[8][d], "pu = 140" ,"l");
	legend35->AddEntry(ProjectionY3[9][d], "pu = 200" ,"l");
	legend35->SetFillColor(0);
	legend35->SetLineColor(0);
	legend35->SetFillColor(0);
	legend35->Draw();

	char *Projection16 = new char[10];
	Int_t pro16 = d + 1;
	sprintf(Projection16,"ProjectiondsRing4_%d.gif",pro16);
	cout<<"=========================="<<Projection16<<endl;
	c41->Print(outputpath12 + Projection16);
	c41->Clear();
	
		
	
	TCanvas *c42 = new TCanvas();
	c42->cd();
	c42->SetLogy();
	
	ProjectionY4[0][d]->SetMinimum(0.011);
	ProjectionY4[0][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[0][d]->GetYaxis()->SetTitle("# of events (normalized to unit)");
	ProjectionY4[0][d]->SetLineColor(1);
	ProjectionY4[0][d]->Scale(1./ProjectionY4[0][d]->Integral());
	ProjectionY4[0][d]->Draw("same");
	
	ProjectionY4[1][d]->SetMinimum(0.001);
	ProjectionY4[1][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[1][d]->SetLineColor(2);
	ProjectionY4[1][d]->Scale(1./ProjectionY4[1][d]->Integral());
	ProjectionY4[1][d]->Draw("same");
        
	ProjectionY4[2][d]->SetMinimum(0.001);
	ProjectionY4[2][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[2][d]->SetLineColor(3);
	ProjectionY4[2][d]->Scale(1./ProjectionY4[2][d]->Integral());
	ProjectionY4[2][d]->Draw("same");
	
	ProjectionY4[3][d]->SetMinimum(0.01);
	ProjectionY4[3][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[3][d]->SetLineColor(4);
	ProjectionY4[3][d]->Scale(1./ProjectionY4[3][d]->Integral());
	ProjectionY4[3][d]->Draw("same");
	
	ProjectionY4[4][d]->SetMinimum(0.01);
	ProjectionY4[4][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[4][d]->SetLineColor(5);
	ProjectionY4[4][d]->Scale(1./ProjectionY4[4][d]->Integral());
	ProjectionY4[4][d]->Draw("same");

	ProjectionY4[5][d]->SetMinimum(0.01);
	ProjectionY4[5][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[5][d]->SetLineColor(6);
	ProjectionY4[5][d]->Scale(1./ProjectionY4[5][d]->Integral());
	ProjectionY4[5][d]->Draw("same");
	
	ProjectionY4[6][d]->SetMinimum(0.01);
	ProjectionY4[6][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[6][d]->SetLineColor(7);
	ProjectionY4[6][d]->Scale(1./ProjectionY4[6][d]->Integral());
	ProjectionY4[6][d]->Draw("same");
	
	ProjectionY4[7][d]->SetMinimum(0.01);
	ProjectionY4[7][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[7][d]->SetLineColor(8);
	ProjectionY4[7][d]->Scale(1./ProjectionY4[7][d]->Integral());
	ProjectionY4[7][d]->Draw("same");
	
	ProjectionY4[8][d]->SetMinimum(0.01);
	ProjectionY4[8][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[8][d]->SetLineColor(9);
	ProjectionY4[8][d]->Scale(1./ProjectionY4[8][d]->Integral());
	ProjectionY4[8][d]->Draw("same");
	
	ProjectionY4[9][d]->SetMinimum(0.01);
	ProjectionY4[9][d]->GetXaxis()->SetRangeUser(0, 100);
	ProjectionY4[9][d]->SetLineColor(44);
	ProjectionY4[9][d]->Scale(1./ProjectionY4[9][d]->Integral());
	ProjectionY4[9][d]->Draw("same");
	
	
	
	auto legend36 = new TLegend(0.7,0.7,0.88,0.88);
	legend36->AddEntry(ProjectionY4[0][d], "pu = 0.5" ,"l");
	legend36->AddEntry(ProjectionY4[1][d], "pu = 1" ,"l");
	legend36->AddEntry(ProjectionY4[2][d], "pu = 1.5" ,"l");
	legend36->AddEntry(ProjectionY4[3][d], "pu = 2" ,"l");
	legend36->AddEntry(ProjectionY4[4][d], "pu = 10" ,"l");
	legend36->AddEntry(ProjectionY4[5][d], "pu = 30" ,"l");
	legend36->AddEntry(ProjectionY4[6][d], "pu = 50" ,"l");
	legend36->AddEntry(ProjectionY4[7][d], "pu = 100" ,"l");
	legend36->AddEntry(ProjectionY4[8][d], "pu = 140" ,"l");
	legend36->AddEntry(ProjectionY4[9][d], "pu = 200" ,"l");
	legend36->SetFillColor(0);
	legend36->SetLineColor(0);
	legend36->SetFillColor(0);
	legend36->Draw();
	
	
	char *Projection17 = new char[10];
	Int_t pro17 = d + 1;
	sprintf(Projection17,"ProjectiondsRing5_%d.gif",pro17);
	cout<<"=========================="<<Projection17<<endl;
	c42->Print(outputpath12 + Projection17);
	c42->Clear();
	
	
      }

      
      
      
      //Bin content and Bin error of the  Profile X of Histogram H
      for (int r = 0; r < 5; r++) {
	      
	TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1));
	TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1));
              
      }
    }
  }


    
    

  //Make the fit graphs for all Rings and Disks
  TLatex label;
  label.SetTextSize(0.2);
  TF1* FitTEPXClustersPerEvent[20][4];

  for (long d = 0; d < disklist.size(); d++)
    for (long r = 0; r < 5; r++) {

      //fix the pads
      Int_t l = d * 5 + r + 1;
      TCanvas C("C");
      C.cd();
      
      //fit
      FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 200);
      FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
      TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
      
      
      
      //draw the fit graphs for all disks and rings
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetNdivisions(12);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetLabelSize(0.03);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetLabelSize(0.03);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetTitle("Pileup");
      TEPXClustersPerEvent[d][r]->SetMarkerStyle(21);
      TEPXClustersPerEvent[d][r]->SetMarkerSize(1);
      TEPXClustersPerEvent[d][r]->SetMarkerColor(2);
      gStyle->SetOptStat(1111);
      gStyle->SetOptFit(1111);
      gPad->SetGrid(1, 1);

      if (option == 1){
	
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of Clusters");
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 3000);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetNdivisions(12);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
	TEPXClustersPerEvent[d][r]->Draw("ape");
	FitTEPXClustersPerEvent[d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r+ 1));
	char* histname = new char[10];
	sprintf(histname, "histo%d_linearity1.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath4 + histname);
	

        FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
        TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 30);
        TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
        char* histname1 = new char[10];
	sprintf(histname1, "histo%d_linearity4.gif", l);
        C.Update();
        C.Print(outputpath3 + histname1);
        
      }
	

      if (option == 2){
	
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of 2x Coincidences");
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 540);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
	TEPXClustersPerEvent[d][r]->Draw("ape");
	FitTEPXClustersPerEvent[d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r + 1));
	char* histname = new char[10];
	sprintf(histname, "histo%d_linearity2.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath9 + histname);
	

	FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
        TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 8);
        TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
        char* histname1 = new char[10];
	sprintf(histname1, "histo%d_linearity5.gif", l);
        C.Update();
        C.Print(outputpath8 + histname1);
      }
            
      if (option == 3){
	
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of 3x Coincidences");
	TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 80);
	TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 210);
	TEPXClustersPerEvent[d][r]->Draw("ape");
	FitTEPXClustersPerEvent[d][r]->Draw("lsame");
	label.SetTextSize(0.1);
	label.DrawLatexNDC(0.15, 0.8, TString("D=") + (long)(d <= 3 ? d - 4 : d + 1 - 4) + ",  R=" + (long)(r + 1));
	char* histname = new char[10];
	sprintf(histname, "histo%d_linearity3.gif", l);
	cout << "==========================" << histname << endl;
	C.Print(outputpath14 + histname);
	

        FitTEPXClustersPerEvent[d][r] = new TF1(TString("Fit_") + d + "_" + r, "[0]+[1]*x", 0.5, 2);
        FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
        TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r], "", "", 0.5, 2);
        TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0, 1.5);
        TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0, 2);
        char* histname1 = new char[10];
	sprintf(histname1, "histo%d_linearity6.gif", l);
        C.Update();
        C.Print(outputpath13 + histname1);
                
      }      
    }
    
    
  //Set residuals points and residuals point error
  for (int d = 0; d < disklist.size(); d++) {
    for (int r = 0; r < 5; r++) {
      for (int pu = 0; pu < pulist.size(); pu++) {


	float x = pumap[pulist[pu]];
	float y = (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r + 1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]])) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
	float yerr = (Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r + 1)) / FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);

             
	if (pu > 2) {


	  //NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x -(r-2), y);
          NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	  NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	} else {


	  NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
	  NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
	  
	}
	
      }
    }
  }


  TCanvas C3("C3");
  C3.cd();

  //draw residuals vs pileup graph for Disk 4 Ring 1

  if (option == 1){
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetNdivisions(10);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetLabelSize(0.03);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetMaxDigits(4);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetLineColor(1);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetRangeUser(-0.015, 0.015);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetNdivisions(12);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetRangeUser(0, 2);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetTitle("Pileup");
    NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerStyle(21);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerColor(2);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerSize(1);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetTitle("Disk 4 Ring 1");
    TLine* line1 = new TLine(0, 0, 2.5, 0);
    line1->SetLineColor(kBlack);

    gPad->SetGrid(1, 1);
    NonLinearity_TEPXClustersPerEvent[7][0]->Draw("ape");
    line1->Draw("same");

    C3.Print(outputpath5 + "NS1Brane.gif");
    C3.Clear();
    
  }

  if (option == 2){
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetNdivisions(10);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetLabelSize(0.03);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetMaxDigits(4);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetYaxis()->SetRangeUser(-0.16, 0.16);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetNdivisions(12);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetRangeUser(0, 210);
    NonLinearity_TEPXClustersPerEvent[7][0]->GetXaxis()->SetTitle("Pileup");
    NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerStyle(21);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerColor(2);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetMarkerSize(1);
    NonLinearity_TEPXClustersPerEvent[7][0]->SetTitle("Disk 4 Ring 1");
    TLine* line1 = new TLine(0, 0, 210, 0);
    line1->SetLineColor(kBlack);

    gPad->SetGrid(1, 1);
    NonLinearity_TEPXClustersPerEvent[7][0]->Draw("ape");
    line1->Draw("same");

    C3.Print(outputpath10 + "NS2Brane.gif");
    C3.Clear();
  }
  if (option == 3){
    NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetNdivisions(10);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetLabelSize(0.03);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
    NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetMaxDigits(4);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetYaxis()->SetRangeUser(-5, 5);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetNdivisions(12);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetRangeUser(0, 210);
    NonLinearity_TEPXClustersPerEvent[7][1]->GetXaxis()->SetTitle("Pileup");
    NonLinearity_TEPXClustersPerEvent[7][1]->SetMarkerStyle(21);
    NonLinearity_TEPXClustersPerEvent[7][1]->SetMarkerColor(2);
    NonLinearity_TEPXClustersPerEvent[7][1]->SetMarkerSize(0.6);
    NonLinearity_TEPXClustersPerEvent[7][1]->SetTitle("Disk 4 Ring 2");
    TLine* line1 = new TLine(0, 0, 210, 0);
    line1->SetLineColor(kBlack);

    gPad->SetGrid(1, 1);
    NonLinearity_TEPXClustersPerEvent[7][1]->Draw("ape");
    line1->Draw("same");

    C3.Print(outputpath15 + "NS3Brane.gif");
    C3.Clear();
  }
    
  TCanvas C2("C2");
  C2.cd();
    

  //draw residuals vs pileup graph
  if(option == 1){
    for (int d = 0; d < disklist.size(); d++) {

      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetNdivisions(10);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetLabelSize(0.02);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetRangeUser(-0.015, 0.015);
      
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetNdivisions(12);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetLabelSize(0.04);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetRangeUser(0, 210);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetTitle("Pileup");
      
      NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerStyle(20);
      NonLinearity_TEPXClustersPerEvent[d][0]->SetLineColor(1);
      NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerSize(0);
      if (d <= 3) {
            NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 4));
      } else {
	NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 3));
      }

      auto legend = new TLegend(0.7, 0.2, 0.8, 0.4);
      NonLinearity_TEPXClustersPerEvent[d][0]->Draw("ape");
      legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][0], TString(" Ring ") + 1, "l");

      for (int r = 1; r < 5; r++) {

	NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
	NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
	NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
	NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
	legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1), "l");
      }
      
      TLine* line = new TLine(0, 0, 220, 0);
      line->SetLineColor(kBlack);
      line->Draw("same");

      legend->SetFillColor(0);
      legend->SetLineColor(0);
      legend->SetFillColor(0);
      legend->Draw("same");

      C2.Print(outputpath5 + TString("Clusterdisk_") + d + ".gif");
    }
  }
    
  if(option == 2){
    for (int d = 0; d < disklist.size(); d++) {

      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetNdivisions(10);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetLabelSize(0.02);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
      NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetRangeUser(-0.15, 0.15);
      
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetNdivisions(12);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetLabelSize(0.04);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetRangeUser(0, 210);
      NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetTitle("Pileup");
      
      NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerStyle(20);
      NonLinearity_TEPXClustersPerEvent[d][0]->SetLineColor(1);
      NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerSize(0);

      if (d <= 3) {
	NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 4));
      } else {
	NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ") + (d - 3));
      }

      auto legend = new TLegend(0.7, 0.2, 0.8, 0.4);
      NonLinearity_TEPXClustersPerEvent[d][0]->Draw("ape");
      legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][0], TString(" Ring ") + 1, "l");

      for (int r = 1; r < 5; r++) {

	NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
	NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
	NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
	NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
	legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1), "l");
	
      }

      TLine* line = new TLine(0, 0, 220, 0);
      line->SetLineColor(kBlack);
      line->Draw("same");

      legend->SetFillColor(0);
      legend->SetLineColor(0);
      legend->SetFillColor(0);
      legend->Draw("same");

      C2.Print(outputpath10 + TString("2xCoincidencesdisk_") + d + ".gif");
      
    }
  } 

  
  if(option == 3){
    for (int d = 0; d < disklist.size(); d++) {

      NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetNdivisions(10);
      NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetLabelSize(0.02);
      NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
      NonLinearity_TEPXClustersPerEvent[d][1]->GetYaxis()->SetRangeUser(-50, 50);

      NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetNdivisions(12);
      NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetLabelSize(0.04);
      NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetRangeUser(0, 210);
      NonLinearity_TEPXClustersPerEvent[d][1]->GetXaxis()->SetTitle("Pileup");

      NonLinearity_TEPXClustersPerEvent[d][1]->SetMarkerStyle(20);
      NonLinearity_TEPXClustersPerEvent[d][1]->SetLineColor(1);
      NonLinearity_TEPXClustersPerEvent[d][1]->SetMarkerSize(0);
      if (d <= 3) {
	NonLinearity_TEPXClustersPerEvent[d][1]->SetTitle(TString("Disk ") + (d - 4));
      } else {
	NonLinearity_TEPXClustersPerEvent[d][1]->SetTitle(TString("Disk ") + (d - 3));
      }

      auto legend = new TLegend(0.7, 0.2, 0.8, 0.4);
      NonLinearity_TEPXClustersPerEvent[d][1]->Draw("ape");
      legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][1], TString(" Ring ") + 2, "l");
      
      for (int r = 2; r < 5; r++) {

	NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
	NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r + 1);
	NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
	NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
	legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r], TString(" Ring ") + (r + 1) , "l");
      }

      TLine* line = new TLine(0, 0, 220, 0);
      line->SetLineColor(kBlack);
      line->Draw("same");

      legend->SetFillColor(0);
      legend->SetLineColor(0);
      legend->SetFillColor(0);
      legend->Draw("same");

      C2.Print(outputpath15 + TString("3xCoincidencesdisk_") + d + ".gif");
      
    }
  }   
}
