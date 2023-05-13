#include "controller.h"

void Controller::printXY(){
  char x[18], y[18];
  
  view.printXY(calc.getXStr(x), calc.getYStr(y)); // 液晶ユニットにx,yスタックを表示
}

void Controller::printResult(){
  printXY();
}

void Controller::numberKeyEdit(){
  char x[18], y[18];

  // 数字の入力
  byte key = view.readKey();
  if(key <= K_CLR){
    calc.dup();           // push(x)
    calc.editNumInit(x);  // 数字入力の初期化
    do{
      view.printXY(calc.editNum(x, key), calc.getYStr(y));  // 入力中の数字とyを表示
      key = view.readKey();
    }while(key <= K_CLR);
    calc.setStr2X(x); // 入力された数字をxにセット
  }
}

void Controller::execCalc(){
  // 計算実行
  byte key = view.readLastKey();
  calc.mathFunc1(key);    // 数学関数の実行
  if(key == K_SHIFT){
    key = view.readKey();
    calc.mathFunc2(key);  // 数学関数の実行
    if(key == K_SHIFT){
      config();           // 設定処理
    } 
  }
}

void Controller::config(){  // 画面表示フォーマット、角度モードの設定処理
  switch(view.configTop()){ //設定（表示フォーマット、角度）
    case 1:{
      byte dispMode, sci;
      view.dispFormatSetting(dispMode, sci);
      calc.setDispMode(dispMode, sci);
      break;
    }
    case 2:
      calc.setAngle(view.angleSetting());
      break;
  }
  view.wait(2000);
}
