
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This code will read all 6 Atlas Scientific probes connected to their corresponding circuits on the  Tentacle Shield 
// (EC, pH, DO) x2, as well as the name of the peristaltic pump controlled by a Float Valve being turned On/Off (1/0) 
// and output to Serial Monitor in the format specified for the mySQL Database 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


char sensordata[30];                  // A 30 byte character array to hold incoming data from the sensors
byte sensor_bytes_received = 0;       // We need to know how many characters bytes have been received

byte code = 0;                        // used to hold the I2C response code.
byte in_char = 0;                     // used as a 1 byte buffer to store in bound bytes from the I2C Circuit.

#define TOTAL_CIRCUITS 8              // <-- CHANGE THIS | set how many I2C circuits are attached to the Tentacle shield(s): 1-8


int get_address(String name) {
    if(name == "ORP_LNS_1") return 94;
    else if(name == "ORP_LNS_2") return 95;  
    else if(name == "DO_LNS_1") return 96;
    else if(name == "DO_LNS_2") return 97;
    else if(name == "PH_LNS_1") return 98;
    else if(name == "PH_LNS_2") return 99;
    else if(name == "EC_LNS_1") return 100;
    else if(name == "EC_LNS_2") return 101;
    return 0;
}


//From pH Dosing Pump Example
#include <Ezo_i2c.h> //include the EZO I2C library from https://github.com/Atlas-Scientific/Ezo_I2c_lib
#include <Wire.h>    //include arduinos i2c library
#include <Ezo_i2c_util.h> //brings in common print statements

Ezo_board PUMP_103 = Ezo_board(103, "PUMP_103");                   //create a pump circuit object, whose address is 103
Ezo_board PUMP_104 = Ezo_board(104, "PUMP_104");                   //create a pump circuit object, whose address is 104

Ezo_board PUMP_105 = Ezo_board(105, "PUMP_105");                   //create a pump circuit object, whose address is 105
Ezo_board PUMP_106 = Ezo_board(106, "PUMP_106");                   //create a pump circuit object, whose address is 106

Ezo_board PUMP_107 = Ezo_board(107, "PUMP_107");                   //create a pump circuit object, whose address is 107
Ezo_board PUMP_108 = Ezo_board(108, "PUMP_108");                   //create a pump circuit object, whose address is 108
Ezo_board PUMP_109 = Ezo_board(109, "PUMP_109");                   //create a pump circuit object, whose address is 109
Ezo_board PUMP_110 = Ezo_board(110, "PUMP_110");                   //create a pump circuit object, whose address is 110


//For Float Valve's
byte Float_Sensor_1 = 11;
byte Float_Sensor_2 = 12;


byte computer_bytes_received = 0;   // We need to know how many characters bytes have been received
char computerdata[48];              // we make a 20 byte character array to hold incoming data from a pc/mac/other.
int channel;                        // INT pointer for channel switching - 0-7 serial, 8-127 I2C addresses
char *cmd;                          // Char pointer used in string parsing




/////////////////////////////////////////////////////////////////////////////////////////////////////////




void setup() {                        // startup function
  Serial.begin(9600);                 // Set the hardware serial port.
  Wire.begin();                       // enable I2C port.

pinMode(Float_Sensor_1, OUTPUT);
pinMode(Float_Sensor_2, OUTPUT);

}



/////////////////////////////////////////////////////////////////////////////////////////////////////////




