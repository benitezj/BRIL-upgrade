
//long Fill=7314;
//long Run=324841;
//#define MAXL 1.7
//#define MAXRATE 250e3
//#define MAXRATEEMTF 40e6


long Fill=7321;
long Run=324980;
#define MAXL 2.0
#define MAXRATE 300e3
#define MAXRATEEMTF 2e6


TString InstLumiTitle("Offline Inst. Luminosity  [x10^{34} cm^{-2} s^{-1}]");
float L[3000];

void readLumi(TString file){
  
  for(int i=0;i<3000;i++) L[i] = 0.;
  
  ifstream myfile(file.Data());
  if (!myfile.is_open()){
    std::cout << "Unable to open lumi file"<<endl;
    return;
  }
  
  int LSL;
  float Lum;
  std::string line;
  while (std::getline(myfile,line)){
    std::stringstream iss(line);
    iss>>LSL>>Lum;
    if(LSL < 0 && LSL > 3000) continue;
    L[LSL] = Lum/10000; ///convert to 1e34 
  }
  
  cout<<"done reading lumi file : "<<file<<endl;
}


void OMS_rates(TString Type="BMTF"){
  
  //readLumi(TString("OMS-lumi-Run"+Run+".dat"));
  readLumi(TString("brilcalc-lumi-Run")+Run+".dat");
  
  TString RateFile(TString("OMS-")+Type+"-Run"+Run+".dat");
  ifstream bmtffile(RateFile.Data());
  if (!bmtffile.is_open()){
    std::cout << "Unable to open rate file"<<endl;
    return;
  }
  cout<<"reading rates: "<<RateFile<<endl;
  
  
  TGraph GLvsLS;
  TGraph GBvsLS;
  TGraph GBvsL;   
  int c=0;

  TH2F TH2Linearity("TH2Linearity","",26,0.6,1.9,1000,0,300);
  

  std::string bmtfline;
  int LS;
  float B;  
  while (std::getline(bmtffile,bmtfline)){
    std::getline(bmtffile,bmtfline);
    std::stringstream issb(bmtfline);
    issb>>LS>>B;
    
    if(L[LS]==0.) continue;
    //cout<<LS<<" "<<L[LS]<<" "<<B<<endl;
    
    GLvsLS.SetPoint(c,LS,L[LS]);
    GBvsLS.SetPoint(c,LS,B);
    GBvsL.SetPoint(c,L[LS],B);


    TH2Linearity.Fill(L[LS],B/1e3);
    
    c++;
  }

  ///create TGraphErrors for Linearity
  TProfile* TH2Prof=TH2Linearity.ProfileX();
  TGraphErrors Linearity;
  int pcount=0;
  for(int i=0;i<TH2Prof->GetNbinsX();i++){
    //cout<<TH2Prof->GetBinCenter(i+1)<<" "<<TH2Prof->GetBinContent(i+1)<<" "<<TH2Prof->GetBinError(i+1)<<endl;
    if(TH2Prof->GetBinContent(i+1)<=0. || TH2Prof->GetBinError(i+1)<=0. ) continue;
    if(TH2Prof->GetBinError(i+1)/TH2Prof->GetBinContent(i+1)>0.005) continue;//only save precise points
    Linearity.SetPoint(pcount,TH2Prof->GetBinCenter(i+1),TH2Prof->GetBinContent(i+1));
    Linearity.SetPointError(pcount,0,TH2Prof->GetBinError(i+1));
    pcount++;
  }
  TFile Output(Type+"_"+Run+".root","recreate");
  TH2Linearity.SetName("TH2RateVsLumi");
  TH2Linearity.Write();
  Linearity.SetName("RateVsLumi_RateInkHz_LumiInE34");
  Linearity.Write();
  Output.Close();
  
  
  TCanvas C;
  C.Clear();
  GLvsLS.SetTitle(TString("Fill ")+Fill+", Run "+Run);
  GLvsLS.GetYaxis()->SetRangeUser(0,MAXL);
  GLvsLS.GetYaxis()->SetTitle(InstLumiTitle);
  GLvsLS.GetXaxis()->SetTitle("Lumi section");
  GLvsLS.Draw("ap");
  C.Print(TString("OMS_rates_LvsLS-")+Run+".png");
  
  C.Clear();
  GBvsLS.SetTitle(TString("Fill ")+Fill+", Run "+Run);
  GBvsLS.GetYaxis()->SetRangeUser(0,Type.CompareTo("EMTF")==0 ? MAXRATEEMTF : MAXRATE);
  GBvsLS.GetYaxis()->SetTitle(Type+"  total rate (Hz)");
  GBvsLS.GetXaxis()->SetTitle("Lumi section");
  GBvsLS.Draw("ap");
  C.Print(TString("OMS_ratevsLS-")+Type+"-"+Run+".png");



  TF1 FLine("FLine","[0]+[1]*x",0,MAXL);
  FLine.SetLineColor(2);
  GBvsL.Fit(&FLine);
  
  C.Clear();
  GBvsL.SetTitle(TString("Fill ")+Fill+", Run "+Run);
  GBvsL.GetXaxis()->SetRangeUser(0,MAXL);
  GBvsL.GetYaxis()->SetRangeUser(0,Type.CompareTo("EMTF")==0 ? MAXRATEEMTF : MAXRATE);
  GBvsL.GetYaxis()->SetTitle(Type+"  total rate (Hz)");
  GBvsL.GetXaxis()->SetTitle(InstLumiTitle.Data());
  GBvsL.SetMarkerStyle(2);
  
  GBvsL.Draw("ap");

  //FLine.Draw("lsame");

  TLatex text;
  text.SetTextColor(2);
  char txt[100];
  sprintf(txt," y = p_{0} + p_{1} * x");
  text.SetTextSize(.04);
  text.DrawLatexNDC(0.6,0.4,txt);
  sprintf(txt,"p_{0} = %.0f +/- %.0f ",FLine.GetParameter(0),FLine.GetParError(0));
  text.SetTextSize(.035);
  text.DrawLatexNDC(0.6,0.35,txt);
  sprintf(txt,"p_{1} = %.0f +/- %.0f ",FLine.GetParameter(1),FLine.GetParError(1));
  text.SetTextSize(.035);
  text.DrawLatexNDC(0.6,0.3,txt);
  sprintf(txt,"extrapolated rate @ L=7.5e34 :  %.2e Hz",FLine.Eval(7.5));
  text.SetTextSize(.035);
  text.DrawLatexNDC(0.4,0.2,txt);
  C.Print(TString("OMS_ratevsL-")+Type+"-"+Run+".png");




  ///////////
  ///Linearity
  ///////////
  TGraph GBoverLvsL;
  double * X=GBvsL.GetX();
  double * Y=GBvsL.GetY();
  int lin_c=0;
  for(int i=0;i<GBvsL.GetN();i++){
    //cout<<i<<" "<<X[i]<<" "<<Y[i]<<" "<<FLine.Eval(X[i])<<endl;
    float r=(Y[i]-FLine.Eval(X[i]))/FLine.Eval(X[i]);
    if(fabs(r)>0.05) continue;
    GBoverLvsL.SetPoint(lin_c++,X[i],r);
  }

  TF1 FZero("FZero","0",0,MAXL);
  FZero.SetLineColor(1);
  FZero.SetLineStyle(2);
  TF1 FLinearity("FLinearity","[0]+[1]*x",0,MAXL);
  GBoverLvsL.Fit(&FLinearity);

  
  C.Clear();
  GBoverLvsL.SetTitle(TString("Fill ")+Fill+", Run "+Run);
  GBoverLvsL.GetYaxis()->SetTitleOffset(1.2);
  GBoverLvsL.GetYaxis()->SetRangeUser(-0.02,0.02);
  GBoverLvsL.GetYaxis()->SetTitle(TString("( ")+Type+" - Fit ) / Fit ");
  GBoverLvsL.GetXaxis()->SetTitle(InstLumiTitle);
  GBoverLvsL.Draw("ap");
  FZero.Draw("lsame");
  //FLinearity.Draw("lsame");
  sprintf(txt,"slope = %.3f +/- %.3f %%",100*FLinearity.GetParameter(1),100*FLinearity.GetParError(1));
  text.SetTextSize(.035);
  text.DrawLatexNDC(0.3,0.2,txt);
  C.Print(TString("OMS_ratiovsL-")+Type+"-"+Run+".png");
  
  
}

