// suto drive scenario 

#define BITMASK_1 0x01
#define BITMASK_2 0x02
#define BITMASK_3 0x04
#define BITMASK_4 0x08
#define BITMASK_5 0x10
#define BITMASK_6 0x20
#define BITMASK_7 0x40
#define BITMASK_8 0x80

/*
 ----6-------7-------5---
|                        |
|      1  2          CROSS
|       \  \             |
|        \-P2            |
|            \           |
|             3          8
|              \         |
 ----4----------P1-------

Direction <- TRAIN_DIRECTION_CLOCKWISE
          -> TRAIN_DIRECTION_COUNTERCLOCKWISE
POINT     <- POINT_DIRECTION_LEFT
          -> POINT_DIRECTION_RIGHT
CROSS     off CROSSING_STATUS_OFF
          on  CROSSING_STATUS_ON
*/

//#define _DEBUG 1

#define SPEED_STOP 0
#define SPEED_LOW 50
#define SPEED_MID 70
#define SPEED_HIGH 80

// Scenario macros
#define WAIT_TIME(time)   gbScenario[i++] = {SCN_TRIGGER_MSEC, time, 0}
//#ifdef _DEBUG
//  #define WAIT_SENSOR(no)   gbScenario[i++] = {SCN_TRIGGER_MSEC, 2000, 0}
//#else
  #define WAIT_SENSOR(no)   gbScenario[i++] = {SCN_TRIGGER_SENSOR, no, 0}
//#endif
#define POINT_1(dir)      gbScenario[i++] = {SCN_TRIGGER_NO, SCN_NOTG_P1, dir}
#define POINT_2(dir)      gbScenario[i++] = {SCN_TRIGGER_NO, SCN_NOTG_P2, dir}
#define CROSS(onoff)      gbScenario[i++] = {SCN_TRIGGER_NO, SCN_NOTG_CROSS, onoff}
#define SPEED(spd)        gbScenario[i++] = {SCN_TRIGGER_NO, SCN_NOTG_SPEED, spd}
#define DIRECTION(drctn)  gbScenario[i++] = {SCN_TRIGGER_NO, SCN_NOTG_TR_DIR, drctn}

