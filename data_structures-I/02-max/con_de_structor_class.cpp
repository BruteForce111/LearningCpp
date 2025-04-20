#include <iostream>
#include <string>
using namespace std;

class Widget {
private:
    int     id;     // only Widget’s own methods (and its friends) can access
protected:
    string  name;   // accessible in Widget and any subclasses
public:
    static int count;  // one shared counter for all Widget instances

    // -------------------------
    // 1) Default constructor
    // -------------------------
    // Called when you write: Widget w;
    // Initializes id to 0, name to empty, and increments count.
    Widget()
      : id(0), name("")           // initializer list
    {
        ++count;
        cout << "[Widget#"<< id <<"] default-constructed. Total count="<< count <<"\n";
    }

    // -------------------------
    // 2) Parameterized constructor
    // -------------------------
    // Called when you write: Widget w(42, "foo");
    Widget(int i, const string &n)
      : id(i), name(n)
    {
        ++count;
        cout << "[Widget#"<< id <<"] parameterized-constructed. Total count="<< count <<"\n";
    }

    // -------------------------
    // 3) Copy constructor
    // -------------------------
    // Called when you write: Widget w2 = w1;
    Widget(const Widget &other)
      : id(other.id), name(other.name)
    {
        ++count;
        cout << "[Widget#"<< id <<"] copy-constructed from Widget#"<< other.id 
             <<" . Total count="<< count <<"\n";
    }

    // -------------------------
    // 4) Move constructor
    // -------------------------
    // Called when you write: Widget w2 = std::move(w1);
    /*
    4. Move‑Assignment: w1 = std::move(w3);
    w1 = std::move(w3);
    a. What happens under the hood?

    - std::move(w3) casts w3 to an rvalue of type Widget&&.

    - The compiler picks your move‑assignment operator (if you’ve defined one) or the defaulted one (if not).

    - That operator typically:

    1. Destroys or releases w1’s old resources,

    2. “Steals” w3’s resources (pointers, buffers, etc.),

    3. Leaves w3 in a valid but unspecified state.

    b. There is no hidden buffer: you’re not moving “into some temporary” — you’re moving directly from w3 into w1.

    c. Afterwards w3 is in whatever state your move logic left it (often “empty” or zeroed). Accessing it beyond assignment or destruction is legal but limited.
    */
    /*
    Why std::move(other.name) but not other.id?
    - id is a simple scalar (int or similar). Copying it is as cheap as “moving” it.
    - name is a std::string. Moving a string typically just swaps pointers/internal buffers, which is much cheaper than copying the entire character buffer.
    - std::move(...) is a cast that turns its argument into an rvalue, so you invoke string’s move constructor instead of its copy constructor.
    */
    /*
    What does noexcept mean?
    - It promises this constructor won’t throw exceptions.
    - Many standard library containers (like std::vector) will use your move constructor in preference to the copy constructor only if it’s noexcept, because they rely on strong exception-safety guarantees during reallocation.
    */
    Widget(Widget &&other) noexcept
      : id(other.id), name(std::move(other.name))
    {
        ++count;
        /*
        Why other.id = 0;?
        - After you “steal” data from other, you should leave other in a valid state (destructible, assignable, etc.).
        - Zeroing other.id is one way to reset it; other.name is already safe (a moved‑from std::string is valid but unspecified).
        - This helps avoid surprising bugs if someone inspects or destroys the moved‑from object.
        */
        other.id = 0;             // leave 'other' in a valid state

        cout << "[Widget#"<< id <<"] move-constructed. Other reset to #"<< other.id
             <<". Total count="<< count <<"\n";
    }

    // -------------------------
    // 5) Copy assignment
    // -------------------------
    // Called when you write: w2 = w1;
    /*
    1. operator=: this tells the compiler you’re overloading the assignment operator = for Widget.
    operator is not an ordinary identifier you’re free to rename—it’s part of the language syntax that tells the compiler “this is my overload of the built‑in = operator.”
    You must use exactly operator= (and similarly operator+, operator<<, etc.) when you want your class to support that operator syntax (a = b;, a + b;, std::cout << a;, and so on).
    2. (): parameters list
    */
    Widget& operator=(const Widget &other) {
        // A built‑in pointer inside every non‑static member function that points to the current object.
        if (this != &other) {    // protect against self‑assignment
            id   = other.id;
            name = other.name;
        }
        cout << "[Widget#"<< id <<"] copy-assigned from Widget#"<< other.id <<"\n";
        // Explanation in [1]
        return *this;
    }

    // -------------------------
    // 6) Move assignment
    // -------------------------
    // Called when you write: w2 = std::move(w1);
    Widget& operator=(Widget &&other) noexcept {
        if (this != &other) {
            id    = other.id;
            name  = std::move(other.name);
            other.id = 0;
        }
        cout << "[Widget#"<< id <<"] move-assigned. Other reset to #"<< other.id <<"\n";
        return *this;
    }

