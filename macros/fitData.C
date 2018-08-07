void setStyle();

TH1D* importHist(std::string fname)
{

  // １次元ヒストグラムの定義
  auto *hist = new TH1D("h100",";channel;entries/channel",1024,0,1024);
  //  auto *hist = new TH1D("h100","Title",1024,0,1024);
  std::ifstream infile(fname);

  // データコンテナを確保
  std::vector<std::pair<int,int>> var;

  // ファイルから一行づつ読み込み
  int index = 0;
  for (string line = ""; getline(infile, line);++index)
    {
      // std::cout << line << std::endl;
      int  num = std::atoi(line.c_str());
      var.push_back(std::make_pair(index+1,num));
    }
  // std::cout << "size " <<  var.size() << std::endl;

  // ヒストグラムにデータをフィル
  for (const auto & v : var){
    hist->SetBinContent(v.first+1, v.second);
  }
  // TH1Dのポインタを返す
  return hist;
}

TH1D* rebin(TH1D *hist, int ndiv = 1, std::string title="")
{
  // rebining
  TH1D *hist_rebin = (TH1D *)hist->Rebin(ndiv,title.c_str());
  return hist_rebin;
}
/**
 * gaus.
 * x: variable.
 * par[0]: magnitude
 * par[1]: mean
 * par[2]: sigma
 * par[3]: bins/channel
 */
Double_t gaus(Double_t *x, Double_t *par) {
  return par[0]*TMath::Gaus(x[0], par[1], par[2], kTRUE); // normalized gaus
}

Double_t doubleGaus(Double_t *x, Double_t *par){
  double g1 = TMath::Gaus(x[0], par[1], par[2], kTRUE); 
  double g2 = TMath::Gaus(x[0], par[1], par[3], kTRUE); 
  return par[0]*(par[4]*g1+(1-par[4])*g2);
}


double step(double x, double t){
  return x < t? 0.0 :1.0;
}

Double_t asymGaus(Double_t *x, Double_t *par){
  double sigma = 0.5*(par[2]+par[3]);
  double g1 = (1.0-step(x[0],par[1])) * TMath::Gaus(x[0], par[1], par[2]);
  double g2 = step(x[0],par[1]) * TMath::Gaus(x[0], par[1], par[3]);
  return par[0]/(TMath::Sqrt(2.0*TMath::Pi())*sigma)*(g1+g2);
}

Double_t breitWigner(Double_t *x, Double_t *par){
  return par[0]*TMath::BreitWigner(x[0],par[1],par[2]);
}

Double_t voigt(Double_t *x, Double_t *par){
  return par[0]*TMath::Voigt(x[0]-par[1],par[2],par[3]);
}

void fitData(){
  gStyle->SetOptStat(0);
  setStyle();
  const double binsPerChannel =8.0;
  auto c = new TCanvas("can","",600,600);
  auto h = importHist("test.dat");
  auto hRebin = rebin(h,binsPerChannel,"rebinned histogram");
  //  hRebin->Draw();
  //  c->Draw();

  auto sg = new TF1("sg",gaus,600,1000,3);
  sg->SetParameters(1000,770,50);
  hRebin->Fit("sg");
  hRebin->Draw();
  c->Draw();
  double Y = sg->GetParameter(0)/binsPerChannel;
  double dY = sg->GetParError(0)/binsPerChannel;
  std::cout << Y << "+/-" << dY << std::endl;

  auto dg = new TF1("dg",doubleGaus,600,1000,5);
  dg->SetParameters(1000,770,15,50,0.8);
  hRebin->Fit("dg");

  Y = dg->GetParameter(0)/binsPerChannel;
  dY = dg->GetParError(0)/binsPerChannel;
  std::cout << Y << "+/-" << dY << std::endl;

  auto ag = new TF1("ag",asymGaus,600,1000,4);
  ag->SetParameters(1000,770,50,100);
  hRebin->Fit("ag");

  Y = ag->GetParameter(0)/binsPerChannel;
  dY = ag->GetParError(0)/binsPerChannel;
  std::cout << Y << "+/-" << dY << std::endl;

  auto bw = new TF1("bw",breitWigner,600,1000,3);
  bw->SetParameters(1000,770,50);
  hRebin->Fit("bw");

  Y = bw->GetParameter(0)/binsPerChannel;
  dY = bw->GetParError(0)/binsPerChannel;
  std::cout << Y << "+/-" << dY << std::endl;

  auto vg = new TF1("vg",voigt,600,1000,4);
  vg->SetParameters(1000,770,50,5);
  hRebin->Fit("vg");

  Y = vg->GetParameter(0)/binsPerChannel;
  dY = vg->GetParError(0)/binsPerChannel;
  std::cout << Y << "+/-" << dY << std::endl;

  hRebin->Draw();
  sg->SetLineColor(kBlue);
  sg->Draw("same");
  dg->SetLineColor(kMagenta);
  dg->Draw("same");
  ag->SetLineColor(kGreen);
  ag->Draw("same");
  bw->SetLineColor(kCyan);
  bw->Draw("same");
  vg->SetLineColor(kYellow);
  vg->Draw("same");
  auto leg = new TLegend(0.15,0.7,0.4,0.9,"","NDC");
  leg->SetBorderSize(0);
  leg->AddEntry(hRebin,"Data","lep");
  leg->AddEntry(sg,"Single gaussian","l");
  leg->AddEntry(dg,"Double gaussian","l");
  leg->AddEntry(ag,"Asym. gaussian","l");
  leg->AddEntry(bw,"Breit Wigner","l");
  leg->AddEntry(vg,"Voigt","l");
  leg->Draw();
}  

void setStyle(){
  Int_t icol=0; // WHITE
  gStyle->SetFrameBorderMode(icol);
  gStyle->SetFrameFillColor(icol);
  gStyle->SetCanvasBorderMode(icol);
  gStyle->SetCanvasColor(icol);
  gStyle->SetPadBorderMode(icol);
  gStyle->SetPadColor(icol);
  gStyle->SetStatColor(icol);
  //  gStyle->SetPaperSize(26,26);
  // set margin sizes
  gStyle->SetPadTopMargin(0.07);
  gStyle->SetPadRightMargin(0.07);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadLeftMargin(0.12);

  // set title offsets (for axis label)
  gStyle->SetTitleXOffset(1.1);
  gStyle->SetTitleYOffset(1.4);

  // use large fonts
  //Int_t font=72; // Helvetica italics
  Int_t font=42; // Helvetica
  Double_t tsize=0.04;
  gStyle->SetTextFont(font);

  gStyle->SetTextSize(tsize);
  gStyle->SetLabelFont(font,"x");
  gStyle->SetTitleFont(font,"x");
  gStyle->SetLabelFont(font,"y");
  gStyle->SetTitleFont(font,"y");
  gStyle->SetLabelFont(font,"z");
  gStyle->SetTitleFont(font,"z");
  
  gStyle->SetLabelSize(tsize,"x");

  gStyle->SetTitleSize(tsize,"x");
  gStyle->SetLabelSize(tsize,"y");
  gStyle->SetTitleSize(tsize,"y");
  gStyle->SetLabelSize(tsize,"z");
  gStyle->SetTitleSize(tsize,"z");

  gStyle->SetLabelOffset(0.01,"xy");
  gStyle->SetNdivisions(315,"xyz");

  // use bold lines and markers
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.0);
  gStyle->SetHistLineWidth(2.);
  gStyle->SetLineStyleString(2,"[12 12]"); 
}


