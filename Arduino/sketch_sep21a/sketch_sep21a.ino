int inPin = 2;
int outPin = 13;
int state = HIGH;
int previous = LOW;
int reading;
long time = 0;
long debounce = 20;
void setup(){
    pinMode(inPin, INPUT);
    pinMode(outPin, OUTPUT);
  }
void loop(){
    reading = digitalRead(inPin);

    if(reading == HIGH && previous == LOW && millis()-time > debounce)
    {
      if (state == HIGH)
      state = LOW;
      else
      state=HIGH;

      time=millis();
      }

      digitalWrite(outPin, state);

      previous = reading;
  }
