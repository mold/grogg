#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
// #include "MenuItem.cpp"
// #include "Menu.cpp"
#include "Drink.cpp"

using namespace std;

vector<Drink> get_drink_vector() {
    // File pointer
    fstream fin;
    // Open an existing file
    fin.open("drinks.csv", ios::in);
    // Read the Data from the file as String Vector
    vector<string> row;
    string line, word, temp;

    vector<Drink> drinks;

    while (fin >> temp) {
        row.clear();
        // read an entire row and store it in a string variable 'line'
        getline(fin, line);
        // used for breaking words
        stringstream s(temp); // stringstream s(line);
        // read every column data of a row and store it in a string variable, 'word'
        while (getline(s, word, ',')) {
            row.push_back(word);
        };

        Drink drink;
        drink.setName(row[0]);
        int number_of_ingredients = (row.size() - 1);
        for(int i=1; i<number_of_ingredients; i += 2){
            drink.addIngredientToRecipe(stoi(row[i]), stof(row[i+1]));
        }
        
        cout << drink.getName() << endl;
        drink.printRecipe();
        drinks.push_back(drink);
    };
    return drinks;
}

int main() {
    // SET UP RECIPES! //
    vector<Drink> drinks = get_drink_vector();
    cout << "number of drinks: " << drinks.size() << endl;
    // END SET UP RECIPES! //

    // vector<string> my_vector = {"daniel", "johan"};
    // Menu my_menu(my_vector);
    // for (auto i : my_menu.getMenuItems()) {
    //     cout << i.getText() << endl;
    // }
    // MenuItem menuitem1("johan");
    // std::cout << menuitem1.getText() << std::endl;
    return 0;
}

