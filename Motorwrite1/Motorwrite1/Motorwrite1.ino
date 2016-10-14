
//the nano can analogWrite to pins 3,5,6,9,10,11
//in this example, we are using pin 3
//analogWrite sends varying degrees of power from 0-255
//0 = 0 volts, 255 = 5 Volts

int motorPin1 = 3; //the motor will be connected to pin D3 on the Nano

void setup() {

  pinMode (motorPin1, OUTPUT); //set the pin to send electricity out
}

void loop() {
  // put your main code here, to run repeatedly:

  //this incrementally increases power to the motor
  for (int i=0; i<255; i++){
    analogWrite(motorPin1, i);
    delay(20);
  }

delay(2000);//power off for 2 seconds

}
