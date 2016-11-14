#include <SoftwareSerial.h>
#include <dht11.h>
dht11 DHT;

#define DHT11_PIN 4 //Temp & Humidity Pin Digital
#define DEBUG true
#define SSID        "Barron Res." //SSID of Wireless Network
#define PASS        "incorrect" //Password of Wireless Network
#define URL        "www.dweet.io" //Post data to dweet.io
#define PORT        80//443 is for secure socket which seems not to be supported at this point on the ESP8266
#define thing_name  "gerrybarrontest1" //Name of the device
#define MAX_SERVER_CONNECT_ATTEMPTS 5

int smkPin = 0; //Smoke Pin Analog
int alrtPin = 13; //LED ALERT
int txPin = 12; //LED SEND
int rxPin = 11; //LED RECIEVE
int pwrPin = 10; //LED POWER
int bzPin = 9; //BUZZER

SoftwareSerial esp8266(2,3);//TX,RX

void setup() {
  pinMode(alrtPin,OUTPUT);
  pinMode(txPin,OUTPUT);
  pinMode(rxPin,OUTPUT);
  pinMode(pwrPin,OUTPUT);
  pinMode(bzPin,OUTPUT);
  
  lightTest(); //Test all LED lights if its working
  
  digitalWrite(pwrPin,HIGH); //Check if the device is Powered On
  
  Serial.begin(9600); //Baud rate for Serial
  esp8266.begin(9600); // your esp's baud rate might be different

  testDHT11(); //Test if DHT11 is Working
  
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
  float lat = 14.929194;
  float lng = 120.198920;
  String lat_string;
  String lng_string;
  
  lat_string = String(lat);
  lng_string = String(lng);
  lat_string.trim();
  lng_string.trim();
  
  len = 119; //97
  len += (sizeof(DHT.humidity));
  len += (sizeof(DHT.temperature));
  len += (sizeof(smkVal));
  len += lat_string.length();
  len += lng_string.length();
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
  cmdSend += "&Latitude="; //54
  cmdSend += lat; 
  cmdSend += "&Longitude="; //65
  cmdSend += lng; 
  cmdSend += " HTTP/1.1\r\n"; //50
  cmdSend += "Host: dweet.io\r\n"; //66
  //Serial.print(F("Connection: close\r\n"));//in some cases connection needs to be closed after POST
  cmdSend += "Connection: keep-alive\r\n";//in this case we want to keep the connection alive
  sendData(cmdSend+"\r\n",5000,DEBUG); //97  
}

//test all LED lights if working
void lightTest() { 
  digitalWrite(alrtPin,HIGH);
  delay(100);
  digitalWrite(alrtPin,LOW);
  digitalWrite(txPin,HIGH);
  delay(100);
  digitalWrite(txPin,LOW);
  digitalWrite(rxPin,HIGH);
  delay(100);
  digitalWrite(rxPin,LOW);
  digitalWrite(pwrPin,HIGH);
  delay(100);
  digitalWrite(pwrPin,LOW);
  delay(100);
  digitalWrite(pwrPin,HIGH);
  digitalWrite(alrtPin,HIGH);
  digitalWrite(rxPin,HIGH);
  digitalWrite(txPin,HIGH);
  delay(500);
  digitalWrite(pwrPin,LOW);
  digitalWrite(alrtPin,LOW);
  digitalWrite(rxPin,LOW);
  digitalWrite(txPin,LOW);
  } // end of lightTest

//Start of function testDHT11: Test if DHT11 is Working
void testDHT11(){
  Serial.print("LIBRARY VERSION: "); //Check the Library Version of DHT11 module
  Serial.println(DHT11LIB_VERSION); //Print Version Number
  
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
}//end of testDHT11

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

