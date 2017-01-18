// All menu options are defined below. Note this system is flexible and easily applicable to other projects on small screents, particularly where an encoder is used to navigate menus. 

void Menus(){
  
  switch (menu) {
      case 0:  // home screen (displays values)
          SensorCheck();
          //Triggers(); //RUN from within sensorcheck
      if(pulselast != pulses){
          lcd.backlight();
          backlighton = millis();}
      if(buttonstate == true  && (millis() - buttontimeon) > 2000){   
          lcd.clear();
          lcd.backlight();
          backlighton = millis();
          Loading();
          pulses = 9000;
          buttontimeon = millis();
          buttonstate = false;
          menu = 10;
          }
          break;


      case 10:
          EncoderTranslate(9);
          lcd.setCursor(0, 0);
          lcd.print("Menu: Home");
          lcd.setCursor(1, 1);
          lcd.write(0x7E);
          
          switch(selector) {
           case 7:
            lcd.print(mainMenu[selector]);
            lcd.setCursor(2, 2);
            lcd.print(mainMenu[selector+1]);
            lcd.setCursor(2, 3);
            lcd.print(mainMenu[0]);
           break;
           case 8:
            lcd.print(mainMenu[selector]);
            lcd.setCursor(2, 2);
            lcd.print(mainMenu[0]);
            lcd.setCursor(2, 3);
            lcd.print(mainMenu[1]);
           break;
           default:
            lcd.print(mainMenu[selector]);
            lcd.setCursor(2, 2);
            lcd.print(mainMenu[selector+1]);
            lcd.setCursor(2, 3);
            lcd.print(mainMenu[selector+2]);
          }
          //delay (10);
          selector = pulseMod;
                   

          if(buttonstate == true) {
            selectorprev = pulseMod;
            lcd.clear();
            buttonstate = false;
            delay(100);
            switch (selectorprev) {
              case 0: Loading(); HomeSetup(); menu = 0; break;
              case 1: pulses = brewtimer*4; Loading(); menu = 20;  break; //program
              case 2: pulses = (SvT * 40); Loading();  menu = 30; break; //manual
              case 3: pulses = dutyCycle*2; Loading(); menu = 50;  break; //
              case 4: pulses = (fanON * 5); Loading(); menu = 60;  break;
              case 5: pulses = (TimeAdjust / 60000);  Hours = (Time%86400000)/3600000; Minutes = (Time%3600000)/60000;Loading(); menu = 70;  break;
              case 6: Loading(); menu = 80;  break;
              case 7: if (Mode == 1) menu = 90; if (Mode == 0) menu = 92; pulseprev = pulses; break; //save settings
              case 8: menu = 100;  break; //save settings
              delay (50);
            }   
          }
     break;
      
    

     
      case 20: 
          brewtimerON = 1;
          lcd.setCursor(3, 0);
          lcd.print("In ");
          lcd.write(0x7E);
          lcd.print(brewtimer);
          lcd.print(" hours,  ");
          lcd.setCursor(6, 1);
          lcd.print("(");
          lcd.print(brewtimer / 24);
          lcd.print("Days)");
          lcd.setCursor(1, 2);
          lcd.print("Set temperature to:");
          lcd.setCursor(8, 3);
          lcd.print(brewtimerSv,1);
          lcd.print("  ");
          
          pulseprev = pulses;
          brewtimer = (pulseprev/4);
          
          if(brewtimer - (millis()/3600000) < 0 ) brewtimer = millis()/3600000;
          
          if(buttonstate == true) {
            pulses = (brewtimerSv * 40);
            brewtimerRef = millis();
            if (brewtimer > 0) brewtimerON = 1;
            delay(500);
            menu = 21;
          }
      break;

      case 21:
        
          lcd.setCursor(6, 0);
          lcd.print(" ");
          lcd.setCursor(7, 3);         
          lcd.write(0x7E);
          lcd.print(brewtimerSv,1);
          lcd.printByte(1);
          
          pulseprev = pulses;
          brewtimerSv = (pulseprev/40);
          
          if(buttonstate == true) {
                goHome();
          }
      break;
    
      
      
      case 30: 
          lcd.setCursor(1, 1);
          lcd.write(0x7E);
          lcd.setCursor(2, 1);
          lcd.print("Set Temp: ");
          lcd.setCursor(12, 1);
          lcd.print(SvT,2);
          lcd.printByte(1);
          lcd.print(" ");

          lcd.setCursor(2, 2);
          lcd.print("Set Hum%: ");
          lcd.setCursor(12, 2);
          lcd.print(SvH,0);
          lcd.printByte(2);
          
          pulseprev = pulses;
          SvT = (pulseprev/40);
          
          if(buttonstate == true) {
            buttonstate = false;
            pulses = (SvH * 4);
            delay(500);
            menu = 32;
          }
      break;

      case 32:
          lcd.setCursor(1, 1);
          lcd.print(" ");
          lcd.setCursor(1, 2);
          lcd.write(0x7E);
          lcd.setCursor(2, 2);
          lcd.print("Set Hum%: ");
          lcd.setCursor(12, 2);
          lcd.print(SvH,0);
          lcd.printByte(2);
          lcd.print(" ");
          
          pulseprev = pulses;
          SvH = (pulseprev/4);
          
          if(buttonstate == true) {
            goHome();
          }
      break; 
      
      
      
      case 50: 
          lcd.setCursor(1, 0);
          lcd.print("DutyCycle:");
          lcd.setCursor(1, 1);
          lcd.print("Begin autotune?");
          lcd.setCursor(1, 2);
          lcd.print("Manual tune");
          lcd.setCursor(1, 3);
          lcd.print("Exit");
                    
          lcd.setCursor(12, 0);
          lcd.print(dutyCycle,0);
          lcd.print(" min ");
          delay (10);
          
          EncoderTranslate(4);
          submenu = pulseMod;
          
          switch(submenu){
          case 0:
            lcd.setCursor(0, 0);
            lcd.write(0x7E);
            lcd.setCursor(0, 1);
            lcd.print(" ");
            lcd.setCursor(0, 2);
            lcd.print(" ");
            lcd.setCursor(0, 3);
            lcd.print(" ");
            if(buttonstate == true) {
              buttonstate = false;
              pulses = dutyCycle*4;
              menu = 51;
            }
            break; 
          case 1:
            lcd.setCursor(0, 0);
            lcd.print(" ");
            lcd.setCursor(0, 1);
            lcd.write(0x7E);
            lcd.setCursor(0, 2);
            lcd.print(" ");
            lcd.setCursor(0, 3);
            lcd.print(" ");
            if(buttonstate == true) {
              buttonstate = false;
              lcd.clear();
              menu = 52;
            }
            break;    
          case 2:
            lcd.setCursor(0, 0);
            lcd.print(" ");
            lcd.setCursor(0, 1);
            lcd.print(" ");
            lcd.setCursor(0, 2);
            lcd.write(0x7E);
            lcd.setCursor(0, 3);
            lcd.print(" ");
            if(buttonstate == true) {
              pulses = Kp * 40;
              lcd.clear();
              buttonstate = false;
              menu = 53;
            }
            break;             
          case 3:
            lcd.setCursor(0, 0);
            lcd.print(" ");
            lcd.setCursor(0, 1);
            lcd.print(" ");
            lcd.setCursor(0, 2);
            lcd.print(" ");
            lcd.setCursor(0, 3);
            lcd.write(0x7E);
            if(buttonstate == true) {
              goHome();
            }
           break; } 
            
      break;         
      
      case 51:

          lcd.setCursor(11, 0);
          lcd.write(0x7E);
          lcd.print(dutyCycle,0);
          lcd.print(" min ");
          
          pulseprev = pulses;
          dutyCycle = (pulseprev/4);

          if(buttonstate == true) {
            lcd.setCursor(11, 0);
            lcd.print(" ");
            coolWindowSize = dutyCycle * 60000; 
            coolOffElapsed = millis();
            buttonstate = false;
            menu = 50;
          }    
      break;      
      case 52:

          
          lcd.setCursor(0, 1);
          lcd.print("Begin (est ");
          lcd.print((dutyCycle*4),0);
          lcd.print(" min)");
          
              EncoderTranslate(2);
              submenu = pulseMod;
              lcd.setCursor(8, 2);
              lcd.write(0x7E);
              lcd.print(YesNo[submenu]);

          if(buttonstate == true && submenu == 0) {
            //insert autotune
            goHome();
          }
          if(buttonstate == true && submenu == 1) {
            goHome();
          }     
      break;  
      case 53: 
          lcd.setCursor(0, 0);
          lcd.write(0x7E);          
          lcd.setCursor(1, 0);
          lcd.print("Kp: ");
          lcd.print(Kp,2);
          lcd.setCursor(1, 1);
          lcd.print("Ki: ");
          lcd.print(Ki,2);
          lcd.setCursor(1, 2);
          lcd.print("Kd: ");
          lcd.print(Kd,2);
          lcd.setCursor(1, 3);
 
        
        pulseprev = pulses;
        Kp = (pulseprev/40);
        
         if(buttonstate == true) {
          buttonstate = false;
          pulses = Ki * 40;
          lcd.setCursor(0, 0);
          lcd.print(" ");
          lcd.setCursor(0, 1);
          lcd.write(0x7E);          
          menu = 54;
         }
      break; 
      
      
      case 54: 
      lcd.setCursor(5, 1);
      lcd.print(Ki,2);
        pulseprev = pulses;
        Ki = (pulseprev/40);
       if(buttonstate == true) {
          buttonstate = false;
          pulses = Kd * 40;
          lcd.setCursor(0, 1);
          lcd.print(" ");
          lcd.setCursor(0, 2);
          lcd.write(0x7E);          
          menu = 55;
       }      
      break;
     
       case 55: 
      lcd.setCursor(5, 2);
      lcd.print(Kd,2);
        pulseprev = pulses;
        Kd = (pulseprev/40);
       if(buttonstate == true) {
         coolPID.SetTunings(Kp,Ki,Kd);
         goHome();
       }      
      break;     
          
      case 60:
          lcd.setCursor(0, 1);
          lcd.print("Fan RUN for:");
          lcd.setCursor(12, 1);
          lcd.write(0x7E);
          lcd.setCursor(13, 1);
          lcd.print(fanON);
          lcd.print(" min");
          lcd.setCursor(0, 2);
          lcd.print("Fan OFF for:");
          lcd.setCursor(13, 2);
          lcd.print(fanOFF);
          lcd.print(" min");
          delay (10);
          
          pulseprev = pulses;
          fanON = (pulseprev/4);
          
          if(buttonstate == true) {
          buttonstate = false;
            lcd.setCursor(12, 1);
            lcd.print(" ");
            lcd.setCursor(12, 2);
            lcd.write(0x7E);
            pulses = (fanOFF * 5);
            menu = 61;
          }

      break;
      case 61:
          lcd.setCursor(13, 2);
          lcd.print(fanOFF);
          lcd.print(" min");
          delay (10);
          
          pulseprev = pulses;
          fanOFF = (pulseprev/4);
          
          if(buttonstate == true) {
            buttonstate = false; 
            lcd.clear();
            menu = 62;}
      break;
      
      case 62:
          lcd.setCursor(0,0);
          lcd.print("Run fan when ");
          lcd.setCursor(0,1);
          lcd.print("sensors disagree?");
          delay (10);
          
              EncoderTranslate(2);
              FanAuto = pulseMod;
              lcd.setCursor(3, 3);
              lcd.write(0x7E);
              lcd.print(OnOff[FanAuto]);

          if(buttonstate == true) goHome();         
      break;
      
      
      case 70: 
          lcd.setCursor(0, 0);
          lcd.print("Current time: ");
          lcd.write(0x7E);
          lcd.setCursor(1, 2);
          lcd.print("Lights on: ");
          lcd.setCursor(1, 3);
          lcd.print("Lights off:");
          
          Time = millis() + TimeAdjust;
          Hours = (Time%86400000)/3600000;
          Minutes = (Time%3600000)/60000;
          
          lcd.setCursor(15, 0);
          if (Hours < 10) lcd.print("0");
          lcd.print(Hours);
          lcd.print(":");
          if (Minutes < 10) lcd.print("0");  
          lcd.print(Minutes);
          delay (10);
          
          pulseprev = pulses;
          TimeAdjust = pulseprev * 60000;
          
          if (TimeAdjust > 86400000){
          TimeAdjust = 60000;
          pulses = 1; }
          if (TimeAdjust < 60000){
          TimeAdjust = 86400000;
          pulses = 1440; }

          if(buttonstate == true) {
            buttonstate = false;
            lcd.setCursor(14, 0);
            lcd.print(" ");
            pulses = (LightON / 60000);
            menu = 71;
          }
      break;
      
      case 71: 
          Hours = (LightON%86400000)/3600000;
          Minutes = (LightON%3600000)/60000;

          lcd.setCursor(14, 2);
          lcd.write(0x7E);
          
          
          lcd.setCursor(15, 2);
          if (Hours < 10)
            {lcd.print("0");}
          lcd.print(Hours);
          lcd.print(":");
          if (Minutes < 10)
            lcd.print("0");  
          lcd.print(Minutes);
          delay (10);
          
          pulseprev = pulses;
          LightON = pulseprev * 60000;
          
          if (LightON > 86400000){
          LightON = 60000;
          pulses = 1; }
          if (LightON < 60000){
          LightON = 86400000;
          pulses = 1440; }
          
          if(buttonstate == true) {
            buttonstate = false;
            lcd.setCursor(14, 2);
            lcd.print(" ");
            pulses = (LightOFF / 60000);
            menu = 72;
          }
      break;
      
      case 72: 
          Hours = (LightOFF%86400000)/3600000;
          Minutes = (LightOFF%3600000)/60000;
          lcd.setCursor(14, 3);
          lcd.write(0x7E);
                 
          lcd.setCursor(15, 3);
          if (Hours < 10) lcd.print("0");
          lcd.print(Hours);
          lcd.print(":");
          if (Minutes < 10) lcd.print("0");  
          lcd.print(Minutes);
          delay (10);
          
          pulseprev = pulses;
          LightOFF = pulseprev * 60000;
          
          if (LightOFF > 86400000){
          LightOFF = 60000;
          pulses = 1; }
          if (LightOFF < 60000){
          LightOFF = 86400000;
          pulses = 1440; }
          
          if(buttonstate == true){ 
            // Return clock vars to time (from lightoff)
            Time = millis() + TimeAdjust;
            EEPROM_record();
            Hours = (Time%86400000)/3600000;
            Minutes = (Time%3600000)/60000;
            goHome();}
      break;
          
      case 80: 

          lcd.setCursor(0, 0);
          lcd.print("Sensor summary:");
          lcd.print((100*Output/1800000),0);
          lcd.print("%");
          lcd.setCursor(0, 1);
          lcd.print("DHT22: ");
          lcd.print(Temp3,1);
          lcd.printByte(1);
          lcd.setCursor(13, 1);
          
          lcd.print(Hum,0);
          lcd.printByte(2);
          lcd.setCursor(0, 2);
          lcd.print("Temp1: ");lcd.print(Temp1,1);
          lcd.printByte(1);
          lcd.setCursor(0, 3);
          lcd.print("Temp2: ");lcd.print(Temp2,1);
          lcd.printByte(1); 
 
          SensorCheck();         
          
          if(buttonstate == true) {
             goHome();
          }
          
      break;     
      
      case 90:
        lcd.setCursor(1, 1);
        lcd.write(0x7E);
        lcd.setCursor(1, 2);
        lcd.print(" ");       
        lcd.setCursor(2, 1);
        lcd.print("Go to brew mode!");
        lcd.setCursor(2, 2);
        lcd.print("Cancel");
        
        if(abs((pulseprev - pulses)) > 3){
          menu = 91;
          pulseprev = pulses;
        } 
        
        if(buttonstate == true) {
             buttonstate = false; 
             Loading();
             lcd.setCursor(0, 0);
             for( int x = 0; x < 20; x++){
             lcd.printByte(0);}
             lcd.setCursor(0, 3);
             for( int x = 0; x < 20; x++){
             lcd.printByte(0);}
             lcd.setCursor(1, 1);
             lcd.print("IT'S BREWIN' TIME!");
             lcd.setCursor(2, 2);
             lcd.print("*glug glug glug*");
             delay(3000);
             sensorTime2 = millis();
             Mode = 0;
             //preset = 0;
             EEPROM_writeAnything(8, Mode);
             goHome();
        }
        
      break;
      
      case 91:
        lcd.setCursor(1, 1);
        lcd.print(" ");
        lcd.setCursor(1, 2);
        lcd.write(0x7E);
        
        if(abs((pulseprev - pulses)) > 3){
          menu = 90;
          pulseprev = pulses;
        } 
        
        if(buttonstate == true) {
             goHome();
        }
      break;
      
      case 92:
        lcd.setCursor(1, 1);
        lcd.write(0x7E);
        lcd.setCursor(1, 2);
        lcd.print(" ");       
        lcd.setCursor(2, 1);
        lcd.print("Go to grow mode!");
        lcd.setCursor(2, 2);
        lcd.print("Cancel");
        
        if(abs((pulseprev - pulses)) > 20){
          menu = 93;
          pulseprev = pulses;
        } 
        
        if(buttonstate == true) {
             Loading();
             lcd.setCursor(0, 0);
             for( int x = 0; x < 20; x++){
             lcd.printByte(0);}
             lcd.setCursor(0, 3);
             for( int x = 0; x < 20; x++){
             lcd.printByte(0);}
             lcd.setCursor(1, 1);
             lcd.print("IT'S GROWIN' TIME!");
             lcd.setCursor(2, 2);
             lcd.print("*nom nom nom nom*");
             delay(3000);
             Mode = 1;
             //preset = 0;
             EEPROM_writeAnything(8, Mode);
             goHome();
        }
        
      break;
      
      case 93:
        lcd.setCursor(1, 1);
        lcd.print(" ");
        lcd.setCursor(1, 2);
        lcd.write(0x7E);
        
        if(abs((pulseprev - pulses)) > 20){
          menu = 90;
          pulseprev = pulses;
        } 
        
        if(buttonstate == true) {
             goHome();
        }
      break;
      
      case 100:
            EEPROM_record();
            lcd.clear();
            lcd.setCursor(3, 1);
            lcd.print("Settings Saved");
            lcd.setCursor(7, 2);
            lcd.printByte(0);
            lcd.printByte(0);
            lcd.printByte(0);
            delay (1000);
            goHome();
     break;
     
     delay (50);
  }
}
