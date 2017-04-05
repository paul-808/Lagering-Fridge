// goHome returns the interface to the home screen, and resets the navigation

void goHome (){
   buttonstate = false; 
   sensorTime2 = millis();
   Loading();
   HomeSetup(); 
   menu = 0;
}

// loadScreen defines the cute animations on startup! Note that nothing actually loads as load time is less than a tenth of a second.
void LoadScreen (){
  lcd.clear();
  lcd.home();
  lcd.setCursor(1,0);
  lcd.printByte(0);
  lcd.print("  o88b          "); 
  lcd.printByte(0);
  lcd.setCursor(0,1);
  lcd.printByte(0);
  lcd.print("  _| 9p  Lager    "); 
  lcd.printByte(0);
  lcd.setCursor(0,2);
  lcd.printByte(0);
  lcd.print("  []  [   Logger  ");
  lcd.printByte(0); 
  lcd.setCursor(1,3);
  lcd.printByte(0);
  lcd.print("  [__]    v0.9  ");  
  lcd.printByte(0);
  delay(100);
  
  for(int x = 0; x < 3; x++){ 
   lcd.setCursor(5,1);
   lcd.printByte(7);
   lcd.setCursor(5,2);
   lcd.printByte(4)
   lcd.setCursor(5,3);
   lcd.printByte(3);
   lcd.setCursor(6,2);
   lcd.printByte(5);
   lcd.setCursor(6,3);
   lcd.printByte(4)
   delay(400);
   lcd.setCursor(5,1);
   lcd.printByte(3);
   lcd.setCursor(5,2);
   lcd.printByte(6)
   lcd.setCursor(5,3);
   lcd.printByte(4);
   lcd.setCursor(6,2);
   lcd.printByte(3);
   lcd.setCursor(6,3);
   lcd.printByte(2)
   delay(400);
   lcd.setCursor(5,1);
   lcd.printByte(4);
   lcd.setCursor(5,2);
   lcd.printByte(3)
   lcd.setCursor(5,3);
   lcd.printByte(5);
   lcd.setCursor(6,2);
   lcd.printByte(1);
   lcd.setCursor(6,3);
   lcd.printByte(3)
   delay(400);
    
    // Section below populates sensor averaging array with current values
    /*totalT= totalT - readingsT[index];         
    readingsT[index] = dht.readTemperature(); 
    totalT= totalT + readingsT[index];       
    PvT = totalT / numReadings; 
    totalH= totalH - readingsH[index];         
    readingsH[index] = dht.readHumidity(); 
    totalH= totalH + readingsH[index];    
    PvH = totalH / numReadings;     
    index = index + 1;                    
    if (index >= numReadings)              
    index = 0; */
    
  }
  lcd.clear();
}






//write the home screen to the LCD with current data about the brew
void HomeSetup(){
  
  Day = millis()/86400000;
  //Line 1
  lcd.setCursor(0,0);
  if(Mode == 1) lcd.print("Growing");
  if(Mode == 0) lcd.print("Brewing");
  lcd.setCursor(13,0);
  if (coolON == 1) lcd.print("Cool");
  else if (heatON == 1) lcd.print("Heat");
  else lcd.print("    ");
  /*lcd.print(Hours);
  lcd.print(":");
  if (Minutes < 10) lcd.print("0");  
  lcd.print(Minutes);*/


  //Line 2
  lcd.setCursor(0,1);
  lcd.print("___________");
  lcd.print("  ");
  lcd.print("_______"); 
  //Line 3
  lcd.setCursor(0,2);
  lcd.printByte(7);
  lcd.print(" ");
  lcd.print(SvT,1);     //svt
  lcd.printByte(1);
  lcd.setCursor(8,2);
  lcd.print(SvH,0);     //svh no decimal
  lcd.printByte(2);
  lcd.setCursor(13,2); 
  lcd.print("Day:"); //time
    if((Day - daysAdj) < 10){
    lcd.setCursor(18,2);
    lcd.print("0"); }  
    if((Day - daysAdj) > 9 && Day < 100)
    lcd.setCursor(18,2); 
    if ((Day - daysAdj) > 99)
    lcd.setCursor(17,2); 
  lcd.print((Day - daysAdj),0);
  
  //Line 4
  lcd.setCursor(0,3);
  lcd.printByte(6);
  lcd.print(" "); 
  lcd.print(PvT,1);   //pvt
  lcd.printByte(1);
  lcd.setCursor(8,3);
  lcd.print(PvH,0);//pvh
  lcd.printByte(2);
  lcd.setCursor(13,3);
  //if(Mode == 1) lcd.print(growthPreset[preset]);
  //if(Mode == 0) lcd.print(growthPresetB[preset]);
  if (Hours < 10) lcd.print("0");
  lcd.print(Hours);
  lcd.print(":");
  if (Minutes < 10) lcd.print("0");  
  lcd.print(Minutes);
  lcd.print(" ");
}

// a cute loading animation!
void Loading (){
            lcd.clear();          
            for (byte LoadPos = 1; LoadPos <19; LoadPos++){
              lcd.setCursor(LoadPos, 1);
              lcd.printByte(0);
              lcd.setCursor(LoadPos, 2);
              lcd.printByte(0);
              delay (20);
            }
            delay (200);
            lcd.clear();
}


