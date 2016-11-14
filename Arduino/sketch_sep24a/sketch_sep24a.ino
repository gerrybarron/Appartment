byte ledPin[] = {1,2,3,4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int ledDelay(65); // delay between changes
int inPin = 0;
int direction = 1;
int currentLED = 0;
unsigned long changeTime;
int state = HIGH;
int previous = LOW;
int reading;
long time =0;
long debounce = 20;

void setup() {
for (int x=0; x<13; x++) {
pinMode(ledPin[x], OUTPUT); }
changeTime = millis();
pinMode(inPin, INPUT);
}
void wasak(){
  if ((millis() - changeTime) > ledDelay) {
  changeLED();
changeTime = millis();

} 

  }
void loop() {
// if it has been ledDelay ms since last change
       
  wasak();
 reading = digitalRead(inPin);


    if(reading == HIGH && previous == LOW && millis()-time > debounce)
    {
      if (state == HIGH){
      state = LOW;
      digitalWrite(ledPin[1], state);
       digitalWrite(ledPin[2], state);
       digitalWrite(ledPin[3], HIGH);
       digitalWrite(ledPin[4], state);
       digitalWrite(ledPin[5], state);
       digitalWrite(ledPin[6], state);
       digitalWrite(ledPin[7], state);
       digitalWrite(ledPin[8], HIGH);
       digitalWrite(ledPin[9], state);
       digitalWrite(ledPin[10], state);
       digitalWrite(ledPin[11], state);
       digitalWrite(ledPin[12], state);
      }
      else{
      state=HIGH;
      wasak();     
      }
      time=millis();
      }

       

      previous = reading;
}
void changeLED() {
// turn off all LED's
for (int x=0; x<13; x++) {
digitalWrite(ledPin[x], LOW);
}
// turn on the current LED

if(reading == HIGH && previous == LOW && millis()-time > debounce)
    {
      if (state == HIGH){
      state = LOW;
      digitalWrite(ledPin[currentLED], LOW);
      digitalWrite(ledPin[1], state);
       digitalWrite(ledPin[2], state);
       digitalWrite(ledPin[3], HIGH);
       digitalWrite(ledPin[4], state);
       digitalWrite(ledPin[5], state);
       digitalWrite(ledPin[6], state);
       digitalWrite(ledPin[7], state);
       digitalWrite(ledPin[8], HIGH);
       digitalWrite(ledPin[9], state);
       digitalWrite(ledPin[10], state);
       digitalWrite(ledPin[11], state);
       digitalWrite(ledPin[12], state);
      }
      else{
      state=HIGH;
      digitalWrite(ledPin[currentLED], HIGH);     
      }
      time=millis();
      }
// increment by the direction value
currentLED += direction;
// change direction if we reach the end
if (currentLED == 12) {direction = -1;}
if (currentLED == 0) {direction = 1;}
}

