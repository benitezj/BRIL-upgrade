void fit1() {
  
TFile * f = new TFile("/home/ashish/Desktop/20thOct2020/TEPX/samples_20thOct2020/2023D42PU0p5.root");

TCanvas * C = new TCanvas("2xCoincidences","");

TH2F * histo = NULL; 

histo = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/2xCoincidences/m_dphi_sametrack_side2_Disk4_Ring5");

 if (histo==NULL){
    return;
  }

histo->SetTitle("Side 2 Disk 4 Ring 5 fit");
histo->GetXaxis()->SetTitle("phi2-phi1");
histo->GetYaxis()->SetTitle("counts");
histo->SetLineColor(1);
histo->GetXaxis()->SetRangeUser(-0.01, 0.01);
gStyle -> SetOptStat(111111111);

auto legend = new TLegend(0.2,0.6,0.4,0.9);
legend->SetFillColor(0);
legend->SetLineColor(0);
legend->SetFillColor(0);

TF1 DG("DG", "[0]*exp(-0.5*(x-[1])**2/[2]**2)", -0.01, 0.01);
DG.SetLineColor(8);
DG.SetParLimits(0,0,10000000);
DG.FixParameter(1,0);
DG.SetParLimits(2,0.0001, 0.02);
histo->Fit(&DG);

cout << DG.GetParameter(1) << " " <<endl;
cout<< DG.GetParameter(2) << endl;

C->Clear();

histo->Draw();
DG.Draw("lsame");
legend->AddEntry(histo, "PU 0.5 true 2x in phi","l");
legend->AddEntry(&DG, "PU 0.5 true 2x in phi fit","l");
legend->Draw();
C->Print("/home/ashish/fit1.gif");

}





