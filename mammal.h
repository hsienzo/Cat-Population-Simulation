#ifndef MAMMAL_H
#define MAMMAL_H

#include <iostream>  // Include for I/O operations
#include <cstdlib>   // Include for general purpose functions such as rand()
#include <ctime>     // Include for time functions
#include <string>    // Include for string operations
#include <vector>    // Include for using vector container
#include <fstream>   // Include for file operations

using namespace std;

// Define the base class Mammal
class Mammal {
protected:
    string gender_obj; // Attribute to store gender of the mammal
    int age_obj;       // Attribute to store age of the mammal

public:
    // Constructor initializes Mammal with gender and age
    explicit Mammal(string gender, int age) : gender_obj(gender), age_obj(age) {}

    // Randomly assigns gender to the mammal as either 'male' or 'female'
    void setGender() {
        int random = rand() % 2; // Generate a random number (0 or 1)
        gender_obj = (random == 0) ? "male" : "female"; // Set gender based on random number
    }

    // Sets the age of the mammal
    void setAge(int age) {
        age_obj = age; // Directly set age_obj to the given age parameter
    }
    
    // Increments the age of the mammal by one year
    void incrementAge() {
        age_obj++; // Increase age_obj by 1
    }
    
    // Returns the gender of the mammal
    string getGender() const {
        return gender_obj; // Return the value of gender_obj
    }
    
    // Returns the age of the mammal
    int getAge() const {
        return age_obj; // Return the value of age_obj
    }
};

#endif // MAMMAL_H
