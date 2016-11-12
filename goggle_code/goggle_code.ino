#include <NewPing.h>

/*
 * Code isn't glass, PLEASE EDIT THIS FILE!! :D
 *  (We've got a lot of example/test code floating around,
 *  but the norm is to have a single code-base to edit so
 *  let's start centralizing our work)
 */

#define SONAR_NUM       3           // Number of sensors
#define MAX_DISTANCE  200           // Max distance in cm
#define MIN_DISTANCE   10           // Min distance in cm
#define PING_INTERVAL  33           // Millisecond between pings. (3*33 = 99ms per ping cycle)

unsigned long pingTimer[SONAR_NUM]; // When each pings
unsigned int cm[SONAR_NUM];         // Store ping distances
uint8_t currentSensor = 0;          // Which sensor is active
int motorSpeed = 0;
int motorPin[3] = {
  3,                                // Motor for sonar0
  5,                                // Motor for sensor1
  6                                 // Motor for sensor2
};

NewPing sonar[SONAR_NUM] = {        // Array of sensors
  NewPing(11, 12, MAX_DISTANCE),
  NewPing(10, 9, MAX_DISTANCE),
  NewPing(8, 7, MAX_DISTANCE)
};

void setup() {
  // Serial Port begin
  Serial.begin (9600);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++) 
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL; 

  // Define motor pins
  for (int i = 0; i < sizeof(motorPin); i++) {
    pinMode (motorPin[i], OUTPUT);
  }
}// end of setup

void loop() {
  getSensorValues();
  writeMotor();
}//end of loop()

void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}// end of echoCheck()
 
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
}// end of oneSensorCycle()

//void writeMotor(long dist, int motorToWrite){
//
//  if (dist < MAX_DISTANCE) {
//    motorSpeed = map(dist, MIN_DISTANCE, MAX_DISTANCE, 200, 10);
//
//    analogWrite(motorToWrite, motorSpeed);
//  }else{
//    analogWrite(motorToWrite, 0);
//  }
//}// end of writeMotor()

void writeMotor() {
  for (int i = 0; i  < 3; i++){
    analogWrite(motorPin[i], 0);
  }
  delay(40);
  for (int i = 0; i < 3; i++) {
      motorSpeed = map(cm[i], MIN_DISTANCE, MAX_DISTANCE, 200, 10);

      analogWrite(motorPin[i], motorSpeed);
  }
  
}

void getSensorValues() {
    for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
//      if (i == 0 && currentSensor == SONAR_NUM - 1)
//        oneSensorCycle(); // Do something with results.
      sonar[i].timer_stop();
      cm[i] = 0;
      sonar[i].ping_timer(echoCheck);
    }
  }
}// end of getSensorValues()



