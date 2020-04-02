void linearity2(){
  TString outputpath = "/eos/user/a/asehrawa/";
  TString inpath="/eos/user/a/asehrawa/TEPX/samples_17Feb2020/";
  //TString histoname="BRIL_IT_Analysis/TEPX/Clusters/Number of clusters for Disk ";
  TString histoname="BRIL_IT_Analysis/TEPX/2xCoincidences/Number of 2x Coincidences for Disk ";
  //TString histoname="BRIL_IT_Analysis/TEPX/3xCoincidences/Number of 3x Coincidences for Disk ";  
  gROOT->ProcessLine(".x /afs/cern.ch/user/a/asehrawa/CMSSW_10_6_0_patch2/src/rootlogon.C");
	
  std::vector<std::string> pulist={"2023D42PU0p5","2023D42PU1","2023D42PU1p5","2023D42PU2","2023D42PU10","2023D42PU30","2023D42PU50","2023D42PU100","2023D42PU140","2023D42PU200"};
  std::map<std::string,float> pumap={{"2023D42PU0p5",0.5},{"2023D42PU1",1},{"2023D42PU1p5",1.5},{"2023D42PU2",2},{"2023D42PU10",10},{"2023D42PU30",30},{"2023D42PU50",50},{"2023D42PU100",100},{"2023D42PU140",140},{"2023D42PU200",200}};

  std::vector<std::string> disklist={"-4","-3","-2","-1","1","2","3","4"};

  //create the profiles to be filled below.
  TGraphErrors * TEPXClustersPerEvent[20][4];//number of clusters vs pu
  for(int d=0; d<disklist.size(); d++) 
    for(int r=0 ; r<5; r++)
       TEPXClustersPerEvent[d][r] = new TGraphErrors();



  //Non-linearity graphs
  TGraphErrors * NonLinearity_TEPXClustersPerEvent[20][4];//number of clusters vs pu
   for(int d=0; d<disklist.size(); d++){
    for(int r=0 ; r<5; r++){
      	NonLinearity_TEPXClustersPerEvent[d][r] = new TGraphErrors();
    	}
  }


  //read the histograms
  TProfile * Prof_TEPXClustersPerEvent[20][20];//array pu,disk
  TProfile * Prof_TEPXClustersPerEvent1[20][20];
   for(int pu=0;pu<pulist.size();pu++){
    TFile F(inpath+pulist[pu]+".root","read");  
    gROOT->cd();

    for(int d=0;d<disklist.size();d++){
      TH2F* H=(TH2F*)F.Get(histoname+disklist[d]);
      Prof_TEPXClustersPerEvent[pu][d] = (TProfile*) H->ProfileX()->Clone(TString(H->GetName())+"Profile");//number of cluster vs ring
     
     for(int r=0;r<5;r++){
      TEPXClustersPerEvent[d][r]->SetPoint(pu, pumap[pulist[pu]], Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1));
      TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r+1));
        
      cout<<"pu is "<<pu<<endl;
	      
       for(int bin=1;bin<6;bin++){
		 
        cout<<"Bin Content of Histogram H-X is "<<H->ProfileX()->GetBinContent(bin)<<endl;
        cout<<"Bin Error of Histogram H-X is "<<H->ProfileX()->GetBinError(bin)<<endl;
        
	 }

        
      }

    }
  }
  

  //Make the graphs
  TLatex label; 
  label.SetTextSize(0.2);
  TF1 * FitTEPXClustersPerEvent[20][4];
 
  
  for(long d=0;d<disklist.size();d++)
    for(long r=0;r<5;r++){

      //fix the pads
      Int_t l = d*5+r+1;
      TCanvas C("C");
      C.cd();
 
      //fit
      FitTEPXClustersPerEvent[d][r]=new TF1(TString("Fit_")+d+"_"+r,"[0]+[1]*x",0.5,2);
      FitTEPXClustersPerEvent[d][r]->SetLineColor(4);
      TEPXClustersPerEvent[d][r]->Fit(FitTEPXClustersPerEvent[d][r],"","",0.5,2);

      cout<<"Intercept is "<<FitTEPXClustersPerEvent[d][r]->GetParameter(0)<<endl;
      cout<<"Slope is "<<FitTEPXClustersPerEvent[d][r]->GetParameter(1)<<endl;
      cout<<"Chisquare value is "<<FitTEPXClustersPerEvent[d][r]->GetChisquare()<<endl;
      cout<<"Number of degrees of freedom are "<<FitTEPXClustersPerEvent[d][r]->GetNDF()<<endl;
      cout<<"Intercept error is "<<FitTEPXClustersPerEvent[d][r]->GetParError(0)<<endl;
      cout<<"Slope error is "<<FitTEPXClustersPerEvent[d][r]->GetParError(1)<<endl;
      
    
      //draw
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetNdivisions(12);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetLabelSize(0.05);
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetTitle("Mean Number of 2x Coincidences");
      TEPXClustersPerEvent[d][r]->GetYaxis()->SetRangeUser(0,6);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetNdivisions(12);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetLabelSize(0.05);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetRangeUser(0,2);
      TEPXClustersPerEvent[d][r]->GetXaxis()->SetTitle("Pileup");
      TEPXClustersPerEvent[d][r]->SetMarkerStyle(21);
      TEPXClustersPerEvent[d][r]->SetMarkerSize(1);
      TEPXClustersPerEvent[d][r]->SetMarkerColor(2);
      gPad->SetGrid(1,1);
      TEPXClustersPerEvent[d][r]->Draw("ape");
      FitTEPXClustersPerEvent[d][r]->Draw("lsame");
      label.SetTextSize(0.1);
      label.DrawLatexNDC(0.23,0.8,TString("D=")+(long)(d<=3?d-4:d+1-4)+",  R="+(long)(r+1));
      char *histname = new char[10];
      sprintf(histname,"histo%d_linearity.gif",l);
      cout<<"=========================="<<histname<<endl;
      C.Print(outputpath+histname);
      C.Clear();

    }

      

  	for(int d=0; d<disklist.size(); d++){
    	for(int r=0 ; r<5; r++){
      	for(int pu=0;pu<pulist.size();pu++){
		
       float x = pumap[pulist[pu]]+(r-2);
       float y = (Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r+1) - FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]))/FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]);
       float yerr = (Prof_TEPXClustersPerEvent[pu][d]->GetBinError(r+1))/FitTEPXClustersPerEvent[d][r]->Eval(pumap[pulist[pu]]); 
		
        if(pu > 2) 
	  { 

       NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x, y);
       NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu, 0, yerr);
       cout<< x <<"    "<< y <<"    "<< yerr<<endl;

	  }

       else

         {	  

	    NonLinearity_TEPXClustersPerEvent[d][r]->SetPoint(pu, x-(r-2), y);
            NonLinearity_TEPXClustersPerEvent[d][r]->SetPointError(pu,0, yerr);

	  }


       cout<<"pu is "<<pu<<endl;
       cout<<"PU list name is "<<pulist[pu]<<endl;
	      
	     for(int r=0 ; r<5; r++) {

		     cout<<"Bin Content is "<<Prof_TEPXClustersPerEvent[pu][d]->GetBinContent(r)<<endl;
        
	     }
        

      } 
    }
  }


  
  TCanvas C2("C2");
  C2.cd();
  //draw
  for(int d=0; d<disklist.size(); d++){

    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetNdivisions(10);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
    NonLinearity_TEPXClustersPerEvent[d][0]->GetYaxis()->SetRangeUser(-0.2,0.2);
  
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetNdivisions(12);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetRangeUser(0,220);
    NonLinearity_TEPXClustersPerEvent[d][0]->GetXaxis()->SetTitle("Pileup");

    NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerStyle(20);
    NonLinearity_TEPXClustersPerEvent[d][0]->SetLineColor(1);
    NonLinearity_TEPXClustersPerEvent[d][0]->SetMarkerSize(0);
    if(d<=3){
      NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ")+(d-4));
     }
    else
      {
	NonLinearity_TEPXClustersPerEvent[d][0]->SetTitle(TString("Disk ")+(d-3));
	}
    
    auto legend = new TLegend(0.7,0.3,0.9,0.5);                                      
    NonLinearity_TEPXClustersPerEvent[d][0]->Draw("ape");
    legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][0],TString(" Ring ")+1,"l");

    for(int r=1 ; r<5; r++){

     
       NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerStyle(20);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetLineColor(r+1);
      NonLinearity_TEPXClustersPerEvent[d][r]->SetMarkerSize(0);
      NonLinearity_TEPXClustersPerEvent[d][r]->Draw("pesame");
      legend->AddEntry(NonLinearity_TEPXClustersPerEvent[d][r],TString(" Ring ")+(r+1),"l");

      
      }

    


    TLine *line = new TLine(0,0,220,0);
    line->SetLineColor(kBlack);
    line->Draw("same");

    legend->SetFillColor(0);
    legend->SetLineColor(0);
    legend->SetFillColor(0);
    legend->Draw("same");

    
    C2.Print(outputpath + TString("disk_")+d+".png");
  }    
    TCanvas C3("C3");
    C3.cd();

  

    //drawDisk4Ring1
    NonLinearity_TEPXClustersPerEvent[3][0]->GetYaxis()->SetNdivisions(10);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetYaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetYaxis()->SetTitle("Residual   (Data-Fit)/Fit");
    NonLinearity_TEPXClustersPerEvent[3][0]->GetYaxis()->SetMaxDigits(4);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetYaxis()->SetRangeUser(0,1500);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetYaxis()->SetRangeUser(-0.015,0.015);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetXaxis()->SetNdivisions(12);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetXaxis()->SetLabelSize(0.04);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetXaxis()->SetRangeUser(0,4);
    NonLinearity_TEPXClustersPerEvent[3][0]->GetXaxis()->SetTitle("Pileup");
    NonLinearity_TEPXClustersPerEvent[3][0]->SetMarkerStyle(21);
    NonLinearity_TEPXClustersPerEvent[3][0]->SetMarkerColor(2);
    NonLinearity_TEPXClustersPerEvent[3][0]->SetMarkerSize(1);
    NonLinearity_TEPXClustersPerEvent[3][0]->SetTitle("Disk 4 Ring 1"); 
    TLine *line1 = new TLine(0,0,200,0);
    line1->SetLineColor(kBlack);

    gPad->SetGrid(1,1);
    NonLinearity_TEPXClustersPerEvent[3][0]->Draw("ape");
    line1->Draw("same");
    
    C3.Print(outputpath + "NS5Brane.gif");
    C3.Clear();

  }
