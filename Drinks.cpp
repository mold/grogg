#include "Drink.cpp"

const int NUMBER_OF_DRINKS = 3;

class Drinks
{
private:
    const Drink drinks[NUMBER_OF_DRINKS] = {
        Drink("Grosshandlargrogg", new float[4]{0.2, 0.8, 0.0, 0.0}),
        Drink("Vargtass", new float[4]{0.0, 0.0, 0.3, 0.7}),
        Drink("Johans balle", new float[4]{1, 1, 1, 1})};
    int drinkIndex = 0;

public:
    Drinks() {}
    Drink nextDrink()
    {
        return drinks[++drinkIndex % NUMBER_OF_DRINKS];
    }
    Drink prevDrink()
    {
        return drinks[--drinkIndex % NUMBER_OF_DRINKS];
    }
};