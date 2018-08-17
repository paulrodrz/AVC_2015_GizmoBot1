/**
 * GizmoBot2018 
 */

 

#include "WheelEncoder.h"

// TODO: Figure out how to encapsulate ISR's in WheelEncoder
WheelEncoder wheelEncoder;
uint32_t printEncoderTracker=0;
float totalDistance = 0;

void leftISR() {
  wheelEncoder.leftInc();
} 

void rightISR() {
  wheelEncoder.rightInc();
}

void setup() {
  Serial.begin(115200);

  attachInterrupt(digitalPinToInterrupt(WHEEL_LEFT_PIN), leftISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(WHEEL_RIGHT_PIN), rightISR, CHANGE);
  
  printEncoderTracker=millis();  // Grab start time
}

void loop() {
  static uint8_t staleDataCount = 0;
  
  if (millis() - printEncoderTracker >= 1000) {
    printEncoderTracker+=1000;  // Next print time is in 1 sec

    wheelEncoder.update();
    float traveled = wheelEncoder.getForwardDistance();
    totalDistance += traveled;

#if 1  // Resets output periodically for testing
    if (traveled == 0) 
      staleDataCount++;
    else
      staleDataCount=0;
      
    if (staleDataCount > 5) {
      staleDataCount=0;
      totalDistance=0;
      wheelEncoder.reset();
    }
#endif    
    
    Serial.print("Traveled: ");
    Serial.print(traveled);
    Serial.print("mm");
    Serial.print("\tTotal: ");
    Serial.print(totalDistance);
    Serial.println("mm");
  }
}



