#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);
// Constants
const int buttonPin = 3;
const int numberOfTextOptions = 2;
// Variables
const char pmT1[] PROGMEM = "Hej Johan";
const char pmT2[] PROGMEM = "Hej Daniel";
const char *const pmTab[] PROGMEM = {pmT1, pmT2};
bool inInitialState = true;
// String displayTexts[numberOfTextOptions] = {"Hej Johan", "Hej Daniel"};
int displayTextsIndex = 0;
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
      inInitialState = false;
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      displayTextsIndex++; // increment the index for the texts
      // wrap around the texts if index is at the last element
      if (displayTextsIndex == numberOfTextOptions)
      {
        displayTextsIndex = 0;
      }
      if (!inInitialState && lastButtonState != buttonState)
      {
        lcd.clear();
        lcd.print("looll");
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
