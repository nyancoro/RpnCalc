#pragma once
#include <Arduino.h>

/*
  ソニー製赤外線リモコンRM-D550の受信クラス
  readメソッドで１レコード分の信号を受信。信号未検知なら即リターンする。
  isRepeatメソッドにより、リピートコマンド（連続した同一コマンド）を判定する。
*/
class SonyIr{
  public:
  SonyIr(byte irPort){ this->irPort = irPort; }
  void init();                      // 初期化
  bool read();                      // true:受信完, false:未受信
  word getCommand(){ return cmd; }  // 受信コマンド取得
  bool isRepeat(){ return repeat; } // true:リピートされたコマンド, false:初回受信

  private:
  typedef unsigned long dword;
  const bool ON  = true;
  const bool OFF = false; 
  byte  irPort;
  byte  irData[2];
  dword endTime;
  word  cmd, oldCommand;
  bool  repeat;
  bool  irCheck(dword &startTime, dword &deltaTime, dword timeShort, dword timeOver, bool careerOn);

  public: // キーコマンドの定義
  static const word KEY_1 =         0x8008;
  static const word KEY_2 =         0x8108;
  static const word KEY_3 =         0x8208;
  static const word KEY_4 =         0x8308;
  static const word KEY_5 =         0x8408;
  static const word KEY_6 =         0x8508;
  static const word KEY_7 =         0x8608;
  static const word KEY_8 =         0x8708;
  static const word KEY_9 =         0x8808;
  static const word KEY_0 =         0x8908;
  static const word KEY_CLEAR =     0x8F08;
  static const word KEY_17 =        0x9008;
  static const word KEY_18 =        0x9108;
  static const word KEY_19 =        0x9708;
  static const word KEY_CONTINUE =  0x9D08;
  static const word KEY_SINGLE =    0x9E08;
  static const word KEY_PGM =       0x9F08;
  static const word KEY_10 =        0xA008;
  static const word KEY_11 =        0xA108;
  static const word KEY_12 =        0xA208;
  static const word KEY_13 =        0xA308;
  static const word KEY_14 =        0xA408;
  static const word KEY_15 =        0xA508;
  static const word KEY_16 =        0xA608;
  static const word KEY_PLUS10 =    0xA708;  // +10
  static const word KEY_TIME =      0xA808;
  static const word KEY_20 =        0xA908;
  static const word KEY_AB =        0xAA08;  // A↔B
  static const word KEY_REPEAT =    0xAC08;
  static const word KEY_AMS_LL =    0xB008; // ◀◀ AMS
  static const word KEY_AMS_RR =    0xB108; //     AMS ▶▶
  static const word KEY_PLAY =      0xB208; // ▶
  static const word KEY_SHUFFLE =   0xB508;
  static const word KEY_INDEX_L =   0xB608; // ◀ INDEX
  static const word KEY_INDEX_R =   0xB708; //    INDEX ▶
  static const word KEY_STOP =      0xB808; // ■
  static const word KEY_PAUSE =     0xB908; // ||
  static const word KEY_LL =        0xBA08; // ◀◀
  static const word KEY_RR =        0xBB08; // ▶▶
};
