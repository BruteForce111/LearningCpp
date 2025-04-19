//Change source code to use C++ style comments
/*
Additional Knowledge:
In C++, **overloading** refers to defining multiple functions or operators with the **same name** but with **different parameter lists** (or types). The compiler determines which version of the function or operator to call based on the arguments provided.

---

### 1. **Function Overloading**
Function overloading allows you to define multiple functions with the same name but different parameter types or numbers of parameters.

#### Example:
```cpp
#include <iostream>
using namespace std;

// Overloaded functions
void print(int x) {
    cout << "Integer: " << x << endl;
}

void print(double x) {
    cout << "Double: " << x << endl;
}

void print(string x) {
    cout << "String: " << x << endl;
}

int main() {
    print(10);         // Calls the version with int
    print(3.14);       // Calls the version with double
    print("Hello");    // Calls the version with string
    return 0;
}
```

---

### 2. **Operator Overloading**
Operator overloading allows you to redefine the behavior of operators (e.g., `+`, `-`, `*`, etc.) for user-defined types like classes or structs.

#### Example:
```cpp
#include <iostream>
using namespace std;

class Complex {
public:
    double real, imag;

    Complex(double r, double i) : real(r), imag(i) {}

    // Overload the + operator
    Complex operator+(const Complex &other) {
        return Complex(real + other.real, imag + other.imag);
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1(1.0, 2.0), c2(3.0, 4.0);
    Complex c3 = c1 + c2; // Calls the overloaded + operator
    c3.display();         // Output: 4.0 + 6.0i
    return 0;
}
```

---

### Key Points:
1. **Function Overloading**:
   - Same function name, different parameter types or counts.
   - Resolved at **compile time**.

2. **Operator Overloading**:
   - Redefines the behavior of operators for custom types.
   - Must be implemented as a member or friend function.

3. **Rules for Overloading**:
   - The parameter list must differ (either in type or number of parameters).
   - Return type alone **cannot** distinguish overloaded functions.

---

### Why Use Overloading?
- To improve code readability and usability.
- To allow the same function/operator to work with different types of data.

Let me know if you'd like more examples or clarification!
*/


#include <iostream>
using namespace std;

// A simple class to represent a complex number: real + imag·i
class Complex {
private:
    double real;   // the real part
    double imag;   // the imaginary part

public:
    // ----------------------------------
    // 1) Constructor
    // ----------------------------------
    // Complex(double r, double i)
    //   - r initializes real
    //   - i initializes imag
    //   - we give default values 0.0 so you can write Complex() or Complex(5)
    Complex(double r = 0.0, double i = 0.0)
        : real(r), imag(i) 
    {}

    // ----------------------------------
    // 2) Member operator+ overload
    // ----------------------------------
    // This lets you write c1 + c2
    // as shorthand for c1.operator+(c2)
    Complex operator+(const Complex &other) const {
        // 'this->real' + other.real, and same for imag
        return Complex(real + other.real,
                       imag + other.imag);
    }

    // ----------------------------------
    // 3) display helper
    // ----------------------------------
    // Prints the complex number in the form "a + bi"
    void display() const {
        cout << real << " + " << imag << "i" << endl;
    }

    // ----------------------------------
    // 4) Friend operator* overload
    // ----------------------------------
    // A non‑member function needs access to private members,
    // so we declare it 'friend'.  That means it can see real & imag.
    friend Complex operator*(const Complex &a, const Complex &b) {
        // (a + bi)(c + di) = (ac − bd) + (ad + bc)i
        double r = a.real * b.real - a.imag * b.imag;
        double i = a.real * b.imag + a.imag * b.real;
        return Complex(r, i);
    }

    // ----------------------------------
    // 5) Friend ostream<< overload
    // ----------------------------------
    // Allows you to write: cout << c;
    // instead of c.display()
    friend ostream& operator<<(ostream &out, const Complex &c) {
        out << c.real << " + " << c.imag << "i";
        return out;  // enable chaining: cout << c1 << c2;
    }
};

//--------------------------------------
// main: demonstrate our operators
//--------------------------------------
int main() {
    Complex c1(1.0, 2.0);       // 1 + 2i
    Complex c2(3.0, 4.0);       // 3 + 4i

    // Uses member operator+:
    //   Complex operator+(const Complex&)
    Complex sum = c1 + c2;      // equivalent to c1.operator+(c2)
    sum.display();              // prints: 4.0 + 6.0i

    // Uses friend operator*:
    //   Complex operator*(const Complex&, const Complex&)
    Complex prod = c1 * c2;     
    cout << "Product: " << prod << endl;
    // prints: Product: -5.0 + 10.0i

    return 0;
}
