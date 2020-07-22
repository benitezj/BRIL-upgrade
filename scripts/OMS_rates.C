long Fill=7314;
long Run=324841;
#define MAXL 1.7
#define MAXRATE 250e3
//#define MAXRATE 40e6

TString InstLumiTitle("Inst. Luminosity (x10^{34} cm^{-2} s^{-1})");


void OMS_rates(TString Type="BMTF"){

  ifstream lumifile(TString("OMS-lumi-Fill")+Fill+"-Run"+Run+".dat");
  if (!lumifile.is_open()){
    std::cout << "Unable to open lumi file"<<endl;
    return;
  }

  ifstream bmtffile(TString("OMS-")+Type+"-Fill"+Fill+"-Run"+Run+".dat");
  if (!bmtffile.is_open()){
    std::cout << "Unable to open rate file"<<endl;
    return;
  }


  
  TGraph GLvsLS;
  TGraph GBvsLS;
  TGraph GBvsL;
  
   
  std::string lumiline;
  int c=0;
  int LSL;
  float L;

  std::string bmtfline;
  int LSB;
  float B;
  
  while (std::getline(lumifile,lumiline)){
    std::stringstream iss(lumiline);
    iss>>LSL>>L;


    std::getline(bmtffile,bmtfline);
    std::stringstream issb(bmtfline);
    issb>>LSB>>B;
    
    if(LSB!=LSL){
      cout<<LSB<<"!"<<LSL<<endl;
      break;
    }
    
    //cout<<LS<<" "<<L<<endl;
    GLvsLS.SetPoint(c,LSL,L);
    GBvsLS.SetPoint(c,LSL,B);
    GBvsL.SetPoint(c,L,B);
    c++;
  }


  TCanvas C;
  C.Clear();
  GLvsLS.GetYaxis()->SetRangeUser(0,MAXL);
  GLvsLS.GetYaxis()->SetTitle(InstLumiTitle);
  GLvsLS.GetXaxis()->SetTitle("Lumi section");
  GLvsLS.Draw("ap");
  C.Print("OMS_rates_LvsLS.png");

  C.Clear();
  GBvsLS.GetYaxis()->SetRangeUser(0,MAXRATE);
  GBvsLS.GetYaxis()->SetTitle(Type+"  total rate (Hz)");
  GBvsLS.GetXaxis()->SetTitle("Lumi section");
  GBvsLS.Draw("ap");
  C.Print("OMS_ratevsLS.png");



  TF1 FLine("FLine","[0]+[1]*x",0,MAXL);
  FLine.SetLineColor(2);
  GBvsL.Fit(&FLine);
  
  C.Clear();
  GBvsL.GetXaxis()->SetRangeUser(0,MAXL);
  GBvsL.GetYaxis()->SetRangeUser(0,MAXRATE);
  GBvsL.GetYaxis()->SetTitle(Type+"  total rate (Hz)");
  GBvsL.GetXaxis()->SetTitle("Inst. Luminosity (x10^{34} cm^{-2} s^{-1})");
  GBvsL.SetTitle(TString("Fill ")+Fill+", Run "+Run);
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
  sprintf(txt,"extrapolated rate @ L=7.5e34 (HL-LHC):  %.2e Hz",FLine.Eval(7.5));
  text.SetTextSize(.035);
  text.DrawLatexNDC(0.3,0.2,txt);
  C.Print("OMS_ratevsL-"+Type+".png");






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
  GBoverLvsL.GetYaxis()->SetTitleOffset(1.2);
  GBoverLvsL.GetYaxis()->SetRangeUser(-0.02,0.02);
  GBoverLvsL.GetYaxis()->SetTitle(TString("( ")+Type+" - Fit ) / Fit ");
  GBoverLvsL.GetXaxis()->SetTitle(InstLumiTitle);
  GBoverLvsL.Draw("ap");
  FZero.Draw("lsame");
  //FLinearity.Draw("lsame");
  sprintf(txt,"slope = %.2f %% / 1e34 cm^{-2} s^{-1}",100*FLinearity.GetParameter(1));
  text.SetTextSize(.035);
  text.DrawLatexNDC(0.3,0.2,txt);
  C.Print("OMS_ratiovsL-"+Type+".png");




  
  
}

