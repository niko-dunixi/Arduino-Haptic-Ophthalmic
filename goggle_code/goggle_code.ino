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

int arrSize = sizeof(sensorMotorCombo)/sizeof(int); //cluge because you can't do array.length in c

//data manipulation variables
long duration, cm;
long distances[3];
int MAX_DISTANCE = 35; //this is in cm - we will use this distance to map the values for analogWrite
int MIN_DISTANCE = 10; //this is in cm - this is the closest we want to read from the sensor
unsigned long NEXT_TIME = millis();
int motorSpeed = 0; // variable to hold map function data

int MAX_SPEED = 200;

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
  if (millis() < NEXT_TIME) {
    return;
  }

  for (int i = 0; i < 3; i++) {
    int triggerPin = sensorMotorCombo[i][0];
    int echoPin = sensorMotorCombo[i][1];
    distances[i] = readSensor(triggerPin, echoPin);
  }
  double potValue = readPot();
  for (int i = 0; i < 3; i++) {
    int strength = (map(distances[i], MIN_DISTANCE, MAX_DISTANCE, 200, 0) * potValue);
    writeMotor(sensorMotorCombo[i][2], strength);
  }
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

void resetMotor(int motorPin) {
  analogWrite(motorPin, 0);
}

void writeMotor(int motorPin, int vibrateStr) {
  analogWrite(motorPin, vibrateStr);
}
