// LCD
extern void EraceLCD(int posx, int posy, int numOfChar);
extern void PrintInt2Digit(int value, int px, int py);
extern void PrintInt3Digit(int value, int px, int py);
extern void PrintInt4Digit(int value, int px, int py);
extern void PrintBinLCD(unsigned char bindata);

extern void MySerialOutput( void );
extern void MySerialInput( void );
extern void GetSpeedVr( void );
extern void HandleEncoder(void);
extern void DrivePoint(void);

