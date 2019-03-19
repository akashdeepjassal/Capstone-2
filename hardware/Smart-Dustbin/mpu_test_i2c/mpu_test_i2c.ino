#include "Wire.h"

// I2C address of the MPU-6050 when ADo=0
const int MPU_addr=0x68; 

// I2C address of the MPU-6050 when ADO=1

const int MPU_addr=0x68; 

void setup() {
Wire.begin();
 
Serial.begin(115200);
}
 
void loop() {
byte error;
// We are using the return value of
// the Write.endTransmisstion to see if
// a device did acknowledge to the address.
Wire.beginTransmission(MPU_addr);
error = Wire.endTransmission();
 
if (error == 0)
{
Serial.println("Device Found");
}
else
{
Serial.println("No Device Found");
}
delay(5000); // Wait 5 seconds and scan again
}
