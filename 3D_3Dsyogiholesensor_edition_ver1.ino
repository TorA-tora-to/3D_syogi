/*
3D将棋first program 対応基盤ver2.1 hole_sensor eition
cube x,y*GND Vcc切替 z:データ線
x,yに接続される線(9本ずつ)を逐次切り替え、DATAのアナログ出力を読むことで
信号を感知。
*/

#include <MCP23S17.h>


#define SPICLOCK 37;//SCK
#define SPIMOSI 36;//MOSI
#define SPIMISO 35;//MISO
#define CS1 43;//MCP23S17:1,CS
#define CS2 44;//MCP23S17:2,CS
#define leftKomadai 15;//left komadai's DATA
#define rightKomadai 20;//right komadai's DATA
#define DATA 16;//mainboards' DATA(board1~8) MCP3208
#define DATA9 41;//mainords' board9 DATA pin
#define frd 17;//mainboards' Position(borad1~8) MCP3208
#define frd9 40;//mainboards' board9 pssition pin
#define SW1 12;//push sw1
#define SW2 13;//push sw2
#define LED 14;//LED
#define sSEGa 4;//7segment LED a:7
#define sSEGb 5;//7segment LED b:6
#define sSEGc 6;//7segment LED c:4
#define sSEGa 7;//7segment LED d:2
#define sSEGb 8;//7segment LED e:1
#define sSEGa 9;//7segment LED f:9
#define sSEGa 10;//7segment LED g:10


MCP23S17 MCP_1(CS1,SPIMISO,SPIMOSI,SPICLOCK);//MCP1
MCP23S17 MCP_2(CS2,SPIMISO,SPIMOSI,SPICLOCK);//MCP2



void setup() {
  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:

}
