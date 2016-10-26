#include <NewPing.h>

/*
 * Code isn't glass, PLEASE EDIT THIS FILE!! :D
 *  (We've got a lot of example/test code floating around,
 *  but the norm is to have a single code-base to edit so
 *  let's start centralizing our work)
 */
//const int farthestDistance = 25;
//const int closestDistance = 5;

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

//typedef struct {
//  //int trigger;
//  //int echo;
//  NewPing sonar;
//  int motor;
//} SensorMotorNode;
//
//SensorMotorNode nodes[] = {
//  { .sonar = NewPing(11, 12, farthestDistance), .motor = 3},
////  { .sonar = NewPing(10, 9, farthestDistance), .motor = 5 },
////  { .sonar = NewPing(8, 7, farthestDistance), .motor = 6 }
//  //{.sonar(11, 12, farthestDistance), .motor = 3 }
//  //{.trigger = 11, .echo = 12, .motor = 3},
//  //{.trigger = 10, .echo = 9, .motor = 5},
//  //{.trigger = 8, .echo = 7, .motor = 6}
//};
//
//int node_count = 3;

void setup() {
  // Serial Port begin
  Serial.begin (9600);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;

  // Define motor pins
//  pinMode (motorPin[0], OUTPUT);
//  pinMode (motorPin[1], OUTPUT);
//  pinMode (motorPin[2], OUTPUT);

  for (int i = 0; i < sizeof(motorPin); i++) {
    pinMode (motorPin[i], OUTPUT);
  }
    
//  for(int i = 0; i < node_count; ++i) {
//    //pinMode(nodes[i].trigger, OUTPUT);
//    //pinMode(nodes[i].echo, INPUT);
//  }
}

void loop() {
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    if (millis() >= pingTimer[i]) {
      pingTimer[i] += PING_INTERVAL * SONAR_NUM;
      if (i == 0 && currentSensor == SONAR_NUM - 1)
        oneSensorCycle(); // Do something with results.
      sonar[currentSensor].timer_stop();
      currentSensor = i;
      cm[currentSensor] = 0;
      sonar[currentSensor].ping_timer(echoCheck);
    }
  }
//  delay(50);
//  int uS = sonar.ping();
//  for (int i = 0; i < node_count; ++i) {
//    int median = nodes[i].sonar.ping_median();
//    Serial.print("median: ");
//    Serial.print(median);
//    // Per docs, median is in microseconds and has to be converted to cm
//    int cm = nodes[i].sonar.convert_cm(median);
//    // Now we need to hit-up the motor
//    int motorSpeed = map(cm, closestDistance, farthestDistance, 200, 10);
//    Serial.print(" motorSpeed: ");
//    Serial.println(motorSpeed);
//    //Serial.print(cm);
//    if (cm < farthestDistance){
//      analogWrite(nodes[i].motor, motorSpeed);
////      Serial.print(nodes[i].motor, motorSpeed);
////      Serial.println() ;
//    } else {
//      analogWrite(nodes[i].motor, 0);
//    } 
//  }// end of for loop

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

void writeMotor(long dist, int motorToWrite){

  if (dist < MAX_DISTANCE) {
    motorSpeed = map(dist, MIN_DISTANCE, MAX_DISTANCE, 200, 10);

    analogWrite(motorToWrite, motorSpeed);
  }else{
    analogWrite(motorToWrite, 0);
  }
}// end of writeMotor()



