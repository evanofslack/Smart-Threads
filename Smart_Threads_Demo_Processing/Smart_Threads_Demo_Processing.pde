import controlP5.*; //import ControlP5 library
import processing.serial.*;

// Define global variables
Serial myPort;
String val;
String angle = "0";

// Serial handshake initialization
boolean firstContact = false;

//create ControlP5 object
ControlP5 cp5; 

// Create Fonts
PFont font; 
PFont fontTitle;

void setup(){
  
  // Uncomment to see supported fonts
  //String[] fontList = PFont.list();
  //printArray(fontList);  
  
  // Uncomment to see avaliable serial ports to find Arduino 
  //printArray(Serial.list());
  
  //Set window size
  size(1000, 700);    
  
  // Initialize serial communications
  //port = new Serial(this, "COM3", 9600);
  myPort = new Serial(this, Serial.list()[7], 9600);
  myPort.bufferUntil('\n'); 
  
  // Create control object
  cp5 = new ControlP5(this);
  
  // Define custom fonts
  font = createFont("Calibri", 20);    // custom fonts for buttons and title
  fontTitle = createFont("Calibri", 60);
  textFont(font);
  

  // Add buttons
  cp5.addButton("Start") 
    .setPosition(100, 50)   //x and y coordinates from upper left corner of button
    .setSize(120, 70)       //(width, height)
    .setFont(font)          // Set font
  ;   

  cp5.addButton("End")     
    .setPosition(100, 150)  //x and y coordinates from upper left corner of button
    .setSize(120, 70)       //(width, height)
    .setFont(font)          // Set font
  ;
  
  cp5.addButton("Plot")     
    .setPosition(100, 250)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)       //(width, height)
    .setFont(font)          // Set font
  ;

  
  cp5.addButton("Reset")    
    .setPosition(100, 350)  //x and y coordinates of upper left corner of button
    .setSize(120, 70)       //(width, height)
    .setFont(font)          // Set font
  ;
}

// Main loop to draw the GUI
void draw(){  

  // Set background color (r, g, b) from (0 to 255)
  background(255, 255 , 255); 
  
  //Title the GUI
  fill(0, 0, 0);                  //text color (r, g, b)
  textFont(font);                 // Set font
  text("Knee Movement Visualization", 300, 120);  // ("text", x coordinate, y coordinate)
  
  // Read angle data from Arduino
  
  val = myPort.readStringUntil('\n');
  if (val!= null){
    val = trim(val);
    println(val);
    
    if (firstContact == false) {
      if (val.equals("A")) {
        myPort.clear();
        firstContact = true;
        myPort.write("A");
        println("contact");
      }
    }
    else {
      println(val);
      angle = val;
      
      
       myPort.write("A");
    }
  }
  text("Status:", 300,250);
  text(angle, 380,250);           // Display the angle
}

// Add functions for buttons
// Each button sends a serial charecter to the Arduino
void Start(){
  myPort.write('s');
  println("s");  
}

void End(){
  myPort.write('e');
}

void Plot(){
  myPort.write('p');
}

void Reset(){
  myPort.write('r');
}
