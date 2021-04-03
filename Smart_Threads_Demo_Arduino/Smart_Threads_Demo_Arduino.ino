
#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260();

// Define Global Variables
float voltageStart;
float voltageEnd;
float voltageCurrent;
float range;
String angle;
char val;

// Setup INA260 Voltage Sensor
void setup() {

  //start serial communication @9600 bps
  Serial.begin(9600);   
  establishContact(); 
  //Wait until serial port is opened
  while (!Serial) { delay(10); }

  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    while (1);
  }
  Serial.println("Found INA260 chip");
}


void loop(){

  // Listen to Processing GUI and execute functions when buttons are pressed
    if (Serial.available() > 0) { // If data is available to read,
      val = Serial.read(); // read it and store it in val


    // Get Starting Position Voltage
    if(val == 's'){      
      voltageStart = ina260.readBusVoltage();
      Serial.println("Start Voltage Measurement: " + String(voltageStart) + "mV"); 
      delay(50);
      }

    // Get End Position Voltage
    if(val == 'e'){        
      voltageEnd = ina260.readBusVoltage();
      Serial.println("End Voltage Measurement: " + String(voltageEnd) + "mV");
      delay(50);
      }
      
    // Return the current angle of the knee
    if(val == 'p'){ 
      
      while (true){

        // Compute angle from voltage
        range = voltageStart - voltageEnd;
        voltageCurrent = ina260.readBusVoltage();
        angle = String(((voltageCurrent -voltageEnd)/range)*90);

        // Send angle to Processing GUI
        Serial.println("Current Angle: " + angle);
        delay(1000);
      }
    }
  }
}

void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}

 
