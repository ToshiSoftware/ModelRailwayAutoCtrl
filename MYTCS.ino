// MYTCS N-GAUGE LAYOUT CONTROLLER
// 2024/05/21
// tokada

#include <ST7032.h>
#include <time.h>

#include "MYTCS.h"
#include "inthandler.h"
#include "util.h"


// Def: LCD
ST7032 lcd;

// Def: HwTimer
hw_timer_t *timer1ms = NULL;

// global params
Type_System     gbSystem;
Type_Scenario   gbScenario[NUM_SCENARIO];
Type_Train      gbTrain;
Type_CtrlButton gbCtrlButton[NUM_CTRLBUTTON];
Type_LedButton  gbLedButton[NUM_LEDBUTTON];
Type_SpeedLED   gbSpeedLED[NUM_SPEED_LED];
Type_Point      gbPoint[NUM_POINT];
Type_Signal     gbSignal[NUM_SIGNAL];
Type_Crossing   gbCrossing[NUM_CROSSING];
Type_Sensor     gbSensor[NUM_SENSOR];
int gbIsUiChanged = 0;
int gbIsHC595Update = 0;

Type_EncoderBit gbEncoder[NUM_ENCODER];

unsigned int gbHC595Data[NUM_HC595];
unsigned int gbHC166Data[NUM_HC166];

//unsigned int uintTempValue=0xff;

// interrupt handler
int gbIntCounter=0;

void initParams(void)
{
  int i;
  // device state
  for(i=0;i<NUM_HC595;i++){
    gbHC595Data[i] = 0;
  }
  for(i=0;i<NUM_HC166;i++){
    gbHC166Data[i] = 0;
  }  

  // init system mode
  gbSystem.mode = SYSTEM_MODE_MANUAL;
  gbSystem.scenario_counter = 0;
  gbSystem.wait_timer = 0;
  gbSystem.scenario_number = 0;
  gbSystem.isEndless = 0;

  // init auto drive scenario
  for(i=0;i<NUM_SCENARIO;i++){
    gbScenario[i].trigger = SCN_TRIGGER_INVALID;
    gbScenario[i].param_0 = 0;
    gbScenario[i].param_1 = 0;
  }  

  // init train status
  gbTrain.direction = TRAIN_DIRECTION_CLOCKWISE;
  gbTrain.prevDirection = TRAIN_DIRECTION_CLOCKWISE;
  gbTrain.speed = 0;
  gbTrain.prevSpeed = 0;
  gbTrain.maxSpeed = 255;
  gbTrain.targetSpeed = 0;

  // init ctrl buttons
  for(i=0;i<NUM_CTRLBUTTON;i++){
    gbCtrlButton[i].status=0;
    gbCtrlButton[i].prevStatus=0;
  }
  
  // init led button
  for(i=0;i<NUM_LEDBUTTON;i++){
    gbLedButton[i].led=0;
    gbLedButton[i].status=0;
    gbLedButton[i].prevStatus=0;
  }
  // init speed led
  for(i=0;i<NUM_SPEED_LED;i++){
    gbSpeedLED[i].led=0;
  } 
  // init points
  for(i=0;i<NUM_POINT;i++) {
    gbPoint[i].direction=POINT_DIRECTION_LEFT;
    gbPoint[i].prevDirection=POINT_DIRECTION_LEFT;
    gbPoint[i].onCounter=0;
    gbPoint[i].isDriving=false;
    gbPoint[i].driveM1 = true; // moter driver -> HIGH
    gbPoint[i].driveM2 = true; //
  } 
  // init train signals
  for(i=0;i<NUM_SIGNAL;i++){
    gbSignal[i].status=SIGNAL_STATUS_STOP;
    gbSignal[i].prevStatus=SIGNAL_STATUS_STOP;
    gbSignal[i].color=SIGNAL_COLOR_RED;
    gbSignal[i].isChanging=false;
    gbSignal[i].counter=0;
  }
  // init crossing sign
  for(i=0;i<NUM_CROSSING;i++) {
    gbCrossing[i].status=CROSSING_STATUS_OFF;
    gbCrossing[i].prevStatus=CROSSING_STATUS_OFF;
    gbCrossing[i].led1 = false;
    gbCrossing[i].led1 = false;
    gbCrossing[i].counter = 0;
  }
  // init sensor
  for(i=0;i<NUM_SENSOR;i++){
    gbSensor[i].status=0;
  } 
  // sencoder reset
  memset(&gbEncoder, 0, sizeof(Type_EncoderBit)*NUM_ENCODER);
}

