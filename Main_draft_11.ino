
//**************************************************************//
//  Name    : LAGERLOGGER! (With IC2 display)                            
//  Author  : Paul Jarvey
//  Date    : 5 Oct, 2013    
//  Modified: 17 Jan, 2017                                
//  Version : BETA 0.8                                             
//  Notes   : 20x4 lc2 display, DHT22 temp/hum mon, 
//          : control via rotary encoder, and 4 output controls     
//          : note to self - control backlight with   lcd.setBacklight(1)
//          : screen connected  : SDA >> A4 , SCL >> A5
//****************************************************************

//redefine how compiler understands "B_SIG", "A_SIg"
unsigned int pulses = 0, A_SIG=0, B_SIG=1;
int pulseAdjust = 4;

// Call libraries for display, sensor, I2C, and memory. Library setup included as well.
#include <avr/pgmspace.h>
char buffer[20];

#include <OneWire.h> 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4); 
#include <DHT.h>
#include <EEPROM.h>
#include "EEPROMAnything.h"


// Special Characters for the display and display animations
#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

uint8_t heart[8] = { 0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t deg[8] = { 0x1c,0x14,0x1c,0x0,0x3,0x4,0x4,0x3};
uint8_t hum[8] = { 0x12,0x4,0x9,0x0,0x4,0x7,0x5,0x5};
uint8_t up1[8] = { 0x10,0x14,0x2,0x10,0x0,0x2,0x10,0x0};
uint8_t up2[8] = { 0x0,0x2,0x10,0x0,0x2,0x10,0xa,0x0};
uint8_t up3[8] = { 0x2,0x10,0x0,0x2,0x10,0x0,0x2,0x10};
uint8_t Pv[8] = { 0x1c,0x14,0x1c,0x10,0x10,0x5,0x5,0x2};
uint8_t Sv[8] = { 0xc,0x10,0x8,0x4,0x18,0x5,0x5,0x2};
// end special chars 

// Sensor pins:
#define DHTPIN 4
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);

//user i/o pins
const int buttonPin = 11;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to (for status)



//************* Begin Libraries Setup ***************//

const char* OnOff[3] = {
"ON  ",
"OFF ",
"AUTO"}; 

const char* YesNo[2] = {
"Yes",
"No "}; 


const char* mainMenu[9] = {
"Exit            ",
"Program sequence",
"Set temp/hum    ", 
"Options & PID",
"Fan timer    ",
"Light timer     ",
"View sensor data",
"Brew/grow mode  ", 
"Save settings "};




//************* Begin Variables Setup ***************//

//Sensors (ds18s20 needs additional chatter)
int DS18S20_Pin = 5; //DS18S20 Signal pin on digital 2
  byte addr1[8]= {0x28, 0x48, 0xAE, 0x3C, 0x05, 0x00, 0x00, 0x34};
  byte addr2[8]= {0x28, 0xC7, 0xCD, 0x4C, 0x05, 0x00, 0x00, 0x0D};
  byte data1[12];
  byte data2[12];
  byte MSB = 0;
  byte LSB = 0; 
  float tempRead = 0;
  float TemperatureSum = 0;
  OneWire ds(DS18S20_Pin);
  
//controller outputs
int ControlCpin = 9; // control to fridge
int ControlTpin = 7; // control to temperature/heater  (get aquarium heater)
int ControlHpin = 8; // control to humidifier
int ControlLpin = 6; // control to light
int ControlApin = 10; // control to airflow

//operational vars (the button)
//int buttonPushCounter = 0;   // counter for the number of button presses DEPRACATED
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
boolean buttonstate = false; // calculastate of the button (includes timer delay. use this in menus)
int buttontime = 0;          // press length measure 
int buttontimeon = 0;        // necessary for press length measure 

//operational vars (the rotary)
int pulseMod = 0;            // modulus to reduce scroll speed
int pulseprev = 0;         // to measure change in rotary position
int pulselast = 0;         // backlight onoff
//operational vars (the menus and presets)
byte menu = 0;               // defines current screen (used in cases in main loop)
byte submenu = 0;            // defines submenu screen (used in cases in main loop)
byte Mode = 0;               // define mode: brew = 0, myc = 1 COULD JUST USE MENU
//byte preset = 0;             // Active Preset (grow and brew)
int selector = 0;            // could change to byte
int selectorprev = 0;        // Must be int. Maybe long. Defines the next menu position by changing pulses

//operational vars (sensors and timing)
unsigned int sensorInterval = 5000;         // time between readings
unsigned long int sensorTime = 0;           // current time 
unsigned long int sensorTime2 = 0;          // time of last sensor reading
unsigned long int backlighton = 0;  
unsigned long int backlighttime = 120000;  




