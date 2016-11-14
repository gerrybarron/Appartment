#include <SoftwareSerial.h>
#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
#define DEBUG true
#define SSID        "Barron Res."
#define PASS        "incorrect"
#define URL        "www.dweet.io"                                   
#define PORT        80//443 is for secure socket which seems not to be supported at this point on the ESP8266
#define thing_name  "gerrybarrontest1"
#define MAX_SERVER_CONNECT_ATTEMPTS 5
int smkPin = 0;
SoftwareSerial esp8266(2,3);

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  int chk;
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
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
  sendData("AT+RST\r\n",2000,DEBUG);
  sendData("AT+GMR\r\n",2000,DEBUG);
  sendData("AT+CWMODE=1\r\n",1000,DEBUG);
  sendData("AT+CIPMUX=0\r\n",1000,DEBUG);
  
  Serial.println("Connecting to WiFi access point...");
  
  String cmd = "AT+CWJAP=\"";
  cmd += SSID;
  cmd += "\",\"";
  cmd += PASS;
  cmd += "\"";
  
  sendData(cmd+"\r\n",10000,DEBUG);
  //sendData("AT+CWJAP?\r\n",1000,DEBUG);
  Serial.println("Connected to the Access Point");
  Serial.println("Connecting to dweet...");

  cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += URL;//"www.dweet.io";
  cmd += "\",";
  cmd += PORT;
  Serial.println(cmd);
  sendData(cmd+"\r\n",5000,DEBUG);
}

void loop() {
  int smkVal = analogRead(smkPin);
  int len;
  int hum = DHT.humidity;
  int temp = DHT.temperature;
  
  len = 97;
  len += (sizeof(DHT.humidity));
  len += (sizeof(DHT.temperature));
  len += (sizeof(smkVal));
  len += (sizeof(thing_name) - 1);

  //form and send the HTTP POST message
  String cmd;
  cmd = "AT+CIPSEND=";
  cmd += len;
  sendData(cmd+"\r\n",1000,DEBUG);
  
  String cmdSend;
  cmdSend = "POST /dweet/for/"; //16  
  //Serial.print(F("GET /dweet/for/"));// both POST and GET work
  cmdSend += thing_name;
  cmdSend += "?Humidity="; //26
  cmdSend += hum;
  cmdSend += "&Temperature="; //39
  cmdSend += temp;
  cmdSend += "&Gas="; //44
  cmdSend += smkVal;
  cmdSend += " HTTP/1.1\r\n"; //50
  cmdSend += "Host: dweet.io\r\n"; //66
  //Serial.print(F("Connection: close\r\n"));//in some cases connection needs to be closed after POST
  cmdSend += "Connection: keep-alive\r\n";//in this case we want to keep the connection alive
  sendData(cmdSend+"\r\n",5000,DEBUG); //97
}

String sendData(String command, const int timeout, boolean debug)
{
    String response = "";
    
    esp8266.print(command); // send the read character to the esp8266
    
    long int time = millis();
    
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = esp8266.read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
      Serial.print(response);
    }
    
    return response;
}

