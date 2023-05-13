#include "rpn.h"

void Rpn::push(float val){
  t = z;
  z = y;
  y = x;
  x = val;
}

float Rpn::pop(){
  float val = x;
  x = y;
  y = z;
  z = t;
  return val;
}

void Rpn::dup(){
  push(x);
}

void Rpn::xy(){
  float temp = x;
  x = y;
  y = temp;
}

void Rpn::LastX(){
  push(lastX);
}

void Rpn::Add(){
  lastX = x;
  x = y + x;
  y = z;
  z = t;
}

void Rpn::Subtract(){
  lastX = x;
  x = y - x;
  y = z;
  z = t;
}

void Rpn::Divide(){
  lastX = x;
  x = y / x;
  y = z;
  z = t;
}

void Rpn::Multiply(){
  lastX = x;
  x = y * x;
  y = z;
  z = t;
}

void Rpn::Change(){
  x = -x;
}

void Rpn::RollUp(){
  float temp = t;
  t = z;
  z = y;
  y = x;
  x = temp;
}

void Rpn::RollDown(){
  float temp = x;
  x = y;
  y = z;
  z = t;
  t = temp;
}

void Rpn::Inverse(){
  lastX = x;
  x = 1.0 / x;
}

void Rpn::Pow(){
  lastX = x;
  x = pow(y, x);
  y = z;
  z = t;
}

void Rpn::Pow2(){
  lastX = x;
  x = pow(x, 2.0f);
}

void Rpn::Pow10(){
  lastX = x;
  x = pow(10.0f, x);
}

void Rpn::Abs(){
  lastX = x;
  x = fabsf(x);
}

void Rpn::Sqrt(){
  lastX = x;
  x = sqrt(x);
}

void Rpn::E(){
  lastX = x;
  x = M_E;
}

void Rpn::Pi(){
  lastX = x;
  x = M_PI;
}

void Rpn::Log10(){
  lastX = x;
  x = log10(x);
}

void Rpn::Log(){
  lastX = x;
  x = log(x);
}

void Rpn::Exp(){
  lastX = x;
  x = exp(x);
}

void Rpn::Cbrt(){
  lastX = x;
  x = cbrt(x);
}

void Rpn::Sin(){
  lastX = x;
  x = sin(x * angle2rad);
}

void Rpn::Cos(){
  lastX = x;
  x = cos(x * angle2rad);
}

void Rpn::Tan(){
  lastX = x;
  x = tan(x * angle2rad);
}

void Rpn::Asin(){
  lastX = x;
  x = asin(x) * rad2angle;
}

void Rpn::Acos(){
  lastX = x;
  x = acos(x) * rad2angle;
}

void Rpn::Atan(){
  lastX = x;
  x = atan(x) * rad2angle;
}

void Rpn::Sinh(){
  lastX = x;
  x = sinh(x);
}

void Rpn::Cosh(){
  lastX = x;
  x = cosh(x);
}

void Rpn::Tanh(){
  lastX = x;
  x = tanh(x);
}

void Rpn::Asinh(){
  lastX = x;
  x = log(x + sqrt(x * x + 1.0f));
}

void Rpn::Acosh(){
  lastX = x;
  x = log(x + sqrt(x + 1.0f) * sqrt(x - 1.0f));
}

void Rpn::Atanh(){
  lastX = x;
  x = log((1.0f + x) / (1.0f - x)) / 2.0f;
}

float Rpn::getX(){
  return x;
}

float Rpn::getY(){
  return y;
}

void Rpn::setX(float val){
  x = val;
}

void Rpn::setAngle(byte angleMode){
  this->angleMode = angleMode;
  switch(angleMode){
    case 0: // RAD
      rad2angle = angle2rad = 1.0f;
      break;
    case 1: // DEG
      rad2angle = 180.0f / M_PI;
      angle2rad = M_PI / 180.0f;
      break;
    case 2: // GRAD
      rad2angle = 200.0f / M_PI;
      angle2rad = M_PI / 200.0f;
      break;
    default:
      this->angleMode = 0;  // deg
      rad2angle = angle2rad = 1.0f;
  }
}

byte Rpn::getAngleMode(){
  return angleMode;
}

void Rpn::setStr2X(const char *str){
  setX(atof(str));
}

void Rpn::setDispMode(byte dispMode, byte sci){
  this->dispMode = dispMode < 4? dispMode : 0;
  this->sci = sci >= 1 && sci <= 9? sci : 5;
}

char *Rpn::getYStr(char *str){
  return f2Str(str, getY());
}

char *Rpn::getXStr(char *str){
  return f2Str(str, getX());
}

void Rpn::swap(char &a, char &b){
  char temp;
  temp = a;
  a = b;
  b = temp;
}

char *Rpn::f2Str(char *str, float val){
  str[0] = '\0';

  if(isnan(val)){
    strcpy(str, "NaN");
  }else if(isinf(val)){
    if(signbit(val)){
      strcpy(str, "-INFINITE");
    }else{
      strcpy(str, "+INFINITE");    
    }
  }else{
    byte dispMode = this->dispMode;
    float range = fabsf(val);
    if(dispMode == 0){    // ALL すべて表示
      if(range <= 1.0e7 && range >= 1.0e-7){
        const byte prec = 8; // 小数点未満の桁を最大数表示
        const char width = 0;
        dtostrf(val, width, prec, str); // +3.0000000e+00
        
        for(byte p = strlen(str) -1; p >= 3 && str[p] == '0'; --p) // 小数点未満の0を削除
          str[p] = '\0';
      }else{
        dispMode = 3;
      }
    }
    if(dispMode == 1){    // FIX 固定小数表示
      if(range <= 1.0e7 && range >= 1.0e-7){
        const char width = 0; // 左右寄せ及び桁数指定
        const byte prec = sci; // 小数点未満の桁指定
        dtostrf(val, width, prec, str);
      }else{
        dispMode = 3;
      }
    }
    if(dispMode == 2){  // ENG エンジニア表示
      if(range < 1.0e21 && range >= 1.0e-18){ // エクサ~アトまで
        const byte prec = sci - 1;  // 有効数字として指定
        const byte flg = 2;         // 仮数部はプラス符号を表示する
        dtostre(val, str, prec, flg); // +3.0000000e+00
        char *p = strstr(str, "e");
        int exx = atoi(p + 1);  // 指数部取得
        int shift;
        if(exx >= 0){
          shift = abs(exx % 3);  // 左シフト数(*10) 
          exx = (exx / 3) * 3;
        }else{
          shift = (exx - 2) % 3 + 2;  // 左シフト数(*10) 
          exx = (exx - 2) / 3 * 3;
        }
        *p = '\0';            // 有効数字で切り取る
        for(int i = 0; i < shift; ++i){ // 仮数部の正規化
          if(str[i + 2 + 1] != '\0')
            swap(str[i + 2 + 1], str[i + 2]);
          else
            strcpy(&str[i + 2], "0.");
        }
        byte len = strlen(str);
        sprintf(&str[len], "e %02d", abs(exx)); // 指数部の挿入
        str[len + 1] = exx >= 0? '+' : '-';     // 指数部符号の挿入
        if(str[0] == '+') strcpy(str, &str[1]); // 仮数部のプラス符号を落とす
      }else{
        dispMode = 3;
      }
    }
    if(dispMode == 3){    // SCI 科学表示
      const byte prec = sci; // 小数点未満の桁を最大数表示
      const byte flg = 0;   // 仮数部の符号はマイナスのみ表示
      dtostre(val, str, prec, flg); // +3.0000000e+00
    }
  }
  return str;
}
