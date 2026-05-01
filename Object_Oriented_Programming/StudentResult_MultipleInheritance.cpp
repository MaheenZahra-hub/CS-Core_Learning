#include <iostream>
#include <string>
using namespace std;

/**
 * Base Class: Academics
 * Handles academic performance data.
 */
class Academics {
private:
    float mathMarks;
    float scienceMarks;

public:
    Academics() : mathMarks(0), scienceMarks(0) {}
    Academics(float math, float science) : mathMarks(math), scienceMarks(science) {}

    // Getters and Setters
    void setMathMarks(float math) { mathMarks = math; }
    void setScienceMarks(float science) { scienceMarks = science; }
    float getMathMarks() const { return mathMarks; }
    float getScienceMarks() const { return scienceMarks; }
};

/**
 * Base Class: Sports
 * Handles extracurricular/athletic performance data.
 */
class Sports {
private:
    float sportsScore;

public:
    Sports() : sportsScore(0) {}
    Sports(float score) : sportsScore(score) {}

    void setSportsScore(float score) { sportsScore = score; }
    float getSportsScore() const { return sportsScore; }
};

/**
 * Derived Class: StudentResult
 * Demonstrates MULTIPLE INHERITANCE by combining Academics and Sports.
 */
class StudentResult : public Academics, public Sports {
private:
    string studentName;

public:
    StudentResult() : studentName("") {}

    // Constructor passing arguments to multiple base classes
    StudentResult(string name, float math, float science, float score)
        : Academics(math, science), Sports(score), studentName(name) {}

    // Using const reference for string to optimize performance
    void setStudentName(const string& name) { studentName = name; }
    string getStudentName() const { return studentName; }

    // Combines data from both parent classes
    float calculateTotalScore() const {
        return getMathMarks() + getScienceMarks() + getSportsScore();
    }

    void showStudentResult() const {
        cout << "------------------------------------" << endl;
        cout << "STUDENT REPORT: " << studentName << endl;
        cout << "------------------------------------" << endl;
        cout << "Math:    " << getMathMarks() << endl;
        cout << "Science: " << getScienceMarks() << endl;
        cout << "Sports:  " << getSportsScore() << endl;
        cout << "TOTAL:   " << calculateTotalScore() << " / 300" << endl;
        cout << "------------------------------------" << endl;
    }
};

int main() {
    // Scenario 1: Using the Parameterized Constructor
    StudentResult student1("Maheen Zahra", 85.5, 90.0, 88.0);
    student1.showStudentResult();
    cout << endl;

    // Scenario 2: Using Default Constructor and Setters
    StudentResult student2;
    student2.setStudentName("Dania Shahid");
    student2.setMathMarks(75.0);
    student2.setScienceMarks(80.5);
    student2.setSportsScore(70.0);
    student2.showStudentResult();

    return 0;
}