#include <LiquidCrystal.h>
#include "Drinks.cpp"

LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Constants
const int buttonPinNext = A1;
const int buttonPinPrev = A2;
const int buttonPinPour = A0;

int pumpSpeedPWM = 255;
const int pumpControlPin1 = 10;
const int pumpControlPin2 = 9;

Drinks drinks = Drinks();

// Variables
int buttonStateNext = 0;
int lastButtonStateNext = 0;

int buttonStatePrev = 0;
int lastButtonStatePrev = 0;

int buttonStatePour = 0;
int lastButtonStatePour = 0;

// Pump pump1 = new Pump(10, 255);
// Pump pump2 = new Pump(9, 255);

// Setup
void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(buttonPinNext, INPUT);
  pinMode(buttonPinPrev, INPUT);
  pinMode(buttonPinPour, INPUT);

  pinMode(pumpControlPin1, OUTPUT);
  pinMode(pumpControlPin2, OUTPUT);

  lcd.print("Press the button...");
}
// Main program
void loop()
{
  checkButtonNext();
  checkButtonPrev();
  int currentMillis = millis();
  checkButtonPour(currentMillis);
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

void checkButtonPour(int currentMillis)
{
  // read the state of the switch into a local variable:
  int buttonStatePour = digitalRead(buttonPinPour);

  if (buttonStatePour != lastButtonStatePour && buttonStatePour != HIGH)
  {
    // Button release
    lcd.clear();
    lcd.print(drinks.currDrink().getName());
    analogWrite(pumpControlPin1, 0);
    analogWrite(pumpControlPin2, 0);
  }

  if (buttonStatePour != lastButtonStatePour && buttonStatePour == HIGH)
  {
    // First button press read
    lcd.clear();
    lcd.print("Enjoy!");
    Serial.println("POUR");
  }

  if (buttonStatePour == HIGH)
  {
    if (((int)(currentMillis / 1000)) % 2 == 0)
    {
      analogWrite(pumpControlPin1, pumpSpeedPWM);
      analogWrite(pumpControlPin2, 0);
    }
    else
    {
      analogWrite(pumpControlPin2, pumpSpeedPWM);
      analogWrite(pumpControlPin1, 0);

    }

    delay(50);
  }

  lastButtonStatePour = buttonStatePour;
}
