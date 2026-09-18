#ifndef CAT_H
#define CAT_H

#include "mammal.h"  // Include the base class header, Mammal, for inheritance
#include <iostream>
#include <cstdlib>  // Include for using rand() function
#include <ctime>
#include <string>
#include <vector>
#include <fstream>  // Include for file operations

// Cat class inherits from Mammal class
class Cat: public Mammal {
protected:
    string color_obj; // Attribute to store the color of the cat
    string name_obj; // Attribute to store the name of the cat
    int marvelpower_obj; // Attribute to store the Marvel power level of the cat

public:
    // Constructor to initialize Cat object with specified attributes
    explicit Cat(string gender, int age, string color, string name, int marvelpower) 
    : Mammal(gender, age), color_obj(color), name_obj(name), marvelpower_obj(marvelpower) {}

    // Sets the color of the cat
    void setColor(const string& color) {
        color_obj = color;
    }

    // Returns the current color of the cat
    string getColor() const {
        return color_obj;
    }   

    // Randomizes the color of the cat using predefined color options
    void randomizeColor() {
        const vector<string> colors = {"white", "brown", "grey", "black", "blonde"}; // Predefined colors
        int random_index = rand() % colors.size();  // Generate a random index
        setColor(colors[random_index]);  // Set the cat's color to the randomly selected color
    }

    // Sets the name of the cat
    void setName(const string& name) {
        name_obj = name;
    }

    // Returns the current name of the cat
    string getName() const {
        return name_obj;
    }

    // Randomizes the name of the cat by reading from a file containing names
    void randomizeNameFromFile() {
        fstream file;
        file.open("names.txt", ios::in); // Open the names file

        vector<string> names; // Vector to hold the names from the file
        string temp;
        while (file >> temp) { // Read names into temp and push into names vector
            names.push_back(temp);
        }

        if (!names.empty()) {
            int random = rand() % names.size(); // Generate a random index
            setName(names[random]); // Set the cat's name to the randomly selected name
        }

        file.close(); // Close the file after reading names
    }

    // Randomly sets the Marvel power status using a random number
    void setMarvelPowerRandomly() {
        int marvelpower = rand() % 100 + 1; // Generate a random number between 1 and 100
        marvelpower_obj = marvelpower; // Set the marvelpower attribute to the generated number
    }

    // Determines if the cat has a Marvel power (true if power is <= 2)
    bool getMarvelPower() const {
        return marvelpower_obj <= 2; // Returns true if marvelpower_obj is 2 or less
    }

};

#endif // CAT_H
