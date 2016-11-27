//red wire connects 5v on Nano to VCC on SR04
//brown wire connects SR04 to Ground
//Trigger pin of the SR04 sensor - green Jumper
//Echo pin of the SR04 sensor- yellow Jumper

//the nano can analogWrite to pins 3,5,6,9,10,11
//set up distance sensor pins
int sensorMotorCombo[3][3]={
  {11,  12, 3},  // Trigger pin for sensor0 = 11, echo pin for sensor0 = 12, motor for sensor0 = 3
  {10, 9, 5},    // Trigger pin for sensor1 = 10, echo pin for sensor1 = 9, motor for sensor1 = 5
  {8, 7, 6}     // Trigger pin for sensor2 = 8, echo pin for sensor2 = 7, motor for sensor2 = 6
};

//data manipulation variables
long distances[3];
const int MAX_DISTANCE = 35; //this is in cm - we will use this distance to map the values for analogWrite
const int MIN_DISTANCE = 10; //this is in cm - this is the closest we want to read from the sensor
const int MAX_SPEED = 200;
unsigned long NEXT_TIME = millis();

void setup() {
  //Serial Port begin
  Serial.begin(9600);

  //Define inputs and outputs
  pinMode(sensorMotorCombo[0][0], OUTPUT); //pin 11 (trigger pin) is output
  pinMode(sensorMotorCombo[0][1], INPUT); //pin 12 (echo pin) is input
  pinMode(sensorMotorCombo[0][2], OUTPUT); //pin 11 (trigger pin) is output

  pinMode(sensorMotorCombo[1][0], OUTPUT); //pin 10 (trigger pin) is output
  pinMode(sensorMotorCombo[1][1], INPUT); //pin 9 (echo pin) is input
  pinMode(sensorMotorCombo[1][2], OUTPUT); //pin 11 (trigger pin) is output

  pinMode(sensorMotorCombo[2][0], OUTPUT); //pin 8 (trigger pin) is output
  pinMode(sensorMotorCombo[2][1], INPUT); //pin 7 (echo pin) is input
  pinMode(sensorMotorCombo[2][2], OUTPUT); //pin 11 (trigger pin) is output

}

void loop() {
  // If it is too soon, we will not run the loop again.
  if (millis() < NEXT_TIME) {
    return;
  }
  // Read values from all sensors.
  // Store them into array
  for (int i = 0; i < 3; i++) {
    int triggerPin = sensorMotorCombo[i][0];
    int echoPin = sensorMotorCombo[i][1];
    distances[i] = readSensor(triggerPin, echoPin);
  }
  // Read value from potentiometer
  double potValue = readPot();
  // Take distances, calculate how much they should be vibrating with relation
  // to distance. Multiply that by the potentiometer value (which is between 0 and 1)
  // as a strength multiplier.
  for (int i = 0; i < 3; i++) {
    int strength = (map(distances[i], MIN_DISTANCE, MAX_DISTANCE, 200, 0) * potValue);
    writeMotor(sensorMotorCombo[i][2], strength);
  }
  // Set the next time the loop will be allowed to execute again.
  NEXT_TIME = millis() + 60;
}//end of loop

/***
 * Reads potentiometer and returns percentage
 */
double readPot() {
  // Read the value from the pin, it will be between 0 and 1024, we then convert this to a percentage from this range.
  // This is done with map and then a double divide/cast.
  int pinValue = analogRead(A7);
  return map(pinValue, 0, 1024, 0, 100) / (double) 100;
}

/***
 * Reads a value from a sensor by taking a trigger and echo pin.
 */
long readSensor(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long cm = duration / 2 / 29.1;
  if (cm < MIN_DISTANCE) {
    return MIN_DISTANCE;
  } else if (cm > MAX_DISTANCE) {
    return MAX_DISTANCE;
  }
  return cm;
}

/***
 * Writes a value to our motor, this value will be how much it vibrates.
 */
void writeMotor(int motorPin, int vibrateStr) {
  analogWrite(motorPin, vibrateStr);
}
