#include <iostream>
#include <string>
using namespace std;

/**
 * StudentRecord Class
 * Manages individual student data and tracks global enrollment.
 */
class StudentRecord {
private:
    int studentID;
    string name;
    float gpa;
    static int studentCount; // Global counter for all StudentRecord instances

public:
    // Constructor: Assigns data and increments global enrollment count
    StudentRecord(int id, string n, float g) {
        studentID = id;
        name = n;
        gpa = g;
        studentCount++; 
    }

    // --- Accessor Methods (Getters) ---
    int getStudentID() const { return studentID; }
    string getName() const { return name; }
    float getGPA() const { return gpa; }

    // --- Mutator Method (Setter) ---
    void setGPA(float newGPA) { 
        if(newGPA >= 0.0 && newGPA <= 4.0) // Added basic validation
            gpa = newGPA; 
    }

    // Static function to access the shared student count
    static int getStudentCount() { return studentCount; }

    // Displays student information in a formatted line
    void display() const {
        cout << "[ID: " << studentID << "] Name: " << name << "\t GPA: " << gpa << endl;
    }
};

// Initialize the static member variable outside the class
int StudentRecord::studentCount = 0;

int main() {
    const int SIZE = 5;

    // Initializing an array of 5 StudentRecord objects
    StudentRecord students[SIZE] = {
        StudentRecord(101, "Dania", 3.8),
        StudentRecord(102, "Danial", 3.5),
        StudentRecord(103, "Maheen", 3.9),
        StudentRecord(104, "Murtaza", 3.7),
        StudentRecord(105, "Ali", 3.6)
    };

    cout << "--- Initial Student Records ---\n";
    for (int i = 0; i < SIZE; i++) {
        students[i].display();
    }
    
    // --- Search and Update Feature ---
    int searchID;
    float newGPA;
    cout << "\nEnter Student ID to update GPA: ";
    cin >> searchID;
    cout << "Enter new GPA: ";
    cin >> newGPA;
    
    bool found = false;
    for (int i = 0; i < SIZE; i++) {
        // Checking if the current student ID matches user input
        if (students[i].getStudentID() == searchID) {
            students[i].setGPA(newGPA);
            cout << "Update Success: " << students[i].getName() << "'s GPA is now " << newGPA << endl;
            found = true;
            break; // Stop searching once found
        }
    }
    
    if (!found) {
        cout << "Update Failed: Student ID " << searchID << " does not exist." << endl;
    }
    
    // Display total count using the static method
    cout << "\nTotal Enrolled Students: " << StudentRecord::getStudentCount() << endl;
    
    return 0;
}