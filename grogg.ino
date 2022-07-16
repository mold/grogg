#include <LiquidCrystal.h>
#include "Drinks.cpp"

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Constants
const int buttonPinNext = 3;
const int buttonPinPrev = 2;
const int buttonPinPour = 4;

Drinks drinks = Drinks();

// Variables
int buttonStateNext = 0;
int lastButtonStateNext = 0;

int buttonStatePrev = 0;
int lastButtonStatePrev = 0;

int buttonStatePour = 0;
int lastButtonStatePour = 0;

// Setup
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buttonPinNext, INPUT);
  pinMode(buttonPinPrev, INPUT);
  lcd.print("Press the button...");
}
// Main program
void loop()
{
  checkButtonNext();
  checkButtonPrev();
  checkButtonPour();
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

    delay(50);
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

    delay(50);
  }

  lastButtonStatePrev = buttonStatePrev;
}

void checkButtonPour()
{
  // read the state of the switch into a local variable:
  int buttonStatePour = digitalRead(buttonPinPour);

  if (buttonStatePour != lastButtonStatePour)
  {
    if (buttonStatePour == HIGH)
    {
      if (lastButtonStatePour != buttonStatePour)
      {
        lcd.clear();
        lcd.print("Enjoy!");
        // TODO: Pour drink
      }
    }

    delay(50);
  }

  lastButtonStatePour = buttonStatePour;
}