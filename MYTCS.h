// MYTCS.h

// 1ms counter
#define TIMER_COUNTER_MAX 100000

// PIN assign
#define PIN_MOTER_M1 D1
#define PIN_MOTER_M2 D2

//#define PIN_LCD_SDA  D4 // defined by ST7032.h
//#define PIN_LCD_SCL  D5

#define PIN_166_DAT  D3
#define PIN_166_CLK  D6
#define PIN_166_STB  D7

#define PIN_595_STB  D8
#define PIN_595_DAT  D10
#define PIN_595_CLK  D9

#define PIN_ANALOG_VR D0

// PWM
#define PWM_FREQ 20000  // 20kHz
#define PWM_RESO_BIT 8  // resolution　8bit
#define PWM_TIMER_CH 0

// hardware timer
#define PRESCALER_DIVIDE_RATE 80
#define TIMER_UI_INTERVAL 1000  // 10ms
#define TIMER_UI_HANDLER_CH 1

// num of chip
#define NUM_HC166 3
#define NUM_HC595 5

// number of items
#define NUM_CTRLBUTTON 4
#define NUM_ENCODER 2
#define NUM_LEDBUTTON 8
#define NUM_SPEED_LED 8
#define NUM_POINT 4
#define NUM_SIGNAL 4
#define NUM_CROSSING 2
#define NUM_SENSOR 8

// TRAIN status
#define TRAIN_SPEED_TOLERANCE 3
#define TRAIN_DIRECTION_CLOCKWISE 0
#define TRAIN_DIRECTION_COUNTERCLOCKWISE 1

// SYSTEM
#define NUM_SCENARIO 10
#define SYSTEM_MODE_MANUAL 0
#define SYSTEM_MODE_AUTO   1
typedef struct _Type_System
{
  int mode; // 0:manual, 1:auto
  int scenario_counter;
  int wait_timer;
  int scenario_number;
  int isEndless;
}Type_System;

/*
TRIGGER             PARAM_0      PARAM_1
---------------------------------------
SCN_TRIGGER_INVALID *ignore the scenario*
---------------------------------------
SCN_NOTRIGGER       0:point_1      dir
                    1:point_2      dir
                    2:train_dir    dir
                    3:train_spped  255
                    4:crossing     on/off
---------------------------------------
SCN_TRIGGER_SENSOR  sensor_no      N/A
---------------------------------------
SCN_TRIGGER_MSEC    wait_msec      N/A
---------------------------------------
*/

// auto drive scenario
#define NUM_SCENARIO     200
#define SCN_TRIGGER_INVALID 0
#define SCN_TRIGGER_NO      1  // just do it
#define SCN_TRIGGER_SENSOR  2  // wait specified sensor
#define SCN_TRIGGER_MSEC    3  // wait specified msec

#define SCN_NOTG_P1 0
#define SCN_NOTG_P2 1
#define SCN_NOTG_TR_DIR 2
#define SCN_NOTG_SPEED 3
#define SCN_NOTG_CROSS 4


typedef struct _Type_Scenario
{
  int trigger;
  int param_0;
  int param_1;
}Type_Scenario;


typedef struct _Type_Train
{
  int direction; // 0 or 1
  int prevDirection; // 0 or 1
  int speed; // 0-255
  int prevSpeed; // revious state
  int tempSpeed; // for def comparison
  int maxSpeed; // 255
  int targetSpeed; // target speed specified when AUTO mode
} Type_Train;

// Button LED
typedef struct _Type_CtrlButton
{
  int status; // 1=pressed
  int prevStatus; // revious state
} Type_CtrlButton;

// Button LED
typedef struct _Type_LedButton
{
  int led;   // 0 or 1
  int status; // 1=pressed
  int prevStatus; // revious state
} Type_LedButton;

// Speed Indicator LED
typedef struct _Type_SpeedLED
{
  int led; // 0 or 1
} Type_SpeedLED;

// POINT status
#define POINT_DIRECTION_LEFT   0
#define POINT_DIRECTION_RIGHT 1
#define POINT_DRIVE_DURATION 50 // test 50ms

typedef struct _Type_Point
{
  int direction; // 0 or 1
  int prevDirection;
  int driveM1;
  int driveM2;
  int isDriving;
  int onCounter;
} Type_Point;

// SIGNAL status
#define SIGNAL_COLOR_RED 0
#define SIGNAL_COLOR_YELLOW 1
#define SIGNAL_COLOR_GREEN 2

#define SIGNAL_STATUS_STOP 0
#define SIGNAL_STATUS_GO 1

#define SIGNAL_YELLOW_DURATION 3000 // 3sec

typedef struct _Type_Signal
{
  int status; // 0:stop, 1:go
  int prevStatus;
  int color; // 0:red, 
  int isChanging; //
  int counter;
} Type_Signal;

// Crossing status
#define CROSSING_STATUS_OFF 0
#define CROSSING_STATUS_ON 1
#define CROSSING_ON_DURATION 500

typedef struct _Type_Crossing
{
  int status; // 0 or 1
  int prevStatus;
  int led1;     
  int led2;     
  int counter;
} Type_Crossing;

// SENSOR status
typedef struct _Type_Sensor
{
  int status; // 0 or 1
} Type_Sensor;

// rotary encoder
#define ENCODER_TOLERANCE 2
#define ROTATION_STOP 0
#define ROTATION_PLUS 1
#define ROTATION_MINUS -1
#define ENCODER_VALUE_MIN 0
#define ENCODER_VALUE_MAX 255

typedef struct _Type_EncoderBit
{
	// sdi
	int A;
	int B;
	int prev_pinValue;
	int value;
	// value for app
	int prev_appValue;
	int rotation_dir; // 0:stop -1:++ 1:--
} Type_EncoderBit;

// 

