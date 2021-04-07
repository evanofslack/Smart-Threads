
#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260();

// Define Global Variables
float voltageStart;
float voltageEnd;
float voltageCurrent;
float range;
String angle;
char val;
int angleRound;
int arrSize = 5;
int loopCount = 0;
int angleTally = 0;


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

        // Average over 5 angle measurements and round
        angleRound = round(((voltageCurrent -voltageEnd)/range)*90);
        angleTally += angleRound;
        
        if (loopCount % 5 == 0) {
          
          // Limit ROM from 0-90 degrees
          if(angleTally > 90*5){
            angleTally = 90*5;
          }
          if(angleTally < 0){
            angleTally = 0;
          }
          
          angleTally = 90*5 - (angleTally);
          angle = String(angleTally/5);

          // Send angle to Processing GUI
          Serial.println("Current Angle: " + angle);
          angleTally = 0;
          
        }
          delay(100);
        loopCount++;
      }
    }
  }
}

// Establish serial connection to Processing 
void establishContact() {
  while (Serial.available() <= 0) {
  Serial.println("A");   // send a capital A
  delay(300);
  }
}

 
