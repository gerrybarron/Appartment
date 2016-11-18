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

int Ramp = 22; //Ramp, Sig and freq are variables used to generate output to dweet.io for freeboard.io, etc.
float Sig = 0;
float freq = 1/8.1737;

SoftwareSerial esp8266(2,3);

void setup() {
  Serial.begin(9600);
  esp8266.begin(9600); // your esp's baud rate might be different
   
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
  int len;
  char ramp_buf[10];
  char sig_buf[10];
  String sig_string;

  len = 80;
  
  dtostrf(Sig, 9, 3, sig_buf);//Special appraoch required for floating point value here.
                              //Have to use dtostrf instead of sprintf since sprintf doesn't
                              //support floats on Arduino. 
  sig_string = String(sig_buf); //convert from character buffer array to string so
                                //white space can be cleared with .trim().
  sig_string.trim();
  
  len += sig_string.length();
  len += sprintf (ramp_buf, "%d", Ramp);
  len += (sizeof(thing_name) - 1);//sizeof will return 11 for a 10 character thing name because of null terminator
                                  //so subtract 1

  //form and send the HTTP POST message
  String cmd;
  cmd = "AT+CIPSEND=";
  cmd += len;
  sendData(cmd+"\r\n",1000,DEBUG);
  
  String cmdSend;
  cmdSend = "POST /dweet/for/";  
  //Serial.print(F("GET /dweet/for/"));// both POST and GET work
  cmdSend += thing_name;
  cmdSend += "?Ramp=";
  cmdSend += ramp_buf;
  cmdSend += "&Sig=";
  cmdSend += sig_string;
  cmdSend += " HTTP/1.1\r\n";
  cmdSend += "Host: dweet.io\r\n";
  //Serial.print(F("Connection: close\r\n"));//in some cases connection needs to be closed after POST
  cmdSend += "Connection: keep-alive\r\n";//in this case we want to keep the connection alive
  sendData(cmdSend+"\r\n",10000,DEBUG);
  
  
  delay(1000);
 
  Ramp+=17;
  if(Ramp>99){
    Ramp=10;
  }
  Sig = sin(2 * PI * freq * millis() / 1000);

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