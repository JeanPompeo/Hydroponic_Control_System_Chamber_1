
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---- Description ----
// This Sensor Array is collecting data from 5 Vasiala CO2 sensors and outputting them to the monitor 
// for the python code to extract. It is also controlling the CO2 enrichment (set to roughly 800 ppm)
// based on the average of Plant Canopy CO2 sensors, by turning a relay ON/OFF
///////////////////////////////////////////////////////////////////////////////////////////////////////////////


//CO2 Probes inputs
int VaisalaSensor_1 = A9;
int VaisalaSensor_2 = A2;
int VaisalaSensor_3 = A0;
int VaisalaSensor_4 = A11;
int VaisalaSensor_5 = A13;


//Relay + Siren
int relay = A5; 
int SirenPin = 10;    //Siren pin (PWM Digital Pin works with AnalogWrite 0 - 255)



////////////////////////////////////////////////////////////////////////////////////////////////




void setup() {
  
 Serial.begin(19200);
 analogReference(DEFAULT);

 pinMode(SirenPin, OUTPUT);
}



////////////////////////////////////////////////////////////////////////////////////////////////



void loop() {

VaisalaLoop();          // Includes Relay Loop / Control
SirenLoop();

Serial.println();

delay(4500+5000-265-30);
}



////////////////////////////////////////////////////////////////////////////////////////////////



void VaisalaLoop() {

int V_1 = analogRead(VaisalaSensor_1);    delay(50);
int V_2 = analogRead(VaisalaSensor_2);    delay(50);
int V_3 = analogRead(VaisalaSensor_3);    delay(50);
int V_4 = analogRead(VaisalaSensor_4);    delay(50);
int V_5 = analogRead(VaisalaSensor_5);    delay(50);

float V_CO2_1 = V_1*(5000/1024);
float V_CO2_2 = V_2*(5000/1024);
float V_CO2_3 = V_3*(5000/1024);
float V_CO2_4 = V_4*(5000/1024);
float V_CO2_5 = V_5*(5000/1024);

float Avg_CO2 = ( (V_CO2_2 + V_CO2_3) / 2 );
    
delay(500);

    // Serial.print(Vaisala), Serial.print(",");        # Outputs voltage reading
    
  //  Serial.print("V_CO2_below"); Serial.print(";");                               // Prints name of sensor
        if (! isnan(V_CO2_1)) { Serial.print(V_CO2_1); Serial.print(","); }       // Checks if sensor reading is a number and prints value
        if (V_CO2_1 > 2050) { Serial.print("NA"); Serial.print(","); }            // If sensor reading is > 2050, prints "NA"
        if (V_CO2_1 < 50) { Serial.print("NA"); Serial.print(","); }              // If sensor reading is < 50, prints "NA"
    
  //  Serial.print("V_CO2_lower"); Serial.print(";");
        if (! isnan(V_CO2_2)) { Serial.print(V_CO2_2); Serial.print(","); }
        if (V_CO2_2 > 2050) { Serial.print("NA"); Serial.print(","); }
        if (V_CO2_2 < 50) { Serial.print("NA"); Serial.print(","); }
    
  //  Serial.print("V_CO2_upper"); Serial.print(";");
        if (! isnan(V_CO2_3)) { Serial.print(V_CO2_3); Serial.print(","); }
        if (V_CO2_3 > 2050) { Serial.print("NA"); Serial.print(","); }
        if (V_CO2_3 < 50) { Serial.print("NA"); Serial.print(","); }
        
  //  Serial.print("V_CO2_above"); Serial.print(";");
        if (! isnan(V_CO2_4)) { Serial.print(V_CO2_4); Serial.print(","); }
        if (V_CO2_4 > 2050) { Serial.print("NA"); Serial.print(","); }
        if (V_CO2_4 < 50) { Serial.print("NA"); Serial.print(","); }

  //  Serial.print("V_CO2_sensor"); Serial.print(";");
        if (! isnan(V_CO2_5)) { Serial.print(V_CO2_5); Serial.print(","); }
        if (V_CO2_5 > 2050) { Serial.print("NA"); Serial.print(","); }
        if (V_CO2_5 < 50) { Serial.print("NA"); Serial.print(","); }



// ------ Relay Loop ------


// Serial.print("CO2_Tank"); Serial.print(";");             //Print name of value, followed by comma

if (Avg_CO2 > 49 && Avg_CO2 < 700) {analogWrite(relay, 150);
Serial.print("1"); Serial.print(","); }                          //Print to Monitor (1 = ON)

if (Avg_CO2 > 699) {analogWrite(relay, 0);
Serial.print("0"); Serial.print(","); }                          //Print to Monitor (0 = OFF)        

if (Avg_CO2 < 50) {analogWrite(relay, 0);
Serial.print("0"); Serial.print(","); }    

if ( isnan(Avg_CO2) ) {analogWrite(relay, 0);
Serial.print("0"); Serial.print(","); }   
}



////////////////////////////////////////////////////////////////////////////////////////////////



void SirenLoop() {

int V_1 = analogRead(VaisalaSensor_1); 
float V_CO2_1 = V_1*(5000/1024);

if (V_CO2_1 > 1750) {
   analogWrite(SirenPin, 5);
   delay(1000);
   analogWrite(SirenPin, 0);  }
}
