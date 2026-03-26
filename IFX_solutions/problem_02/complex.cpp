#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Declare operator<< as a friend to access private members
    friend ostream& operator+(ostream& os, const Complex& c);
    friend ostream& operator-(ostream& os, const Complex& c);
};

// Define operator<< (non-member function)
ostream& operator+(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) {
        os << " + " << c.imag << "i";
    } else {
        os << " - " << -c.imag << "i"; // Handles negative imaginary parts
    }
    return os; // Return the stream to allow chaining
}

ostream& operator-(ostream& os, const Complex& c) {
    os << c.real;
    if (c.imag >= 0) {
        os << " + " << c.imag << "i";
    } else {
        os << " - " << -c.imag << "i"; // Handles negative imaginary parts
    }
    return os; // Return the stream to allow chaining
}


int main() {
    Complex c1(3.5, 2.5);
    Complex c2(1.0, -4.0);

    // Using the overloaded << operator
    //cout << "Complex Number 1: " + c1 << endl;
    //cout << "Complex Number 2: " + c2 << endl;
    cout - c1 << endl;
    cout + c2 << endl;

    return 0;
}
