#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
 
void setup(){
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
  Serial.println("TempStats,\tSmokeStats,\tHumidity (%),\tTemperature (C),\tSmoke");
}
 
void loop(){
  dhtSensor();
  
}
void dhtSensor(){
    int chk;
    int smokeVal;
  smokeVal=analogRead(0);
  //Serial.print("DHT11, \t");
  
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
  if (smokeVal > 0){
    Serial.print("OK,\t");
  }
  else {
    Serial.print("Sensor is offline.,\t");
    }
 // DISPLAT DATA
 
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.print(DHT.temperature,1);
  Serial.print(",\t");
  Serial.println(smokeVal);
 
  delay(1000);
}

