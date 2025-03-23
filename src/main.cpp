#include "altimeter.h"
#include <Arduino.h>
#define ONPAD 0
#define ASCENDING 1
#define DESCENDING 2
#define POST_FLIGHT 3

// put function declarations here:
bool apogeeDetected = false;
double currentAltitude = 0.0;
double priorAltitude = 0.0;
double apogeeAltitude = 0.0;  
double apogeeTime = 0.0;
bool mainDeployed = false;

const int main_parchute = 19;
const int drogue_parchute = 18;

void setup() {
  // put your setup code here, to run once:
  Serial.println("Flight Computer Booting up...");
  setupBMP();
  Serial.println("Flight Computer is Booted up!");


  pinMode(main_parchute, OUTPUT); //Use for Pyro Channels
  pinMode(drogue_parchute, OUTPUT); //Use for Pyro Channels
  digitalWrite(main_parchute, LOW);
  digitalWrite(drogue_parchute, LOW);

}

//int runOnPad(uint32_t tick);
//int runAscending(uint32_t tick);
//int runDescending(uint32_t tick);
//int runPostFlight(uint32_t tick);

void loop() {
  // put your main code here, to run repeatedly:
  //int status;
  //uint32_t tick = 0; // Initialize tick with the current time in milliseconds
  

  currentAltitude = readAltitude();
  double difference = currentAltitude - priorAltitude;

  if(difference < 0 && !apogeeDetected) {
    apogeeAltitude = priorAltitude;
    apogeeDetected = true;
    apogeeTime = millis();
    Serial.println("Apogee Detected! Reading: "); 
    Serial.println(apogeeAltitude); 
    mainDeployed = true;
  }

  if(apogeeDetected && (millis() - apogeeTime > 1000) && mainDeployed) {
    //status = DESCENDING;  
    digitalWrite(drogue_parchute, HIGH);
  }
  
  if(apogeeDetected && currentAltitude < 1000) {
    //status = DESCENDING;
    Serial.println("Deploying Main Parchute");
    digitalWrite(main_parchute, HIGH);
  }
  
  priorAltitude = currentAltitude;
  delay(1000);
  
  /*if(status == ONPAD) {
    status = runOnPad(tick);
  }
  else if(status == ASCENDING) {
    status = runAscending(tick);
  }
  else if(status == DESCENDING) {
    status = runDescending(tick); 
  }
  else if(status == POST_FLIGHT) {
    status = runPostFlight(tick); 
  }
    */


}

// put function definitions here:
