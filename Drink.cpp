#include <string>
#include <map>
#include <iostream>

using namespace std;

class Drink {
    private:
        string _name;
        map<int, float> _recipe;
    public:
        Drink() {};
        Drink(string name, map<int, float> recipe) { // Constructor
            _name = name;
            _recipe = recipe;
        };
        string getName() {
            return _name;
        };
        map<int, float> getRecipe() {
            return _recipe;
        };
        void setName(string name) {
            _name = name;
        };
        void addIngredientToRecipe(int ingredientIndex, float decimalAmount) {
            _recipe.insert(pair<int, float>(ingredientIndex, decimalAmount));
        };
        void printRecipe() {
            for (auto const& [key, val] : _recipe) {
                cout << key        // string (key)
                        << ':'  
                        << val        // string's value
                        << endl;
            }
        };
};