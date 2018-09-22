// These functinos write and read key variables from EEPROM memory

void EEPROM_recall(){
  EEPROM_readAnything(4, SvT);
  EEPROM_readAnything(11, daysAdj);
  EEPROM_readAnything(15, TimeAdjust);

}

void EEPROM_record(){
  EEPROM_writeAnything(4, SvT);
  EEPROM_writeAnything(11, daysAdj);
  EEPROM_writeAnything(15, TimeAdjust);

}

