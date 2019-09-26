
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
#define EVENTGAS "GasTrigger"
#define IFTTTKEY "f5pl4NqClPQ9OJDG-qyt5uRr3SpEn8CJ1WhCUb0YavY"

#define FIREBASE_HOST "iot-g-78a25.firebaseio.com"
#define WIFI_SSID "AndroidAP" // Change the name of your WIFI
#define WIFI_PASSWORD "123456789" // Change the password of your WIFI



float gasValue;


const int MQ2pin = A0; // gas sensor

void notifyIFTT(){
  if (client.connected())
  {
    client.stop();
  }
  client.flush();


void notifyGas(){
//  if (client.connected())
//  {
//    client.stop();
//  }
//  client.flush();
  if (client.connect(HOSTIFTTT,80)) {
    Serial.println("Connected");
    // build the HTTP request
    String toSend = "GET /trigger/";
    toSend += EVENTGAS;
    toSend += "/with/key/";
    toSend += IFTTTKEY;
    toSend += "?value1=";
    toSend += "GAS LEAKAGE";
    toSend += "&value2=";
    toSend += "ALERT!!!";
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += HOSTIFTTT;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";
    client.print(toSend);
    Serial.println("GAS ALERT");
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
    dht.begin();

      pinMode (MQ2pin,INPUT);
   delay(20000); // allow the MQ-2 to warm up
    
     pinMode(trigPin, OUTPUT);
     pinMode (echoPin, INPUT);
     delay(10);
   
   
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {


    gasValue =analogRead(MQ2pin);
    Serial.print("Gas Value: ");
    Serial.println(gasValue);
    String gasV = String(gasValue);
    Firebase.pushString("GAS",gasV);
    delay(200);

    if(gasValue > 300){
      
        notifyGas();
      }
      
  //  delay(200);
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
                            

                             //gasLevel
                              postStr +="&field4=";
                             postStr += String(gasValue);
                            
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
 
                             Serial.println("%. Send to Thingspeak.");

                         
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}
