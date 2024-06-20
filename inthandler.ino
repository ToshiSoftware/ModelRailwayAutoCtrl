

// called every 1 msec
void IRAM_ATTR My1msIntHandler(void) {
  // counter
  gbIntCounter++;
  if(gbIntCounter>TIMER_COUNTER_MAX) gbIntCounter=0; // 100sec timer

  // serial in
  MySerialInput();  // read HC166 and then put into gbHC166Data

  // serial in handler
  HandleEncoder();  // read gbHC166Data[0](upper byte) and change gbEncoder[i].value: if changed, gbIsUiChanged = true;
  HandleCtrlButton(); // read gbHC166Data[0](lower byte) and change gbCtrlButton[i].status: if changed, gbIsUiChanged = true;
  HandleLedButton(); // read gbHC166Data[1], and change gbLedButton[i].status: if changed, gbIsUiChanged = true;
  //updateParamsFromLcdButton(); // read gbLedButton[i].status and change Point/Crossing/Signal/ButtonLED status

  // drive devices
  HandleSignal(); // read gbSignal[i].status, if changed goto signal sequence
  DrivePoint(); // read gbPoint[i].direction, if changed drive Point
  DriveCrossing(); // read gbCrossing[i].status, if changed drive Crossing
  
  // VR
  if(gbSystem.mode == SYSTEM_MODE_MANUAL){
    GetSpeedVr();  // read Analog pin, and then set gbTrain.speed
  }
  else{
    if(gbTrain.speed > gbTrain.targetSpeed){
      if(gbIntCounter % 10 == 0){
        gbTrain.speed--;
        gbTrain.prevSpeed = gbTrain.speed;
        gbIsUiChanged = true;
        gbIsHC595Update = true;
    }
    }
    else if(gbTrain.speed < gbTrain.targetSpeed){
      if(gbIntCounter % 50 == 0){
        gbTrain.speed++;
        gbTrain.prevSpeed = gbTrain.speed;
        gbIsUiChanged = true;
        gbIsHC595Update = true;
    }
    }
    HandleAutoDriveScenario();
  }
}