#pragma once
#include <Arduino.h>
#include "rpn.h"
/*
  計算機クラス
  計算機クラスは逆ポーランドRpnクラスを継承。
  入力数字の編集機能、入力キーコードに応じた計算を行う。
*/
class Calc: public Rpn{
  public:
  void init(){
    Rpn::init();
  }
  void editNumInit(char *str);    // 数字列入力の初期化
  char *editNum(char *str, byte key);  // 入力数字の編集
  void mathFunc1(byte key);       // 関数計算1 キーコードに応じて計算を実行
  void mathFunc2(byte key);       // 関数計算2（SHIFTによる裏関数）

  private:
  byte p;       // 数字を代入する位置を示すポインタ
  bool plus;    // 仮数部の符号
  bool dot;     // 少数点あり
  bool e;       // 指数入力あり
  byte ep;      // 指数記号eの位置を示すポインタ
  bool ePlus;   // 指数部の符号
};