#pragma once
#include <Arduino.h>

// LCD MODE
#define LCD_16x1  0
#define SII_16x1  1
#define LCD_16x2  2
#define LCD_20x4  3
/*
  液晶表示クラス
  文字列はいったんバッファに蓄えて、updateメソッドを呼び出す毎に1文字ずつ液晶ユニットに出力。
  したがって、updateまたはupdateAllメソッドを呼ばないと液晶画面に表示されない。
  これは、液晶との通信を1文字ずつに分割して処理時間の短縮を図っている。
*/
class Lcd{
  public:
    Lcd(byte lcdMode, byte d7, byte d6, byte d5, byte d4, byte e, byte rs, byte rw = 0xFF);
    void init();                              // 液晶ユニット初期化処理
    void command(byte data, bool rs = false); // 制御コマンド、データの出力
    void data(byte ch);                       // データ出力
    void update();                            // バッファから1文字分出力
    void updateAll();                         // バッファから全文字を出力
    void locate(byte p);                      // バッファへ文字出力位置を指定
    void charactor(byte ch);                  // バッファへ1文字出力
    void string(const char *ch);              // バッファへ文字列出力
    void string(const byte *ch);              // バッファへ1バイト出力
    void clear();                             // バッファをクリア。文字列出力位置は先頭。
    void printf(const char *args, ...);       // バッファへprintフォーマット出力

  private:
    byte d7,d6,d5,d4, e, rs, rw;
    byte cp;
    byte buf[20*4];
    byte updateP;
    byte charSize;
    byte lcdMode;
    byte lineSize;

    void nipple(byte data);
};
