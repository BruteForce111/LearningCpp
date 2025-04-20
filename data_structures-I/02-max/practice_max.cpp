#include <cstring>
#include <iostream>
#include <typeinfo> //so that we can use typeid(T).name()
using namespace std;

// Declaration purpose only
template <typename T>
void getData(T &a, T& b);

void getData(char a[], char b[]);

template <typename T>
T findMax(T a, T b);

char* findMax(char a[], char b[]);

template <typename T>
void displayMax(T a, T b, T max);

int main(){
    int aInt, bInt, maxInt;
    double aDouble, bDouble, maxDouble;
    char aChar, bChar, maxChar;
    char aArray[100], bArray[100];
    char *maxArray;

    getData(aInt, bInt);
    getData(aDouble, bDouble);
    getData(aChar, bChar);
    getData(aArray, bArray);

    maxInt = findMax(aInt, bInt);
    maxDouble = findMax(aDouble, bDouble);
    maxChar = findMax(aChar, bChar);
    maxArray = findMax(aArray, bArray);

    displayMax(aInt,    bInt,    maxInt);
    displayMax(aDouble, bDouble, maxDouble);
    displayMax(aChar,   bChar,   maxChar);
    displayMax(aArray,  bArray,  maxArray);

    return 0;  // end of main
}

template <typename T>
void getData(T &a, T& b){
    cout << "\nEnter two " << typeid(T).name() << "s" << endl;

    cout << "First: ";
    cin >> a;

    cout << "Second: ";
    cin >> b;
}

void getData(char a[], char b[]){
    cout << "\nEnter two c‑strings" << endl;

    cout << "First: ";
    cin.ignore();
    cin.getline(a, 100);

    cout << "Second: ";
    cin.getline(b, 100);
}
template <typename T>
T findMax(T a, T b){
    T max = a;
    if (max < b) max = b;
    return max;
}

char* findMax(char a[], char b[]){
    char* max = a;
    if (strcmp(a, b) < 0) max = b;
    return max;
}

template <typename T>
void displayMax(T a, T b, T max) {
    cout << "\nType: "   << typeid(T).name()
         << "\nFirst: "  << a
         << "\nSecond: " << b
         << "\nMax: "    << max
         << endl;
}