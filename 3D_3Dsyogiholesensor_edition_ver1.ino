/*
3D将棋first program 対応基盤ver2.1 hole_sensor eition
cube x,y*GND Vcc切替 z:データ線
x,yに接続される線(9本ずつ)を逐次切り替え、DATAのアナログ出力を読むことで
信号を感知。
予算;12万くらいかな?

*/

#include <MCP23S17.h>
#include<MCP320x.h>
#include<SPI.h>

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
#define frd9 40;//mainboards' board9 position pin
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
#define Vref 5000;
#define ADC_CLK 1600000;

MCP23S17 MCP_1(CS1,SPIMISO,SPIMOSI,SPICLOCK);//MCP1:mainboardGND rightkomadaiVcc,GND 
MCP23S17 MCP_2(CS2,SPIMISO,SPIMOSI,SPICLOCK);//MCP2:mainboardVcc leftkomadaiVcc,GND
MCP3208 adc_DATA(Vref,DATA);//MCP3208:board(1~8)DATA
MCP3208 adc_position(Vref,frd);//MCP3208:board(1~8)position;
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


int white=500;

int floor;//階層指定
int time;
int t,t0;

int banmen1[9][9]={0};
int banmen2[9][9]={0};
int banmen3[9][9]={0};
int banmen4[9][9]={0};
int banmen5[9][9]={0};
int banmen6[9][9]={0};
int banmen7[9][9]={0};
int banmen8[9][9]={0};
int banmen9[9][9]={0};

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("MCP23S17_LIB_ VERSION:");
  Serial.println(MCP23S17_LIB_ VERSION);
  delay(100);
  SPI.begin();
  bool b = MCP_1.begin();
  Serial.print("MCP23S17_1 begin:")
  Serial.println(b?"true":"false");
  delay(100);
  bool b = MCP_2.begin();
  Serial.print("MCP23S17_2 begin:")
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
    val = MCP_2.read1(pin);
    Serial.print(val);
    Serial.print(' ');
    delay(100);
  }
  Serial.println();
  
  SPISettings settings(ADC_CLK, MSBFIRST, SPI_MODE0);
  
  SPI.beginTransaction(settings);
}

int hantei(floor)//階層、位置を入力し、磁石センサ光センサを読み取る。
{
    int koma=0;
    if(floor==9)
    {
      mdata=analogRead(DATA9);
      mfrd=analogRead(frd9);
    }
    else
    {
      mdata=analogRead(DATA);
      mfrd=analogRead(frd);
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
  if(digitalRead(12,HIGH)||digitalRead(13,HIGH)||time<10000)
  {
    time=miillis();
  }
  while(millis()-time<500);
  {
    digitalWrite(14,HIGH);
  }
  x=t/9;
  y=t%9;
  
  banmen1[x][y]=hantei(1);
  
  
  t++;
  if(t==80)
  {
    t=0;
  }
}
