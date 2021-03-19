void totalcount2x1(){
  
  //TFile *f = new TFile("./TDRplots_2xinphi.root","RECREATE");
  //TFile *f = new TFile("./TDRplots_2xinR.root","RECREATE");
  TFile *f = new TFile("./TDRplots2x_phi_R.root","RECREATE");

  f->cd();
  gDirectory->cd();
  f->ls();
  
  TString inpath = "/home/ashish/Desktop/2xresults_all/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/2xcombined_3dphi_2dr/TEPX/samples_17Feb2020/";
  //TString inpath = "/home/ashish/Desktop/26thOct2020_28thOct2020presentation_drdphicuts_2sigma/TEPX/samples_17Feb2020/";
  gROOT->ProcessLine(".x /home/ashish/rootlogon.C");
  
  //string containing names of input sample files
  std::vector<std::string> pulist = {//"2023D42noPU" , 
    "2023D42PU0p5", "2023D42PU1", "2023D42PU1p5", "2023D42PU2", "2023D42PU10", "2023D42PU30", "2023D42PU50", "2023D42PU100", "2023D42PU140", "2023D42PU200" };
  std::map<std::string, float> pumap = {//{ "2023D42noPU", 0 },
    { "2023D42PU0p5", 0.5 }, { "2023D42PU1", 1 }, { "2023D42PU1p5", 1.5 }, { "2023D42PU2", 2 }, { "2023D42PU10", 10 }, { "2023D42PU30", 30 }, { "2023D42PU50", 50 }, { "2023D42PU100", 100 }, { "2023D42PU140", 140 }, { "2023D42PU200", 200 } };
  
  std::vector<std::string> disklist = { "1", "2", "3", "4" };
  std::vector<std::string> sidelist = { "1", "2"};
  
  //create the profiles to be filled below.
  TGraphErrors* TEPXClustersPerEvent; //number of clusters vs pu
  TGraphErrors* TEPXClustersPerEvent1[20][20][20]; 
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
  TGraphErrors* TEPXClustersPerEvent_D4R1;


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


  TH2F* Histogram2D[20][20][20];
  
  //Non-linearity graphs
  TGraphErrors* NonLinearity_TEPXClustersPerEvent; //number of clusters vs pu 
  NonLinearity_TEPXClustersPerEvent = new TGraphErrors();
  
  for (int pu = 0; pu < pulist.size(); pu++) {
    for (int s = 0; s < sidelist.size(); s++){
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
          TEPXClustersPerEvent1[s][d][r] = new TGraphErrors();


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
    }
    
    
    //read the histograms
    TProfile* Prof_TEPXClustersPerEvent[20][20][20]; //array pu,disk
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

      
      
      
      for (int s = 0; s < sidelist.size(); s++) {
	for (int d = 0; d < disklist.size(); d++) {
	  
	  //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_Inphi_side";
	  //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidences_InR_side";
	  //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencess_InR_side";        
	  //TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_InR_side";
	  TString histoname = "BRIL_IT_Analysis/TEPX/2xCoincidences/Numberof2xCoincidencestotal_side";
	  
	  TH2F* H = (TH2F*)F.Get(histoname + sidelist[s].c_str() + "_Disk" + disklist[d].c_str());
	  Histogram2D[s][pu][d] = (TH2F*)H->Clone(TString(H->GetName()));
	  Prof_TEPXClustersPerEvent[s][pu][d] = (TProfile*)H->ProfileX()->Clone(TString(H->GetName()) + "Profile");
	  
	  for (int r = 0; r < 5; r++) {
	    
	    
	    float count = Prof_TEPXClustersPerEvent[s][pu][d]->GetBinContent(r + 1);
	    float counterror = Prof_TEPXClustersPerEvent[s][pu][d]->GetBinError(r + 1);
	    
	    TEPXClustersPerEvent1[s][d][r]->SetPoint(pu, pumap[pulist[pu]], count);
	    TEPXClustersPerEvent1[s][d][r]->SetPointError(pu, 0, counterror);


	    
	   
if (d == 0 && r == 0) {

totalcount_disk1combinedring1+=count;
	   totalcounterror_disk1combinedring1+= counterror * counterror;

}


if (d == 0 && r == 1) {

totalcount_disk1combinedring2+=count;
	   totalcounterror_disk1combinedring2+= counterror * counterror;

}



if (d == 0 && r == 2) {


totalcount_disk1combinedring3+=count;
	   totalcounterror_disk1combinedring3+= counterror * counterror;
}


if (d == 0 && r == 3) {

totalcount_disk1combinedring4+=count;
	   totalcounterror_disk1combinedring4+= counterror * counterror;

}


if (d == 0 && r == 4) {

totalcount_disk1combinedring5+=count;
	   totalcounterror_disk1combinedring5+= counterror * counterror;

}


 if(d == 1 && r == 0) {


totalcount_disk2combinedring1+=count;
	   totalcounterror_disk2combinedring1+= counterror * counterror;
}


if(d == 1 && r == 1) {

totalcount_disk2combinedring2+=count;
	   totalcounterror_disk2combinedring2+= counterror * counterror;

}


if(d == 1 && r == 2) {

totalcount_disk2combinedring3+=count;
	   totalcounterror_disk2combinedring3+= counterror * counterror;
}


if(d == 1 && r == 3) {

totalcount_disk2combinedring4+=count;
	   totalcounterror_disk2combinedring4+= counterror * counterror;
}


if(d == 1 && r == 4) {

totalcount_disk2combinedring5+=count;
	   totalcounterror_disk2combinedring5+= counterror * counterror;
}



 if(d == 2 && r == 0) {

totalcount_disk3combinedring1+=count;
	   totalcounterror_disk3combinedring1+= counterror * counterror;

}


if(d == 2 && r == 1) {

totalcount_disk3combinedring2+=count;
	   totalcounterror_disk3combinedring2+= counterror * counterror;


}

if(d == 2 && r == 2) {

totalcount_disk3combinedring3+=count;
	   totalcounterror_disk3combinedring3+= counterror * counterror;


}


if(d == 2 && r == 3) {

totalcount_disk3combinedring4+=count;
	   totalcounterror_disk3combinedring4+= counterror * counterror;


}


if(d == 2 && r == 4) {

totalcount_disk3combinedring5+=count;
	   totalcounterror_disk3combinedring5+= counterror * counterror;


}


if(d == 2 && r == 0) {

totalcount_disk4combinedring1+=count;
	   totalcounterror_disk4combinedring1+= counterror * counterror;

}


if(d == 3 && r == 1) {

totalcount_disk4combinedring2+=count;
	   totalcounterror_disk4combinedring2+= counterror * counterror;

}



if(d == 3 && r == 2) {

totalcount_disk4combinedring3+=count;
	   totalcounterror_disk4combinedring3+= counterror * counterror;

}



if(d == 3 && r == 3) {

totalcount_disk4combinedring4+=count;
	   totalcounterror_disk4combinedring4+= counterror * counterror;

}


if(d == 3 && r == 4) {

totalcount_disk4combinedring5+=count;
	   totalcounterror_disk4combinedring5+= counterror * counterror;

}











 
	    if(!(d == 0 && r == 0)){
	      
	      totalcount+=count;
	      totalcounterror+= counterror * counterror;

            }	
	    
            if((d == 0) && r == 0){
	      
	      totalcount_D4R1+=count;
	      totalcounterror_D4R1 = counterror * counterror;
	      
	    }    
	    
	    
	    
	    if (d == 0 && s == 0) {
	    
	      totalcount_disk1+=count;
	      totalcounterror_disk1+= counterror * counterror;
	      
	    }


          if (d == 0 && s == 1) {
	    
	      totalcount_disk5+=count;
	      totalcounterror_disk5+= counterror * counterror;
	      
	    }

           if(d == 0) {

	     totalcount_disk1combined+=count;
	      totalcounterror_disk1combined+= counterror * counterror;
	      

}

	    if (d == 1 && s == 0) {
	      
	      totalcount_disk2+=count;
	      totalcounterror_disk2+= counterror * counterror;
	      
	    }


            if (d == 1 && s == 1) {
	      
	      totalcount_disk6+=count;
	      totalcounterror_disk6+= counterror * counterror;
	      
	    }

            if(d == 1) {

              totalcount_disk2combined+=count;
	      totalcounterror_disk2combined+= counterror * counterror;
	      

}	    


	    if (d == 2 && s == 0) {
	      
	      totalcount_disk3+=count;
	      totalcounterror_disk3+= counterror * counterror;
	      
	    }
	    
           if (d == 2 && s == 1) {
	      
	      totalcount_disk7+=count;
	      totalcounterror_disk7+= counterror * counterror;
	      
	    }
	    
       if(d == 2) {

              totalcount_disk3combined+=count;
	      totalcounterror_disk3combined+= counterror * counterror;

}


	    if (d == 3 && s == 0) {
	      
	      totalcount_disk4+=count;
	     totalcounterror_disk4+= counterror * counterror;
	     
	    }

	 if (d == 3 && s == 1) {
	      
	      totalcount_disk8+=count;
	     totalcounterror_disk8+= counterror * counterror;
	     
	    }
          if (d == 3) {

             totalcount_disk4combined+=count;
	     totalcounterror_disk4combined+= counterror * counterror;

}

	    
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
  TEPXClustersPerEvent->SetName(TString("2xCoincidences_TEPX"));  
  f->WriteTObject(TEPXClustersPerEvent);
  
  
  TEPXClustersPerEvent_D4R1->SetMarkerSize(2);
  TEPXClustersPerEvent_D4R1->SetMarkerColor(2);
  TEPXClustersPerEvent_D4R1->SetName(TString("2xCoincidences_D4R1"));  
  f->WriteTObject(TEPXClustersPerEvent_D4R1);
  
  TEPXClustersPerEvent_disk1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1->SetName(TString("2xCoincidences_disk-4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1);
  
  TEPXClustersPerEvent_disk2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2->SetName(TString("2xCoincidences_disk-3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2);
  
  
  TEPXClustersPerEvent_disk3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3->SetName(TString("2xCoincidences_disk-2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3);
  
  TEPXClustersPerEvent_disk4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4->SetName(TString("2xCoincidences_disk-1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4);


  TEPXClustersPerEvent_disk5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk5->SetName(TString("2xCoincidences_disk1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk5);
  
  TEPXClustersPerEvent_disk6->SetMarkerSize(2);
  TEPXClustersPerEvent_disk6->SetMarkerColor(2);
  TEPXClustersPerEvent_disk6->SetName(TString("2xCoincidences_disk2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk6);
  
  
  TEPXClustersPerEvent_disk7->SetMarkerSize(2);
  TEPXClustersPerEvent_disk7->SetMarkerColor(2);
  TEPXClustersPerEvent_disk7->SetName(TString("2xCoincidences_disk3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk7);
  
  TEPXClustersPerEvent_disk8->SetMarkerSize(2);
  TEPXClustersPerEvent_disk8->SetMarkerColor(2);
  TEPXClustersPerEvent_disk8->SetName(TString("2xCoincidences_disk4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk8);


  TEPXClustersPerEvent_disk1combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combined->SetName(TString("2xCoincidences_disk1combined"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combined);
  
  TEPXClustersPerEvent_disk2combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combined->SetName(TString("2xCoincidences_disk2combined"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combined);
  
  
  TEPXClustersPerEvent_disk3combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combined->SetName(TString("2xCoincidences_disk3combined"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combined);
  
  TEPXClustersPerEvent_disk4combined->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combined->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combined->SetName(TString("2xCoincidences_disk4combined"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combined);



  TEPXClustersPerEvent_disk1combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring1->SetName(TString("2xCoincidences_disk1combinedring1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring1);
  
  TEPXClustersPerEvent_disk1combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring2->SetName(TString("2xCoincidences_disk1combinedring2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring2);
  
  TEPXClustersPerEvent_disk1combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring3->SetName(TString("2xCoincidences_disk1combinedring3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring3);
  
  TEPXClustersPerEvent_disk1combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring4->SetName(TString("2xCoincidences_disk1combinedring4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring4);

  TEPXClustersPerEvent_disk1combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk1combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk1combinedring5->SetName(TString("2xCoincidences_disk1combinedring5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk1combinedring5);




TEPXClustersPerEvent_disk2combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring1->SetName(TString("2xCoincidences_disk2combinedring1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring1);
  
  TEPXClustersPerEvent_disk2combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring2->SetName(TString("2xCoincidences_disk2combinedring2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring2);
  
  TEPXClustersPerEvent_disk2combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring3->SetName(TString("2xCoincidences_disk2combinedring3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring3);
  
  TEPXClustersPerEvent_disk2combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring4->SetName(TString("2xCoincidences_disk2combinedring4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring4);

TEPXClustersPerEvent_disk2combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk2combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk2combinedring5->SetName(TString("2xCoincidences_disk2combinedring5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk2combinedring5);



TEPXClustersPerEvent_disk3combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring1->SetName(TString("2xCoincidences_disk3combinedring1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring1);
  
  TEPXClustersPerEvent_disk3combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring2->SetName(TString("2xCoincidences_disk3combinedring2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring2);
  
  TEPXClustersPerEvent_disk3combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring3->SetName(TString("2xCoincidences_disk3combinedring3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring3);
  
  TEPXClustersPerEvent_disk3combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring4->SetName(TString("2xCoincidences_disk3combinedring4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring4);

TEPXClustersPerEvent_disk3combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk3combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk3combinedring5->SetName(TString("2xCoincidences_disk3combinedring5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk3combinedring5);




TEPXClustersPerEvent_disk4combinedring1->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring1->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring1->SetName(TString("2xCoincidences_disk4combinedring1"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring1);
  
  TEPXClustersPerEvent_disk4combinedring2->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring2->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring2->SetName(TString("2xCoincidences_disk4combinedring2"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring2);
  
  TEPXClustersPerEvent_disk4combinedring3->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring3->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring3->SetName(TString("2xCoincidences_disk4combinedring3"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring3);
  
  TEPXClustersPerEvent_disk4combinedring4->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring4->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring4->SetName(TString("2xCoincidences_disk4combinedring4"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring4);

TEPXClustersPerEvent_disk4combinedring5->SetMarkerSize(2);
  TEPXClustersPerEvent_disk4combinedring5->SetMarkerColor(2);
  TEPXClustersPerEvent_disk4combinedring5->SetName(TString("2xCoincidences_disk4combinedring5"));  
  f->WriteTObject(TEPXClustersPerEvent_disk4combinedring5);



  
  for (int s = 0; s < sidelist.size(); s++) {
    for (int d = 0; d < disklist.size(); d++) {
      for (int r = 0; r < 5; r++){
	
	TEPXClustersPerEvent1[s][d][r]->SetMarkerSize(2);
	TEPXClustersPerEvent1[s][d][r]->SetMarkerColor(2);
	TEPXClustersPerEvent1[s][d][r]->SetName(TString("2xCoincidences") + "S" + (s+1) + "D" + (d+1) + "R" + (r+1));
	f->WriteTObject(TEPXClustersPerEvent1[s][d][r]);
	
	
      }
    }
  }
  
}




