#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4

void setup(){
  Serial.begin(9600);
  Serial.println ("DHT TEST PROGRAM");
  Serial.print("LIBRARY VERSION");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("Type, \tstatus, \tHumidity, (%), \tTemperature(C)");
}

void loop(){
  int chk;
  int val;
  int val1;
  val=analogRead(0);//Connect the sensor to analog pin 0
  val1=analogRead(5);
  Serial.print("DHT11, \t");
  chk = DHT.read(DHT11_PIN);
  switch(chk){
    case DHTLIB_OK:
          Serial.print("OK, \t");
          break;
    case DHTLIB_ERROR_CHECKSUM:
          Serial.print("Checksum error, \t");
          break;
    case DHTLIB_ERROR_TIMEOUT:
          Serial.print("Time out error, \t");
          break;
    default:
          Serial.print("Unknown error, \t");
          break;
    }
    Serial.print(val,DEC);
    Serial.println(val1,DEC);
    Serial.print(DHT.humidity, 1);
    Serial.print(",\t");
    Serial.println(DHT.temperature,1);
    
    delay(1000);
}
