// These functions are used to interpret input from the rotary encoder and the integrated button

void EncoderTranslate (int x) {  
  pulseMod = (pulses/pulseAdjust) % x; 
}



// ** BUTTON **//
void Button(){  
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) {
      buttontime = millis();
      buttonstate = true;
    } 
    else {
      buttontime = millis() - buttontime;
      buttonstate = false;
      delay(10); 
    }
  }
  lastButtonState = buttonState;
}

// ** INTERRUPT ** //

void A_RISE(){  
 detachInterrupt(0);
 A_SIG=1;
 
 if(B_SIG==0)
 pulses++;//moving forward
 if(B_SIG==1)
 pulses--;//moving reverse
 //Serial.println(pulses);
 attachInterrupt(0, A_FALL, FALLING);
}

void A_FALL(){
  detachInterrupt(0);
 A_SIG=0;
 
 if(B_SIG==1)
 pulses++;//moving forward
 if(B_SIG==0)
 pulses--;//moving reverse
 //Serial.println(pulses);
 attachInterrupt(0, A_RISE, RISING);  
}

void B_RISE(){
 detachInterrupt(1);
 B_SIG=1;
 
 if(A_SIG==1)
 pulses++;//moving forward
 if(A_SIG==0)
 pulses--;//moving reverse
 //Serial.println(pulses);
 attachInterrupt(1, B_FALL, FALLING);
}

void B_FALL(){
 detachInterrupt(1);
 B_SIG=0;
 
 if(A_SIG==0)
 pulses++;//moving forward
 if(A_SIG==1)
 pulses--;//moving reverse
 //Serial.println(pulses);
 attachInterrupt(1, B_RISE, RISING);
}
