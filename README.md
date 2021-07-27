# ３年生後期学生実験 (α線)
実験で得れるデータの解析、グラフ作成に`python`プログラミング言語と数値計算、グラフ化パッケージを使用します。
注意：説明では分かりやすくするため日本語のコメントをコード内に書き込んでいるが、本来は英語で書くべき。  

## Jupyter
`Jupyter` (ジュピターまたはジュパイター)はウェブブラウザ経由で`python`プログラミングが可能なサービスです。正確には他の言語 (`R`,`Julia`など)もコード作成可能です。  
作業はすべて`notebook`と呼ばれるファイル上で行います。  
最小実行単位を`セル`とよび、`セル`にコードを書いて、実行ボタンで処理を行うことができます。  
`セル`はコードを書き込むだけではなく、マークダウン記法で説明文を記述することができます(`m`をタイプするとマークダウンモードになります)。  
`latex`での記述も可能なので数式など必要であれば説明に加えることができます。
```
$$
 m \vec{a} = \vec{F}
$$
```

## Jupyter上での操作
上部のツールバーで必要な操作を行う子ができます。  
以下に頻繁に使用するショートカットを列挙しておきます。  
* `シフト`+`リターン` : 選択している`セル`のコードを実行
* `m` : マークダウン記述モード
* `y` : コード記述モード


## プログラミング言語Pythonについての簡単な説明
1. [Python言語の基礎](notebooks/01_python_basics.ipynb)  
2. [数値計算、グラフ化パッケージ](02_python_pkgs.ipynb)  
<!--  
1. [1次元ヒストグラムの作成](notebooks/basic_root_001.html)  
1.1 [スタイルの編集方法](notebooks/basic_root_009.md)
2. [グラフの作成](notebooks/basic_root_002.html)
3. [エラーバー付きグラフの作成](notebooks/basic_root_003.html)
4. [ラザフォード散乱の理論線作例](notebooks/basic_root_004.html)
5. [MCAデータからヒストグラムの作成](notebooks/basic_root_005.html)  
6. [MCAデータをフィッティング(シグナルのみの場合)](notebooks/basic_root_006.html)
7. [MCAデータをフィッティング(シグナルとバックグラウンドの場合)](notebooks/basic_root_007.html)  
8. [微分断面積のグラフ作成](notebooks/basic_root_008.html)  
9. [Geiger-Nuttallのプロット](notebooks/basic_root_009.html)

! .. ## マクロ集
.. 実際に端末上で使用することになるROOTマクロは[こちら](macros/README.md)
-->
## プレゼンテーション
1. [プレゼン資料作成時に気をつけること](notebooks/presentation_001.md)  
