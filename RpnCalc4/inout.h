#pragma once
#include "SonyIr.h"
#include "Lcd.h"
#include "common.h"
/*
  入出力クラス
  Lcd液晶とSonyIr赤外線リモコンの必要なメソッドを継承。
  キー入力に特化した新規メソッドの追加
*/
class Inout: private Lcd, private IrRemote{
  public:
  Inout(): Lcd(LCD_16x2, LCD_D7, LCD_D6, LCD_D5, LCD_D4, LCD_E, LCD_RS),
           IrRemote(IR_RX){ }
  void init(){
    Lcd::init();
    IrRemote::init();
    lastKey = 0xff;
  }
  // 入力処理
  byte readLastKey();             // 最後に確定したキー入力
  byte readNumKey(byte size);     // 1~9(size)のキー入力
  byte readKey();                 // 液晶表示更新しながらのキー入力待ち

  // 出力処理
  void clear();                   // 液晶画面バッファのクリア
  void printf(const char *args, ...); // 液晶画面バッファに文字フォーマット形式で出力
  void update();                  // 液晶画面に液晶画面バッファを出力

  private:
  byte irReadKey();
  byte keyMapSearch(word target);
  byte lastKey;
};

