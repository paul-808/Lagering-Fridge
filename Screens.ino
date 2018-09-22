// loadScreen defines the cute animations on startup! Note that nothing actually loads as load time is less than a tenth of a second.

void LoadScreen (){
  lcd.clear();
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print(" LaggerLogger "); 
  lcd.printByte(0);
  lcd.setCursor(0,1);
  lcd.print(" V2.0 Beepboop!"); 
  delay(3000);
  lcd.clear();
 }


//write the home screen to the LCD with current data about the brew

void HomeSetup(){

  //print status
  lcd.setCursor(16,1);
  if (coolON == 1) lcd.print("C");
  else if (heatON == 1) lcd.print("H");
  else lcd.print(" ");

  //print values
  lcd.setCursor(0,0);
  lcd.printByte(3);
  lcd.print(" ");
  lcd.print(SvTdisplayOld,1);     //svt
  lcd.printByte(1);
  lcd.print(" ");
 
  //Line 4
  lcd.setCursor(0,1);
  lcd.printByte(2);
  lcd.print(" "); 
  lcd.print(PvT,1);   //pvt
  lcd.printByte(1);
  lcd.print(" ");
  
  lcd.setCursor(8,1);
  if (Hours < 10) lcd.print("0");
  lcd.print(Hours);
  lcd.print(":");
  if (Minutes < 10) lcd.print("0");  
  lcd.print(Minutes);
  lcd.print(" ");

  lcd.setCursor(8,0);
  float z = (100*Output/(coolWindowSize/1000));
  lcd.print(z,1);
  lcd.print("% ");     
}
