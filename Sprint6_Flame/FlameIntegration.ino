//#include <Servo.h>
//Servo servo1;
int buzzer = 8; 
int relayPin = 9;
int trigPin = 5;
int echoPin = 4;
long distance;
long duration;

int flame_sensor = 7;
int flame_detected;

 
void setup() 
{
  pinMode(relayPin, OUTPUT);  //initialize the LED as output
  Serial.begin(9600); 
   //pinMode(led, OUTPUT);
  //servo1.attach(7); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);// put your setup code here, to run once:

 pinMode(buzzer, OUTPUT);
//  pinMode(LED, OUTPUT);
  pinMode(flame_sensor, INPUT);


}
 
void loop() {
  ultra();
  //servo1.write(0);
  if(distance <= 10){
  //servo1.write(90);
 // digitalWrite(led, LOW);
  digitalWrite(relayPin, LOW);
  } else {
    //digitalWrite(led, LOW);
    digitalWrite(relayPin, HIGH);
  }

  flame_detected = digitalRead(flame_sensor);
  if (flame_detected == 1)
  {
    Serial.println("Flame detected...! take action immediately.");
    digitalWrite(buzzer, LOW);
//    digitalWrite(LED, HIGH);
    delay(200);
//    digitalWrite(LED, LOW);
    delay(200);
  }
  else
  {
    Serial.println("No flame detected. stay cool");
    digitalWrite(buzzer, HIGH);
//    digitalWrite(LED, LOW);
  }
  delay(1000);
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
