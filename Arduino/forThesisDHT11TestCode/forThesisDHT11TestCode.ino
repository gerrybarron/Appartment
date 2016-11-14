#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
int redPin = 13;
int greenPin = 12;
int buzzPin = 8;

void setup(){
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
}
 
void loop(){
  int chk;
  int fah;
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);    // READ DATA
  switch (chk){
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
 int f = DHT.temperature;
 fah = ((f*9)/5)+32;
 // DISPLAT DATA

 
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
 
  delay(1000);
  
  if ((DHT.temperature >= 32))
    {
      digitalWrite(redPin, HIGH);
      digitalWrite(buzzPin, HIGH);
      delay(500);
      digitalWrite(greenPin, LOW);
      
    }
  else
    {
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
      digitalWrite(buzzPin, LOW);
      
    }
}
