/*MCP41010 Tutorial*/

#include <SPI.h>  
const int CS = 4;
int PotWiperVoltage = A0;
int RawVoltage = 0;
float Voltage = 0;
 
void setup() {
  pinMode (CS, OUTPUT);
  digitalWrite(CS,HIGH);    
  Serial.begin(9600); while(!Serial);delay(1);Serial.println();
  SPI.begin();
  Serial.println("Setup done!");
}
 
void loop() {
  // move the potentiometer in one direction
  for (int level = 0; level < 255; level++) 
  {
    MCP41010Write(level);
    delay(10);
    RawVoltage = analogRead(PotWiperVoltage);
    Voltage = (RawVoltage * 3.3 )/ 1024.0;
    Serial.print("Level = " );                      
    Serial.print(level);      
    Serial.print("\t Voltage = ");
    Serial.println(Voltage);  
  }
  delay(2000);  // wait a couple seconds
  // Now mover potentiometer in other directions
  
  for (int level = 255; level > 0; level--) 
  {
    MCP41010Write(level);
    delay(10);
    RawVoltage = analogRead(PotWiperVoltage);
    Voltage = (RawVoltage * 3.3 )/ 1024.0;
    Serial.print("Level = " );                      
    Serial.print(level);      
    Serial.print("\t Voltage = ");
    Serial.println(Voltage); 
  }
   delay(2000);
}
 
void MCP41010Write(byte value) 
{
  
  // Note that the integer vale passed to this subroutine
  // is cast to a byte
  digitalWrite(CS,LOW);
  delay(10);
  SPI.transfer(B00010001); // This tells the chip to set the pot
  SPI.transfer(value);     // This tells it the pot position
  digitalWrite(CS,HIGH); 
}
