#include <SPI.h>
#include <WiFi.h>
#include <Wire.h>
#include "Adafruit_TMP006.h"
#include <BlynkSimpleEnergiaWiFi.h>
// your network name also called SSID
char ssid[] = "Nokia8";
char auth[] = "06abb7cd5fe148dfb1e2573c4695162f";
// your network password
char password[] = "hello123";
#include <BMA222.h>
// Sensor objects
BMA222 mySensor;
Adafruit_TMP006 tmp006(0x41);
BlynkTimer timer;
int dataX = 0;
int dataY = 0;
int dataZ = 0;
void setup() {  
  Serial.begin(115200);
  Blynk.begin(auth, ssid, password);
  mySensor.begin();
//  Blynk.begin(auth, ssid, pass);
  // attempt to connect to Wifi network:
  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, LOW);
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  // We are connected and have an IP address.
  Serial.print("\nIP Address obtained: ");
  Serial.println(WiFi.localIP());
  // Get Temperature Test
  if (!tmp006.begin()) {
    Serial.println("No sensor found");
    while (1);
  } 
  timer.setInterval(3000L, sendSensor);
}
BLYNK_WRITE(V1)
{
  //Print to the terminal
  BLYNK_LOG("Got a value: %s", param.asStr());
  
  //save teh value fromt he app to the variable i
  //if i=1, turn the LED on
  //if i=0, turn the LED off
  int i = param.asInt(); 
  if(i == 1)
  {
    digitalWrite(RED_LED, HIGH);
  }
  else if(i == 0)
  {
    digitalWrite(RED_LED, LOW);
  }
}
void sendSensor()
{
  
  Blynk.virtualWrite(V5,getTemp());
  dataX = mySensor.readXData();
  Blynk.virtualWrite(V6,dataX);
  //Send Y axis data
  dataY = mySensor.readYData();
  Blynk.virtualWrite(V7,dataY);
  //Send Z axis data
  dataZ = mySensor.readZData();
  Blynk.virtualWrite(V8,dataZ);
}

void loop() {   
  
  Serial.println("Temperature: ");
  //double t=getTemp();
  
  Serial.println(getTemp());
  Serial.println("X: ");
  //double t=getTemp();
  
  Serial.println(dataX);
  Serial.println("Y: ");
  //double t=getTemp();
  
  Serial.println(dataY);
  Serial.println("Z: ");
  //double t=getTemp();
  
  Serial.println(dataZ);

  Blynk.run();
  timer.run();
  
  //delay(3000);  
}
// getTemp() function for CC3200
double getTemp() {
  return (double)tmp006.readObjTempC();
}
