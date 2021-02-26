
const int NSENSOR = 4*5*8*2; // Total Number detector sensors (FBCM example)
const float NORBIT = 11223*1; // Number of orbits in integration period: frev_LHC * 1s
const float MAXN = NSENSOR*NORBIT; 
float ZEROPROB = 0.1; //prob of un-triggered sensor 

float NAVG(){
  return MAXN*ZEROPROB;//number of sensors in zero bin for integration period
}
  
double lambda(int nzero){
  if(nzero>MAXN) return 0;
  if(nzero<=0) return 0;
  return log(MAXN/nzero);
}

int nzero(double lambda){
  if(lambda<=0) return 0;
  return MAXN*exp(-lambda);
}

float pdf_n(int nzero){
  if(nzero>MAXN) return 0;
  if(nzero<=0) return 0;  
  return exp(- 0.5 * pow(nzero - NAVG(),2) / NAVG() ); ///assum number of zeros has sqrt(n) standard deviation
}

float pdf_lambda(float lambda){
  if(lambda<=0) return 0;

  //this formula is derived follwoing G. Cowan
  // if a(x) is invertible map , the PDF(a) = PDF(x) |dx/da|
  // here x : n, and a : lambda = log(M/n)
  // PDF(x) is Gaussian with mean=NAVG() and Variance=NAVG()

  return exp(-lambda) * exp( -0.5 * pow( MAXN*exp(-lambda) - NAVG(), 2) / NAVG());
}

float lambda_mu(){
  if(ZEROPROB<=0 || ZEROPROB>=1)return 0.;
  return (log(1/ZEROPROB) - 1/NAVG());
}

float lambda_sigma(){//this is the relative uncertainty already, do not divide further by lambda
  if(ZEROPROB<=0 || ZEROPROB>=1)return 0.;
  return 1./(sqrt(NAVG()) * (log(1./ZEROPROB) - 1./NAVG()));
}

float lambda_sigma_derivative(){//this is the relative uncertainty already, do not divide further by lambda
  if(ZEROPROB<=0 || ZEROPROB>=1)return 0.;
  return 1./(sqrt(NAVG()) * log(1./ZEROPROB));
}

float lambda_sigma_Mohammad(){//this is the relative uncertainty already, do not divide further by lambda
  if(ZEROPROB<=0 || ZEROPROB>=1)return 0.;
  return sqrt(1.0 - ZEROPROB) / ( sqrt(NAVG()) * log(1./ZEROPROB) );
}

