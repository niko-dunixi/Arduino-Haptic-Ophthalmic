#include <NewPing.h>

/*
 * Code isn't glass, PLEASE EDIT THIS FILE!! :D
 *  (We've got a lot of example/test code floating around,
 *  but the norm is to have a single code-base to edit so
 *  let's start centralizing our work)
 */
const int farthestDistance = 25;
const int closestDistance = 5;

typedef struct {
  //int trigger;
  //int echo;
  NewPing sonar;
  int motor;
} SensorMotorNode;

SensorMotorNode nodes[] = {
  { .sonar = NewPing(11, 12, farthestDistance), .motor = 3},
  { .sonar = NewPing(10, 9, farthestDistance), .motor = 5 },
  { .sonar = NewPing(8, 7, farthestDistance), .motor = 6 }
  //{.sonar(11, 12, farthestDistance), .motor = 3 }
  //{.trigger = 11, .echo = 12, .motor = 3},
  //{.trigger = 10, .echo = 9, .motor = 5},
  //{.trigger = 8, .echo = 7, .motor = 6}
};

int node_count = 3;

void setup() {
  for(int i = 0; i < node_count; ++i) {
    //pinMode(nodes[i].trigger, OUTPUT);
    //pinMode(nodes[i].echo, INPUT);
  }
}

void loop() {
  for (int i = 0; i < node_count; ++i) {
    int median = nodes[i].sonar.ping_median();
    // Per docs, median is in microseconds and has to be converted to cm
    int cm = nodes[i].sonar.convert_cm(median);
    // Now we need to hit-up the motor
    int motorSpeed = map(cm, closestDistance, farthestDistance, 200, 10);
    if (cm < farthestDistance){
      analogWrite(nodes[i].motor, motorSpeed);
    } else {
      analogWrite(nodes[i].motor, 0);
    } 
  }
}
