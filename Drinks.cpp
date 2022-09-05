#include "Drink.cpp"

const int NUMBER_OF_DRINKS = 4;

class Drinks
{
private:
    const Drink drinks[NUMBER_OF_DRINKS] = {
        // Drink("Grosshandlargrogg", new float[4]{0.2, 0.8, 0.0, 0.0}),
        // Drink("Vargtass", new float[4]{0.0, 0.0, 0.3, 0.7}),
        // Drink("Johans balle", new float[4]{1, 1, 1, 1}),
        // Drink("MonsterRadler", new float[4]{1, 1, 0, 0})};
        
        Drink("Sour New Yorker", new float[4]{1, 0, 1, 0}),
        Drink("Big Apple", new float[4]{1, 1, 0, 0}),
        Drink("Super Trouper", new float[4]{1, 1, 1, 0}),
        Drink("Cleaning procedure (DO NOT RUN!!!!)", new float[4]{1, 1, 1, 1})};
        
    int drinkIndex = 0;

    void stepDrinkIndex(int steps) {
       drinkIndex = (((drinkIndex + steps) % NUMBER_OF_DRINKS) + NUMBER_OF_DRINKS) % NUMBER_OF_DRINKS;
    }
    

public:
    Drinks() {}
    Drink nextDrink()
    {
        stepDrinkIndex(1);
        Serial.println("Next drink: " + String(drinkIndex));
        return drinks[drinkIndex];
    }
    Drink prevDrink()
    {
        stepDrinkIndex(-1);
        Serial.println("Prev drink: " + String(drinkIndex));
        return drinks[drinkIndex];
    }
    Drink currDrink(){
        return drinks[drinkIndex];
    }
};
