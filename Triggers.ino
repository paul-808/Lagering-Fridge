
// Triggers checks the PID algorithms and timers, and decides whether to change the state of any of the relays

void Triggers (){
  
    // temp - PID
    coolPID.Compute();
    if(millis() - coolWindowStartTime > coolWindowSize)
        { //time to shift the Relay Window
          coolWindowStartTime += coolWindowSize;  }
          
    heatPID.Compute();
    if(millis() - heatWindowStartTime > heatWindowSize)
        { //time to shift the Relay Window
          heatWindowStartTime += heatWindowSize;   }         
    
    // temp - logic      
    if(Output > (millis() - coolWindowStartTime)/1000 && Output > 2 && (millis() - coolOffElapsed) > minCool*60000) coolON = 1;
    else {
       if (coolON == 1) coolOffElapsed = millis(); 
       coolON = 0; 
    }
    if(Outputh > (millis() - heatWindowStartTime)/1000 && Outputh > 2) heatON = 1;
    else heatON = 0;   
    
    // temp - pins
    if (coolON == 1) {
      digitalWrite(ControlCpin, LOW);
      } 
    else {
      digitalWrite(ControlCpin, HIGH);
      }
    
    if (heatON == 1) digitalWrite(ControlHpin, LOW);
    else digitalWrite(ControlHpin, HIGH);      
    
    //hum on 
    //hum off   

    // lights
    if ( (millis()+TimeAdjust)%86400000 > LightON && (millis()+TimeAdjust)%86400000 < LightOFF){
       digitalWrite(ControlLpin, LOW); }
    else {
       digitalWrite(ControlLpin, HIGH); }
    
    // fans
    if (fanOFF > 0){
      //If off, check for ON criteria
      if((millis() - fanOFFmillis) > (fanOFF * 60000) && fanstate == false && coolON == 1){
         digitalWrite(ControlApin, LOW);
         fanOFFmillis = millis();
         fanONmillis = millis();
         fanstate = true;
       }
      //if on, check ffor OFF criteria 
      if((millis() - fanONmillis) > (fanON * 60000) && fanstate == true){
         digitalWrite(ControlApin, HIGH);
         fanONmillis = millis();
         fanOFFmillis = millis();
         fanstate = false;
       }    
    }
    else {
      int x = PvT - Temp3 ;  
      if(FanAuto == 0 && abs(x) > 3) //fan on when temp diff is >3 high 
         digitalWrite(ControlApin, LOW);
      else digitalWrite(ControlApin, HIGH);
         //lcd.setCursor(15,0);
    }
    
    //brewtimer
    
    if (brewtimerON == 1 && millis() > brewtimerRef + (brewtimer * 60000)){
      brewtimerON = 0;
      SvT = brewtimerSv;}
    
    //backlight
    if(millis() - backlighton > backlighttime && menu == 0){
      lcd.noBacklight();
      pulselast = pulses;
    }
    else lcd.backlight();
    
    delay(50);
}      
      
