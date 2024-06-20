/*

void updateLCD(void)
{
    //EraceLCD(0, 0, 16); 
    //EraceLCD(0, 1, 16); 
    int i;

    for(i=0; i<NUM_HC166; i++){
      PrintInt2DigitHEX((unsigned int) gbHC166Data[i], i*3, 0);
      lcd.print(",");
    }

    #if (0)
    for(i=0; i<NUM_HC595; i++){
      PrintInt2DigitHEX((unsigned int) gbHC595Data[i], i*3, 1);
      lcd.print(",");
    }
    #else
    //PrintInt2Digit(gbSignal[0].status, 0, 1);
    //PrintInt2Digit(gbCrossing[0].status, 4, 1);
    //PrintInt2Digit(gbCrossing[0].led1, 8, 1);
    //PrintInt2Digit(gbSignal[0].color, 12, 1);
    //PrintInt2Digit(gbSignal[0].color, 0, 1);
    //PrintInt2Digit(gbSignal[1].color, 4, 1);
    EraceLCD(0, 1, 8);
    PrintBinLCD((unsigned char) gbHC166Data[2]);
    {
      unsigned int gbTrainSensorNo=0;
      if((gbHC166Data[2]&0xff)!=0xff){
        gbTrainPosition = (~(gbHC166Data[2])) &0xff;
      }
      gbTrainSensorNo = (unsigned int)log2((float)gbTrainPosition)+1;
      PrintInt2Digit(gbTrainSensorNo, 12, 1);
    }
    #endif

    PrintInt2Digit((gbIntCounter/1000)%100, 14, 0);
    EraceLCD(10, 0, 3); // 
    lcd.print( gbTrain.speed );

    return;

    // VR input test
    EraceLCD(0, 1, 8); // 
    lcd.print("TS:");
    lcd.print(gbTrain.speed);

    // serial in test
    //EraceLCD(8, 1, 8); // 
    //PrintBinLCD((unsigned char)gbHC166Data[0]);
    //PrintBinLCD((unsigned char)gbHC166Data[0]);
    
    // serial in test
    //EraceLCD(8, 0, 8); // 
    //lcd.print(gbEncoderTestValue);

    //
    EraceLCD(8, 0, 4); // 
    lcd.print(gbCtrlButton[0].status);
    lcd.print(gbCtrlButton[1].status);

    // train direction
    EraceLCD(12, 0, 4); // 
    if(gbTrain.direction==TRAIN_DIRECTION_CLOCKWISE){
      lcd.print("[->]");
    }
    else{
      lcd.print("[<-]");
    }
}

























*/