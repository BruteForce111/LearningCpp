//*****************************************************************************************************
//
//      This program demonstrates the use of function templates and function overloading,
//      which let you write generic code that works with different data types.
//
//*****************************************************************************************************

#include <cstring>    // for strcmp (comparing C‑style strings)
#include <iostream>   // for std::cin, std::cout
#include <typeinfo>   // for typeid to get the type’s name at runtime
using namespace std;  // bring std::cin, std::cout, std::string, etc. into scope

//*****************************************************************************************************
// Function declarations (prototypes)

// A generic function template to read two values of any type T
template <typename T>
void getData(T &a, T &b);

// An overload specifically for reading two C‑strings (char arrays)
void getData(char a[], char b[]);

// A generic function template that returns the larger of two values of type T
template <typename T>
T findMax(T a, T b);

// An overload for comparing two C‑strings and returning the larger one
char *findMax(char a[], char b[]);

// A generic function template to display the inputs and the computed max
template <typename T>
void displayMax(T a, T b, T max);

//*****************************************************************************************************

int main() {
    // Variables for each type we’ll test
    int    aInt,    bInt,    maxInt;       // integers
    double aDouble, bDouble, maxDouble;    // floating‑point numbers
    char   aChar,   bChar,   maxChar;      // single characters
    char   aArray[100], bArray[100];       // C‑style strings (arrays of char)
    char  *maxArray;                       // to hold pointer to “larger” C‑string

    // 1) Read input for each type
    getData(aInt,    bInt);      // reads two ints
    getData(aDouble, bDouble);   // reads two doubles
    getData(aChar,   bChar);     // reads two chars
    getData(aArray,  bArray);    // reads two C‑strings

    // 2) Compute the max for each type
    maxInt    = findMax(aInt,    bInt);
    maxDouble = findMax(aDouble, bDouble);
    maxChar   = findMax(aChar,   bChar);
    maxArray  = findMax(aArray,  bArray);

    // 3) Display the results
    displayMax(aInt,    bInt,    maxInt);
    displayMax(aDouble, bDouble, maxDouble);
    displayMax(aChar,   bChar,   maxChar);
    displayMax(aArray,  bArray,  maxArray);

    return 0;  // end of main
}

//*****************************************************************************************************

// Generic version: reads two values of type T from standard input
template <typename T>
void getData(T &a, T &b) {
    // typeid(T).name() prints a (compiler‑specific) name for T
    cout << "\nEnter two " << typeid(T).name() << "s" << endl;

    cout << "First: ";
    cin  >> a;   // read first value

    cout << "Second: ";
    cin  >> b;   // read second value
}

//*****************************************************************************************************

// Overload for C‑strings (char arrays)
void getData(char a[], char b[]) {
    cout << "\nEnter two c‑strings" << endl;

    cout << "First: ";
    cin.ignore();           // clear any leftover newline from previous input
    cin.getline(a, 100);    // read up to 99 chars + null terminator into a

    cout << "Second: ";
    cin.getline(b, 100);    // read up to 99 chars + null terminator into b
}

//*****************************************************************************************************

// Generic version: returns the larger of a and b for any type that supports operator<
template <typename T>
T findMax(T a, T b) {
    T max = a;            // assume a is largest
    if (max < b)          // if b is actually larger
        max = b;
    return max;           // return the larger value
}

//*****************************************************************************************************

// Overload for C‑strings: uses strcmp to compare text lexicographically
char *findMax(char a[], char b[]) {
    char *max = a;        // assume the first string is “larger”
    // strcmp returns <0 if a<b, 0 if equal, >0 if a>b
    if (strcmp(a, b) < 0)
        max = b;          // if b is lexicographically greater, pick b
    return max;           // return pointer to the “larger” string
}

//*****************************************************************************************************

// Generic version: prints the type name, inputs, and the max value
template <typename T>
void displayMax(T a, T b, T max) {
    cout << "\nType: "   << typeid(T).name()
         << "\nFirst: "  << a
         << "\nSecond: " << b
         << "\nMax: "    << max
         << endl;
}

//*****************************************************************************************************
/*
 Sample run (user input in bold):

 Enter two ints
 First: **1**
 Second: **2**

 Enter two doubles
 First: **1.5**
 Second: **2.5**

 Enter two chars
 First: **a**
 Second: **b**

 Enter two c-strings
 First: **apple**
 Second: **orange**

 Type: int
 First: 1
 Second: 2
 Max: 2

 Type: double
 First: 1.5
 Second: 2.5
 Max: 2.5

 Type: char
 First: a
 Second: b
 Max: b

 Type: char *
 First: apple
 Second: orange
 Max: orange
*/