    // -------------------------
    // 7) Destructor
    // -------------------------
    // Automatically called when a Widget goes out of scope
    ~Widget() {
        --count;
        cout << "[Widget#"<< id <<"] destructed. Remaining count="<< count <<"\n";
    }

    // -------------------------
    // Public interface
    // -------------------------
    void setName(const string &n) { name = n; }
    string getName() const {        // const: doesn’t modify *this
        return name;
    }

    int getId() const { return id; }

    // -------------------------
    // Static member function
    // -------------------------
    // Can be called as Widget::printCount();
    static void printCount() {
        cout << "Current live Widget count: " << count << "\n";
    }

    // -------------------------
    // Friend function: operator<<
    // -------------------------
    // Not a member, but declared friend so it can access private/protected data
    // if you dont understand ostream& data type, read [2]
    // if you wanna understand more about ostream& and operator<<, read [3]
    friend ostream& operator<<(ostream &out, const Widget &w) {
        out << "Widget#" << w.id << " [" << w.name << "]";
        return out;
    }
};

// Definition of the static data member
int Widget::count = 0;

// --------------------------------------
// Demonstration in main()
// --------------------------------------
int main() {
    cout << "--- Creating w1 with default ctor ---\n";
    Widget w1;                    // default ctor

    cout << "\n--- Creating w2 with param ctor ---\n";
    Widget w2(100, "Gizmo");      // parameterized ctor

    cout << "\n--- Copy-constructing w3 from w2 ---\n";
    Widget w3 = w2;               // copy ctor

    cout << "\n--- Move-constructing w4 from temporary ---\n";
    Widget w4 = Widget(200, "Flux");  // param ctor, then move ctor

    cout << "\n--- Assigning w1 = w2 (copy) ---\n";
    w1 = w2;                      // copy assignment

    cout << "\n--- Assigning w1 = move(w3) (move) ---\n";
    w1 = std::move(w3);           // move assignment

    cout << "\n--- Printing objects with operator<< ---\n";
    cout << w1 << "\n" 
         << w2 << "\n"
         << w3 << "\n"   // w3.id was reset to 0 by move
         << w4 << "\n";

    cout << "\n--- Static count check ---\n";
    Widget::printCount();

    cout << "\n--- Exiting main() — destructors will run in reverse order ---\n";
    return 0;
}


