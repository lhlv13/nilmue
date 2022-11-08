# nilmue
Non-intrusive load monitoring (NILM)，是一種在總電力入口端量測聚合電氣信號(如: 電壓波型、電流波型)並從聚合電氣信號中辨識出目前場域正在使用的用電負載之方法。隨著科技的進步，小領域隨著大領域走，NILM從以往的統計、演算法開發逐漸轉型為機器學習、深度學習之負載辨識，其主流語言為python、matlab兩種。<br>
我也不例外，在這股時代的大洪流中飄移，跟著AI的腳步，製作屬於自己的NILM負載辨識，但我不想束縛在 python的權威之下!?即使他是深度學習的大宗，也一定會有其缺點。比如: python 的執行速度就不比 C (CPU的狀況下)。因此!!我就想試試把 python沒扯到深度學習的運算丟給 C 來做，雖然 python 也有 numpy 這種幫助張量運算的套件，但實際丟給 C 才發現，真的還是有比較快!! 可喜可賀~ 希望未來可以完善這份 side project 。
## How to use？
nilmue 其實就是一個可以幫助提取負載特徵的Python套件，其底層以C語言構築而成，所以速度要比只用Python還快。

* <b>Demo</b>
將 `demo.py`檔 移到 nilmue資料夾 外(任意一個地方)，在 第8行的 path 填上 nilmue的絕對路徑。
```bash
$ python3 demo.py
```


