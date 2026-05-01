#include <iostream>
#include <cmath> // Required for sqrt()
using namespace std;

/**
 * Complex Class
 * Implements complex number arithmetic using Operator Overloading.
 */
class Complex {
private:
    double real, imag;

public:
    // Constructor with default arguments (initializes to 0 if no values provided)
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // --- Arithmetic Operator Overloading ---

    // Adds two complex numbers: (a + bi) + (c + di) = (a+c) + (b+d)i
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Subtracts two complex numbers
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Multiplies two complex numbers: (a+bi)(c+di) = (ac-bd) + (ad+bc)i
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, 
                       real * other.imag + imag * other.real);
    }

    // Divides two complex numbers using the conjugate method
    Complex operator/(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        if (denom == 0) return Complex(0, 0); // Basic safety check for division by zero
        return Complex((real * other.real + imag * other.imag) / denom, 
                       (imag * other.real - real * other.imag) / denom);
    }

    // --- Stream Operator Overloading (Friend Functions) ---

    // Overloads 'cout' to print complex numbers nicely (e.g., 3 + 4i)
    friend ostream& operator<<(ostream& out, const Complex& c) {
        if (c.imag >= 0)
            out << c.real << " + " << c.imag << "i";
        else
            out << c.real << " - " << -c.imag << "i"; // Handles negative imaginary parts
        return out;
    }

    // Overloads 'cin' to take user input for complex numbers
    friend istream& operator>>(istream& in, Complex& c) {
        cout << "Enter real part: ";
        in >> c.real;
        cout << "Enter imaginary part: ";
        in >> c.imag;
        return in;
    }

    // --- Relational Operator Overloading ---

    // Calculates the absolute value (magnitude) of the complex number
    double magnitude() const {
        return sqrt(real * real + imag * imag);
    }

    // Comparisons based on the magnitude of the numbers
    bool operator==(const Complex& other) const { return magnitude() == other.magnitude(); }
    bool operator!=(const Complex& other) const { return magnitude() != other.magnitude(); }
    bool operator<(const Complex& other) const { return magnitude() < other.magnitude(); }
    bool operator>(const Complex& other) const { return magnitude() > other.magnitude(); }

    // --- Compound Assignment Operators ---

    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this; // Returns reference to the updated object
    }

    Complex& operator*=(const Complex& other) {
        double r = real * other.real - imag * other.imag;
        double i = real * other.imag + imag * other.real;
        real = r;
        imag = i;
        return *this;
    }

    // --- Subscript Operator Overloading ---

    // Allows access to parts via index: [0] for real, [1] for imaginary
    double operator[](int index) const {
        if (index == 0) return real;
        if (index == 1) return imag;
        cerr << "Error: Index must be 0 or 1" << endl;
        return 0;
    }

    ~Complex() {} // Destructor
};

int main() {
    Complex c1(3, 4); // Magnitude = 5
    Complex c2;

    // Use overloaded input operator
    cin >> c2;

    cout << "\n--- Results ---" << endl;
    cout << "c1: " << c1 << endl;
    cout << "c2: " << c2 << endl;
    
    // Arithmetic demonstration
    cout << "Addition:       " << c1 + c2 << endl;
    cout << "Multiplication: " << c1 * c2 << endl;

    // Comparison demonstration
    cout << "\n--- Comparisons (By Magnitude) ---" << endl;
    if (c1 > c2) cout << "c1 has a larger magnitude than c2." << endl;
    else if (c1 < c2) cout << "c2 has a larger magnitude than c1." << endl;
    else cout << "Both have the same magnitude." << endl;

    return 0;
}