// fans, lights, and timers
byte FanAuto = 0;
unsigned long int fanONmillis = 0;
unsigned long int fanOFFmillis = 0;
byte fanON = 0;
byte fanOFF = 0;
boolean fanstate = false;
unsigned long int Time = 0;
unsigned long int TimeAdjust = 0;
int brewtimer = 0;
double brewtimerRef = 0;
byte brewtimerON = 0;
float brewtimerSv = 20;
unsigned long int LightON = 0;
unsigned long int LightOFF = 0;
unsigned int Hours = 0;
unsigned int Minutes = 0;
unsigned int Seconds = 0;
byte daysAdj = 0; //not implemented yet

//key var storage
float PvH = 0; 
double PvT = 0;
float SvH = 0; 
double SvT = 0; 



//Reading averaging
//const int numReadings = 4;   // number of readings to average (rolling average) ALSO changes loading screen length (as values are populated twice per second)
//float readingsT[numReadings];// Temp readings to average
//float readingsH[numReadings];// Hum readings to average

//byte readingsCount = 0;
//byte index = 0;               // index of the current reading
//byte index2 = 0;
//float totalT = 0;            // current Temp total
//float totalH = 0;            // current Hum total
//float totalIT = 0;            // current Temp total
//fafloat totalIH = 0; 

float Temp1;                   //Current readings
float Temp2;                   //Current readings
float Temp3;                   //Current readings
float Hum;
int Day = 0;                //Current day in program (for calcs) 
int DayPrev = 0;            //Previous day for counting and eeprom NOT SET UP YET 



// Fridge limits
int dutyCycle = 2; // in minutes
int minCool = 10; // in minutes
byte coolON = 0;  // PID attached to this

// Heat limits
byte heatON = 0;  // PID attached to this

//PID  variables
#include <PID_v1.h>
byte autotune = 0;

//cool
double Kp = 8;
double Ki = 2;
double Kd = 2;
double Output;
PID coolPID(&PvT, &Output, &SvT ,Kp,Ki,Kd, REVERSE);
double coolWindowSize = 1800000;  //  60k = 1min
unsigned long coolWindowStartTime;
unsigned long coolOffElapsed = 0;

//heat
double Outputh;
PID heatPID(&PvT, &Outputh, &SvT ,4,0.8,0.8, DIRECT);
double heatWindowSize = 600000;  // 60k = 1min
unsigned long heatWindowStartTime;
unsigned long heatOffElapsed = 0;



// ensure setpoint, input, and outpit are defined

//************* End Variables Setup ***************//


void setup(){

//Sensor start
  dht.begin();
  
//Interrupts initialize
  attachInterrupt(0, A_RISE, RISING);
  attachInterrupt(1, B_RISE, RISING);
  pinMode(buttonPin, INPUT); // initialize momentary button input
  
//Pin declarations  
  pinMode(ControlTpin, OUTPUT); //set outputs
  pinMode(ControlHpin, OUTPUT);
  pinMode(ControlLpin, OUTPUT);
  pinMode(ControlApin, OUTPUT);
  pinMode(ControlCpin, OUTPUT);
  digitalWrite(ControlTpin, HIGH); // write outputs HIGH (off in this case) FIRST to prevent startup jitters.
  digitalWrite(ControlHpin, HIGH); 
  digitalWrite(ControlLpin, HIGH); 
  digitalWrite(ControlApin, HIGH); 
  digitalWrite(ControlCpin, HIGH); 
  
//LCD and special chars
  Serial.begin(115200);
  lcd.init();                      
  lcd.backlight();
  lcd.createChar(0, heart);
  lcd.createChar(1, deg);
  lcd.createChar(2, hum);
  lcd.createChar(3, up1);
  lcd.createChar(4, up2);
  lcd.createChar(5, up3);
  lcd.createChar(6, Pv);
  lcd.createChar(7, Sv);
  lcd.clear();
  LoadScreen();
  
// load all the saved values from EEPROM
  EEPROM_recall();
  
  //fanONmillis = 0;
  fanOFFmillis = millis();
  HomeSetup();
  
  //PID shit
  //coolWindowSize = dutyCycle * 60000;
  coolPID.SetOutputLimits(0, coolWindowSize/1000);
  coolPID.SetMode(AUTOMATIC);
  coolOffElapsed = millis();
  heatPID.SetOutputLimits(0, heatWindowSize/1000);
  heatPID.SetMode(AUTOMATIC);
  coolOffElapsed = millis();
}


void loop(){

  Button(); 
  Menus ();
  
  /* //TESTING OUTPUT (enable this line to print interrupt data to the serial port
  Serial.print(pulses);
  Serial.print(" : ");
  Serial.println(pulseMod);*/
  
  
}




      
      

