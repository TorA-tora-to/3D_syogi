# 3D将棋_holesensor_ver.5.0
3D将棋_project
対応ハードウェア制御:3Dver.5.0 8/6現在
ハードウェア制御部
x,y方向はセンサに供給するVccとGNDのON,OFFを切り替える。
リニアホールセンサx747:https://www.marutsu.co.jp/GoodsDetail.jsp?q=AH49HZ3-G1%20Diodes%20Incorporated&salesGoodsCode=46304099&shopNo=3
マイコンボード:https://www.marutsu.co.jp/pc/i/41434008/
基板間固定金具:https://www.hirosugi-net.co.jp/shop/c/c1011/
電源平滑キャパシタ:https://akizukidenshi.com/catalog/g/g108294/
7セグ:https://akizukidenshi.com/catalog/g/g104114/
その他:https://akizukidenshi.com/catalog/cart/cart.aspx

# What is "3Dsyogi"

We made "3D syogi" on either software and hardware.In recent years,There are alot of 3D board games.
for example 3Dches,3Dothello,and so on.But, We couldn't find "3D syogi",so I decide to mede "3Dsyogi".
The software, 3Dgraphic is made by "Unity".
The hardware, electric circuit is designed on "KICAD".We use "ESP32-S3-DevKitC-1-N8R8 ESP32-S3-WROOM-1 [1]"
to control the circuit and to get and send infometion of sensors.Also we write program of control ESP32 by Alduino language.
We use serial communication between hardware and software.The infomation which is ESP32 got send for Unity on realtime,
and to influence the graphic by Unity.
# The technology of hardware 
The way of ditecting peice of syogi,we use hole sensor [2] and photo transistor [3].if magnet is into the peises of syogi,
we can measure the Magnetic flux density of the magnet by the holesensor.Also if Vary the magnetic flux density for each piece,
we can get vary of output voltage by holesensor.By using this method, we can distinguish the pieces.In syogi, it have very inportant consept "nari".It's like "promotion" in ches. In this rule,we turn over the piece so the direction of Magnetic flux　will
turn over,too.so we can get infomation of "nari" by holesensor.In this game,we need  able to distinguish whose piece it is,so we drow harf of the piece bluck.
And,we use LED and photo transistor to measure the luminosity of　light from reflect in the piece,and we can know the direction of it.if the color of piece is bluck, the output voltage of photo transistorr is smaller them white.
In this way, we can distinguish the pieces ,but ESP32 couldn't get data of sensors,becouse there are a lot of sensor ,and there aren't enough I/O pins.So we use sensor matrix.In ths way,all of the sensors use same data line to ESP32,but the Vcc lines and GND line will sepalate.


-8,-108,8,108玉　
-7,-107,7,107飛車
-6,-106,6,106角
-5,-105,5,105金
-4,-104,4,104銀
-3,-103,3,103桂馬
-2,-102,2,102香車
-1,-101,1,101歩
0なし
