
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---- Description ----
// This Sensor Array is collecting data from the Thermocouples for tanks 1, 2, 3, and 4 and 
// outputting them to the monitor for the python code to extract 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Thermocouple
#include <OneWire.h> 
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6 

//--- Reference ranges for all Thermocouples based on Atmospheric Pressure ----//
// float RawHigh = 99.6;
// float RawLow = 0.01;
float ReferenceHigh = 99.87;
float ReferenceLow = 0;
// float RawRange = RawHigh - RawLow;
float ReferenceRange = ReferenceHigh - ReferenceLow;

// Reference ranges for Thermocouple 1 
float RawHigh_1 = 99.6;
float RawLow_1 = -0.06;
float RawRange_1 = RawHigh_1 - RawLow_1;

// Reference/Calibration ranges for Thermocouple 1 
float RawHigh_2 = 99.6;
float RawLow_2 = 0.19;
float RawRange_2 = RawHigh_2 - RawLow_2;

// Reference ranges for Thermocouple 1 
float RawHigh_3 = 99.6;
float RawLow_3 = 1.8;
float RawRange_3 = RawHigh_3 - RawLow_3;

float RawHigh_4 = 99.6;
float RawLow_4 = 0.06;
float RawRange_4 = RawHigh_4 - RawLow_4;


//--- Floating values that will hold Raw Thermocouple readings
float RawValue_1 = 0;
float RawValue_2 = 0;
float RawValue_3 = 0;
float RawValue_4 = 0;

// Used to communicate with Thermocouples all on the same bus (multiple sensors on one pin)
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

//RTC
#include <Wire.h>
#include <ds3231.h>
#include <RTClib.h>
RTC_DS3231 rtc;
struct ts t; 
int h = t.hour;
int m = t.min;
int s = t.sec;
int d = t.mday; 
int mo = t.mon;
int yr = t.year;



////////////////////////////////////////////////////////////////////////////////////////////////


void setup() {
  
Serial.begin(9600);

// For Thermocouples
 sensors.begin(); 
 sensors.setResolution(20);

// For RTC Module
Wire.begin();
DS3231_init(DS3231_INTCN);                                    
rtc.begin();
rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));

// Manually adjusts time when re-uploading code
 /*
  t.hour=14; 
  t.min=24;
  t.sec=00;
  t.mday=1;
  t.mon=3;
  t.year=2022;
  DS3231_set(t); 
  */
    
 }



////////////////////////////////////////////////////////////////////////////////////////////////


void loop() {
  
  DateTime t = rtc.now();
  // DS3231_get(&t);
 
 /* 
  if (t.second() % 10 == 0){
    Serial.print(t.month()); Serial.print(".");          //Print to Monitor
    Serial.print(t.day()); Serial.print(".");
    Serial.print(t.year()); Serial.print(" ");
    Serial.print(t.hour()); Serial.print(":");
    Serial.print(t.minute()); Serial.print(":");
    Serial.print(t.second());  
    Serial.print(";");
 */
    
    ThermocoupleLoop();
    Serial.print('\n');
    delay(1100+6200+25);
  } 


////////////////////////////////////////////////////////////////////////////////////////////////



void ThermocoupleLoop() {


sensors.requestTemperatures(); 

//--- Thermocouple 1 ----//
RawValue_1 = sensors.getTempCByIndex(0);
float Temp_Value_1 = (((RawValue_1 - RawLow_1) * ReferenceRange) / RawRange_1) + ReferenceLow;
// Serial.print("temp_LNS_1"); Serial.print(";");
    if (! isnan(Temp_Value_1)) {
    Serial.print(Temp_Value_1); Serial.print(","); }
    else {
    Serial.print("NA"); Serial.print(","); }
delay(500); 

//--- Thermocouple 2 ----//
RawValue_2 = sensors.getTempCByIndex(1);
float Temp_Value_2 = (((RawValue_2 - RawLow_2) * ReferenceRange) / RawRange_2) + ReferenceLow;
// Serial.print("temp_LNS_2"); Serial.print(";");
    if (! isnan(Temp_Value_2)) {
    Serial.print(Temp_Value_2); Serial.print(","); }
    else {
    Serial.print("NA"); Serial.print(","); }
delay(500); 

//--- Thermocouple 3 ----//
RawValue_3 = sensors.getTempCByIndex(2);
float Temp_Value_3 = (((RawValue_3 - RawLow_3) * ReferenceRange) / RawRange_3) + ReferenceLow;
// Serial.print("temp_LNS_3"); Serial.print(";");
    if (! isnan(Temp_Value_3)) {
    Serial.print(Temp_Value_3); Serial.print(","); }
    else {
    Serial.print("NA"); Serial.print(","); }
delay(500); 

//--- Thermocouple 4 ----//
RawValue_4 = sensors.getTempCByIndex(3);
float Temp_Value_4 = (((RawValue_4 - RawLow_4) * ReferenceRange) / RawRange_4) + ReferenceLow;
// Serial.print("temp_LNS_4"); Serial.print(";");
    if (! isnan(Temp_Value_4)) {
    Serial.print(Temp_Value_4); Serial.print(","); }
    else {
    Serial.print("NA"); Serial.print(","); }
delay(500); 
  
}                  


  
  
  
