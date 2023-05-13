#include "SonyIr.h"
/*
  RM-D550

		23932
0	2432	560
1	1268	536
2	1232	564
3	1236	556
4	1240	564
5	1236	568
6	628	568
7	636	556
8	1248	552
9	636	568
10	628	560
11	648	552
12	1244	
12bit	9F08
PGM

		23924
0	2460	552
1	1236	560
2	1224	564
3	1240	560
4	1240	560
5	1236	568
6	660	532
7	636	568
8	1236	556
9	640	560
10	640	560
11	640	560
12	1232	
12bit	9F08
PGM

*/
void IrRemote::init(){
  pinMode(irPort, INPUT_PULLUP);
  repeat = false;
  endTime = 0;
  cmd = oldCommand = 0x0000;
}

bool IrRemote::read(){
  dword dt;

  dword startTime = micros();
  if(irCheck(startTime, dt,  500, 3000, ON)) return false;    // リーダーチェック(2450us)
  irData[0] = irData[1] = 0;
  for(byte i = 0; i < 12; ++i){ // データビットの読込 LSB FIRST 12bit
    if(irCheck(startTime, dt, 450, 650, OFF)) return false;   // 550us
    if(irCheck(startTime, dt, 550, 1350, ON)) return false;   // 1:1250us, 0:650us
    if(dt > 950){ // データ1の判定
      bitWrite(irData[i >> 3], i & 0b111, 1);
    }
  }
  
  cmd = (irData[0] << 8) | irData[1];
  if(oldCommand == cmd && startTime - endTime < 48000){
    repeat = true;
  }else{
    repeat = false;
  }
  oldCommand = cmd;
  endTime = startTime;
  return true;
}

bool IrRemote::irCheck(dword &startTime, dword &deltaTime, dword timeShort, dword timeOver, bool careerOn){
  dword t;

  do{
    t = micros();
    deltaTime = t - startTime;
  }while(!digitalRead(irPort) == careerOn && deltaTime < timeOver);

  if(deltaTime < timeShort || deltaTime > timeOver){
    return true;  // タイムショート・オーバーエラー
  }
  startTime = t;
  return false;   // 有効時間幅
}
