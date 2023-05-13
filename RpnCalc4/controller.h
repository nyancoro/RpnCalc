#pragma once
#include "Arduino.h"
#include "view.h"
#include "calc.h"
#include "common.h"
/*
  入出力、計算指示に係わる処理

*/
class Controller{
  public:
  void init(){
    view.init();
    calc.init();
    printXY();          // x,yを表示
  }
  void calculate(){
    numberKeyEdit();    // 計算値の入力
    execCalc();         // 計算処理
    printResult();      // 計算結果を表示
  }

  private:
  void printXY();       // x,yを表示
  void printResult();   // 計算結果を表示
  void numberKeyEdit(); // 数字キーの入力編集処理
  void execCalc();      // 計算処理
  void config();        // 画面表示フォーマット、角度モードの設定処理
  View view;            // 液晶表示とキー入力に係るインスタンス
  Calc calc;            // 計算に係るインスタンス
};