void ZeroCountingStats(){

  ///make a graph of PDF(n)
  int n_min = NAVG() - 5*sqrt(NAVG());//only consider +/-5 sigma around the mean
  int n_max = NAVG() + 5*sqrt(NAVG());//only consider +/-5 sigma around the mean
  float PDFAvg_n=pdf_n(NAVG());
  TGraph PDF_n;
  for(int i=0;i<(n_max-n_min);i++)
    PDF_n.SetPoint(i,n_min+i,pdf_n(n_min+i)/PDFAvg_n);

  TCanvas Canvas;
  Canvas.Clear();
  PDF_n.GetYaxis()->SetTitle("PDF(n_{0})");
  PDF_n.GetXaxis()->SetTitle("number of zero counts (n_{0})");
  PDF_n.Draw("alp");
  Canvas.Print("PDF_n.png");


  
  ///make a graph of PDF(lambda)
  float PDFAvg_l=pdf_lambda(lambda(NAVG()));
  TGraphErrors PDF_l;
  for(int i=0;i<100;i++){
    double l = lambda(n_min + (n_max-n_min)*i/100);
    float pdf=pdf_lambda(l)/PDFAvg_l;
    PDF_l.SetPoint(i,l,pdf);
    PDF_l.SetPointError(i,0,pdf/1000.);
  }

  float l_min=lambda(n_max);
  float l_max=lambda(n_min);
  cout<<l_min<<" "<<l_max<<endl;
  TF1 FGauss("FGauss","[0]*exp(-0.5*(x-[1])^2/[2]^2)",l_min,l_max);
  FGauss.SetLineColor(2);
  FGauss.SetParameter(0,1);
  FGauss.SetParameter(1,(l_min+l_max)/2.);
  FGauss.SetParLimits(1,l_min,l_max);
  FGauss.SetParameter(2,(l_max-l_min)/4.);
  FGauss.SetParLimits(2,0,(l_max-l_min));
  PDF_l.Fit(&FGauss);
  Canvas.Clear();
  PDF_l.SetMarkerStyle(8);
  PDF_l.GetXaxis()->SetTitle("#lambda");
  PDF_l.GetYaxis()->SetTitle("PDF(#lambda)");
  PDF_l.Draw("alp");
  FGauss.Draw("lsame");
  Canvas.Print("PDF_lambda.png");



  ////Now lets scan the hit probability p to map sigma_lambda vs sigma_n
  TGraph GLambda;
  TGraph GLambdaSigma;
  TGraph GLambda_analytical;
  TGraph GLambdaSigma_analytical;
  TGraph GLambdaSigma_derivative;
  TGraph GLambdaSigma_Mohammad;

  int NSTEP=100;//nsteps scanning probability
  int ngood=0;
  for(int i=0;i<NSTEP;i++){
    ZEROPROB = 0.005+(0.5-0.005)*((float)i/NSTEP);
    
    int n_min = NAVG() - 5*sqrt(NAVG());//only consider +/-5 sigma around the mean
    int n_max = NAVG() + 5*sqrt(NAVG());//only consider +/-5 sigma around the mean
    float l_min=lambda(n_max);
    float l_max=lambda(n_min);
    float PDFAvg_l=pdf_lambda(lambda(NAVG()));
    TGraphErrors PDF_l;
    for(int i=0;i<1000;i++){
      double l=lambda(n_min+(n_max-n_min)*(float)i/1000);
      double pdf=pdf_lambda(l)/PDFAvg_l;
      PDF_l.SetPoint(i,l,pdf);
      PDF_l.SetPointError(i,0,pdf/100.);//fake error to run fit
    }
    FGauss.SetParameter(0,1);
    FGauss.SetParameter(1,(l_min+l_max)/2.);
    FGauss.SetParameter(2,(l_max-l_min)/4.);
    FGauss.SetParLimits(1,l_min,l_max);
    FGauss.SetParLimits(2,0,10*(l_max-l_min));
    PDF_l.Fit(&FGauss,"Q","N",l_min,l_max);

    if(FGauss.GetChisquare()/FGauss.GetNDF()>100) continue;

    ///Numerical Method
    GLambda.SetPoint(ngood,ZEROPROB,FGauss.GetParameter(1));
    GLambdaSigma.SetPoint(ngood,ZEROPROB,100*FGauss.GetParameter(2)/FGauss.GetParameter(1));

    ///analytical PDF transform from Random variable theory:  PDF(a) = PDF(x) * |dx/da|
    GLambda_analytical.SetPoint(ngood,ZEROPROB,lambda_mu());
    GLambdaSigma_analytical.SetPoint(ngood,ZEROPROB,100*lambda_sigma());

    //simple derivative error propagation
    GLambdaSigma_derivative.SetPoint(ngood,ZEROPROB,100*lambda_sigma_derivative());

    //Mohammad analysis
    GLambdaSigma_Mohammad.SetPoint(ngood,ZEROPROB,100*lambda_sigma_Mohammad());

    ngood++;

  }
  
  ///Analytical graphs for mean lambda and sigma_lambda

  
  Canvas.Clear();
  GLambda.SetMarkerStyle(8);
  GLambda.GetXaxis()->SetTitle("zero count probability");
  GLambda.GetYaxis()->SetTitle("#lambda");
  GLambda.Draw("alp");
  GLambda_analytical.SetLineColor(2);
  GLambda_analytical.Draw("lsame");
  Canvas.SetLogx(1);
  Canvas.Print("Lambda_vs_NAVG.png");

  Canvas.Clear();
  GLambdaSigma.SetMarkerStyle(8);
  GLambdaSigma.GetXaxis()->SetTitle("zero count probability (p_{0})");
  GLambdaSigma.GetYaxis()->SetTitle("uncertainty on #lambda (%)");
  GLambdaSigma.Draw("alp");
  GLambdaSigma_derivative.SetLineColor(2);
  GLambdaSigma_derivative.Draw("lsame");
  GLambdaSigma_Mohammad.SetLineColor(4);
  GLambdaSigma_Mohammad.Draw("lsame");
  //GLambdaSigma_analytical.SetLineColor(2);
  //GLambdaSigma_analytical.Draw("lsame");
  Canvas.Print("LambdaSigma_vs_NAVG.png");

}
