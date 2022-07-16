#include <Vector.h>

using namespace std;

const int INGREDIENT_CONTAINERS = 4;

class Drink {
    private:
        String _name;
        float _recipe[INGREDIENT_CONTAINERS];
    public:
        Drink() {};
        Drink(String name, float recipe[INGREDIENT_CONTAINERS]) { // Constructor
            _name = name;
            memcpy(_recipe, recipe, INGREDIENT_CONTAINERS*sizeof(float)); 
        };
        String getName() {
            return _name;
        };
        void setName(String name) {
            _name = name;
        };
        void addIngredientToRecipe(int ingredientIndex, float decimalAmount) {
            _recipe[ingredientIndex] = decimalAmount;
        };
        void printRecipe() {
            for (int i=0; i < INGREDIENT_CONTAINERS; i++) {
                Serial.println(i + ": " + String(_recipe[i], 2));
            }
        };
};