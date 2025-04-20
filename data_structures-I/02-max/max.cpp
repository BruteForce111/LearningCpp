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

// [1] Why do we need declare template <typename T> for everytime we declare new functions

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

    // [2]: when to use cin, when to use getline()
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


/* 
[1]: 

Why do we need declare template <typename T> for everytime we declare new functions
In C++, **every** function (and every class) that you want to parameterize by a template type needs its own `template<…>` prefix—there’s no “file‑level” or “block‑level” template parameter list that covers multiple free functions.  The grammar is literally

```cpp
template<typename T>
ReturnType funcName(…);

template<typename T>
OtherReturn otherFuncName(…);

// …etc.
```

and each `template<…>` applies **only** to the very next declaration.

---

### Why it works this way

- **Self‑contained templates.**  A function template is its own entity.  Its template parameters (`T`, in your case) are part of its signature.  You can’t “open” a template parameter scope and drop in more functions without repeating the keyword.
- **Clarity & modularity.**  By writing `template<typename T>` on each function, it’s immediately obvious which functions are generic.  If one day you want a non‑template overload or a different set of template parameters, you don’t have to untangle a shared declaration.

---

### Alternative: group under a class template

If you really want to avoid repeating yourself, you *can* bundle them into a single class (or struct) template, where you only write `template<typename T>` once:

```cpp
template<typename T>
struct Utils {
    static void getData(T &a, T &b);
    static T    findMax(T a, T b);
    static void displayMax(T a, T b, T mx);
};

// definitions:

template<typename T>
void Utils<T>::getData(T &a, T &b) { }

template<typename T>
T Utils<T>::findMax(T a, T b) { }

template<typename T>
void Utils<T>::displayMax(T a, T b, T mx) { }

// use it:
int x, y;
Utils<int>::getData(x,y);
auto m = Utils<int>::findMax(x,y);
Utils<int>::displayMax(x,y,m);
```

But for three free functions, most C++ code simply repeats the `template<typename T>` header each time. It’s the language’s design—and it keeps each template declaration explicit and self‑contained.



[2]
Use cin >> a; when you only need a single “word” (no spaces) and you’ve ensured your buffer is large enough (or you’re okay risking overflow).

Use cin.getline(a, size); when you need to read a full line of text (possibly containing spaces) and want to guard against overrunning your buffer.

*/