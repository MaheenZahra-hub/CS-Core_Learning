#include <iostream>
#include <string>

using namespace std;

// 1. Modular Programming: Function to determine Grade based on Logic (Point 3 & 5)
char calculateGrade(float score) {
    if (score >= 90) return 'A';
    else if (score >= 80) return 'B';
    else if (score >= 70) return 'C';
    else if (score >= 60) return 'D';
    else return 'F';
}

// 2. Pointers/References: Update a value in memory directly (Point 1)
void applyExtraCredit(float *score, float bonus) {
    *score = *score + bonus;
    if (*score > 100) *score = 100; // Cap at 100%
}

int main() {
    // 3. Variables & Data Types (Point 2)
    const int NUM_STUDENTS = 5;
    string names[NUM_STUDENTS] = {"Maheen", "Dania", "Ali", "Murtaza", "Zahra"};
    
    // 4. Arrays: Storing multiple items (Point 6)
    float scores[NUM_STUDENTS] = {88.5, 92.0, 71.5, 55.0, 82.5};

    cout << "--- Initial Student Grades ---" << endl;

    // 5. Loops: Iterating through data (Point 3)
    float highest = scores[0];
    for (int i = 0; i < NUM_STUDENTS; i++) {
        // 6. Relational & Logical Operators (Point 4)
        if (scores[i] > highest) {
            highest = scores[i];
        }

        cout << names[i] << ": " << scores[i] << " [Grade: " << calculateGrade(scores[i]) << "]" << endl;
    }

    // 7. Demonstration of Pointer Logic
    cout << "\nApplying +5 Extra Credit to the first student using pointers..." << endl;
    applyExtraCredit(&scores[0], 5.0); // Passing memory address

    cout << "New score for " << names[0] << ": " << scores[0] << " [New Grade: " << calculateGrade(scores[0]) << "]" << endl;

    cout << "\nClass Highest Score: " << highest << endl;

    return 0;
}