/*
[1]: 
the line  
```cpp
return *this;
```
does two things:

1. **Returns by reference**  
   - The function is declared to return `Widget&` (a reference to a `Widget`).  
   - Inside a member function, `this` is a pointer (`Widget*`) to the object being assigned-to.  
   - `*this` dereferences that pointer, yielding an lvalue of type `Widget&`—exactly what the function signature promises.

2. **Enables chaining and expression‑use**  
   - C++ lets you write chained assignments like  
     ```cpp
     a = b = c;
     ```  
     Here the compiler evaluates `b = c` first, which returns a `Widget&` referring to `b`. Then it does `a = (that reference)`, just as if you’d written `a = b;`.  
   - Without returning `*this`, `a = b = c;` wouldn’t compile (or would return something meaningless), and you also couldn’t do things like  
     ```cpp
     (a = b).doSomething();
     ```  
     because `(a = b)` wouldn’t be an object you could call methods on.

---

### Visualizing it step by step

1. **Call** `b = c;`  
   - Enters `operator=(b, c)`, copies data, then `return *this;` returns `b` by reference.
2. **Call** `a = (result of b=c);`  
   - That result is `b&`, so it’s exactly `a = b;`.

[2]
Question: is ostream& a string, operation, etc? (Cuz ostream is equal to cout <<)
Think of it this way:

```cpp
friend std::ostream& operator<<(std::ostream &out, const Widget &w) {
    out << "Widget#" << w.id << " [" << w.name << "]";
    return out;
}
```

---

### 1. What’s `std::ostream`?

- **`std::ostream`** is a C++ **class** (in `<iostream>`) that represents “some destination you can write characters to.”  
- Common concrete instances include:  
  - **`std::cout`**: the console’s standard output (an `ostream`)  
  - **`std::ofstream`**: a file output stream  
  - **`std::ostringstream`**: an in‑memory string buffer  

You can think of it like a “printer” object that you can feed data into.

---

### 2. What’s `out`?

- Inside the function it’s just a **parameter name**. You could as well have written:

  ```cpp
  friend std::ostream& operator<<(std::ostream &stream, const Widget &w) { … }
  ```

- At the call site, when you write
  ```cpp
  std::cout << myWidget;
  ```
  the compiler actually does
  ```cpp
  operator<<(std::cout, myWidget);
  ```
  binding `out` to `std::cout`.

---

### 3. How the chaining works

- The expression
  ```cpp
  out << "Widget#"
      << w.id
      << " ["
      << w.name
      << "]";
  ```
  is a sequence of calls to **other** `operator<<` overloads:

  1. `operator<<(out, "Widget#")` — writes the literal, returns `out`  
  2. `operator<<(out, w.id)` — writes the integer, returns `out`  
  3. …and so on.

- Because each `operator<<` returns the same `ostream&`, you can chain them in one expression.

---

### 4. Why not a `string`?  

- You could build a `std::string` if you wanted:
  ```cpp
  std::ostringstream buf;
  buf << "Widget#" << w.id << " [" << w.name << "]";
  std::string s = buf.str();
  ```
- But by overloading `operator<<` for `Widget`, you let *any* `ostream` (console, file, string‑buffer, network socket, etc.) automatically know how to print a `Widget`—and you get all the conveniences of `<<` chaining and formatting flags.

---

#### TL;DR

- **`std::ostream`** is an output stream class, not a string or a pure operation.  
- **`out`** is just the name of the parameter referring to whichever stream you’re writing into (`std::cout`, a file stream, a string stream, ...).  
- The free function `operator<<(ostream&, const Widget&)` hooks into C++’s streaming syntax so you can write `someStream << someWidget;` seamlessly.


[3]
Think of it this way:

- **`std::cout`** is just a global variable of type `std::ostream`.  
- **`operator<<`** is the function that actually does the work under the hood.  

When you write:
```cpp
std::cout << alice << "\n";
```
that’s *exactly* calling
```cpp
operator<<( std::cout, alice );
operator<<( std::cout, "\n" );
```
—you don’t ever have to type `operator<<` yourself.  The syntax `cout << value` is just C++’s way of letting you chain those calls elegantly.

---

### Why C++ uses this pattern

1. **Consistency**  
   Every printable type (built‑in or user‑defined) uses the same `<<` syntax.  
2. **Extensibility**  
   You can overload `operator<<` for your own classes so they integrate seamlessly with streams.  
3. **Chaining**  
   Because each `operator<<` returns the same stream reference, you can do:
   ```cpp
   std::cout << a << b << c;
   ```
   instead of verbose function calls.

---

**Bottom line:**  
Just keep writing `std::cout << …;`.  You only need to think about `std::ostream` and `operator<<` if you’re defining your own overloads or getting curious about what’s happening behind the scenes. Once you’ve done a few `cout << x;` lines, it will feel natural—and not at all “fucking complicated.”



Code Snippet to explain more:
```cpp
friend std::ostream& operator<<(std::ostream &out, const Person &p);


std::ostream& operator<<(std::ostream &out, const Person &p) {
    out << "Person(\"" << p.name << "\", " << p.age << ")";
    return out;
}
```

### 1. Declaration inside `Person`  
```cpp
friend std::ostream& operator<<(std::ostream &out, const Person &p);
```

- **`friend`**  
  Means “this non‑member function is allowed to touch my private data.” Without `friend`, `operator<<` couldn’t read `p.name` or `p.age` because they’re private.

- **`std::ostream&`**  
  That’s the return type. We return the same stream we were given so you can write things like  
  ```cpp
  std::cout << alice << "!\n";
  ```
  —each `<<` call hands you the stream back.

- **`operator<<`**  
  This declares an overload of the insertion operator. It’s just a function whose name, by convention, lets you write `cout << value`.

- **Parameters**  
  - `std::ostream &out`—the stream you’re writing into (e.g. `std::cout`).  
  - `const Person &p`—the person you want to print, passed by `const&` to avoid copies.

Putting it inside `class Person` with `friend` simply lets that global function peek at your private members.

---

### 2. Definition outside  
```cpp
std::ostream& operator<<(std::ostream &out, const Person &p) {
    out << "Person(\""  // literal text
        << p.name       // access private name
        << "\", "       // more text
        << p.age        // access private age
        << ")";         // close text
    return out;        // allow chaining
}
```

- **Body**  
  1. `out << "Person(\""` writes the text `Person("`.  
  2. `<< p.name` appends the person’s name.  
  3. `<< "\", "` adds `", `.  
  4. `<< p.age` appends the age number.  
  5. `<< ")"` finishes with `)`.  
  Internally each `<<` is a call to another `operator<<`, but you just chain them.

- **`return out;`**  
  Gives back the same stream so you can do more inserts or end with `<< "\n"`.

---

### Putting it to use  
Once you have that in place, you can write in `main`:

```cpp
Person alice{"Alice", 30};
std::cout << alice << "\n";
```

Under the hood the compiler turns `std::cout << alice` into a call to your `operator<<`, passing in `std::cout` and `alice`, producing nicely formatted output.

---

**In essence:**  
- **`friend`** lets your non‑member `operator<<` reach private bits of `Person`.  
- The **signature** (`ostream& …`) makes it behave like all other stream insertions (and lets you chain).  
- The **definition** simply spits out the bits you want in the order you want.
*/