void initScenarioParams(void){
  int i;

  // init auto drive scenario
  for(i=0;i<NUM_SCENARIO;i++){
    gbScenario[i].trigger = SCN_TRIGGER_INVALID;
    gbScenario[i].param_0 = 0;
    gbScenario[i].param_1 = 0;
  }  
  // Planning auto drive scenario
  i=0;

  if(gbSystem.scenario_number == 0){
    // 初期化
    WAIT_TIME(1000);
    WAIT_SENSOR(2);
    SPEED(SPEED_STOP);
    DIRECTION(TRAIN_DIRECTION_COUNTERCLOCKWISE);
    POINT_1(POINT_DIRECTION_RIGHT);
    POINT_2(POINT_DIRECTION_RIGHT);
    // 発車
    WAIT_TIME(3000);
    SPEED(SPEED_LOW);
    // 3を通過
    WAIT_SENSOR(3);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    SPEED(SPEED_LOW);
    CROSS(CROSSING_STATUS_ON);
    // 5を通過
    WAIT_SENSOR(5);
    WAIT_TIME(1500);
    SPEED(SPEED_STOP);
    // 5秒停車
    WAIT_TIME(3000);
    POINT_1(POINT_DIRECTION_LEFT);
    WAIT_TIME(2000);
    DIRECTION(TRAIN_DIRECTION_CLOCKWISE);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 4を通過
    WAIT_SENSOR(4);
    SPEED(SPEED_HIGH);
    // 6を通過
    WAIT_SENSOR(6);
    SPEED(SPEED_MID);
    CROSS(CROSSING_STATUS_ON);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 4を通過
    WAIT_SENSOR(4);
    SPEED(SPEED_MID);
    // 6を通過
    WAIT_SENSOR(6);
    WAIT_TIME(1600);
    SPEED(SPEED_STOP);
    CROSS(CROSSING_STATUS_ON);
    // 5秒停車
    WAIT_TIME(5000);
    POINT_1(POINT_DIRECTION_RIGHT);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 3を通過
    WAIT_SENSOR(3);
    WAIT_TIME(1000);
    SPEED(SPEED_LOW);
    // 2を通過
    WAIT_SENSOR(2);
    //WAIT_TIME(500);
    SPEED(SPEED_STOP);
  }

  else if(gbSystem.scenario_number == 1){
      // 初期化
    WAIT_TIME(1000);
    WAIT_SENSOR(2);
    SPEED(SPEED_STOP);
    DIRECTION(TRAIN_DIRECTION_COUNTERCLOCKWISE);
    POINT_1(POINT_DIRECTION_RIGHT);
    POINT_2(POINT_DIRECTION_RIGHT);
    // 発車
    WAIT_TIME(3000);
    SPEED(SPEED_LOW);
    // 3を通過
    WAIT_SENSOR(3);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    SPEED(SPEED_LOW);
    CROSS(CROSSING_STATUS_ON);
    // 5を通過
    WAIT_SENSOR(5);
    WAIT_TIME(1500);
    SPEED(SPEED_STOP);
    // 5秒停車
    WAIT_TIME(3000);
    POINT_1(POINT_DIRECTION_LEFT);
    WAIT_TIME(2000);
    DIRECTION(TRAIN_DIRECTION_CLOCKWISE);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 4を通過
    WAIT_SENSOR(4);
    SPEED(SPEED_HIGH);
    // 6を通過
    WAIT_SENSOR(6);
    SPEED(SPEED_MID);
    CROSS(CROSSING_STATUS_ON);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 4を通過
    WAIT_SENSOR(4);
    SPEED(SPEED_MID);
    // 6を通過
    WAIT_SENSOR(6);
    WAIT_TIME(1600);
    SPEED(SPEED_STOP);
    CROSS(CROSSING_STATUS_ON);
    // 5秒停車
    WAIT_TIME(5000);
    POINT_1(POINT_DIRECTION_RIGHT);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 3を通過
    WAIT_SENSOR(3);
    WAIT_TIME(1000);
    SPEED(SPEED_LOW);
    // 2を通過
    WAIT_SENSOR(2);
    //WAIT_TIME(500);
    SPEED(SPEED_STOP);
  
    // 10秒停車
    WAIT_TIME(5000);


    // 車両変更　----------------------
        // 初期化
    WAIT_TIME(1000);
    WAIT_SENSOR(1);
    SPEED(SPEED_STOP);
    DIRECTION(TRAIN_DIRECTION_COUNTERCLOCKWISE);
    POINT_1(POINT_DIRECTION_RIGHT);
    POINT_2(POINT_DIRECTION_LEFT);
    // 発車
    WAIT_TIME(3000);
    SPEED(SPEED_LOW);
    // 3を通過
    WAIT_SENSOR(3);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    SPEED(SPEED_LOW);
    CROSS(CROSSING_STATUS_ON);
    // 5を通過
    WAIT_SENSOR(5);
    WAIT_TIME(1500);
    SPEED(SPEED_STOP);
    // 5秒停車
    WAIT_TIME(3000);
    POINT_1(POINT_DIRECTION_LEFT);
    WAIT_TIME(2000);
    DIRECTION(TRAIN_DIRECTION_CLOCKWISE);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 4を通過
    WAIT_SENSOR(4);
    SPEED(SPEED_HIGH);
    // 6を通過
    WAIT_SENSOR(6);
    SPEED(SPEED_MID);
    CROSS(CROSSING_STATUS_ON);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 4を通過
    WAIT_SENSOR(4);
    SPEED(SPEED_MID);
    // 6を通過
    WAIT_SENSOR(6);
    WAIT_TIME(1600);
    SPEED(SPEED_STOP);
    CROSS(CROSSING_STATUS_ON);
    // 5秒停車
    WAIT_TIME(5000);
    POINT_1(POINT_DIRECTION_RIGHT);
    SPEED(SPEED_MID);
    // 8を通過
    WAIT_SENSOR(8);
    CROSS(CROSSING_STATUS_OFF);
    // 3を通過
    WAIT_SENSOR(3);
    WAIT_TIME(1000);
    SPEED(SPEED_LOW);
    // 2を通過
    WAIT_SENSOR(1);
    //WAIT_TIME(500);
    SPEED(SPEED_STOP);

  }
}

// get sensor no
int isSensorActive(int sensor_id)
{
  //int active=false;
  
  switch(sensor_id)
  {
    case 1: if((gbHC166Data[2] & BITMASK_1) == 0) { return true; } break;
    case 2: if((gbHC166Data[2] & BITMASK_2) == 0) { return true; } break;
    case 3: if((gbHC166Data[2] & BITMASK_3) == 0) { return true; } break;
    case 4: if((gbHC166Data[2] & BITMASK_4) == 0) { return true; } break;
    case 5: if((gbHC166Data[2] & BITMASK_5) == 0) { return true; } break;
    case 6: if((gbHC166Data[2] & BITMASK_6) == 0) { return true; } break;
    case 7: if((gbHC166Data[2] & BITMASK_7) == 0) { return true; } break;
    case 8: if((gbHC166Data[2] & BITMASK_8) == 0) { return true; } break;
    default: break;
  }

  //uintTempValue =  active; //gbHC166Data[2] & BITMASK_2;

  return false;
}

