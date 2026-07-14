# 3D将棋_holesensor_ver.1.0
3D将棋_project
対応ハードウェア制御:3Dver2.2.1 7/7現在
ハードウェア制御部
x,y方向はセンサに供給するVccとGNDのON,OFFを切り替える。
z方向は出力線をアナログ値で読む。
リニアホールセンサx747:https://www.marutsu.co.jp/GoodsDetail.jsp?q=AH49HZ3-G1%20Diodes%20Incorporated&salesGoodsCode=46304099&shopNo=3

赤外線LEDx729:https://akizukidenshi.com/catalog/g/g100656/

フォトトランジスタx729:https://akizukidenshi.com/catalog/g/g100656/

降圧バッファx1:https://www.marutsu.co.jp/pc/i/14242773/

昇圧バッファx2:https://www.marutsu.co.jp/pc/i/14226373/

マイコンボード:https://akizukidenshi.com/catalog/g/g131148/

基板間固定金具:https://www.hirosugi-net.co.jp/shop/c/c1011/

We made "3D syogi" on either software and hardware.In recent years,There are alot of 3D board games.
for example 3Dches,3Dothello,and so on.But, We couldn't find "3D syogi",so I decide to mede "3Dsyogi".
The hard ware, electric circuit designed on "KICAD".We use "ESP32-S3-DevKitC-1-N8R8 ESP32-S3-WROOM-1 [1]"
to control the circuit and to get and send infometion of sensors.Also we write program of control ESP32 by Alduino language.
The way of ditecting peice of syogi,we use hole sensor and photo transistor.

-8,-108,8,108玉
-7,-107,7,107飛車
-6,-106,6,106角
-5,-105,5,105金
-4,-104,4,104銀
-3,-103,3,103桂馬
-2,-102,2,102香車
-1,-101,1,101歩
0なし
