#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void writeToFile(const string& filename) {
    ofstream outFile(filename); // open for writing (overwrites file)
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    string data;
    cout << "Enter text to write to the file (type 'exit' to finish):" << endl;
    while (true) {
        getline(cin, data);
        if (data == "exit") break;
        outFile << data << endl;
    }

    outFile.close();
    cout << "Data written successfully.\n";
}

void appendToFile(const string& filename) {
    ofstream outFile(filename, ios::app); // open in append mode
    if (!outFile) {
        cerr << "Error opening file for appending!" << endl;
        return;
    }

    string data;
    cout << "Enter text to append to the file (type 'exit' to finish):" << endl;
    while (true) {
        getline(cin, data);
        if (data == "exit") break;
        outFile << data << endl;
    }

    outFile.close();
    cout << "Data appended successfully.\n";
}

void readFromFile(const string& filename) {
    ifstream inFile(filename); // open for reading
    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    string line;
    cout << "\nFile contents:\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

int main() {
    string filename = "sample.txt";
    int choice;

    do {
        cout << "\n--- File Operations Menu ---\n";
        cout << "1. Write to file (overwrite)\n";
        cout << "2. Append to file\n";
        cout << "3. Read from file\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clear newline character from input buffer

        switch (choice) {
            case 1:
                writeToFile(filename);
                break;
            case 2:
                appendToFile(filename);
                break;
            case 3:
                readFromFile(filename);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

