// Sensors 
int trigPin1 = 7;    //Trig - green Jumper
int echoPin1 = 8;    //Echo - yellow Jumper
int trigPin2 = 9;    //Trig 
int echoPin2 = 10;   //Echo 
int trigPin3 = 11;   //Trig 
int echoPin3 = 12;   //Echo 
long duration1, cm1;
long duration2, cm2;
long duration3, cm3;

//Output Pins
int motor1 = 4;
int motor2 = 5;
int motor3 = 6;

void setup() {
  //Serial Port begin
  Serial.begin (9600);
  
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  //Define motors
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(motor3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);

  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);

  pinMode(echoPin3, INPUT);
  duration3 = pulseIn(echoPin3, HIGH);
 
  // convert the time into a distance
  cm1 = (duration1/2) / 29.1;
  cm2 = (duration2/2) / 29.1;
  cm3 = (duration3/2) / 29.1;
  
  Serial.print(cm1);
  Serial.print("cm1");
  Serial.println();

  Serial.print(cm2);
  Serial.print("cm2");
  Serial.println();

  Serial.print(cm3);
  Serial.print("cm3");
  Serial.println();
  
  if (cm1 < 10) {
    digitalWrite(motor1, HIGH);
  }

  if (cm2 < 10) {
    digitalWrite(motor1, HIGH);
  }

  if (cm3 < 10) {
    digitalWrite(motor1, HIGH);
  }

  delay(250);
  
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
}
