#pragma once
#include <Arduino.h>
/*
  逆ポーランドクラス
  スタック操作、数学計算・関数・float型と文字列の相互変換を行う
*/
class Rpn{
  public:
  void init(){
    x = y = z = t = lastX = 0.0f;
    setAngle(0);      // radian mode
    setDispMode(3, 5); // 科学表示、有効数字5桁
  }
  void push(float val); // スタックへpush
  float pop();          // スタックからpop
  void dup();           // push(x)
  void xy();            // x <> y
  void LastX();         // push(lastX);
  void Add();           // x = y + x;  y = z; z = t;
  void Subtract();      // x = y - x;  y = z; z = t;
  void Divide();        // x = y / x;  y = z; z = t;
  void Multiply();      // x = y * x;  y = z; z = t;
  void Change();        // x = -x
  void RollUp();        // x -> y -> z -> t -> x
  void RollDown();      // x <- y <- z <- t <- x
  void Inverse();       // x = 1 / x
  void Pow();           // x = y ^ x
  void Pow2();          // x = x ^ 2
  void Pow10();         // x = 10 ^ x
  void Abs();           // x = abs(x)
  void Sqrt();          // 平方根
  void Cbrt();          // 立方根
  void E();             // const e = 2.718...
  void Pi();            // const pi = 3.141...
  void Log10();         // x = log10(x)
  void Log();           // x = loge(x)
  void Exp();           // x = e ^ x
  void Sin();           // 三角関数 x = sin(x)
  void Cos();           // x = cos(x)
  void Tan();           // x = tan(x)
  void Asin();          // 逆三角関数
  void Acos();          // x = acos(x)
  void Atan();          // x = atan(x)
  void Sinh();          // 双曲線関数 x = sinh(x)
  void Cosh();          // x = cosh(x)
  void Tanh();          // x = tanh(x)
  void Asinh();         // 逆双曲線関数
  void Acosh();         //
  void Atanh();         //
  float getX();         //
  float getY();         //
  void setX(float val); //
  char *f2Str(char *str, float val);   // floatを文字列に変換
  char *getXStr(char *str);        // Xregを文字列に変換
  char *getYStr(char *str);        // Yregを文字列に変換
  void setStr2X(const char *str); // 文字列をXregにセット
  void setAngle(byte angleMode);  // 角度設定
  byte getAngleMode();            // 角度モードを取得
  void setDispMode(byte dispMode, byte sci);  // 数字文字列のフォーマット指定

  private:
  void swap(char &a, char &b);
  float x, y, z, t;               // スタック
  float lastX;                    //
  float angle2rad, rad2angle;     // 角度変換係数
  byte angleMode;                 // 0:rad 1:deg 2:grad
  byte dispMode;                  // 表示形式 0:全て表示 1:固定数表示 2:エンジニア表示 3:科学表示
  byte sci;                       // 有効数字 1~8
};
