#pragma once
#include "inout.h"
#include "common.h"

/*
  入出力に関するクラス
  Viewクラスは液晶制御クラスLcd(出力装置)と、赤外線リモコン受信クラスSonyIr(入力装置)を継承。
  液晶ユニットへ数字や設定画面の表示とキー入力処理を行う。
*/
class View: public Inout{
  public:
  void init(){
    Inout::init();
  }
  void printXY(const char *x, const char *y);         // 液晶上下段に文字列を表示
  byte configTop();                                   // 設定選択表示(disp mode, angle)
  void dispFormatSetting(byte &dispMode, byte &sci);  // 表示フォーマットの設定
  byte angleSetting();                                // 角度方式の設定
  void wait(word t);                                  // 液晶表示更新しながらの時間待ち
  
  private:
};
