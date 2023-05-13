#include "inout.h"
void Inout::clear(){
  Lcd::clear();
}

void Inout::string(const char *ch){
  Lcd::string(ch);
}

void Inout::update(){
  Lcd::update();
}

void Inout::printf(const char *args, ...){
  va_list ap;
  char buff[32+1];
  va_start(ap, args);
  vsprintf(buff, args, ap);
  string(buff);
  va_end(ap);
}

byte Inout::readLastKey(){
  return lastKey;
}

byte Inout::readNumKey(byte size){ // 1~9(size)の入力
  while(true){
    byte num = readKey();
    if(num && num <= size) return num;
  }
}

byte Inout::readKey(){
  while(true){
    byte key = irReadKey();
    if(key != 0xff){
      #ifdef BEEP
      tone(BEEP, 1500, 60);
      #endif
      lastKey = key;
      return key;
    }
    update(); // 液晶画面の表示更新
  }
}

byte Inout::irReadKey() {
  if (read() && !isRepeat()) {
    return keyMapSearch(getCommand()); // キーコードを返す
  }
  return 0xff;  // 受信なし or 未定義キー or キーリピート
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
  TAN			        LASTx	▶▶

*/
byte Inout::keyMapSearch(word target){
  const word keyMap[][2] = {
    {KEY_1,     K_7},
    {KEY_2,     K_8},
    {KEY_3,     K_9},
    {KEY_4,     K_DIV},
    {KEY_5,     K_INV},
    {KEY_6,     K_4},
    {KEY_7,     K_5},
    {KEY_8,     K_6},
    {KEY_9,     K_MUL},
    {KEY_0,     K_CLR},
    {KEY_CLEAR, K_ENTER},
    {KEY_17,    K_DOT},
    {KEY_18,    K_BS},
    {KEY_19,    K_ADD},
    {KEY_CONTINUE, K_E},
    {KEY_SINGLE, K_CHG},
    {KEY_PGM,   K_XY},
    {KEY_10,    K_SQRT},
    {KEY_11,    K_1},
    {KEY_12,    K_2},
    {KEY_13,    K_3},
    {KEY_14,    K_SUB},
    {KEY_15,    K_POW},
    {KEY_16,    K_0},
    {KEY_PLUS10, K_SIGMA},
    {KEY_TIME,  K_LOG10},
    {KEY_20,    K_POW2},
    {KEY_AB,    K_LN},
    {KEY_REPEAT, K_EXP},
    {KEY_AMS_LL, K_PI},
    {KEY_AMS_RR, K_ROLLDOWN},
    {KEY_PLAY,  K_SIN},
    {KEY_SHUFFLE, K_POW10},
    {KEY_INDEX_L, K_XEQ},
    {KEY_INDEX_R, K_RS},
    {KEY_STOP,  K_TAN},
    {KEY_PAUSE, K_COS},
    {KEY_LL,    K_LASTX},
    {KEY_RR,  K_SHIFT},
  };
  int hi = sizeof(keyMap) / sizeof(word) / 2 - 1;
  int low = 0, mid;
  
  while(low <= hi){
    mid = (low + hi) >> 1;
    if(target <= keyMap[mid][0]) hi  = mid - 1;
    if(target >= keyMap[mid][0]) low = mid + 1;
  }
  if(low == hi + 2)
    return keyMap[low - 1][1];
  return 0xff; // no mutch
}


