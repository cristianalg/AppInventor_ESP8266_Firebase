#include <FirebaseArduino.h>
#include "DHT.h"
#include  <ESP8266WiFi.h>

#define FIREBASE_HOST "seminario-22778.firebaseio.com"
#define FIREBASE_AUTH "VvyG9JPhInF8IzQtsaSWpH2B0geHn8BJQY778OSA"  
#define WIFI_SSID "userWifi"
#define WIFI_PASSWORD "passWifi" 

#define DHTPIN 14    
#define DHTTYPE DHT11   
DHT dht(DHTPIN, DHTTYPE);

void setup() {
 Serial.begin(115200);
 
  Serial.print("A ligar a: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Ligado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  dht.begin();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}
void loop() {
  delay(10);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Humidade: "); Serial.print(h); Serial.println(" %");
  Serial.print("Temperatura: "); Serial.print(t); Serial.println("ºC");

  Firebase.setFloat ("Temperature",t);
  Firebase.setFloat ("Humidity",h);
  delay(200);
}
