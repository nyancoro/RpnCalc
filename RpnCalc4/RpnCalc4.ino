#include "common.h"
#include "controller.h"
/*
  Rpn    Lcd  SonyIr
   |      |    |
   |      Inout
   |        |
  Calc    View
   |        |
   Controller

*/

Controller cnt;

void setup() {
  #ifdef IR_GND
  pinMode(IR_GND, OUTPUT);
  digitalWrite(IR_GND, LOW);
  pinMode(IR_VCC, OUTPUT);
  digitalWrite(IR_VCC, HIGH);
  #endif

  cnt.init();
}

void loop() {
  cnt.calculate();  // 計算処理
}

