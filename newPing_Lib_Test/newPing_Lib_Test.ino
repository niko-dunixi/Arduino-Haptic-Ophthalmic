#include <NewPing.h>
 
//#define TRIGGER_PIN  11
//#define ECHO_PIN     12
//#define MAX_DISTANCE 200
// 
//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
// 
//void setup() {
//  //Serial.begin(115200);
//  Serial.begin(9600);
//}
// 
//void loop() {
//  delay(50);
//  int uS = sonar.ping();
//  Serial.print("Ping: ");
//  Serial.print(uS / US_ROUNDTRIP_CM);
//  Serial.println("cm");
//}

// ---------------------------------------------------------
// This example code was used to successfully communicate
// with 15 ultrasonic sensors. You can adjust the number of
// sensors in your project by changing SONAR_NUM and the
// number of NewPing objects in the "sonar" array. You also
// need to change the pins for each sensor for the NewPing
// objects. Each sensor is pinged at 33ms intervals. So, one
// cycle of all sensors takes 495ms (33 * 15 = 495ms). The
// results are sent to the "oneSensorCycle" function which
// currently just displays the distance data. Your project
// would normally process the sensor results in this
// function (for example, decide if a robot needs to turn
// and call the turn function). Keep in mind this example is
// event-driven. Your complete sketch needs to be written so
// there's no "delay" commands and the loop() cycles at
// faster than a 33ms rate. If other processes take longer
// than 33ms, you'll need to increase PING_INTERVAL so it
// doesn't get behind.
// ---------------------------------------------------------
#include <NewPing.h>
 
#define SONAR_NUM     15 // Number or sensors.
#define MAX_DISTANCE 200 // Max distance in cm.
#define PING_INTERVAL 33 // Milliseconds between pings.
 
unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.
 
NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(41, 42, MAX_DISTANCE),
  NewPing(43, 44, MAX_DISTANCE),
  NewPing(45, 20, MAX_DISTANCE),
  NewPing(21, 22, MAX_DISTANCE),
  NewPing(23, 24, MAX_DISTANCE),
  NewPing(25, 26, MAX_DISTANCE),
  NewPing(27, 28, MAX_DISTANCE),
  NewPing(29, 30, MAX_DISTANCE),
  NewPing(31, 32, MAX_DISTANCE),
  NewPing(34, 33, MAX_DISTANCE),
  NewPing(35, 36, MAX_DISTANCE),
  NewPing(37, 38, MAX_DISTANCE),
  NewPing(39, 40, MAX_DISTANCE),
  NewPing(50, 51, MAX_DISTANCE),
  NewPing(52, 53, MAX_DISTANCE)
};
 
void setup() {
  Serial.begin(115200);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
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
  // The rest of your code would go here.
}
 
void echoCheck() { // If ping echo, set distance to array.
  if (sonar[currentSensor].check_timer())
    cm[currentSensor] = sonar[currentSensor].ping_result / US_ROUNDTRIP_CM;
}
 
void oneSensorCycle() { // Do something with the results.
  for (uint8_t i = 0; i < SONAR_NUM; i++) {
    Serial.print(i);
    Serial.print("=");
    Serial.print(cm[i]);
    Serial.print("cm ");
  }
  Serial.println();
}
