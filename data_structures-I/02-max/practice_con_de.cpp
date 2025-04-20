#include <iostream>
using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Constructor
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    // Member operator+ overload
    Complex operator+(const Complex& c1) const {
        double r1 = real + c1.real;
        double i1 = imag + c1.imag;
        return Complex(r1, i1);
    }

    void display() const {
        std::cout << real << " + " << imag << "i" << "\n";
    }

    // Member operator* overload, but with friend function
    friend Complex operator*(const Complex& a, const Complex& b){
        double r = a.real * b.real - a.imag * b.imag;
        double i = a.real * b.imag + a.imag * b.real;
        return Complex(r, i);
    }

    // Member operator<< overload
    friend std::ostream& operator<<(std::ostream& out, const Complex& c1){
        out << c1.real << " + " << c1.imag << "i" << "\n";
        return out;
    }
};

int main() {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);

    Complex sum = c2 + c2;
    sum.display();

    Complex prod = c1 * c2;     
    cout << "Product: " << prod << endl;

    return 0;
}