#include <LiquidCrystal.h>
#include "Drinks.cpp"

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Constants
const int buttonPin = 3;
Drinks drinks = Drinks();

// Variables
int buttonState = 0;
int lastButtonState = 0;
int buttonPushCounter = 0;

// Setup
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(buttonPin, INPUT);
  lcd.print("Press the button...");
}
// Main program
void loop()
{

  // read the state of the switch into a local variable:
  int buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState)
  {
    if (buttonState == HIGH)
    {
      buttonPushCounter++;
      if (lastButtonState != buttonState)
      {
        lcd.clear();
        lcd.print(drinks.nextDrink().getName());
      }
      Serial.println("on");
    }
    else
    {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    delay(50);
  }
  lastButtonState = buttonState;
}
