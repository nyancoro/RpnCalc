#include "view.h"

void View::printXY(const char *x, const char *y){
  clear();
  printf("%s\n", y);  // 上段にYregを表示
  printf("%s", x);    // 下段にXregを表示
}

void View::wait(word t){
  for(word i = 0; i < t; ++i){
    delay(1);
    update();
  }
}

byte View::configTop(){
  clear();
  printf("Conf>\n1:Disp 2:Angle");
  return readNumKey(2);
}

void View::dispFormatSetting(byte &dispMode, byte &sci){
  clear();
  printf("Conf>Disp\nALL FIX ENG SCI");
  dispMode = readNumKey(4) - 1;
  clear();
  const char *modeText[] ={"ALL", "FIX", "ENG", "SCI"};
  printf("Conf>Disp>%s\n1..8? ", modeText[dispMode]);
  sci = readNumKey(8);  // 有効数字1～8の入力
  printf("%d", sci);
}

byte View::angleSetting(){
  clear();
  printf("Conf>Angle\n1:RAD 2:DEG GRA");
  byte angleMode = readNumKey(3) - 1;
  const char *angleText[] = {"RAD", "DEG", "GRA"};
  clear();
  printf("Conf>Angle>\n%s", angleText[angleMode]);
  return angleMode;
}
