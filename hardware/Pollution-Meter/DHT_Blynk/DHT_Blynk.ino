//DHT11 And NodeMCU With Blynk
//My GitHub https://github.com/manoranjan2050
//My Hackster.io https://www.hackster.io/Manoranjan2050
//This Video Link https://youtu.be/0dbws1i2GoE
#define BLYNK_PRINT Serial
 
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "06abb7cd5fe148dfb1e2573c4695162f";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Nokia8";

char pass[] = "hello123";
int sensorThres = 400;

#define DHTPIN 0          // D3
int smokeA0 = A0;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
   int analogSensor = analogRead(smokeA0);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
  Blynk.virtualWrite(V7, analogSensor);
}
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(smokeA0, INPUT);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
 
  dht.begin();
 
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
