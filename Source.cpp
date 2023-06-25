#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class ItemTracker {
private:
    map<string, int> frequencyMap;

public:
    //Reads the input file and populates the frequency map
    void readInputFile(const string& filename) {
        ifstream inputFile(filename);
        if (inputFile.is_open()) {
            string item;
            while (inputFile >> item) {
                frequencyMap[item]++;
            }
            inputFile.close();
        }
        else {
            cout << "Error: Unable to open input file." << endl;
        }
    }

    //Saves the data (item frequencies) to a file
    void saveDataToFile(const string& filename) {
        ofstream outputFile(filename);
        if (outputFile.is_open()) {
            for (const auto& pair : frequencyMap) {
                outputFile << pair.first << " " << pair.second << endl;
            }
            outputFile.close();
            cout << "Data saved to " << filename << "." << endl;
        }
        else {
            cout << "Error: Unable to create data file." << endl;
        }
    }

    //Returns the frequency of a specific item
    int getItemFrequency(const string& item) {
        if (frequencyMap.count(item) > 0) {
            return frequencyMap[item];
        }
        else {
            return 0;
        }
    }

    //Prints the list of items with their frequencies
    void printList() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    //Prints a histogram representing the item frequencies
    void printHistogram() {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; i++) {
                cout << "*";
            }
            cout << endl;
        }
    }
};
//Funtion that allows main to call the menu
void displayMenu() {
    cout << "*                Menu Options:                  *" << endl;
    cout << "* 1.   Look for an item and get its frequency.  *" << endl;
    cout << "* 2.  Print the list of items with frequencies. *" << endl;
    cout << "* 3.           Print the histogram.             *" << endl;
    cout << "* 4.            Exit the program.               *" << endl;
}
//Gets user input to use in finding the frequency of an item
int getUserChoice() {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}
//Input validation
void validateUserChoice(int& choice, int minChoice, int maxChoice) {
    while (choice < minChoice || choice > maxChoice) {
        cout << "Invalid choice. Please try again." << endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        displayMenu();
        choice = getUserChoice();
    }
}

void printDividerLine() {
    cout << "-------------------------------------------------" << endl;
}

void printMenuHeader() {
    printDividerLine();
    cout << "*             CORNER GROCER MENU                *" << endl;
    printDividerLine();
}

void printExitMessage() {
    printDividerLine();
    cout << "Thank you for using the Corner Grocer program." << endl;
    printDividerLine();
}

int main() {
    ItemTracker itemTracker;
    itemTracker.readInputFile("CS210_Project_Three_Input_File.txt");

    int choice;
    printMenuHeader();
    displayMenu();
    printDividerLine();
    choice = getUserChoice();
    validateUserChoice(choice, 1, 4);

    while (choice != 4) {
        switch (choice) {
        case 1: {
            printDividerLine();
            string item;
            cout << "Enter the item to look for: ";
            cin >> item;
            //Sets the first character to a capital letter for additional input validation/quality of life.
            if (!item.empty())
            {
                item[0] = std::toupper(item[0]);

                for (std::size_t i = 1; i < item.length(); ++i)
                    item[i] = std::tolower(item[i]);
            }
            int frequency = itemTracker.getItemFrequency(item);
            cout << "Frequency of " << item << ": " << frequency << endl;
            printDividerLine();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 2: {
            printDividerLine();
            itemTracker.printList();
            printDividerLine();
            break;
        }
        case 3: {
            printDividerLine();
            itemTracker.printHistogram();
            printDividerLine();
            break;
        }
        }

        displayMenu();
        choice = getUserChoice();
        validateUserChoice(choice, 1, 4);
    }

    itemTracker.saveDataToFile("frequency.dat");
    printExitMessage();

    return 0;
}