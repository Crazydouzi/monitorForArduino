/*
 * OLED显示
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);  //开像素点发光
  refresholed(0,0,0,0);
  Serial.begin(9600);
  while (!Serial) continue;
  Serial.println("Serial Port Ready");
}

char frame[40] = {};  //用于存储AIDA64从串口发来的信息
byte inByte;
int num1, num2, num3,num4;

void refresholed(int n1,int n2, int n3,int n4) {

  display.clearDisplay();  //清屏

  display.setTextSize(1);   //设置字体大小
  display.setCursor(5, 5);  //设置显示位置
  display.println("Computer Information");
  display.println("");
  display.setTextSize(1);
  display.setCursor(5, 20);
  display.print("CPU FREQ : ");
  display.print(n1);
  display.println("Mhz");

  display.setCursor(5, 30);
  display.print("CPU USAGE: ");
  display.print(n2);
  display.println("%");

  display.setCursor(5, 40);
  display.print("CPU TEMP : ");
  display.print(n3);
  display.cp437(true);
  display.write(248);
  display.println("C");

display.setCursor(5, 50);
  display.print("MEM USAGE: ");
  display.print(n4);
  display.println("%");

  display.display();
}

void loop() {

  inByte = Serial.read();
  if (inByte == 0x43) {
    frame[0] = inByte;
    int count = 1;
    //将串口数据写入缓冲
    for (int i = 1; i < 40; i++) {
      while (Serial.available() == 0)
        ;
      frame[i] = Serial.read();
      count++;
    }
    Serial.println(" ");
    num1 = 0;
    for (int i = 2; i < 6; i++) {
      if (frame[i] == 0x20) break;
      num1 = num1 * 10 + (frame[i] - 48);
    }
    num2 = 0;
    for (int i = 9; i < 12; i++) {
      if (frame[i] == 0x20) break;
      num2 = num2 * 10 + (frame[i] - 48);
    }
    num3 = 0;
    for (int i = 15; i < 17; i++) {
      if (frame[i] == 0x20) break;
      num3 = num3 * 10 + (frame[i] - 48);
    }
    num4 = 0;
    for (int i = 22; i < 24; i++) {
      if (frame[i] == 0x20) break;
      num4 = num4 * 10 + (frame[i] - 48);
    }
    refresholed(num1,num2,num3,num4);
  }
}