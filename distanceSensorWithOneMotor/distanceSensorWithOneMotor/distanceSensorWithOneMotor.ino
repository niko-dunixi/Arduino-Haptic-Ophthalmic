//red wire connects 5v on Nano to VCC on SR04
//brown wire connects SR04 to Ground
//Trigger pin of the SR04 sensor - green Jumper
//Echo pin of the SR04 sensor- yellow Jumper

//set up distance sensor pins
int sensorMotorCombo[1][3]={
  {11,  12, 3}  // Trigger pin for sensor0 = 11, echo pin for sensor0 = 12, motor for sensor0 = 3
};


//data manipulation variables
long duration, cm;
int farthestDistance = 25; //this is in cm - we will use this distance to map the values for analogWrite
int closestDistance = 5; //this is in cm - this is the closest we want to read from the sensor
int motorSpeed = 0; // variable to hold map function data
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  
  //Define inputs and outputs
  pinMode(sensorMotorCombo[0][0], OUTPUT);
  pinMode(sensorMotorCombo[0][1], INPUT);

}
 
void loop()
{
  cm = getDistanceFromSensor(0);

  writeMotor(cm, sensorMotorCombo[0][2]);
  
delay(100);  
}//end of loop

long getDistanceFromSensor(int sensorNumber){
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(sensorMotorCombo[sensorNumber][0], LOW);
  delayMicroseconds(5);
  digitalWrite(sensorMotorCombo[sensorNumber][0], HIGH);
  delayMicroseconds(10);
  digitalWrite(sensorMotorCombo[sensorNumber][0], LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(sensorMotorCombo[sensorNumber][1], INPUT);
  duration = pulseIn(sensorMotorCombo[sensorNumber][1], HIGH);
 
  // convert the time into a distance
  long tempCm = (duration/2) / 29.1;
  return tempCm;
}


void writeMotor(long dist, int motorToWrite){

    //vibrate the motor based on cm
    //if statement keeps motor from vibrating if sensor senses beyond farthestDistance  
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

      analogWrite(motorToWrite, motorSpeed); //send the instructions to the motor
  }else{
    analogWrite(motorToWrite, 0);    //turn the motor off
  }
  
}//end of writeMotor function