void setup() {
  // init globals
  initParams();
  initScenarioParams();

  // Serial pins
  pinMode(PIN_166_DAT, INPUT_PULLUP);
  pinMode(PIN_166_CLK, OUTPUT);
  pinMode(PIN_166_STB, OUTPUT);

  pinMode(PIN_595_DAT, OUTPUT);
  pinMode(PIN_595_CLK, OUTPUT);
  pinMode(PIN_595_STB, OUTPUT);

  // reset HC595
  updateHC595();

  // PWM
  pinMode(PIN_MOTER_M1, OUTPUT);     //PWM用のピンにD5を設定
  pinMode(PIN_MOTER_M2, OUTPUT);     //PWM用のピンにD5を設定
  digitalWrite(PIN_MOTER_M1, HIGH); // 無効PINGはHIGH（Lを出力）
  digitalWrite(PIN_MOTER_M2, HIGH); // 無効PINGはHIGH（Lを出力）
  ledcSetup(PWM_TIMER_CH, PWM_FREQ, PWM_RESO_BIT); //チャンネル0、20000Hz、分解能8bitで設定
  ledcAttachPin(PIN_MOTER_M1, PWM_TIMER_CH);    //チャンネル1の出力をPIN_MOTER_M1に
  ledcWrite(PWM_TIMER_CH, 255);      //8bitの場合は最大255 (128=50%)
  digitalWrite(PIN_MOTER_M2, HIGH); // 無効PINGはHIGH（Lを出力）

  // reset HC595
  updateHC595();

  // LCD -
  lcd.begin(16, 2);
  lcd.setContrast(45);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ATCS v2");

  // reset HC595
  updateHC595();
  
  // interrupt timer
  timer1ms = timerBegin(TIMER_UI_HANDLER_CH, PRESCALER_DIVIDE_RATE, true);
  timerAttachInterrupt(timer1ms, &My1msIntHandler, true); // calllback
  timerAlarmWrite(timer1ms, TIMER_UI_INTERVAL, true); // 1000 microsec
  timerAlarmEnable(timer1ms); // start timer

  // reset HC595
  updateHC595();
  
  gbIsHC595Update = true;
}

void debug(int a){
    // VR input test
    EraceLCD(0, 0, 8); // 0文字目、1行目、8文字消す
    //lcd.print("");
    lcd.print(a);
}


void updateLCD(void)
{
  // mode
  EraceLCD(0, 0, 4);
  if(gbSystem.mode==SYSTEM_MODE_MANUAL){
    lcd.print("MN");
  }
  else{
    lcd.print("AT");
  }
  if(gbSystem.isEndless==true)
  {
    lcd.print("*");
  }
  else{
    lcd.print(" ");
  }  // scenario number
  lcd.print(gbSystem.scenario_number);

  // blinking
  if(gbIntCounter%500 < 250){
    EraceLCD(4, 0, 1);
    lcd.print(">");
  }
  else{
    EraceLCD(4, 0, 1);
    lcd.print(" ");
  }
  // scenario no
  PrintInt3Digit(gbSystem.scenario_counter, 5, 0);
  // train dir
  if(gbTrain.direction == TRAIN_DIRECTION_CLOCKWISE){
    EraceLCD(8, 0, 4);
    lcd.print(" <- ");
  }
  else{
    EraceLCD(8, 0, 4);
    lcd.print("  ->");
  }
  // train speed
  PrintInt3Digit(gbTrain.speed, 13, 0);
  // Point
  EraceLCD(0, 1, 4);
  {
    char text[16];
    sprintf(text, "[%d%d]", gbPoint[0].direction, gbPoint[1].direction);
    lcd.print(text);
  }
  // cross
  EraceLCD(4, 1, 4);
  {
    char text[16];
    sprintf(text, "[%d] ", gbCrossing[0].status);
    lcd.print(text);
  }
  // sensor
  EraceLCD(8, 1, 8);
  PrintBinLCD((unsigned char) gbHC166Data[2]);
  //PrintInt2DigitHEX((unsigned char) gbHC166Data[2], 8, 1);
  //lcd.print(gbScenario[gbSystem.scenario_counter].param_0);
  //lcd.print(uintTempValue);
}

int ct =0;

void loop() {
  int i;
  // put your main code here, to run repeatedly:

  //debug(ct++);
  //updateLCD();

  if(gbIntCounter%250 == 0){
    gbIsUiChanged = true;
    gbIsHC595Update = true;
  }

  if(gbIsUiChanged==true){
    // UI
    updateEncoderValue();
    updateParamsFromCtrlButton();
    updateParamsFromLcdButton();

    // set power pack driver
    updatePowerPack();

    // 列車速度からPWMを設定する
    ledcWrite(PWM_TIMER_CH, 255-gbTrain.speed); 

    // 最後にLECをアップデート
    updateLCD();

    // RESET change flag
    gbIsUiChanged = false;
  }

  // Serial out
  if(gbIsHC595Update==true){
    updateHC595();
    // RESET change flag
    gbIsHC595Update = false;
    gbIsUiChanged=true;
  }


}
