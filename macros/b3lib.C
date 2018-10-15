//
// 実験で使うとおもわれる操作を関数にしたもの
//
#include <string>
#include <fstream>
#include <TH1D.h>

/**
 * MCAのデータを読み込んでヒストグラムを作成する.
 */
TH1D* importHist(std::string fname)
{

  // １次元ヒストグラムの定義
  auto *hist = new TH1D("h100",";x label;y label",1024,0,1024);
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
  std::cout << "size " <<  var.size() << std::endl;

  // ヒストグラムにデータをフィル
  for (const auto & v : var){
    hist->SetBinContent(v.first+1, v.second);
  }
  // TH1Dのポインタを返す
  return hist;
}


/**
 * ヒストグラムのリビン.
 */
TH1D* rebin(TH1D *hist, int ndiv = 1, std::string title="hnew")
{
  // rebinin
  TH1D *htmp = (TH1D*)hist->Clone(title.c_str());
  TH1D *hist_rebin = dynamic_cast<TH1D *>(htmp->Rebin(ndiv));
  return hist_rebin;
}


/**
 * ヒストグラムの指定した範囲の積分値を計算する.
 */

double integral(const TH1D* hist, double xmin=0, double xmax=100000){
  std::map<int,double> x;
  const int nbins = hist->GetNbinsX();
  for(int i =0;i<nbins;++i){
    x.insert(std::make_pair(i+1,hist->GetBinLowEdge(i+1)));
  }

  int binMin = 1;
  int binMax = nbins;
  for(const auto &xx : x){
    if(xx.second > xmin){
      binMin = xx.first-1;
      break;
    }
  }

  for(const auto &xx : x){
  if(xx.second > xmax){
      binMax = xx.first-1;
      break;
    }
  }


  return (hist->Integral(binMin,binMax));
}


/**
 * ピーク値に対応するXの値を返す.
 */
double peak(const TH1D* hist){
  cout << "peak value " << hist->GetMaximum() << endl;
  int binx = hist->GetMaximumBin();
  double xpeak =  hist->GetBinCenter(binx);
  return xpeak;
}


/**
 * Xラベルのタイトルを設定.
 */
template <typename T>
void xtitle(T* hist, TString str){
  hist->GetXaxis()->SetTitle(str);
}

/**
 * Yラベルのタイトルを設定.
 */
template <typename T>
void ytitle(T* hist, TString str){
  hist->GetYaxis()->SetTitle(str);
}


/**
* 半減期のデータを読み込むための関数.
*/
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


/**
 * 半減期のデータを読み込んでグラフを作成.
 */
TGraph * gnMakeGraph(std::string file="group1.dat")
{
  std::vector<double> t2_g1 ={};
  std::vector<double> ez_g1 = {};
  std::vector<double> lnL_g1 ={};
  setData(file,t2_g1,ez_g1,lnL_g1);
  // グラフ作成、フィット
  TGraph* gr1 = new TGraph(ez_g1.size(), &ez_g1[0], &lnL_g1[0]);
  gr1->SetMarkerStyle(kFullCircle);
  return gr1;
}

/**
*  フィッティングで使用する線形関数の定義.
*/
double pol1(double *x, double *par)
{
  return par[0]+par[1]*x[0];
}

/**
 * line fit.
 * no constant, slope.
 */
TF1* line(TString name){
  TF1* line = new TF1(name,"pol1",0,100,2);
  return line;
}

/**
 * line fit.
 * with slope
 */
TF1* line(TString name, double slope){
  TF1* line = new TF1(name,"pol1",0,100,2);
  line->FixParameter(1,slope);
  return line;
}


TGraph* ruMakeGraph(std::string fname){
  // データコンテナを確保
  std::vector<double> x={};
  std::vector<double> y={};

  std::ifstream ifs(fname);
  if(ifs.is_open()) {
    while (true) {
      double q,cs;
      ifs >> q >> cs;
      if (ifs.eof()) break;
      x.push_back(q);
      y.push_back(cs);
    }
    ifs.close();
  }

  TGraph* gr = new TGraph(x.size(), &x[0], &y[0]);
  return gr;
}


TGraphErrors* ruMakeGraphErrors(std::string fname){
  std::vector<double> x={};
  std::vector<double> y={};
  std::vector<double> dx={};
  std::vector<double> dy={};

  std::ifstream ifs(fname);
  if(ifs.is_open()) {
    while (true) {
      double q,cs, dq,dcs;
      ifs >> q >> cs >> dq >> dcs;
      if (ifs.eof()) break;
      x.push_back(q);
      y.push_back(cs);
      dx.push_back(dq);
      dy.push_back(dcs);
    }
    ifs.close();
  }
  TGraphErrors *gre = new TGraphErrors(x.size(),&x[0],&y[0],&dx[0],&dy[0]);
  return gre;
}

TGraphAsymmErrors* ruMakeGraphAsymErrors(std::string fname){
  std::vector<double> x={};
  std::vector<double> y={};
  std::vector<double> dxl={};
  std::vector<double> dyl={};
  std::vector<double> dxh={};
  std::vector<double> dyh={};

  std::ifstream ifs(fname);
  if(ifs.is_open()) {
    while (true) {
      double q,cs, dql,dcsl,dqh,dcsh;
      ifs >> q >> cs >> dql >> dcsl >>  dqh >> dcsh;
      if (ifs.eof()) break;
      x.push_back(q);
      y.push_back(cs);
      dxl.push_back(dql);
      dyl.push_back(dcsl);
      dxh.push_back(dqh);
      dyh.push_back(dcsh);
    }
    ifs.close();
  }
  TGraphAsymmErrors *gre = new TGraphAsymmErrors(x.size(),&x[0],&y[0],&dxl[0],&dxh[0],&dyl[0],&dyh[0]);
  return gre;
}
