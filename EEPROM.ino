// These functinos write and read key variables from EEPROM memory

void EEPROM_recall(){
  EEPROM_readAnything(0, SvH);
  EEPROM_readAnything(4, SvT);
  EEPROM_readAnything(8, Mode);
//  EEPROM_readAnything(9, preset);
//  EEPROM_readAnything(10, growphase);
  EEPROM_readAnything(11, daysAdj);
  EEPROM_readAnything(12, fanON);
  EEPROM_readAnything(13, fanOFF);
  //EEPROM_readAnything(14, Tolerance);
  EEPROM_readAnything(15, TimeAdjust);
  EEPROM_readAnything(19, LightON);
  EEPROM_readAnything(23, LightOFF);
  EEPROM_readAnything(27, dutyCycle);
  EEPROM_readAnything(31, Kp);
  EEPROM_readAnything(35, Ki);
  EEPROM_readAnything(39, Kd);
  //EEPROM_readAnything(31, minCool);
}

void EEPROM_record(){
  EEPROM_writeAnything(0, SvH);
  EEPROM_writeAnything(4, SvT);
  EEPROM_writeAnything(8, Mode);
//  EEPROM_writeAnything(9, preset);
//  EEPROM_writeAnything(10, growphase);
  EEPROM_writeAnything(11, daysAdj);
  EEPROM_writeAnything(12, fanON);
  EEPROM_writeAnything(13, fanOFF);
  //EEPROM_writeAnything(14, Tolerance);
  EEPROM_writeAnything(15, TimeAdjust);
  EEPROM_writeAnything(19, LightON);
  EEPROM_writeAnything(23, LightOFF);
  EEPROM_writeAnything(27, dutyCycle);
  EEPROM_writeAnything(31, Kp);
  EEPROM_writeAnything(35, Ki);
  EEPROM_writeAnything(39, Kd);
  //EEPROM_writeAnything(31, minCool);
}

