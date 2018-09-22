// check data from temperature  sensors

void SensorCheck(){ 
  sensorTime = millis();  
  
  //if interval has passed...
  if (sensorTime - sensorTime2 > sensorInterval){ 
     sensorTime2 = millis();
     Temp1 = getTemp1();
     Temp2 = getTemp2();
    
    //average readings and note the difference
    if(Temp1 > 0 && Temp2 >0) { 
      PvT = (Temp1 + Temp2) / 2;
      tempDiff = abs(Temp1 - Temp2);
    }
    
    //... unless there's only one thermometer...
    else if (Temp1 > 0){  
      PvT = Temp1;
      tempDiff = 0;
    }
    else {
      PvT = 99;
      tempDiff = 0;
    }
    
    //clock update
    Time = millis() + TimeAdjust;
    Hours = (Time%86400000)/3600000;
    Minutes = (Time%3600000)/60000;
    Seconds = (Time%60000)/1000;
          
    //Testing output
    /*
    Serial.print("Time: ");
    if (Hours < 10) Serial.print("0");
    Serial.print(Hours);
    Serial.print(":");
    if (Minutes < 10) Serial.print("0");  
    Serial.print(Minutes);
    Serial.print("  SvT:");
    Serial.print(SvT,1);
    Serial.print("  PvT:");
    Serial.print(PvT);Serial.print("/");Serial.print(Temp1);Serial.print("/");Serial.print(Temp2);
    Serial.print("  PID:");
    Serial.print(Output); 
    Serial.print("  Against: ");
    Serial.print(PIDpos); 
    Serial.print("  Rest:");
    Serial.print("180"); 
    Serial.print("  coolON:");
    Serial.print(coolON);
    Serial.print("  Fan:");
    Serial.println(fanstate);
    */
    }
}

float getTemp1(){
 sensors.requestTemperatures();
 float z = sensors.getTempCByIndex(0);
 return z;
 }

float getTemp2(){
 sensors.requestTemperatures();
 float z = sensors.getTempCByIndex(1);
 return z;
 }
