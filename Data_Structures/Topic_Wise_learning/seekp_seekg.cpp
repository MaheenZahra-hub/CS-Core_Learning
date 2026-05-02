#include<iostream>
#include<fstream>
#include<string>
using namespace std; 

int main() {
    string line;
    fstream file;
    // ios::trunc ensures we start with a fresh file
    file.open("example.txt", ios::in | ios::out | ios::trunc);
    
    if (!file) {
        cout << "File not opened" << endl;
    } else {
        file << "hello world"; // Initial write: "hello world"

        // seekp moves the WRITE pointer
        file.seekp(6, ios::beg); 
        file << "C++  "; // Overwrites "world" with "C++  "

        // seekg moves the READ pointer
        file.seekg(0, ios::beg); // Move back to the start to read everything
        getline(file, line);
        cout << "Content: " << line << endl;
    }
    file.close();
    return 0;
}