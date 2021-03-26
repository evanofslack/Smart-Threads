
#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260();

// Define Global Variables
int voltageStart;
int voltageEnd;
int voltageCurrent;
int range;
int angle;

// Setup INA260 Voltage Sensor
void setup() {

  //start serial communication @9600 bps
  Serial.begin(9600);    
  // Wait until serial port is opened
  while (!Serial) { delay(10); }

  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    while (1);
  }
  Serial.println("Found INA260 chip");
}


void loop(){

  // Listen to Processing GUI and execute functions when buttons are pressed
  if(Serial.available()){  //id data is available to read

    // Initialize serial read variable
    char val = Serial.read();

    // Get Starting Position Voltage
    if(val == 's'){       
      voltageStart = ina260.readBusVoltage();
      }

    // Get End Position Voltage
    if(val == 'e'){       
      voltageEnd = ina260.readBusVoltage();
      }
      
    // Return the current angle of the knee
    if(val == 'p'){ 
      
      while (true){

        // Compute angle from voltage
        range = voltageStart - voltageEnd;
        voltageCurrent = ina260.readBusVoltage();
        angle = (voltageCurrent/range) * 90;

        // Send angle to Processing GUI
        Serial.println(angle);
        delay(1000);
      }
    }
  }
}

 
