#include<iostream>
#include<fstream>
#include<string> // Good practice to include this for getline
using namespace std;

int main() {
    fstream Student;
    string input, line;

    // Phase 1: Writing
    Student.open("Student.txt", ios::out); 
    if (!Student) {
        cout << "File is not created";
        return 1;
    } else {
        cout << "File is created" << endl;
    }

    cout << "Enter your name: ";
    getline(cin, input);
    Student << input << endl;

    cout << "Enter your roll no: ";
    getline(cin, line);
    Student << line << endl;

    Student.close(); // CRITICAL: Close the write-stream before re-opening for reading

    // Phase 2: Reading
    Student.open("Student.txt", ios::in);
    if (!Student) {
        cout << "Error opening file for reading";
    } else {
        cout << "\n--- Reading from file ---" << endl;
        while (getline(Student, line)) {
            cout << line << endl;
        }
    }
    Student.close();
    return 0;
}