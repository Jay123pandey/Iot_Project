#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHT.h"

#define DHTPIN D2// what pin we're connected to 2

#define DHTTYPE DHT11// DHT 11 



int Gassensor = A0;
int fan = D5;

char auth[] = "vTOrFmdRpiYFA52cfOhW6dajJB665Z7z"; //auth code to send notification to the smartphone
char ssid[] = "pandey";
char pass[] = "123456789";

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Blynk.begin(auth, ssid, pass);
  pinMode(Gassensor, INPUT);
  pinMode(fan,OUTPUT);
  Serial.begin(9600); 
  Serial.println("Temperature and gas detection");
 
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float humudity = dht.readHumidity();
  // Read temperature as Celsius
  float temperature = dht.readTemperature();
  // Read temperature as Fahrenheit
  float fahrenheit = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humudity) || isnan(temperature) || isnan(fahrenheit)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!
  float hi = dht.computeHeatIndex(fahrenheit, humudity);

  Serial.print("Humidity: "); 
  Serial.print(humudity);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(temperature);
  Serial.print(" *C ");
  Serial.print(fahrenheit);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");


   int reading=analogRead(Gassensor);
   //digitalWrite(fan,LOW);
  if(reading>=300 || temperature>=30){
    digitalWrite(fan,LOW);
    Blynk.notify("High temperature/gas detected");
  }
  else{
    digitalWrite(fan,HIGH);
  }
  delay(10);
  Serial.println("Gas Reading");
Serial.println(reading);
}
