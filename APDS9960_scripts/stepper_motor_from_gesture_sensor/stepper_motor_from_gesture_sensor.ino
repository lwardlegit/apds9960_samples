#include <Arduino_APDS9960.h>
#include <Stepper.h>

// need to configure for the low power/ sleep state later
#define APDS9960_INT 2

const int stepsPerRevolution = 2048;  // For 28BYJ-48 stepper
Stepper stepperMotor(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
   Serial.begin(9600);
  while (!Serial); // Wait for Serial Monitor to open

  // try to connect to the sensor if it fails stop trying to connect
  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
    while (true); // Stop forever
  }

  int proximity = 0;
  stepperMotor.setSpeed(10); 

}


void loop() {
   // Check if a proximity reading is available.
   // proximity is an int if it gets defined
  if (APDS.proximityAvailable()) {
    proximity = APDS.readProximity();
  }

  // Check if a gesture reading is available
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture) {
      case GESTURE_UP:
      if (proximity !== NULL && proximity < 20){
        Serial.println("Detected UP gesture");
        stepperMotor.step(50);  
      }
        break;

      case GESTURE_DOWN:
      if (proximity !== NULL && proximity < 20){
        Serial.println("Detected DOWN gesture");
        stepperMotor.step(-50);  
      }
        break;

      // we can add in left and right gestures for other applications later on but we can exclude them for now

      /*
      case GESTURE_LEFT:
        Serial.println("Detected LEFT gesture");
        break;

      case GESTURE_RIGHT:
        Serial.println("Detected RIGHT gesture");
        break;
        */

      default:
        // Ignore
        break;
    }
}
