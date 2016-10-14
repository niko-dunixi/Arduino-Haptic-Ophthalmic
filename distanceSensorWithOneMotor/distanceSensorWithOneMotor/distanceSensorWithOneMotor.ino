
//set up distance sensor1 pins
                      //red wire connects 5v on Nano to VCC on SR04
                      //brown wire connects SR04 to Ground
int trigPin1 = 11;    //Trigger pin of the SR04 sensor - green Jumper
int echoPin1 = 12;    //Echo pin of the SR04 sensor- yellow Jumper
long duration, cm;


//set up motor pin
int motorPin1 = 3; // grey pin - motor1 will be connected to pin D3

//data manipulation integers
int farthestDistance = 25; //this is in cm - we will use this distance to map the values for analogWrite
int closestDistance = 5; //this is in cm - this is the closest we want to read from the sensor
int motorSpeed = 0; // variable to hold map function data
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);


}
 
void loop()
{
 
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration = pulseIn(echoPin1, HIGH);
 
  // convert the time into a distance
  cm = (duration/2) / 29.1;
  

  //vibrate the motor based on cm
  //if statement keeps motor from vibrating if sensor senses beyond farthestDistance

  writeMotor(cm, motorPin1);
  
delay(100);  
}//end of loop

void writeMotor(long dist, int motorToWrite){
    if (dist < farthestDistance){
    motorSpeed = map(dist, closestDistance, farthestDistance, 200, 10);
    
    Serial.print("MotorPin: ");
    Serial.print(motorToWrite);
    Serial.print(" Distance: ");
    Serial.print(dist);
    Serial.print(" cm, ");
    Serial.print(" Speed: ");
    Serial.print(motorSpeed);
    Serial.println();
    
    analogWrite(motorToWrite, motorSpeed);

  }else{
    analogWrite(motorToWrite, 0);    
  }
}

