#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
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
#define IFTTTKEY "f5pl4NqClPQ9OJDG-qyt5uRr3SpEn8CJ1WhCUb0YavY"

#define FIREBASE_HOST "iot-g-78a25.firebaseio.com"
#define WIFI_SSID "AndroidAP" // Change the name of your WIFI
#define WIFI_PASSWORD "123456789" // Change the password of your WIFI


void setup() {

 Serial.begin(115200);
 delay(10);

  Blynk.begin(auth, ssid, pass);
 
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Firebase.begin(FIREBASE_HOST);
  
}

void loop() {

  Blynk.run();

      
  //  delay(200);
  thingSpeak();
}

}
