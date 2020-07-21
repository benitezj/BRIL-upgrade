long Fill=7314;
long Run=324841;
#define MAXL 1.7
#define MAXBMTF 250e3



void OMS_rates(){

  ifstream lumifile(TString("OMS-lumi-Fill")+Fill+"-Run"+Run+".dat");
  if (!lumifile.is_open()){
    std::cout << "Unable to open lumi"<<endl;
    return;
  }

  ifstream bmtffile(TString("OMS-BMTF-Fill")+Fill+"-Run"+Run+".dat");
  if (!bmtffile.is_open()){
    std::cout << "Unable to open bmtf"<<endl;
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
  GLvsLS.GetYaxis()->SetTitle("Inst. Luminosity (x10^{34} cm^{-2} s^{-1})");
  GLvsLS.GetXaxis()->SetTitle("Lumi section");
  GLvsLS.Draw("ap");
  C.Print("OMS_rates_LvsLS.png");

  C.Clear();
  GBvsLS.GetYaxis()->SetRangeUser(0,MAXBMTF);
  GBvsLS.GetYaxis()->SetTitle("BMTF rate (Hz)");
  GBvsLS.GetXaxis()->SetTitle("Lumi section");
  GBvsLS.Draw("ap");
  C.Print("OMS_rates_BMTFvsLS.png");


  TF1 FLine("FLine","[0]+[1]*x",0,MAXL);
  FLine.SetLineColor(2);
  GBvsL.SetMarkerStyle(2);
  //GBvsL.SetMarkerSize(1.2);
  
  C.Clear();
  GBvsL.GetXaxis()->SetRangeUser(0,MAXL);
  GBvsL.GetYaxis()->SetRangeUser(0,MAXBMTF);
  GBvsL.GetYaxis()->SetTitle("BMTF rate (Hz)");
  GBvsL.GetXaxis()->SetTitle("Inst. Luminosity (x10^{34} cm^{-2} s^{-1})");

  GBvsL.Fit(&FLine);
  GBvsL.SetTitle(TString("Fill ")+Fill+", Run "+Run);
  GBvsL.Draw("ap");
  FLine.Draw("lsame");
  GBvsL.Draw("ap");

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
  C.Print("OMS_rates_BMTFvsL.png");


  
}