void loop() {


  send_r_command("ORP_LNS_1");
  send_r_command("ORP_LNS_2");
  send_r_command("DO_LNS_1");
  send_r_command("DO_LNS_2");
  send_r_command("PH_LNS_1");
  send_r_command("PH_LNS_2");
  send_r_command("EC_LNS_1");
  send_r_command("EC_LNS_2");


  float orp_reading1 = read_sensor("ORP_LNS_1");
  float orp_reading2 = read_sensor("ORP_LNS_2");
  float do_reading1 = read_sensor("DO_LNS_1");
  float do_reading2 = read_sensor("DO_LNS_2");
  float ph_reading1 = read_sensor("PH_LNS_1");
  float ph_reading2 = read_sensor("PH_LNS_2");
  float ec_reading1 = read_sensor("EC_LNS_1");
  float ec_reading2 = read_sensor("EC_LNS_2");


int Float_1 = digitalRead(Float_Sensor_1);
int Float_2 = digitalRead(Float_Sensor_2);


//Control the Peristaltic Pumps Float Valve Readings from LNS containers 1-2
Water_Dose_Control();


/// System 1
 // Serial.print("ORP_LNS_1"); Serial.print(";");
    if (! isnan(orp_reading1)) {
    Serial.print(orp_reading1); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }
    
//  Serial.print("DO_LNS_1"); Serial.print(";");
    if (! isnan(do_reading1)) {
    Serial.print(do_reading1); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }

//  Serial.print("pH_LNS_1"); Serial.print(";");
    if (! isnan(ph_reading1)) {
    Serial.print(ph_reading1); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }

//  Serial.print("EC_LNS_1"); Serial.print(";");
    if (! isnan(ec_reading1)) {
    Serial.print(ec_reading1); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }

 // Serial.print("Water_Dose_1"); Serial.print(";");
    if (Float_1 == 1) { Serial.print("5"); Serial.print(","); }
    else { Serial.print("0"); Serial.print(","); }     

  
/// System 2
 // Serial.print("ORP_LNS_2"); Serial.print(";");
    if (! isnan(orp_reading2)) {
    Serial.print(orp_reading2); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }

 // Serial.print("DO_LNS_2"); Serial.print(";");
    if (! isnan(do_reading2)) {
    Serial.print(do_reading2); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }

 // Serial.print("pH_LNS_2"); Serial.print(";");
    if (! isnan(ph_reading2)) {
    Serial.print(ph_reading2); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }

 // Serial.print("EC_LNS_2"); Serial.print(";");
    if (! isnan(ec_reading2)) {
    Serial.print(ec_reading2); Serial.print(","); }
    else { Serial.print("NA"); Serial.print(","); }
  
 // Serial.print("Water_Dose_2"); Serial.print(";");
    if (Float_2 == 1) { Serial.print("5"); Serial.print(","); }
    else { Serial.print("0"); Serial.print(","); }     



////// Acid Dosing Control - Peristaltic Pumps

// /*
// Serial.print("pH_Dose_1"); Serial.print(";");

if (ph_reading1 > 5.85) { PUMP_105.send_cmd_with_num("d,", 0.5); 
    Serial.print("0.5"); Serial.print(","); }
    else { PUMP_105.send_cmd("x");    
    Serial.print("0"); Serial.print(","); }  

// Serial.print("pH_Dose_2"); Serial.print(";");
    
if (ph_reading2 > 5.85) { PUMP_106.send_cmd_with_num("d,", 0.5);
    Serial.print("0.5"); Serial.print(","); }
    else { PUMP_106.send_cmd("x"); 
    Serial.print("0"); Serial.print(","); }  
// */

////// Base Dosing Control
 /*
if (ph_reading1 < 5.75) { PUMP_105.send_cmd_with_num("d,", 0.5); 
    Serial.print("0.5"); Serial.print(","); }
    else { PUMP_105.send_cmd("x");    
    Serial.print("0"); Serial.print(","); }  

// Serial.print("pH_Dose_2"); Serial.print(";");
    
if (ph_reading2 < 5.75) { PUMP_106.send_cmd_with_num("d,", 0.5);
    Serial.print("0.5"); Serial.print(","); }
    else { PUMP_106.send_cmd("x"); 
    Serial.print("0"); Serial.print(","); } 
  */    


delay(1000);

////// Nutrient A/B Dosing Control - Peristaltic Pumps

// Serial.print("EC_Dose_1"); Serial.print(";");

if (ec_reading1 < 1100) { PUMP_107.send_cmd_with_num("d,", 0.5);
    PUMP_108.send_cmd_with_num("d,", 1); 
    Serial.print("0.5"); Serial.print(",");  }
    else { PUMP_107.send_cmd("x");  PUMP_108.send_cmd("x");  
    Serial.print("0"); Serial.print(",");  }     

// Serial.print("EC_Dose_2"); Serial.print(";");

if (ec_reading2 < 1100) { PUMP_109.send_cmd_with_num("d,", 0.5);
    PUMP_110.send_cmd_with_num("d,", 1); 
    Serial.print("0.5"); Serial.print(",");  }
    else { PUMP_109.send_cmd("x");  PUMP_110.send_cmd("x");  
    Serial.print("0"); Serial.print(",");  }   
    
    

//////

Serial.print('\n');                 // Print this from the final Arduino Board being read by Python in order to have proper data import
delay(5000-1340);
}



//----------------------------------------------------------------------------------



void Water_Dose_Control() {

int Float_1 = digitalRead(Float_Sensor_1);
int Float_2 = digitalRead(Float_Sensor_2);

  
if (Float_1 == 1) { PUMP_103.send_cmd_with_num("d,", 5); }
    else { PUMP_103.send_cmd("x");  }  

if (Float_2 == 1) { PUMP_104.send_cmd_with_num("d,", 5);  }                  
    else { PUMP_104.send_cmd("x");  }       
}




//----------------------------------------------------------------------------------



void send_r_command(String name) {
    int address = get_address(name);
    
    Wire.beginTransmission(address);                   // call the circuit by its ID number.
    Wire.write('r');                                   // request a reading by sending 'r'
    Wire.endTransmission();                            // end the I2C data transmission.
    delay(50);
}



//-------------------------------------------------------------

 

float read_sensor(String name) {
  
      int address = get_address(name);
      int timeout;
      if(name == "PH_LNS_1")  { timeout = 600; }
      else if(name == "PH_LNS_2")  { timeout = 600; }
      else if(name == "DO_LNS_1") { timeout = 600; }
      else if(name == "DO_LNS_2") { timeout = 600; }
      else if(name == "EC_LNS_1") { timeout = 600; }
      else if(name == "EC_LNS_2") { timeout = 600; }
      else if(name == "ORP_LNS_1") { timeout = 600; }
      else if(name == "ORP_LNS_2") { timeout = 600; }      // Different Timeout values due to differing read times
  
      delay(timeout);  // AS circuits need a 1 second before the reading is ready
  
  
      sensor_bytes_received = 0;                        // reset data counter
      memset(sensordata, 0, sizeof(sensordata));        // clear sensordata array;
  
      Wire.requestFrom(address, 48, 1);    // call the circuit and request 48 bytes (this is more then we need).
      code = Wire.read();
  
      while (Wire.available()) {          // are there bytes to receive?
        in_char = Wire.read();            // receive a byte.
  
        if (in_char == 0) {               // null character indicates end of command
          Wire.endTransmission();         // end the I2C data transmission.
          break;                          // exit the while loop, we're done here
        }
        else {
          sensordata[sensor_bytes_received] = in_char;      // append this byte to the sensor data array.
          sensor_bytes_received++;
        }
      }
  
  
      switch (code) {                          // switch case based on what the response code is.
        case 1:                               // decimal 1  means the command was successful.
          return String(sensordata).toFloat();            // print the actual reading
          Serial.print("\t"); 
          break;                                // exits the switch case.
      }
}
