

#include <FirebaseArduino.h>
#include "DHT.h"
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

#define DHTPIN 14    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14

#define DHTTYPE DHT11   // DHT 11
DHT dht(DHTPIN, DHTTYPE);




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

 
 
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
    dht.begin();

      
 
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

    
    
    h = dht.readHumidity();
    
    t = dht.readTemperature();  // Reading temperature as Celsius (the default)
   
    Serial.print("Humidity: ");
    Serial.println(h);
     String hum = String(h);
    Serial.print("Temperature: ");
     String temp = String(t);
    Serial.println(t);
     Firebase.pushString ("/DHT11/Temp",temp);
    Firebase.pushString ("/DHT11/Humidity",hum);
  
    
  
    
  thingSpeak();
}

void thingSpeak(){
   if (isnan(t)) 
                 {
                     Serial.println("Failed to read from sensor!");
                      return;
                 }
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);

                              //humidity
                             postStr +="&field2=";
                             postStr += String(h);

                            
                            
                             postStr += "\r\n\r\n";

                             
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t); 

                              Serial.print("Humidity: ");
                             Serial.print(h);
                             
                             Serial.println("%. Send to Thingspeak.");

                         
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
