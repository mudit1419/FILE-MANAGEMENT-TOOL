# FILE-MANAGEMENT-TOOL
*COMPANY*: CODTECH IT SOLUTIONS
*NAME*: MUDIT KUMAR
*INTERN ID*: CT04DF877
*DOMAIN*: C++ PROGRAMMING
*DURATION*: 4 WEEKS
*MENTOR*: NEELA SANTOSH KUMAR
##DESCRIPTION## 
Overview


📄 File Operations in C++
This C++ program demonstrates basic file handling operations — writing, appending, and reading text from a file — using standard file I/O classes from the C++ Standard Library. It provides a simple menu-driven interface to interact with a file named sample.txt. Users can choose to write new content, append additional content, or read the existing content of the file.

🔧 Features
Overwrite File: Write new data to a file, replacing any existing content.

Append to File: Add new lines of text to the end of an existing file.

Read File: Display the contents of the file on the screen.

Interactive Menu: Choose operations through a simple numeric menu.

🧠 Code Breakdown
1. Header Files and Namespace
cpp
Copy
Edit
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
iostream: For console input/output (e.g., cin, cout).

fstream: For file stream operations.

string: To handle string data.

using namespace std: Allows direct access to standard library components without prefixing std::.

2. Writing to a File
cpp
Copy
Edit
void writeToFile(const string& filename)
Opens the file using ofstream in default mode (which overwrites any existing content).

Prompts the user to enter lines of text until they type "exit".

Each line is written to the file followed by a newline.

Closes the file after writing is complete.

This function is useful when starting fresh with a new set of data.

3. Appending to a File
cpp
Copy
Edit
void appendToFile(const string& filename)
Opens the file using ofstream in ios::app (append) mode.

Like the write function, it accepts input until "exit" is entered.

New lines are added to the end of the file without erasing existing content.

Ensures the data is preserved across multiple runs.

This function allows adding more information without losing previous entries.

4. Reading from a File
cpp
Copy
Edit
void readFromFile(const string& filename)
Uses ifstream to open the file for reading.

Reads and prints each line until the end of the file is reached.

Displays the entire file content to the console.

This function provides a way to view what's currently stored in the file.

5. Main Menu Interface
cpp
Copy
Edit
int main()
Contains a loop that displays a menu with four options:

Write to file

Append to file

Read from file

Exit

Based on the user's choice, it calls the appropriate function.

Uses cin.ignore() after cin >> choice to clear the input buffer before taking multiline string input using getline().

The loop continues until the user selects option 4 (Exit).

📁 File Used
sample.txt: This is the file the program reads from and writes to. It is created automatically if it does not already exist.

🏁 How to Run
Compile the Program:

bash
Copy
Edit
g++ -o file_operations file_operations.cpp
Run the Program:

bash
Copy
Edit
./file_operations
Follow the Menu Prompts:

Enter text and type exit when done.

View the file content using option 3.

🧪 Example Usage
pgsql
Copy
Edit
--- File Operations Menu ---
1. Write to file (overwrite)
2. Append to file
3. Read from file
4. Exit
Enter your choice: 1
Enter text to write to the file (type 'exit' to finish):
Hello, world!
Welcome to file handling in C++.
exit
Data written successfully.
✅ Conclusion
This simple file handling utility is ideal for beginners learning how to manage file input/output in C++. It uses core concepts like streams (ifstream, ofstream), control flow (switch, do-while), and string handling to provide a user-friendly command-line experience.




##OUTPUT##
![Image](https://github.com/user-attachments/assets/f69f220d-3fd2-4156-b323-c05dcb07b974)
