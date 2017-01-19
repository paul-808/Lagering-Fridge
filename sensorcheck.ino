// check data from temperature and humidity sensors

void SensorCheck(){ 
  unsigned long sensorTime = millis();  // Timreading to once per SensorTime 
  if (sensorTime - sensorTime2 > sensorInterval){
    //readingsCount ++;
    lcd.setCursor(19,3);
    lcd.print(" ");
    Temp3 = dht.readTemperature();  // Read sensor
    Hum = dht.readHumidity();
    sensorTime2 = millis();
    
     Temp1 = getTemp1();
     Temp2 = getTemp2();
    
    if (Mode == 1){
      //the next bit calculates a running average of the last n readings. note all readings default to 0, first few readings ramp up.     
      /*totalT= totalT - readingsT[index];         
      readingsT[index] = Temp3; 
      totalT= totalT + readingsT[index];       
      PvT = totalT / numReadings; 
      totalH= totalH - readingsH[index];         
      readingsH[index] = Hum; 
      totalH= totalH + readingsH[index];    
      PvH = totalH / numReadings;     
      index = index + 1;                    
      if (index >= numReadings)              
      index = 0; */
      PvT = Temp3;
      PvH = Hum;
    }
    else {
      PvT = (Temp1 + Temp2) / 2;
      PvH = Hum;
      /*totalH= totalH - readingsH[index];         
      readingsH[index] = Hum; 
      totalH= totalH + readingsH[index];    
      PvH = totalH / numReadings;     
      index = index + 1;                    
      if (index >= numReadings)              
      index = 0; */
    }
    
    
    //clock update
    Time = millis() + TimeAdjust;
    Hours = (Time%86400000)/3600000;
    Minutes = (Time%3600000)/60000;
    Seconds = (Time%60000)/1000;
          
    lcd.setCursor(19,3);
    lcd.printByte(0);   
    
    
    
    if (menu == 0) HomeSetup();
    
    // tRIGGERS!!
    Triggers();
    
    
    
    //Testing
    Serial.print("Time: ");
    //Serial.print(Day,0);
    //Serial.print(" ");
    
      //if(Mode == 0) lcd.print(growthPresetB[preset]);
    if (Hours < 10) Serial.print("0");
    Serial.print(Hours);
    Serial.print(":");
    if (Minutes < 10) Serial.print("0");  
    Serial.print(Minutes);
    Serial.print(":");
    if (Seconds < 10) Serial.print("0");  
    Serial.print(Seconds);
    
    Serial.print("  SvT:");
    Serial.print(SvT,1);
    Serial.print("  PvT:");
    Serial.print(PvT,1);
    Serial.print("  PID:");
    Serial.print(Output); // effectively, seconds per hour (or interval) the fridge will try to be 'on'
    Serial.print("  coolON:");
    Serial.print(coolON);
    Serial.print("  PIDh:");
    Serial.print(Outputh);
    Serial.print("  heatON:");
    Serial.print(heatON);
      
    Serial.print("    cStart:");
    Serial.print(coolWindowStartTime/1000); 
    Serial.print("  cSize:");
    Serial.print(coolWindowSize/1000);    
    Serial.print("  cOff:");
    Serial.print(coolOffElapsed/1000);
    Serial.print("    hStart:");
    Serial.print(heatWindowStartTime/1000); 
    Serial.print("  hSize:");
    Serial.println(heatWindowSize/1000);   


   
  }
}

// Credit to David Gaston for the code below this point - his OneWire projects were used as a base:

float getTemp1(){
  if ( OneWire::crc8( addr1, 7) != addr1[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }
 
 ds.reset();
 ds.select(addr1);
 ds.write(0x44,1); // start conversion, with parasite power on at the end
 
 byte present = ds.reset();
 ds.select(addr1);  
 ds.write(0xBE); // Read Scratchpad
 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data1[i] = ds.read();
 }
 
 MSB = data1[1];
 LSB = data1[0];
 tempRead = ((MSB << 8) | LSB); //using two's compliment
 TemperatureSum = tempRead / 16;
 return TemperatureSum;
 
}

float getTemp2(){
  if ( OneWire::crc8( addr2, 7) != addr2[7]) {
   Serial.println("CRC not valid!");
   return -1000;
 }
 
 ds.reset();
 ds.select(addr2);
 ds.write(0x44,1); // start conversion, with parasite power on at the end
 
 byte present = ds.reset();
 ds.select(addr2);  
 ds.write(0xBE); // Read Scratchpad
 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data2[i] = ds.read();
 }
 
 MSB = data2[1];
 LSB = data2[0];
 tempRead = ((MSB << 8) | LSB); //using two's compliment
 TemperatureSum = tempRead / 16;
 return TemperatureSum;
 
}
