
void vdm_stat_presicion(){

/* defining arrays and variables */
int x[25];/*array to store points on the x axis*/
float f[25];/* array to store points with normal distribution*/
int mean_rate=5.67e+04;/*mean rate */
int mean_value=0;/*center of the normal dsitribution*/
float st_div= 27.84;/*standar diviation*/


/*generating points in x axis*/
   for(int in=0;in<25;in++){
  
      x[in]=in-12;
 
      }

/*generating points for normal distribution*/

   for(int i=0;i<25;i++){
   
       f[i]= mean_rate*exp(-0.5*(pow((x[i]),2))/pow(st_div,2));
   
       }

/*Histogram fill */
    auto h=new TH1F("count_rate","Van der Meer Scan;Rate",25, -12.5, 12.5); 

    for (int l=0;l<25;l++){
        h->SetBinContent(l+1,f[l]);
        h->SetBinError(l+1,sqrt(f[l]));
        }
        
/*Fitting normal distribution to Histogram*/
TF1  F("F","[0]*exp(-0.5*(x-[1])**2/[2]**2)", -12.5,12.5 );
F.SetLineColor(8);
F.SetParLimits(0,0, 1000000);
F.FixParameter(1,h->GetMean());
F.SetParLimits(2,0, 1000000);
h->Fit(&F);

/*plot histogram*/
auto c=F.GetParameter(2);
h->Draw();
cout<<"this is c"<<" "<< c<<endl;
cout<<f[0];
}



