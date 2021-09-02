void linearity_2D(int option){

  TCanvas *c1 = new TCanvas();
TCanvas *c2 = new TCanvas();
  for (int pu = 0; pu < pulist.size(); pu++) {
    for (int d = 0; d < disklist.size(); d++){
      if (option == 1){

	c1->cd();
	c1->Clear();
	Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, pu < 4 ? 350 : 3500);
	Histogram2D[pu][d]->Draw("colz");
	char *hist2Dname = new char[10];
	sprintf(hist2Dname,"histo2D_pu%d_d%d.gif", pu, d);
	cout<<"=========================="<<hist2Dname<<endl;
	c1->Print(outputpath1 + "clusters 2D Histograms/" + hist2Dname);

        c2->cd();
	c2->Clear();
	Histogram12D[pu][d]->GetYaxis()->SetRangeUser(0, pu < 4 ? 1000 : 5000);
	Histogram12D[pu][d]->Draw("colz");
	char *hist2Dname1 = new char[10];
	sprintf(hist2Dname1,"histo2D_pu%d_d%d.gif", pu, d);
	cout<<"=========================="<<hist2Dname1<<endl;
	c2->Print(outputpath1 + "Hits/" + hist2Dname1);
      	
      }
      
      if (option == 2){

	c1->cd();
	c1->Clear();
	Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, pu < 4 ? 100 : 1000);
	Histogram2D[pu][d]->Draw("colz");
	char *hist2Dname = new char[10];
	sprintf(hist2Dname,"histos2D_pu%d_d%d.gif", pu, d);
	cout<<"=========================="<<hist2Dname<<endl;
	c1->Print(outputpath2 + "2xCoincidences 2D Histograms/" + hist2Dname);

	
      }
      
      if (option == 3){
	
	c1->cd();
	c1->Clear();
	Histogram2D[pu][d]->GetYaxis()->SetRangeUser(0, pu < 4 ? 20 : 100);
	Histogram2D[pu][d]->Draw("colz");
	char *hist2Dname = new char[10];
	sprintf(hist2Dname,"histoss2D_pu%d_d%d.gif", pu, d);
	cout<<"=========================="<<hist2Dname<<endl;
	c1->Print(outputpath3 + "3xCoincidences 2D Histograms/" + hist2Dname);

	
      }
    }
  }
  
}
