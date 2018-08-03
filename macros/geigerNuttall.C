#include <TF1.h>
#include <TH2D.h>
#include <TGraph.h>

void setStyle();

double pol1(double *x, double *par)
{
  return par[0]+par[1]*x[0];
}

bool setData(std::string fname,
	     std::vector<double>& t2,
	     std::vector<double>& ez,
	     std::vector<double>& lnL)
{
  ifstream ifs(fname.c_str());
  if(ifs.is_open()) {
    while (true) {
      double t,ea,z,a;
      ifs >> t >> ea >> z >> a; 
      if (ifs.eof()) break;
      t2.push_back(t);
      ez.push_back(std::pow(ea,-0.5)*z);
      // std::cout << t << " " << ea << " " << z << " " << a << std::endl;
    }
    for(const auto& t : t2){
      lnL.push_back(log(log(2.0)/t));
    }
    ifs.close();
    return true;
  } else {
    std::cout << fname << " was not opend!" << std::endl;
    return false;
  }
}

void geigerNuttall(){
  setStyle();
  gStyle->SetOptStat(0); 
  gStyle->SetOptFit(0);

  std::string file1 = "group1.dat";
  std::vector<double> t2_g1 ={};
  std::vector<double> ez_g1 = {};
  std::vector<double> lnL_g1 ={};
  setData(file1,t2_g1,ez_g1,lnL_g1);
  
  auto gr1 = new TGraph(ez_g1.size(), &ez_g1[0], &lnL_g1[0]);
  auto l1 = new TF1("l1",pol1,0,100,2);
  gr1->Fit("l1","0");


  std::string file2 = "group2.dat";
  std::vector<double> t2_g2 ={};
  std::vector<double> ez_g2 = {};
  std::vector<double> lnL_g2 ={};
  setData(file2,t2_g2,ez_g2,lnL_g2);
  auto gr2 = new TGraph(ez_g2.size(), &ez_g2[0], &lnL_g2[0]);
  auto l2 = new TF1("l2",pol1,0,100,2);
  l2->FixParameter(1,l1->GetParameter(1));
  gr2->Fit("l2","0");

  std::string file3 = "group3.dat";
  std::vector<double> t2_g3 ={};
  std::vector<double> ez_g3 = {};
  std::vector<double> lnL_g3 ={};
  setData(file3,t2_g3,ez_g3,lnL_g3);
  auto gr3 = new TGraph(ez_g3.size(), &ez_g3[0], &lnL_g3[0]);
  auto l3 = new TF1("l3",pol1,0,100,2);
  l3->FixParameter(1,l1->GetParameter(1));
  gr3->Fit("l3","0");


  auto c = new TCanvas("can","",600,600);
  auto h = new TH2D("h","Geiger-Nuttall relation;ZE^{-1/2};log#lambda",200,30,50,160,-80,20);
  h->Draw();

  int ci[6] = {3000, 3001, 3002, 3003, 3004, 3005};
  TColor *col[6];
  float rgb[6][3] = {
    {0.9490196078431372, 0.9411764705882353, 0.6313725490196078},
    {0.9882352941176471, 0.6823529411764706, 0.7333333333333333},
    {0.9450980392156862, 0.6980392156862745, 0.8627450980392157},
    {0.7490196078431373, 0.6078431372549019, 0.8705882352941177},
    {0.4549019607843137, 0.8196078431372549, 0.9176470588235294},
    {0.615686274509804, 0.9058823529411765, 0.8431372549019608}
  };


  gr2->SetMarkerStyle(kFullCircle);
  gr3->SetMarkerStyle(kFullCircle);
  gr1->SetFillColor(ci[3]);
  gr2->SetFillColor(ci[4]);
  gr3->SetFillColor(ci[5]);
  gr1->SetMarkerColor(ci[3]);
  gr2->SetMarkerColor(ci[4]);
  gr3->SetMarkerColor(ci[5]);

  gr1->Draw("P");
  gr2->Draw("P");
  gr3->Draw("P");

  for(int i=0;i<6;++i){
    col[i] = new TColor(ci[i],rgb[i][0],rgb[i][1],rgb[i][2]);
  }
  l1->SetLineColor(ci[0]);
  l2->SetLineColor(ci[1]);
  l3->SetLineColor(ci[2]);
  l1->Draw("same");
  l2->Draw("same");
  l3->Draw("same");

  auto leg = new TLegend(0.6,0.6,0.88,0.88,"","NDC");
  leg->SetBorderSize(0);
  leg->AddEntry(gr1, "group1 data", "p");
  leg->AddEntry(gr2, "group2 data", "p");
  leg->AddEntry(gr3, "group3 data", "p");
  leg->AddEntry(l1, "group1 line fit", "l");
  leg->AddEntry(l2, "group2 line fit", "l");
  leg->AddEntry(l3, "group3 line fit", "l");
  leg->Draw();

  c->SaveAs("gnPlot.pdf");
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
  gStyle->SetTitleYOffset(1.1);

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
  gStyle->SetNdivisions(505,"xyz");

  // use bold lines and markers
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(1.0);
  gStyle->SetHistLineWidth(2.);
  gStyle->SetLineStyleString(2,"[12 12]"); 
}