void HandleAutoDriveScenario(void){
  // auto drive
  if(gbSystem.scenario_counter>=NUM_SCENARIO){
    if(gbSystem.isEndless==true){
      gbSystem.scenario_counter=0;
    }
    return;
  }
  // invalid
  if(gbScenario[gbSystem.scenario_counter].trigger == SCN_TRIGGER_INVALID){
      gbSystem.scenario_counter++;
      return;    
  }
  // wait for sensor active
  if(gbScenario[gbSystem.scenario_counter].trigger == SCN_TRIGGER_SENSOR)
  {
    //uintTempValue =isSensorActive(gbScenario[gbSystem.scenario_counter].param_0);
    if(isSensorActive(gbScenario[gbSystem.scenario_counter].param_0)==true){
      gbSystem.scenario_counter++;
      return;
    }
  }
  // wait for timer
  if(gbScenario[gbSystem.scenario_counter].trigger == SCN_TRIGGER_MSEC){
    gbSystem.wait_timer++;
    if(gbSystem.wait_timer > gbScenario[gbSystem.scenario_counter].param_0){
      gbSystem.scenario_counter++;
      gbSystem.wait_timer = 0;
      return;
    }
  }
  // no trigger
  if(gbScenario[gbSystem.scenario_counter].trigger == SCN_TRIGGER_NO){
    // Point1
    if(gbScenario[gbSystem.scenario_counter].param_0 == SCN_NOTG_P1){
      if(gbScenario[gbSystem.scenario_counter].param_1 == POINT_DIRECTION_LEFT){
        gbPoint[0].direction = POINT_DIRECTION_LEFT;
        gbSignal[0].status = SIGNAL_STATUS_STOP;
      }
      else if(gbScenario[gbSystem.scenario_counter].param_1 == POINT_DIRECTION_RIGHT){
        gbPoint[0].direction = POINT_DIRECTION_RIGHT;
        gbSignal[0].status = SIGNAL_STATUS_GO;
      }
      gbIsUiChanged = true;
      gbIsHC595Update = true;
      gbSystem.scenario_counter++;
      updateButtonLedStatus();
      return;
    }
    // Point2
    else if(gbScenario[gbSystem.scenario_counter].param_0 == SCN_NOTG_P2){
      if(gbScenario[gbSystem.scenario_counter].param_1 == POINT_DIRECTION_LEFT){
        gbPoint[1].direction = POINT_DIRECTION_LEFT;
        gbSignal[1].status = SIGNAL_STATUS_GO;
      }
      else if(gbScenario[gbSystem.scenario_counter].param_1 == POINT_DIRECTION_RIGHT){
        gbPoint[1].direction = POINT_DIRECTION_RIGHT;
        gbSignal[1].status = SIGNAL_STATUS_STOP;
      }
      gbIsUiChanged = true;
      gbIsHC595Update = true;
      gbSystem.scenario_counter++;
      updateButtonLedStatus();
      return;
    }
    // train direction
    else if(gbScenario[gbSystem.scenario_counter].param_0 == SCN_NOTG_TR_DIR){
      if(gbScenario[gbSystem.scenario_counter].param_1 == TRAIN_DIRECTION_CLOCKWISE){
        gbTrain.direction = TRAIN_DIRECTION_CLOCKWISE;
        gbSignal[2].status = SIGNAL_STATUS_GO;
      }
      else if(gbScenario[gbSystem.scenario_counter].param_1 == TRAIN_DIRECTION_COUNTERCLOCKWISE){
        gbTrain.direction = TRAIN_DIRECTION_COUNTERCLOCKWISE;
        gbSignal[2].status = SIGNAL_STATUS_STOP;
      }
      gbIsUiChanged = true;
      gbIsHC595Update = true;
      gbSystem.scenario_counter++;
      updateButtonLedStatus();
      return;
     }
    // train speed
    else if(gbScenario[gbSystem.scenario_counter].param_0 == SCN_NOTG_SPEED){
      gbTrain.targetSpeed = gbScenario[gbSystem.scenario_counter].param_1;
      gbIsUiChanged = true;
      gbIsHC595Update = true;
      gbSystem.scenario_counter++;
      updateButtonLedStatus();
      return;
     }
    // crossing
    else if(gbScenario[gbSystem.scenario_counter].param_0 == SCN_NOTG_CROSS){
      gbCrossing[0].status = gbScenario[gbSystem.scenario_counter].param_1;
      gbIsUiChanged = true;
      gbIsHC595Update = true;
      gbSystem.scenario_counter++;
      updateButtonLedStatus();
      return;
    }
  }
}

