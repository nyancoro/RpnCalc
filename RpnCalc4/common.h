#pragma once
#include <Arduino.h>

// 入出力ポート定義
#define IR_RX   10  // IRセンサ
#define IR_GND  11  // IRセンサの電源をポートから供給
#define IR_VCC  12  //   〃
#define BEEP    13  // 圧電ブザー

// 液晶ユニット
// LCD20x4 R/WピンはGND固定
#define LCD_D7  A5
#define LCD_D6  A4
#define LCD_D5  A3
#define LCD_D4  A2
#define LCD_E   A1
#define LCD_RS  A0

// キーコード定義
enum {
  K_0, K_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9,
  K_CHG, K_E, K_BS, K_DOT, K_CLR, 
  K_ENTER, K_XY, K_ADD, K_SUB, K_DIV, K_MUL,
  K_INV, K_SQRT, K_POW, K_POW2, K_SIGMA,
  K_EXP, K_LN, K_LOG10, K_POW10, K_PI, K_ROLLDOWN,
  K_SIN, K_COS, K_TAN, K_XEQ, K_RS, K_LASTX, K_SHIFT,
};
