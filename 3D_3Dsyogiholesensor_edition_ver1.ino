/*
3D将棋first program 対応基盤ver2.2.1 hole_sensor eition
cube x,y*GND Vcc切替 z:データ線
x,yに接続される線(9本ずつ)を逐次切り替え、DATAのアナログ出力を読むことで
信号を感知。
予算;12万くらいかな?
7セグ表示
0　通常
1　シリアル通信不可
2  シリアル通信不可
3　シリアル通信不可
4  測定異常
5  
6
7
8
9
シリアル通信テストを送信(test)したとき、Unity側から、返信する(check)
*/

#include <MCP23S17.h>
#include<Mcp320x.h>
#include<SPI.h>
#include<SevSeg.h>

#define SPICLOCK 37//SCK
#define SPIMOSI 36//MOSI
#define SPIMISO 35//MISO
#define CS1 43//MCP23S17:1,CS
#define CS2 44//MCP23S17:2,CS
#define leftKomadai 15//left komadai's DATA
#define rightKomadai 20//right komadai's DATA
#define DATA 16//mainboards' DATA(board1~8) MCP3208
#define DATA9 41//mainords' board9 DATA pin
#define frd 17//mainboards' Position(borad1~8) MCP3208
#define frd9 40//mainboards' board9 position pin
#define SW1 12//push sw1
#define SW2 13//push sw2
#define LED 14//LED
#define sSEGa 4//7segment LED a:7
#define sSEGb 5//7segment LED b:6
#define sSEGc 6//7segment LED c:4
#define sSEGa 7//7segment LED d:2
#define sSEGb 8//7segment LED e:1
#define sSEGa 9//7segment LED f:9
#define sSEGa 10//7segment LED g:10
#define Vref 5000
#define ADC_CLK 1600000

MCP23S17 MCP_1(CS1,SPIMISO,SPIMOSI,SPICLOCK);//MCP1:mainboardGND rightkomadaiVcc,GND 
MCP23S17 MCP_2(CS2,SPIMISO,SPIMOSI,SPICLOCK);//MCP2:mainboardVcc leftkomadaiVcc,GND
MCP3208 adc_DATA(Vref,16);//MCP3208:board(1~8)DATA
MCP3208 adc_position(Vref,17);//MCP3208:board(1~8)position;

SevSeg sevseg;

//各コマの読み取り最大値
int gyoku=1023;
int hisya=970;
int kaku=920;
int kin=870;
int gin=820;
int kei=770;
int kyou=720;
int fu=670;
int shiki=600;//駒なしと歩の判断閾値
int fu2=420;
int kyou2=370;
int kei2=320;
int gin2=270;
int kin2=220;
int kaku2=170;
int gisya2=120;
int gyoku2=70;

int x,y;

string test_read;
int error_code;

int white=500;

int floorn;//階層指定
int t=0,t0,n;

/*
int banmen1[9][9]={0};
int banmen2[9][9]={0};
int banmen3[9][9]={0};
int banmen4[9][9]={0};
int banmen5[9][9]={0};
int banmen6[9][9]={0};
int banmen7[9][9]={0};
int banmen8[9][9]={0};
int banmen9[9][9]={0};
*/
int banmen[9][9][9]={0};

