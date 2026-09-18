#include "Process.h"  // Include the header file for the Process class
#include <cstdlib>    // Include the standard library for general utilities
#include <ctime>      // Include the library for time functions
#include <iostream>   // Include the library for input and output stream
#include <fstream>    // Include the library for file input/output operations

int main() {
    srand(time(0));  // Seed the random number generator with the current time

    Process myProcess("uk", 5, "uk", "uk", 0);  // Instantiate a Process object with initial parameters
    
    myProcess.setGenesis();  // Initialize or set up initial conditions for the process
    myProcess.displayAllCats(0);  // Display the status of all cats at year 0
    
    int year = 1;  // Start counting years from 1 after genesis
	for(int j = 0 ; j<50; j++) {
		bool flag = true;
		while (flag) {  // Enter an infinite loop to process each year
			cout << "Do you wish to continue? Press 1. Or kill half the population? Press 2. Or end the program? Press any other button: ";
			int choice = 0;
			cin >> choice;  // Read user's choice from standard input

			if (choice == 1) {
				myProcess.ageAllCatsByOneYear();  // Age all cats by one year without any population control
			} else if (choice == 2) {
				myProcess.ageAllCatsByOneYear();  // Age all cats by one year
				myProcess.cullPopulation();  // Execute a function to reduce the population by half
			} else {
				cout << "Ending program." << endl;
				break;  // Exit the loop and end the program if the user chooses any option other than 1 or 2
			}

			myProcess.displayAllCats(year);  // Display the status of all cats for the current year

			if (!myProcess.hasCatNames()) {  // Check if there are no cats remaining
				ofstream outFile("output.txt", ios::app);  // Open or create output file in append mode
				outFile << "All Cats Are Dead!!!" << endl;  // Write to file that all cats are dead
				outFile.close();  // Close the file
				break;  // Exit the loop since no cats are left
			}

			year++;  // Increment year at the end of the loop for the next iteration
		}
	}

    return 0;  // Return 0 to indicate successful completion of the program
}








