#ifndef PROCESS_H
#define PROCESS_H

#include "cat.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>  // Include for access to random number generation and shuffling utilities

using namespace std;

class Process {
protected:
    vector<Cat> cats;  // Stores all Cat instances
    vector<string> names;  // Stores names of cats
    vector<string> colors;  // Stores colors of cats
    vector<int> ages;  // Stores ages of cats
    vector<bool> marvelPowers;  // Stores Marvel power status of cats (true if has power)
    vector<string> genders;  // Stores genders of cats
    default_random_engine rng;  // Random number generator for various random operations

public:
    // Constructor to initialize the Process with a single Cat
    explicit Process(string gender, int age, string color, string name, int marvelpower)
        : cats{Cat(gender, age, color, name, marvelpower)}, rng(static_cast<unsigned>(time(nullptr))) {}

    // Sets up the initial conditions or genesis for the simulation
    void setGenesis() {
        ofstream outFile("output.txt", ios::app);  // Open output file in append mode to log events
        for (int i = 0; i < 5; i++) {
            Cat newCat("unknown", 0, "unknown", "unknown", 0);  // Create new cats with unknown properties
            newCat.randomizeNameFromFile();  // Randomize their names from a file
            newCat.randomizeColor();  // Randomize their color
            newCat.setAge(0);  // Set their age to 0
            newCat.setGender();  // Randomly set their gender
            newCat.setMarvelPowerRandomly();  // Randomly decide if they have a Marvel power
            
            cats.push_back(newCat);  // Add new cat to the vector of cats
            storeCatProperties(newCat);  // Store cat properties in separate vectors
        
            outFile << (newCat.getMarvelPower() ? "Marvel Kitty " : "Kitty ") << newCat.getName() << " is born!" << endl;
        }
        outFile.close();  // Close the output file
    }

    // Helper function to store properties of cats into separate vectors
    void storeCatProperties(const Cat& cat) {
        names.push_back(cat.getName());
        colors.push_back(cat.getColor());
        ages.push_back(cat.getAge());
        marvelPowers.push_back(cat.getMarvelPower());
        genders.push_back(cat.getGender());
    }

    // Ages all cats by one year and manages their life status and effects
    void ageAllCatsByOneYear() {
        ofstream debugLog("debugLog.txt", ios::app);  // Open debug log file in append mode
        ofstream outFile("output.txt", ios::app);  // Open output file in append mode

        vector<size_t> toRemove;  // Indices of cats that will be removed due to age or conditions
        vector<size_t> marvelCats;  // Indices of cats with Marvel powers

        for (size_t i = 0; i < ages.size(); ++i) {
            ages[i]++;  // Increment age of each cat
            if (marvelPowers[i]) {
                marvelCats.push_back(i);  // If cat has Marvel power, add to marvelCats list
                debugLog << "Debug: Cat " << names[i] << " (Marvel Power) is now " << ages[i] << " years old." << endl;
            }
            if (ages[i] >= 10 && (!marvelPowers[i] || ages[i] >= 25)) {  // If cat reaches age limit
                debugLog << names[i] << " passes away." << endl;
                outFile << (marvelPowers[i] ? "Marvel Kitty " : "Kitty ") << names[i] << " passed away." << endl;
                toRemove.push_back(i);
            } else if (marvelPowers[i]) {
                debugLog << "Debug: Cat " << names[i] << " with Marvel Power survives another year." << endl;
            }
        }

        removeCats(toRemove);  // Remove deceased cats from the lists
        createNewCats();  // Create new cats based on remaining cats

        vector<size_t> potentialTargets;  // Indices of cats that can potentially gain Marvel powers
        for (size_t i = 0; i < marvelPowers.size(); ++i) {
            if (!marvelPowers[i]) {
                potentialTargets.push_back(i);
            }
        }

        // Marvel cats infect one non-Marvel cat with Marvel power
        for (size_t index : marvelCats) {
            if (!potentialTargets.empty()) {
                size_t targetPosition = rand() % potentialTargets.size();  // Select a random target
                size_t targetIndex = potentialTargets[targetPosition];
                marvelPowers[targetIndex] = true;  // Infect the target with Marvel power
                debugLog << "Debug: Cat " << names[index] << " with Marvel Power has infected " << names[targetIndex] << "." << endl;
                potentialTargets.erase(potentialTargets.begin() + targetPosition);  // Remove target from potential targets
            }
        }

        debugLog.close();  // Close the debug log
        outFile.close();  // Close the output file
    }

