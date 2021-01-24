class ledBlinking
{
  int ledPin;                     // Pin der LED
  int ledState;                   // Status der LED
  int repeat;                     // Anzahl der Wiederholungen
  long ledIntervall;              // Blinkintervall [ms]
  
  public:
  ledBlinking  (int pin, int iteration, long intervall)
  {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    ledIntervall = intervall;
    repeat = iteration;
  }

  void blinkIntervall()
  {
    for(int i=0; i<(repeat); i++)
    {
      digitalWrite(ledPin, HIGH);     
      delay(ledIntervall/2);
      digitalWrite(ledPin, LOW);
      delay(ledIntervall/2);
    }
  }
  void blinkFreeze()
  {
	for(int i=0; i<(repeat); i++)
	{
	  digitalWrite(ledPin, HIGH);     
      delay(ledIntervall/2);
      digitalWrite(ledPin, LOW);
      delay(ledIntervall/2);
    }
	digitalWrite(ledPin, HIGH);
  }
};

