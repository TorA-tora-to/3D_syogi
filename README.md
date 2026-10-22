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
The hardware, electric circuit is designed on "KICAD".We use "ESP32-S3-DevKitC-1-N8R8 ESP32-S3-WROOM-1" [1]
to control the circuit and to get and send infometion of sensors.Also we write program of control ESP32 by Alduino language.
We use serial communication between hardware and software.The infomation which is ESP32 got send for Unity on realtime,
and to influence the graphic by Unity.
# The technology of hardware 
The way of ditecting peice of syogi,we use hole sensor "AH49HZ3-G1".[2] if magnet is into the peises of syogi,
we can measure the Magnetic flux density of the magnet by the hall sensor.Also if Vary the magnetic flux density for each piece,
we can get vary of output voltage by hall sensor.By using this method, we can distinguish the pieces.In syogi, it have very inportant consept "nari".It's like "promotion" in ches. In this rule,we turn over the piece so the direction of Magnetic flux　will
turn over,too.so we can get infomation of "nari" by holesensor.In this game,we need  able to distinguish whose piece it is,so we drow harf of the piece bluck.
And,we use LED and photo transistor to measure the luminosity of　light from reflect in the piece,and we can know the direction of it.if the color of piece is bluck, the output voltage of photo transistorr is smaller them white.
In this way, we can distinguish the pieces ,but ESP32 couldn't get data of sensors,becouse there are a lot of sensor ,and there aren't enough I/O pins.So we use sensor matrix.In ths way,all of the sensors use same data line to ESP32,but the Vcc lines and GND line will sepalate.

# 
[1]"ESP32-S3-DevKitC-1-N8R8 ESP32-S3-WROOM-1" is one of micro computer board. It equip with microcomputer chip "ESP32 S3".
This chip is one of ESP32 series which designed by "Espressif Systems"."ESP32-S3-DevKitC-1-N8R8"have 36 GPIO pins. Also,it equip
8MB ROMs and 8MB RAMs. Proscssor　of the micro conputer is 32bit and witch frequency of prosess is 240MHz. So it can operat in big projects like this by the strong computing power.
[2]"AH49HZ3-G1"is one of hall sensor. if this sensor into the magnetic field, it output data by magnetic field.
this sensor is type of linear sensor so the data witch output is analog. 
Also if this sensor into positive direction magnetic field,it output more than threshold.And it's also into negative direction magnetic field,it'll output less then threshold.
threshold of this sensor is 2.5V.(if you Apply 5V)
