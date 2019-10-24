//#include <Servo.h>
//Servo servo1;
int led = 13; 
int relayPin = 6;
int trigPin = 9;
int echoPin = 8;
long distance;
long duration;
 
void setup() 
{
  pinMode(relayPin, OUTPUT);  //initialize the LED as output
  Serial.begin(9600); 
   pinMode(led, OUTPUT);
  //servo1.attach(7); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);// put your setup code here, to run once:
}
 
void loop() {
  ultra();
  //servo1.write(0);
  if(distance <= 10){
  //servo1.write(90);
  //digitalWrite(led, HIGH);
  digitalWrite(relayPin, HIGH);
  } else {
    //digitalWrite(led, LOW);
    digitalWrite(relayPin, LOW);
  }
}
 
void ultra(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  Serial.println("Distance: " + distance);
  }
