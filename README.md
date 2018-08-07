# ３年生後期学生実験
データ処理およびグラフ作成に必要な解析ソフトROOTの使い方と、C++言語についての簡単な説明

## ROOTの起動
ターミナル上でROOTプログラムを起動する

```>root -l```

ここで`-l`をオプションをつけることで起動時に表示されるロゴをスキップできるので必ずつけるのが望ましい。  
ROOTを起動すると以下のようなプロンプトが表示されるのでC++構文に基づいてコードを記述していく。     
```root [0] ```   

複雑な処理をするようになるとコマンドプロンプトに一行づつ打ち込んでいくのは効率が悪いためマクロファイルを作成し
そのマクロファイルをROOT上で実行させる、もしくはライブラリとしてロードすることになる。   
マクロファイル (test.Cとする)を例えば次のようなものを用意する。
```c++
int test(int a=1, int b=2)
{
  return (a+b);
}
```    

実行は`.x`で行う。  

```root [1] .x test.C```   

一方ライブラリとしてロードする場合には`.L`を用いる。
ライブラリをロードした後はROOTコマンドプロンプトでその関数を実行できるようになる。  

```
root [1] .L test.C
root [2] test(2,3)
``` 

## プログラミング言語C++についての簡単な説明
1. [C++言語の基礎](notebooks/basic_cpp_001.ipynb)
2. [標準ライブラリ](notebooks/basic_cpp_002.ipynb)

## ROOTを使ったヒストグラム、グラフ作成例
1. [1次元ヒストグラムの作成](notebooks/basic_root_001.ipynb)
2. [グラフの作成](notebooks/basic_root_002.ipynb)
3. [エラーバー付きグラフの作成](notebooks/basic_root_003.ipynb)
4. [ラザフォード散乱の理論線作例](notebooks/basic_root_004.ipynb)
5. [MCAデータからヒストグラムの作成](notebooks/basic_root_005.ipynb)  
6. [MCAデータをフィッティング](notebooks/basic_root_006.ipynb)

## マクロ集
実際に端末上で使用することになるROOTマクロは[こちら](macros/README.md)


