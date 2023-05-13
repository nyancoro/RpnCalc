#include "calc.h"
#include "common.h"

void Calc::editNumInit(char *str){
  p = 0;
  plus = true;
  dot = false;
  e = false;
  ep = 0;
  ePlus = true;
  str[0] = '\0';
}

char *Calc::editNum(char *str, byte key) {
  char zeroStr[18];
  f2Str(zeroStr, 0.0f);

  if (key <= K_9 && p < 15) {   // 0~9
    str[p] = key + '0';
    str[p + 1] = '_';
    str[p + 2] = '\0';
    ++p;
  } else if (key == K_DOT && !dot && !e && p < 15) {  // dot point
    if (p == 0) {
      strcpy(str, "0._");
      p = 2;
    } else {
      strcpy(&str[p], "._");
      ++p;
    }
    dot = true;
  } else if (key == K_BS) { // back space
    if (p <= 1) {
      strcpy(str, zeroStr);
      p = 0;
      plus = true;
      dot = false;
      e = false;
    } else if(p > 1){
      --p;
      if (str[p] == '.'){
        dot = false;
      }else if(toupper(str[p]) == 'E'){
        e = false;
      }else if(str[p] == '-'){
        ePlus = true;
      }
      strcpy(&str[p], "_");
    }
  } else if (key == K_CHG && p < 15) {  // 符号反転
    if (e) {  // 指数部の符号変更
      ePlus = !ePlus;
      byte i;
      if (ePlus) {
        for (i = ep + 1; i <= p + 1; ++i) // マイナス符号を削除して１文字詰める
          str[i] = str[i + 1];
        --p;
      } else {
        for (i = p + 1; i > ep; --i) // 先頭にマイナス符号を挿入
          str[i + 1] = str[i];
        str[ep + 1] = '-';
        ++p;
      }
    } else {  // 仮数部の符号変更
      plus = !plus;
      if(p == 0){
        strcpy(str, "-0_");
        p = 2;
      }else if(plus){
        for(byte i = 0; i <= p + 1; ++i) // マイナス符号を削除して１文字詰める
          str[i] = str[i + 1];
        --p;
      }else{
        for(int i = p + 1; i >= 0; --i) // 先頭にマイナス符号を挿入
          str[i + 1] = str[i];
        str[0] = '-';
        ++p;
      }
    }
  } else if (key == K_E && !e && p < 15) {  // 指数指定
    ePlus = true;
    if (p == 0) {
      strcpy(str, "1e_");
      ep = 1;
      p = 2;
    } else {
      strcpy(&str[p], "e_");
      ep = p;
      ++p;
    }
    e = true;
  } else if (key == K_CLR) {    // 入力クリア
    strcpy(str, zeroStr);
    p = 0;
    plus = true;
    dot = false;
    e = false;
  }
  return str;
}

/*
      key map

  ｘ↔ｙ +/-   E
  7	    8	    9	  ÷     1/ｘ
  4	    5	    6	  *	    √ｘ
  1	    2	    3	  -	    y^x
  0	    ・	  BS	+     x^2
  ∑+	  CLEAR	          ENTER

  e^x	  LN		    Log10 10^x
  SIN			        π	    R↓
  COS			        XEQ	  R/S
  TAN			        LASTx	SHIFT

*/
void Calc::mathFunc1(byte key){
  switch(key){
    case K_ENTER: push(getX()); break;// enter
    case K_XY:    xy(); break;        // x <> y
    case K_ADD:   Add(); break;       // +
    case K_SUB:   Subtract(); break;  // -
    case K_DIV:   Divide(); break;    // /
    case K_MUL:   Multiply(); break;  // *
    case K_INV:   Inverse(); break;   // 1/x
    case K_SQRT:  Sqrt(); break;      // sqrt(x)
    case K_POW:   Pow(); break;       // y^x
    case K_POW2:  Pow2(); break;      // 2^x
    case K_SIGMA: break;
    case K_EXP:   Exp(); break;       // e^x
    case K_LN:    Log(); break;       // loge
    case K_LOG10: Log10(); break;     // log10
    case K_POW10: Pow10(); break;     // 10^x
    case K_PI:    Pi(); break;        // pi
    case K_ROLLDOWN: RollDown(); break; //
    case K_SIN:   Sin(); break;       // sin(x)
    case K_COS:   Cos(); break;       // cos(x)
    case K_TAN:   Tan(); break;       // tan(x)
    case K_XEQ:   break;              
    case K_RS:    break;
    case K_LASTX: LastX(); break;     // lastX
  }
}

void Calc::mathFunc2(byte key){
  switch(key){
    case K_SIN:   Asin(); break;       // asin(x)
    case K_COS:   Acos(); break;       // acos(x)
    case K_TAN:   Atan(); break;       // atan(x)
    case K_7:     Sinh(); break;       // 双曲線関数
    case K_8:     Cosh(); break;       // 
    case K_9:     Tanh(); break;       // 
    case K_4:     Asinh(); break;      // 逆双曲線関数
    case K_5:     Acosh(); break;      // 
    case K_6:     Atanh(); break;      // 
  }
}