    // Creates new cats based on breeding eligible male and female cats
    void createNewCats() {
        ofstream outFile("output.txt", ios::app);
        vector<int> maleIndices, femaleIndices;  // Collect indices for eligible males and females

        // Identify eligible males and females based on age and lack of Marvel power
        for (size_t i = 0; i < genders.size(); ++i) {
            if (ages[i] >= 2 && !marvelPowers[i]) {  // Cats must be old enough and not have Marvel Power
                if (genders[i] == "male") {
                    maleIndices.push_back(i);
                } else if (genders[i] == "female") {
                    femaleIndices.push_back(i);
                }
            }
        }

        // Iterate over each eligible female and pair with each eligible male to create new cats
        for (int femaleIndex : femaleIndices) {
            string motherColor = colors[femaleIndex];  // Use the mother's color for the kitten

            for (int j = 0; j < maleIndices.size(); j++) {
                Cat newCat("unknown", 0, motherColor, "NewCat" + to_string(cats.size()), false);
                newCat.randomizeNameFromFile();  // Assign a name from file
                newCat.setGender();  // Randomly set gender
                newCat.setMarvelPowerRandomly();  // Correctly set Marvel power randomly

                cats.push_back(newCat);
                storeCatProperties(newCat);

                // Output the birth announcement with the correct Marvel status
                outFile << (newCat.getMarvelPower() ? "Marvel Kitty " : "Kitty ") << newCat.getName() << " is born!" << endl;
            }
        }

        outFile.close();  // Always ensure to close the file
    }

    // Remove specified cats from all vectors by indices
    void removeCats(const vector<size_t>& toRemove) {
        if (toRemove.empty()) return;

        for (auto it = toRemove.rbegin(); it != toRemove.rend(); ++it) {
            if (*it < cats.size()) {
                cats.erase(cats.begin() + *it);
                names.erase(names.begin() + *it);
                colors.erase(colors.begin() + *it);
                ages.erase(ages.begin() + *it);
                marvelPowers.erase(marvelPowers.begin() + *it);
                genders.erase(genders.begin() + *it);
            }
        }
    }

    // Culls half the population of cats randomly
    void cullPopulation() {
        ofstream debugLog("populationCullLog.txt", ios::app);
        ofstream outFile("output.txt", ios::app);

        debugLog << "Starting population cull. Initial count: " << cats.size() << endl;

        if (cats.size() < 2) {
            debugLog << "Not enough cats to perform culling. No action taken." << endl;
            outFile << "Not enough cats to perform culling. No action taken." << endl;
            debugLog.close();
            outFile.close();
            return;
        }

        size_t numberToCull = cats.size() / 2;  // Calculate half the population
        vector<size_t> indicesToCull(cats.size());
        iota(indicesToCull.begin(), indicesToCull.end(), 0);  // Generate a list of indices
        shuffle(indicesToCull.begin(), indicesToCull.end(), rng);  // Shuffle the indices

        indicesToCull.resize(numberToCull);  // Resize to number to cull
        sort(indicesToCull.begin(), indicesToCull.end(), greater<size_t>());  // Sort in descending order for safe removal

        debugLog << "Indices to cull (sorted in descending): ";
        for (size_t idx : indicesToCull) debugLog << idx << " ";
        debugLog << endl;

        for (size_t index : indicesToCull) {
            if (index < cats.size()) {
                debugLog << "Culling Cat - Name: " << names[index] << ", Age: " << ages[index] << ", Color: " << colors[index] << ", Marvel Power: " << (marvelPowers[index] ? "True" : "False") << endl;
                outFile << (marvelPowers[index] ? "Marvel Kitty " : "Kitty ") << names[index] << " passed away." << endl;
                cats.erase(cats.begin() + index);
                names.erase(names.begin() + index);
                colors.erase(colors.begin() + index);
                ages.erase(ages.begin() + index);
                marvelPowers.erase(marvelPowers.begin() + index);
                genders.erase(genders.begin() + index);
            }
        }

        debugLog << "Population after cull: " << cats.size() << endl;
        debugLog.close();
        outFile.close();
    }

    // Displays all cats' properties formatted for a specific year
    void displayAllCats(int year) {
        ofstream outFile("output.txt", ios::app);
        if (!outFile.is_open()) {
            cerr << "Failed to open output.txt for writing." << endl;
            return;
        }
        outFile << "\nAfter aging all cats by " << year << " year(s):" << endl;
        for (size_t i = 0; i < names.size(); ++i) {
            outFile << "Cat: " << names[i]
                    << ", Gender: " << genders[i]
                    << ", Color: " << colors[i]
                    << ", Age: " << ages[i]
                    << ", Marvel Power: " << (marvelPowers[i] ? "True" : "False") << endl;
        }
        outFile.close();
    }

    // Checks if there are any cat names in the vector, used to check for existence of cats
    bool hasCatNames() const {
        return !names.empty();
    }
};

#endif // PROCESS_H
