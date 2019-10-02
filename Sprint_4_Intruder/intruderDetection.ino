#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>

#include <FirebaseArduino.h>

#include <ArduinoJson.h>

char auth[] = "7e6899fb4f1d4db0bf924211adb9e8dc";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AndroidAP";
char pass[] = "123456789";

String apiKey = "YY1BHR75VRQZAH96"; 
   //  Enter your Write API key from ThingSpeak
const char* server = "api.thingspeak.com";

#include  <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
WiFiClient client;
#define HOSTIFTTT "maker.ifttt.com"
#define EVENTO "IOT-G"

#define IFTTTKEY "f5pl4NqClPQ9OJDG-qyt5uRr3SpEn8CJ1WhCUb0YavY"

#define FIREBASE_HOST "iot-g-78a25.firebaseio.com"
#define WIFI_SSID "AndroidAP" // Change the name of your WIFI
#define WIFI_PASSWORD "123456789" // Change the password of your WIFI




const int trigPin = 4;
const int echoPin = 5;



void notifyIFTT(){
  if (client.connected())
  {
    client.stop();
  }
  client.flush();
  if (client.connect(HOSTIFTTT,80)) {
    Serial.println("Connected");
    // build the HTTP request
    String toSend = "GET /trigger/";
    toSend += EVENTO;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += "intruder";
    toSend += "&value2=";
    toSend += "detected";
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";
    client.print(toSend);
  }
  client.flush();
  client.stop();  
  delay(500);  
  }



void setup() {

 Serial.begin(115200);
 delay(10);

  Blynk.begin(auth, ssid, pass);
 
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
   
    
     pinMode(trigPin, OUTPUT);
     pinMode (echoPin, INPUT);
     delay(10);
   
   
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {


  
  // proximity detector/intruder detection
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  float duration = pulseIn(echoPin,HIGH);
  float distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);

  String dist = String(distance);
  
  Firebase.pushString("/Distance",dist);
  if(distance<=20){
    notifyIFTT();
    }
      
  //  delay(200);
  thingSpeak();
}


}
