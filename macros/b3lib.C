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


