#include "Drink.cpp"

const int NUMBER_OF_DRINKS = 10;

class Drinks
{
private:
    const Drink drinks[NUMBER_OF_DRINKS] = {
        // Drink("Grosshandlargrogg", new float[4]{0.2, 0.8, 0.0, 0.0}),
        // Drink("Vargtass", new float[4]{0.0, 0.0, 0.3, 0.7}),
        // Drink("Johans balle", new float[4]{1, 1, 1, 1}),
        // Drink("MonsterRadler", new float[4]{1, 1, 0, 0})};

        // 1: Champagne
        // 2: OJ
        // 3: Gin
        // 4: Sockerdricka
        
        Drink("Mimosa", new float[4]{1, 1, 0, 0}),
        Drink("Fortified Mimosa", new float[4]{1, 1, 0.4, 0}),
        Drink("Fizzy Mimose", new float[4]{1, 0, 0, 1}),
        Drink("Spark-Gin Orange", new float[4]{1, 0.7, 0.4, 1}),
        Drink("Gin", new float[4]{0,0,1,0}),
        Drink("Cava", new float[4]{1,0,0,0}),
                Drink("Juice", new float[4]{0,1,0,0}),
                Drink("Läsk", new float[4]{0,0,0,1}),

        Drink("Fresh Gin Fizz", new float[4]{0, 0, 0.3, 1}),
        Drink("Cleany DONT RUN!!!", new float[4]{1, 1, 1, 1})};
        
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
