//*****************************************************************************************************
//
//      This header file defines a class template for a dyad, which is a pair of values of the same 
//      type.
//      The author has chosen the name Dyad (from the Greek for “two”) to emphasize that this class template 
//      always holds exactly two values of the same type. In other words, a Dyad<T> is simply a little wrapper 
//      around two T‑objects
//
//*****************************************************************************************************

#ifndef DYAD_H
#define DYAD_H

// Dyad<T> is like std::pair<T,T>, but specialized to always hold two Ts
template <typename T>
class Dyad {
private:
    T val1;   // the first stored value
    T val2;   // the second stored value

public:
    // Constructor with default arguments: if you call Dyad<T>() both val1 and val2 are initialized to T(0)
    // either declare only + define out‑of‑class or define inline + initialize right away
    // this is declaration only
    Dyad(T v1 = 0, T v2 = 0);

    // Accessor for the first value (does not modify the object)
    T getFirst() const;

    // Accessor for the second value (does not modify the object)
    T getSecond() const;

    // Retrieves both values at once by writing them into the two reference parameters
    void get2Values(T &v1, T &v2) const;

    // Swaps the two stored values in place
    void swapValues();
};

//*****************************************************************************************************
// Definitions of the methods declared above. Because this is a template, definitions go in the header.
//*****************************************************************************************************

template <typename T>
// [3]: how to use out‑of‑class definitions properly
Dyad<T>::Dyad(T val1, T val2)
    : val1(val1),   // initialize member val1 from constructor argument
      val2(val2)    // initialize member val2 from constructor argument
{
    // body left empty: initialization list already did the work
}

template <typename T>
//trailing const here is to promise that the function wont change any data member of Dyad object instance (variables in private scope)
T Dyad<T>::getFirst() const {
    return val1;    // return a copy of the first value
}

template <typename T>
T Dyad<T>::getSecond() const {
    return val2;    // return a copy of the second value
}

template <typename T>
void Dyad<T>::get2Values(T &v1, T &v2) const {
    // write the two stored values into the caller’s references
    v1 = val1;
    v2 = val2;
}

template <typename T>
void Dyad<T>::swapValues() {
    // swap val1 and val2; you could also use std::swap(val1, val2)
    T temp = val1;
    val1 = val2;
    val2 = temp;
}

#endif  // DYAD_H

/*


[1]. The `#ifndef / #define / #endif` block**
These three lines are called an **include guard**, and they prevent the header from being processed more than once if you `#include` it multiple times:

```cpp
#ifndef DYAD_H    // “If DYAD_H is not defined…”
#define DYAD_H    // define the macro DYAD_H now

// … all your class template code …

#endif            // end the conditional
```

* **`#ifndef DYAD_H`** checks whether the preprocessor symbol `DYAD_H` is already defined.
* If it’s **not** defined, it then **defines** it (`#define DYAD_H`) and includes the rest of the file.
* On any subsequent inclusion, `DYAD_H` is already defined, so the compiler skips over the entire block—avoiding duplicate definitions and “redefinition” errors.

---

[2]. Trailing `const` on a member function**

```cpp
T getFirst() const;
          ^^^^^
```

Putting `const` **after** the parameter list of a member function means:

* **Promise:** this method will **not** modify any non‑`mutable` data members of the object.
* **Allows calls on `const` objects:** you can do

  ```cpp
  const Dyad<int> d(1,2);
  int x = d.getFirst();  // OK because getFirst() is a const method
  ```

  but you **couldn’t** call any non‑`const` methods on `d`.

Concretely, inside a `const`‑qualified method:

* `this` is treated as `const Dyad<T>*`
* You can only call other `const` methods or read members
* Any attempt to write `val1 = …` would be a compile‑time error

---

### Why use it?

* **Safety & clarity**: it guarantees to users (and to you later, reading the code) that calling `getFirst()` won’t alter the object.
* **Const‑correctness**: lets you work with `const` instances or references without extra casting or overload confusion.

*/




