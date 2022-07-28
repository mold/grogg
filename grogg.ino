#include <LiquidCrystal.h>
#include "Drinks.cpp"


class Pump {
  private:
    unsigned long startMillis;
    float _ratio;
    int timePeriodMillis = 2000;
    int _pin;
    int _speedPWM;

    shouldPump() {
      unsigned long timeSinceStart = millis() - startMillis;
      int timeElapsedInPeriod = timeSinceStart % timePeriodMillis;
      float percentElapsedOfPeriod = (float)timeElapsedInPeriod / (float)timePeriodMillis;

      // Serial.println("Should pump? timeSinceStart: " + String(timeSinceStart) + " timeElapsedInPeriod: " + String(timeElapsedInPeriod) + " percentElapsedOfPeriod: " + String(percentElapsedOfPeriod) + " ratio: " + String(_ratio));

      return percentElapsedOfPeriod <= _ratio;

    }
  public:
    Pump() {}
    Pump(int pin, float speedPWM) {
      _pin = pin;
      _speedPWM = speedPWM;

      pinMode(pin, OUTPUT);
    }

    start(float ratio) {
      startMillis = millis();
      _ratio = ratio;

      Serial.println("Start ratio: " + String(ratio, 2));
    }

    pump() {
      if (shouldPump()) {
        analogWrite(_pin, _speedPWM);
       // Serial.println("Should pump");
      } else {
        analogWrite(_pin, 0);
       // Serial.println("Shout NOT pump");
      }
    }

    stop() {
      analogWrite(_pin, 0);
    }
};

LiquidCrystal lcd(13, 12, 4, 5, 6, 7);

// Constants
const int buttonPinNext = A1;
const int buttonPinPrev = A2;
const int buttonPinPour = A0;

int pumpSpeedPWM = 150;

Drinks drinks = Drinks();

// Variables
int buttonStateNext = 0;
int lastButtonStateNext = 0;

int buttonStatePrev = 0;
int lastButtonStatePrev = 0;

int buttonStatePour = 0;
int lastButtonStatePour = 0;

Pump pump1 = Pump(10, pumpSpeedPWM);
Pump pump2 = Pump(9, pumpSpeedPWM);
Pump pump3 = Pump(3, pumpSpeedPWM);
Pump pump4 = Pump(11, pumpSpeedPWM);

// Setup
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(buttonPinNext, INPUT);
  pinMode(buttonPinPrev, INPUT);
  pinMode(buttonPinPour, INPUT);

  lcd.print("Press the button...");
}
// Main program
void loop()
{
  checkButtonNext();
  checkButtonPrev();
  checkButtonPour();
  delay(50);
}

void checkButtonNext()
{
  // read the state of the switch into a local variable:
  int buttonStateNext = digitalRead(buttonPinNext);

  if (buttonStateNext != lastButtonStateNext)
  {
    if (buttonStateNext == HIGH)
    {
      if (lastButtonStateNext != buttonStateNext)
      {
        lcd.clear();
        lcd.print(drinks.nextDrink().getName());
      }
    }
  }

  lastButtonStateNext = buttonStateNext;
}

void checkButtonPrev()
{
  // read the state of the switch into a local variable:
  int buttonStatePrev = digitalRead(buttonPinPrev);

  if (buttonStatePrev != lastButtonStatePrev)
  {
    if (buttonStatePrev == HIGH)
    {
      if (lastButtonStatePrev != buttonStatePrev)
      {
        lcd.clear();
        lcd.print(drinks.prevDrink().getName());
      }
    }
  }

  lastButtonStatePrev = buttonStatePrev;
}

void checkButtonPour()
{
  // read the state of the switch into a local variable:
  int buttonStatePour = digitalRead(buttonPinPour);

  if (buttonStatePour != lastButtonStatePour && buttonStatePour != HIGH)
  {
    // Button release
    lcd.clear();
    lcd.print(drinks.currDrink().getName());
    pump1.stop();
    pump2.stop();
    pump3.stop();
    pump4.stop();
  }

  if (buttonStatePour != lastButtonStatePour && buttonStatePour == HIGH)
  {
    // First button press read
    lcd.clear();
    lcd.print("Enjoy!");
    //pump1.start(1);
    //pump2.start(1);
    pump3.start(1);
    pump4.start(1);
    Serial.println("POUR");
  }

  if (buttonStatePour == HIGH)
  {
    pump1.pump();
    pump2.pump();
    pump3.pump();
    pump4.pump();
  }

  lastButtonStatePour = buttonStatePour;
}