void setup() {
  Serial.begin(115200);
  Serial.println();
  delay(100);
  SPI.begin();
  bool b = MCP_1.begin();
  Serial.print("MCP23S17_1 begin:");
  Serial.println(b?"true":"false");
  delay(100);
  bool c = MCP_2.begin();
  Serial.print("MCP23S17_2 begin:");
  Serial.println(b?"true":"false");
  delay(100);
  MCP_1.pinMode8(0,0x00);
  MCP_1.pinMode8(1,0x00);

  MCP_2.pinMode8(0,0x00);
  MCP_2.pinMode8(1,0x00);

  pinMode(DATA,OUTPUT);
  digitalWrite(DATA,HIGH);
  pinMode(frd,OUTPUT);
  digitalWrite(frd,HIGH);
  pinMode(14,OUTPUT);
  pinMode(12,INPUT);
  pinMode(13,INPUT);
  
  Serial.println("TEST write1(0)");
  delay(100);
  for (int i = 0; i < 16; i++)
  {
    MCP_1.write1(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print(' ');
    delay(100);
  }
  MCP_1.write1(0,0);
  for (int i = 0; i < 16; i++)
  {
    MCP_2.write1(0, i % 2);  //  alternating HIGH/LOW
    Serial.print(i % 2);
    Serial.print(' ');
    delay(100);
  }
  MCP_2.write1(0,0);//両方の出力をGNDに落とす。
  
  Serial.println();
  Serial.println();

  Serial.println("TEST write1(pin)");
  delay(100);
  for (int pin = 0; pin < 16; pin++)
  {
    MCP_1.write1(pin, 1 - pin % 2);  //  alternating HIGH/LOW
    Serial.print(1 - pin % 2);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  Serial.println();

  Serial.println("TEST read back");

  for (int pin = 0; pin < 16; pin++)
  {
    int val = MCP_1.read1(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  for (int pin = 0; pin < 16; pin++)
  {
    int val2 = MCP_2.read1(pin);
    Serial.print(val2);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  
  SPI.beginTransaction(settings);

  byte numDigits =1;
  byte digitPins[]={};
  byte segmentPins[]={4,5,6,7,8,9,10,11};
  bool resistorsOnSegments=false;
  byte hardwareConfig=COMMON_ANODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(90);

}

int hantei(int floorn)//階層、位置を入力し、磁石センサ光センサを読み取る。
{
    
    int koma=0;
    int mdata,mfrd;
    if(floorn==9)
    {
      mdata=analogRead(DATA9);
      mfrd=analogRead(frd9);
    }
    else
    {
      adc_DATA.read(static_cast<MCP3208::Channel>(floorn-1));
      adc_position.read(static_cast<MCP3208::Channel>(floorn-1));
    }

  
    if(mdata<gyoku)
    {
      koma=-8;  
    }
    else if(mdata<hisya)
    {
      koma=-7;  
    }
    else if(mdata<kaku2)
    {
      koma=-6;  
    }
    else if(mdata<kin2)
    {
      koma=-5;  
    }
    else if(mdata<gin2)
    {
      koma=-4;  
    }
    else if(mdata<kei2)
    {
      koma=-3;  
    }
    else if(mdata<kyou2)
    {
      koma=-2;  
    }
    else if(mdata<fu2)
    {
      koma=-1;  
    }
    else if(mdata<shiki)
    {
      koma=0;  
    }
    else if(mdata<fu)
    {
      koma=1;
    }
    else if(mdata<kyou)
    {
      koma=2;
    }
    else if(mdata<kei)
    {
      koma=3;
    }
    else if(mdata<gin)
    {
      koma=4;
    }
    else if(mdata<kin)
    {
      koma=5;
    }
    else if(mdata<kaku)
    {
      koma=6;
    }
    else if(DATA<hisya)
    {
      koma=7;
    }
    else if(DATA<gyoku)
    {
      koma=8;
    }

  
    if(mfrd>white)
    {
      if(koma<0)
      {
        koma-=100;
      }
      else if(koma>0)
      {
        koma+=100;
      }
    }
    return koma;  
}


void loop() {
  Serial.println("test");
  delay(20);
  if(Serial.available()>0)
  {
   test_read=Serial.read();
   test_read.trim();
   if(test_read=="test")
   {
    error_code=0;
    sevseg.setNumber(error_code);
    sevseg.refreshDisplay();
   }
   else
   {
    error_code=2;
    sevseg.setNumber(error_code);
    sevseg.refreshDisplay();
   }
    
  }
  else
  {
    error_code=1;
    sevseg.setNumber(error_code);
    sevseg.refreshDisplay();
  }
  
  if(t==0)
  {
        digitalWrite(14,HIGH);
        delay(500);
        digitalWrite(14,LOW);
  }
  x=t/9;
  y=t%9;//特定の行列をVcc,GNDとし、それ以外をGND,Vccとする。
  delay(5);
  for(n=0;n<9;n++)
  {
    banmen[n][x][y]=hantei(n);
    delay(5);
  }
  /*
  banmen[0][x][y]=hantei(1);  
  banmen[1][x][y]=hantei(2);
  banmen[2][x][y]=hantei(3);
  banmen[3][x][y]=hantei(4);
  banmen[4][x][y]=hantei(5);
  banmen[5][x][y]=hantei(6);
  banmen[6][x][y]=hantei(7);
  banmen[7][x][y]=hantei(8);
  banmen[8][x][y]=hantei(9);
  */
  Serial.printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",x,y,banmen[0][x][y],banmen[1][x][y],banmen[2][x][y],banmen[3][x][y],banmen[4][x][y],banmen[5][x][y],banmen[6][x][y],banmen[7][x][y],banmen[8][x][y]);
  delay(5);
  for(n=0;n<9;n++)
  {
    MCP_1.write1(n,LOW);
    MCP_2.write1(n,LOW);
  }
  
  t++;
  if(t==80)
  {
    t=0;
  }
}
