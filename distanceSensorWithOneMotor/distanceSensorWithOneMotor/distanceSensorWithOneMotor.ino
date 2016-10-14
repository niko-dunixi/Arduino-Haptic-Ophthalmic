
//set up distance sensor pins

//red wire connects 5v on Nano to VCC on SR04
//brown wire connects SR04 to Ground
int trigPin = 11;    //Trigger pin of the SR04 sensor - green Jumper
int echoPin = 12;    //Echo pin of the SR04 sensor- yellow Jumper
long duration, cm;


//set up motor pin
int motorPin1 = 3; // grey pin - the motor will be connected to pin D3

//data manipulation integers
int farthestDistance = 25; //this is in cm - we will use this distance to map the values for analogWrite
int closestDistance = 5; //this is in cm - this is the closest we want to read from the sensor
int motorWrite = 0; // variable to hold map function data
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);


}
 
void loop()
{
 
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  

  //vibrate the motor based on cm
  //if statement keeps motor from vibrating if sensor senses beyond farthestDistance

  //if object is within "farthest distance" range
  if (cm < farthestDistance){
    motorWrite = map(cm, closestDistance, farthestDistance, 200, 10);
    Serial.print(cm);
    Serial.print(" cm, ");
    Serial.print("MotorWrite ");
    Serial.print(motorWrite);
    Serial.println();
    
    analogWrite(motorPin1, motorWrite);

  }else{
    analogWrite(motorPin1, 0);    
  }
  
delay(100);  
}