/*
[3]
Here are a handful of small classes (some templated, some not) showing how you can use out‑of‑class definitions, initializer‑lists, and scope‑resolution (`ClassName::…`) in different scenarios.  Try to read each line in the constructor signature the same way you just parsed your `Dyad<T>` example.

---

```cpp
// 1) A non‑template Point class
// header (Point.h)
class Point {
    double x, y;
public:
    Point(double x, double y);    // declaration only
    double getX() const { return x; }
    double getY() const { return y; }
};

// implementation (Point.cpp)
#include "Point.h"

Point::Point(double x, double y)
  : x(x),                        // init member x from parameter x
    y(y)                         // init member y from parameter y
{}                               // empty body
```

**Key takeaways**

* `Point::Point` shows that the first `Point` is the class scope, the second is the constructor name.
* The `: x(x), y(y)` is the initializer‑list.

---

```cpp
// 2) A templated Pair<T1,T2> holding two possibly different types
// header (Pair.h)
template<typename A, typename B>
class Pair {
    A first;
    B second;
public:
    Pair(const A& a, const B& b);
    // … other methods …
};

// implementation (Pair.hpp — included by users)
template<typename A, typename B>
Pair<A,B>::Pair(const A& a, const B& b)
  : first(a),        // initialize member first from parameter a
    second(b)        // initialize member second from parameter b
{}
```

**Key takeaways**

* You repeat the full template parameters (`<A,B>`) on both `Pair<A,B>::Pair` and the template header.
* This gives you a heterogeneous two‑element container.

---

```cpp
// 3) Inheritance + move semantics
struct Shape { 
    int id; 
    Shape(int id): id(id) {} 
};

struct ColoredShape : Shape {
    std::string color;
    // constructor declaration
    ColoredShape(int id, std::string c);
    // … 
};

// implementation (ColoredShape.cpp)
#include "ColoredShape.h"

ColoredShape::ColoredShape(int id, std::string c)
  : Shape(id),              // call base‑class ctor with id
    color(std::move(c))     // move‑construct color from c
{}
```

**Key takeaways**

* `: Shape(id)` invokes the base‑class constructor before your member inits.
* You can `std::move` in the initializer list to steal from parameters.

---

```cpp
// 4) Delegating constructors (C++11+)
class Rectangle {
    double width, height;
public:
    Rectangle();                     // default
    Rectangle(double w, double h);   // main
};

// implementation
Rectangle::Rectangle()
  : Rectangle(1.0, 1.0)  // delegate to the other ctor
{}

Rectangle::Rectangle(double w, double h)
  : width(w), height(h)
{}
```

**Key takeaways**

* One constructor can call another via `: Rectangle(…)`.
* Keeps your initialization logic centralized.

---

```cpp
// 5) Move constructor example
class Buffer {
    char* data;
    std::size_t size;
public:
    Buffer(std::size_t n);
    Buffer(Buffer&& other) noexcept;
    ~Buffer();
    // …
};

// implementation
Buffer::Buffer(std::size_t n)
  : data(new char[n]), size(n)
{}

Buffer::Buffer(Buffer&& other) noexcept
  : data(other.data),     // steal the pointer …
    size(other.size)      // … and the size
{
    other.data = nullptr; // leave other in a safe state
    other.size = 0;
}

Buffer::~Buffer() {
    delete[] data;
}
```

**Key takeaways**

* Move‑ctors often use initializer‑lists to steal resources.
* After the colon you  initialize each member from `other`.

---

### What to look for in each example

1. **`ClassName::ClassName(...)`** — the scope and constructor name always match.
2. **`:`** introduces the **initializer list**, which runs **before** the `{…}` body.
3. **`member(param)`** pairs always read “initialize my member from this parameter.”
4. **Initializer list order ≠ textual order**, but members are actually initialized in the order they’re declared in the class.

Once you spot that pattern, you can confidently define constructors (and even copy/move constructors, delegating ctors, and inherited ctors) all over your codebase following the same rules.

*/