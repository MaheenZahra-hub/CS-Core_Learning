#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main() {
    fstream Student;
    Student.open("Student.txt", ios::out);
    
    if (!Student) {
        cout << "File is not created";
    } else {
        cout << "File created. Entering data..." << endl;
        string input, line;

        cout << "Enter line 1: ";
        getline(cin, input); 
        Student << input << endl;

        cout << "Enter line 2: ";
        getline(cin, line);
        Student << line << endl;
    }
    Student.close();
    return 0;
}