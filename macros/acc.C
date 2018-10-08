void acc(){
  const double qc = 30.0;
  const double dq = 5;
  const double qmin = qc-dq;
  const double qmax = qc+dq;
  const double phic = 0;
  const double dphi = 3.0;
  const double phimin = phic-dphi;
  const double phimax = phic+dphi;
  TH1D *h = new TH1D("h","",3000,0,60);
  TF1 *f1 = new TF1("f1","1/sin(x/2)**4",M_PI*qmin/180,M_PI*qmax/180);
  for(int i=0;i<1000;++i){
    double r = f1->GetRandom();
    h->Fill(r*180/M_PI);
  }
  h->Draw();
  std::cout << "Mean " << h->GetMean() << std::endl;
}
