#include <LiquidCrystal.h>
#include "Drinks.cpp"
#include "Pump.cpp"

LiquidCrystal lcd(12, 3, 2, 4, 7, 8);

// Constants
const int buttonPinNext = A4;
const int buttonPinPrev = A5;
const int buttonPinPour = A3;

int pumpSpeedPWM = 255;

Drinks drinks = Drinks();

// Variables
int buttonStateNext = 0;
int lastButtonStateNext = 0;

int buttonStatePrev = 0;
int lastButtonStatePrev = 0;

int buttonStatePour = 0;
int lastButtonStatePour = 0;

long pumpStartMillis;
long maxPumpDuration = 60000;

Pump pump1 = Pump(5, pumpSpeedPWM, 0.8);
Pump pump2 = Pump(6, pumpSpeedPWM, 0.8);
Pump pump3 = Pump(9, pumpSpeedPWM, 0.9);
Pump pump4 = Pump(10, pumpSpeedPWM, 1);

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
  delay(250);
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
        displayOnLCD(drinks.nextDrink().getName());
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
        displayOnLCD(drinks.prevDrink().getName());
      }
    }
  }

  lastButtonStatePrev = buttonStatePrev;
}

void checkButtonPour()
{
  // read the state of the switch into a local variable:
  int buttonStatePour = digitalRead(buttonPinPour);

  if ((buttonStatePour != lastButtonStatePour && buttonStatePour != HIGH) || (millis() - pumpStartMillis) >= maxPumpDuration)
  {
    // Button release
    displayOnLCD(drinks.currDrink().getName());
    pump1.stop();
    pump2.stop();
    pump3.stop();
    pump4.stop();
  }

  if (buttonStatePour != lastButtonStatePour && buttonStatePour == HIGH)
  {
    // First button press read
    displayOnLCD("Enjoy!");
    Drink currDrink = drinks.currDrink();
    pump1.start(currDrink.getPumpRatio(0));
    pump2.start(currDrink.getPumpRatio(1));
    pump3.start(currDrink.getPumpRatio(2));
    pump4.start(currDrink.getPumpRatio(3));
    Serial.println("POUR DRINK " + currDrink.getName());

    pumpStartMillis = millis();
  }

  if (buttonStatePour == HIGH && !((millis() - pumpStartMillis) >= maxPumpDuration))
  {
    pump1.pump();
    pump2.pump();
    pump3.pump();
    pump4.pump();
  }

  lastButtonStatePour = buttonStatePour;
}

void displayOnLCD(String text){
  lcd.print("                ");
  lcd.print(text);
}
