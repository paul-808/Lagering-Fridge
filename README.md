# Lagering-Fridge
Arduino-controlled lagering fridge with I2C screen and rotary encoder



//*************************************************************//

//  Name    : LAGERLOGGER! (With IC2 display)                            
//  Author  : Paul Jarvey                                             
//  Date    : 5 Oct, 2013    
//  Modified: 5 December 2017                                
//  Version : 1.4                                             
//  Notes                                                
//          :: 20x4 lc2 display, two submersible onewire temperature sensors                                             
//          :: control via rotary encoder, and 4 output controls  (Compressor, heater, light, and air exchange)                                             
//          :: screen connected  : SDA >> A4 , SCL >> A5                                             
//          :: Written in C++ optimized for the arduino nano.                                              
//  Warning                                             
//          :: This code is used to control a compresosr unit borrowed from an old fridge.                                             
//          :: Each compressor has different specifications and limitatins to its duty cycle                                             
//          :: that help prevent wear and overheating. This code might not be right for other                                              
//          :: compressors and may damage them. Check your specs, and note the following vars:                                             
//          ::   - coolWindowSize (milliseconds) determines the length of the duty cycle period                                             
//          ::   - minCool (minutes) is the minimum length the compressor will be turned off, per duty cycle
                                             
//****************************************************************

Planned modifications include better use of the lighting features, better logging, and better programming of the lager cycle.
