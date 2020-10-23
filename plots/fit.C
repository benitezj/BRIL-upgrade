void fit() {
  
TFile * f = new TFile("/home/ashish/Desktop/15thOct2020/TEPX/samples_15thOct2020/2023D42PU0p5.root");

TCanvas * C = new TCanvas("2xCoincidences","");

TH2F * histo = NULL; 

histo = (TH2F*)f->Get("BRIL_IT_Analysis/TEPX/2xCoincidences/m_dr_sametrack_side2_Disk4_Ring1");

 if (histo==NULL){
    return;
  }

TF1 DG("DG", "[0]*exp(-0.5*(x-[1])**2/[2]**2) + [3]*exp(-0.5*(x-[4])**2/[5]**2)", -0.15, 0.15);

DG.SetParLimits(0,0,10000000);
DG.SetParLimits(1,0.0,0.15);
DG.SetParLimits(2,0.001,0.02);
DG.SetParLimits(3,0,10000000);
DG.SetParLimits(4,-0.15,0.15);
DG.SetParLimits(5,0.02,1);

histo->Fit(&DG);

cout << DG.GetParameter(1) << " " <<endl;
cout<< DG.GetParameter(2) << endl;
gStyle -> SetOptStat(111111111);

histo->SetTitle("Side 2 Disk 4 Ring 1 fit");
histo->GetXaxis()->SetTitle("r2-r1");
histo->GetYaxis()->SetTitle("counts");

histo->SetLineColor(1);
DG.SetLineColor(8);

histo->Draw("same");
DG.Draw("same");

auto legend = new TLegend(0.7,0.7,0.9,0.9);

legend->AddEntry(histo, "PU 200 true 2x in phi","l");
legend->AddEntry(&DG, "PU 200 true 2x in phi fit","l");
legend->Draw();

legend->SetFillColor(0);
legend->SetLineColor(0);
legend->SetFillColor(0);

C->Print("/home/ashish/fit.gif");


}





