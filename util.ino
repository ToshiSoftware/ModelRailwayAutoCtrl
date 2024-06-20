// utility
// LCD display
//

// LCD
// Utility: Erace LCD Chars (fill with space)
void EraceLCD(int posx, int posy, int numOfChar)
{
  int i;
  lcd.setCursor(posx, posy);
  for(i=0; i<numOfChar; i++)
  {
    lcd.print(" ");
  }
  lcd.setCursor(posx, posy);
}

// print 8bit binary to LCD
void PrintBinLCD(unsigned char bindata)
{
  int i;
  unsigned char tmp;
  tmp = bindata;
  for(i=0;i<8;i++){
    if(tmp&0x80) lcd.print("1");
    else lcd.print("0");
    tmp = tmp<<1;
  }
}

// print 2 digit integer with justifing to the right
void PrintInt2Digit(int value, int px, int py){
  int tmp;
  
  EraceLCD(px, py, 2);
  tmp=value;
  tmp%=100;
  if(tmp<10) lcd.print("0");
  lcd.print(tmp);
}

// print 2 digit integer with justifing to the right
void PrintInt2DigitHEX(unsigned int value, int px, int py){
  unsigned int tmp;
  char display[16];
  
  EraceLCD(px, py, 2);
  tmp=value;
  tmp = (tmp & 0xff);
  sprintf( display, "%02x", tmp );
  lcd.print(display);
}

// print 3 digit integer with plus/minus display
void PrintInt3DigitPlusMinus(int value, int px, int py){
  int tmp;
  
  EraceLCD(px, py, 3);
  if(value<-9){
    lcd.print(value);
  }
  else if(value<0)
  {
    lcd.print("-0");
    lcd.print(value-1);
  }
  else if(value==0)
  {
    lcd.print(" 00");
  }
  else if(value<10)
  {
    lcd.print("+0");
    lcd.print(value);
  }
  else //if(value<51)
  {
    lcd.print("+");
    lcd.print(value);
  }
}

// print 3 digit integer with justifing to the right
void PrintInt3Digit(int value, int px, int py){
  int tmp;
  
  EraceLCD(px, py, 4);
  tmp=value;
  tmp%=1000;
  if(tmp<100) lcd.print("0");
  if(tmp<10) lcd.print("0");
  lcd.print(tmp);
}

// print 4 digit integer with justifing to the right
void PrintInt4Digit(int value, int px, int py){
  int tmp;
  
  EraceLCD(px, py, 4);
  tmp=value;
  tmp%=10000;
  if(tmp<1000) lcd.print("0");
  if(tmp<100) lcd.print("0");
  if(tmp<10) lcd.print("0");
  lcd.print(tmp);
}
