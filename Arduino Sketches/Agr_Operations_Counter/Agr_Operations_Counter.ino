
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ---- Description ----
// This code collects data for "Agricultural Operations" by counting the time a person is in the Growth Chamber
// via the use of Push Button switches, and the time that chamber door is open/closed via the use of a light 
// sensor. To be used with the "Human Bean Counter" EPS32 Dev Module mounted onto the inner chamber wall.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>


const int buttonPin1 = 15;     // the numbers of the pushbutton pin
const int buttonPin2 = 4;     
const int buttonPin3 = 2;    

const int ledPin1 =  27;      // the number of the LED pin
const int ledPin2 =  26;   
const int ledPin3 =  25;   

int buttonState1 = 0;         // variable for reading the pushbutton status 
int buttonState2 = 0; 
int buttonState3 = 0; 

int ledflag1 = 0;  
int ledflag2 = 0; 
int ledflag3 = 0;   


int sensorPin = 33;
int sensorValue = 0;
int doorCheck = 0;


////////////////////////////////////////////////////////////////////////////////////////////////




void setup() {
  
Serial.begin(9600);

  // initialize the LED pin as an output:
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);


  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);


}


////////////////////////////////////////////////////////////////////////////////////////////////




void loop() {

switchloop();
lightsensorloop(); 

Serial.print('\n');

delay(9900);
  
}




////////////////////////////////////////////////////////////////////////////////////////////////




void switchloop()  {

  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  

if (buttonState1 == HIGH) { 
    if (ledflag1 == 0) { ledflag1 = 1; digitalWrite(ledPin1,HIGH); }                           
    else { ledflag1 = 0; digitalWrite(ledPin1,LOW); }
    }                 

if (buttonState2 == HIGH) { 
    if (ledflag2 == 0) { ledflag2 = 1; digitalWrite(ledPin2,HIGH); }                           
    else { ledflag2 = 0; digitalWrite(ledPin2,LOW); }
    }                 

if (buttonState3 == HIGH) { 
    if (ledflag3 == 0) { ledflag3 = 1; digitalWrite(ledPin3,HIGH); }                           
    else { ledflag3 = 0; digitalWrite(ledPin3,LOW); }
    }            



// Serial.print("Person_1"); Serial.print(",");             //Print name of value, followed by comma
Serial.print(ledflag1); Serial.print(",");  

// Serial.print("Person_2"); Serial.print(",");             //Print name of value, followed by comma
Serial.print(ledflag2); Serial.print(",");  

// Serial.print("Person_3"); Serial.print(",");             //Print name of value, followed by comma
Serial.print(ledflag3); Serial.print(","); 

delay(100);

}



//-----------------------------------------




void lightsensorloop() {

sensorValue = analogRead(sensorPin); 

if (sensorValue >= 60) {
  doorCheck = 1;
}

if (sensorValue < 60) {
  doorCheck = 0;
}

// Serial.print("Door_Open"); Serial.print(",");
Serial.print(doorCheck); //Serial.print(",");
  
}







                                  


  
