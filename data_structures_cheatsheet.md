# Summary of Basic Data Structures in C++
> If you need to know in details about each Data Structure, pull up to the right below part.
> This is only for skimming through if you have already known in details about each data structure
> but need to snap back the definitions, usage, etc...

Here’s a roadmap of the core C++ data structures you’ll use most—grouped by category, with a brief “what & why” for each. As you learn, you’ll discover when and how to choose among them.

---

## 1. Built‑in (Fundamental) Types  
These are the atoms of your programs—simple, fast, and directly supported by the hardware.  
- **Integer types**: `int`, `short`, `long`, `long long` (and their unsigned variants)  
- **Character types**: `char`, `wchar_t`, `char16_t`, `char32_t`  
- **Floating‑point**: `float`, `double`, `long double`  
- **Boolean**: `bool`  
- **Void**: `void` (used in functions)  

---

## 2. Derived Types  
Built from the fundamentals to let you build more complex structures.  
- **Arrays**: `int a[10];` —​contiguous fixed‑size collections
- **Pointers**: `int* p;` —​holds the address of another object  
- **References**: `int& r = a[i];` —​an alias to another variable  
- **Functions & function pointers**: define and pass around behavior  

---

## 3. Strings  
Text in C++ is most commonly managed via:  
- **`std::string`** (dynamic, mutable UTF‑8‐style string)  
- **`std::wstring`** (wide‑character string)  

They handle memory automatically, grow as needed, and support rich operations (concatenation, substring, search).

---

## 4. The STL “Container” Library  
The Standard Template Library (STL) is your one‑stop shop for reusable, well‑tested data structures. All live in `<vector>`, `<list>`, `<map>`, … etc.

### 4.1 Sequence Containers  
Maintain elements in a strict order (by insertion or index).

| Container        | When to use                                                                 |
|------------------|------------------------------------------------------------------------------|
| `std::vector<T>` | Dynamic array; random access in O(1); good default for most lists.          |
| `std::deque<T>`  | Double‑ended queue; fast push/pop front & back; random access.              |
| `std::list<T>`   | Doubly‑linked list; fast insert/erase anywhere; no random access.           |
| `std::forward_list<T>` | Singly‑linked list; lighter than `list`, but only single‑direction traversal. |
| `std::array<T,N>`| Fixed‑size array wrapper; stack‑allocated; size known at compile time.      |

### 4.2 Associative Containers  
Automatically sort their elements (by key) and provide logarithmic lookup.

| Container                 | Key‑value behavior                                                   |
|---------------------------|----------------------------------------------------------------------|
| `std::set<T>`             | Unique sorted keys; no duplicates.                                  |
| `std::multiset<T>`        | Sorted keys; allows duplicates.                                     |
| `std::map<Key,T>`         | Unique sorted keys mapped to values.                                |
| `std::multimap<Key,T>`    | Sorted keys (duplicates allowed) → values.                          |

### 4.3 Unordered Containers  
Hash‑based; average O(1) lookup, but no ordering.

| Container                         | Characteristics                                               |
|-----------------------------------|--------------------------------------------------------------|
| `std::unordered_set<T>`           | Unique keys; hashed.                                         |
| `std::unordered_multiset<T>`      | Keys hashed; duplicates allowed.                             |
| `std::unordered_map<Key,T>`       | Key→value hash map; unique keys.                             |
| `std::unordered_multimap<Key,T>`  | Hash map; duplicate keys allowed.                            |

### 4.4 Container Adapters  
Wrap other containers to provide specific interfaces.

| Adapter                       | Underlying container (default) | Interface            |
|-------------------------------|-------------------------------|----------------------|
| `std::stack<T>`               | `deque<T>`                   | LIFO (push/pop/top)  |
| `std::queue<T>`               | `deque<T>`                   | FIFO (push/pop/front)|
| `std::priority_queue<T>`      | `vector<T>`                  | Heap (max or min)    |

---

## 5. Utility Classes  
Handy helpers that pair well with containers and algorithms.

- **`std::pair<A,B>`**: two‐element struct; useful for key→value in `map`  
- **`std::tuple<Ts…>`**: fixed‐length heterogeneous collection  
- **`std::bitset<N>`**: compile‑time fixed‐size sequence of bits—great for flags/masks  

---

## 6. Your Own Structs & Classes  
When none of the above fit, you define your own:

```cpp
struct Point {
    double x, y;
    // member functions, constructors, operators…
};
```

Over time you’ll combine these with pointers, references, and STL containers to build linked lists, trees, graphs, and more specialized structures.

---

## 7. Iterators & Algorithms  
Almost all STL containers work via **iterators** (`begin()`, `end()`) so you can plug them into generic algorithms in `<algorithm>`:

```cpp
#include <algorithm>
#include <vector>

std::vector<int> v = {/*…*/};
std::sort(v.begin(), v.end());
auto it = std::find(v.begin(), v.end(), 42);
```

---



# Verbosity of Basic Data Structures in C++

**Part 1 – Fundamental Types & Sequence Containers**  

Below are self‑contained C++ snippets demonstrating the core “built‑in” types, arrays/pointers/strings, and the main sequence containers (`vector`, `deque`, `list`, `array`).  

---

### 1. Fundamental Types  
```cpp
#include <iostream>
int main() {
    int    i   = 42;        // integer
    double d   = 3.14;      // floating‑point
    bool   flag= true;      // boolean
    char   c   = 'A';       // character

    std::cout 
      << "int: "    << i   << "\n"
      << "double: " << d   << "\n"
      << "bool: "   << flag<< "\n"
      << "char: "   << c   << "\n";
}
```

---

### 2. C‑Style Array, Pointer, Reference  
```cpp
#include <iostream>
int main() {
    int arr[5] = {1,2,3,4,5};    // fixed‑size array
    int* ptr   = arr;            // pointer to first element
    int& ref   = arr[2];         // alias of arr[2]
    
    ptr[1] = 20;                  // modifies arr[1]
    ref    = 30;                  // sets arr[2] = 30

    for(int k = 0; k < 5; ++k)
        std::cout << arr[k] << " ";  // prints 1 20 30 4 5
}
```

---

### 3. `std::string`  
```cpp
#include <iostream>
#include <string>
int main() {
    std::string s1 = "Hello";
    std::string s2 = ", world!";
    std::string s3 = s1 + s2;      // concatenation

    std::cout << s3              // prints "Hello, world!"
              << "\nlength: " 
              << s3.size()       // length = 13
              << "\nfind ',': " 
              << s3.find(',')    // index of comma
              << "\nsubstr(7): " 
              << s3.substr(7)    // from index 7 → "world!"
              << "\n";
}
```

---

### 4. `std::vector` (Dynamic Array)  
Here’s a rundown of the most common things you can do with a `std::vector<T>` in C++:

---

#### 1. Element Access  
```cpp
vector<int> v = {10,20,30};

// by index (no bounds checking)
int x = v[1];        // x = 20

// with bounds checking (throws if out of range)
int y = v.at(2);     // y = 30

// first / last element
int f = v.front();   // f = 10
int b = v.back();    // b = 30

// raw pointer to underlying array (C‑style)
int* data = v.data();
```

---

#### 2. Capacity Queries & Management  
```cpp
v.size();       // number of elements   → 3
v.empty();      // true if size()==0    → false
v.capacity();   // how many it can hold before reallocating
v.reserve(100);// pre‑allocate space for 100 elements
v.shrink_to_fit(); // ask to reduce capacity to match size
```

---

#### 3. Modifiers  
```cpp
v.push_back(40);        // append 40
v.pop_back();           // remove last element

// insert before the iterator position:
v.insert(v.begin()+1, 15);  // v = {10,15,20,30,40}

// construct–in‑place (avoiding copies):
v.emplace(v.begin()+2, 17); // v = {10,15,17,20,30,40}
v.emplace_back(50);         // same as push_back(50)

// erase a single element or a range:
v.erase(v.begin());         // remove first
v.erase(v.begin()+2, v.begin()+4); // remove two elements

v.clear();      // remove all elements
v.resize(5);    // change size to 5 (truncates or fills with default T{})
v.swap(other);  // swap contents with another vector
```

---

#### 4. Iteration  
```cpp
// classic for
for (size_t i = 0; i < v.size(); ++i)
    cout << v[i] << "\n";

// range‑based for
for (int val : v)
    cout << val << "\n";

// with iterators
for (auto it = v.begin(); it != v.end(); ++it)
    cout << *it << "\n";

// reverse
for (auto it = v.rbegin(); it != v.rend(); ++it)
    cout << *it << "\n";
```

---

#### 5. Integration with `<algorithm>`  
Almost anything in `<algorithm>` works on `vector` iterators:
```cpp
#include <algorithm>

sort(v.begin(), v.end());
auto it = find(v.begin(), v.end(), 20);  // returns iterator or v.end()
reverse(v.begin(), v.end());
```

---

### 5. `std::deque` (Double‑Ended Queue)  
```cpp
#include <iostream>
#include <deque>
int main() {
    std::deque<std::string> dq;
    dq.push_back("end");
    dq.push_front("start");

    for(auto &str : dq)
        std::cout << str << " ";    // start end
    std::cout << "\n";
}
```

---

### 6. `std::list` (Doubly‑Linked List)  
```cpp
#include <iostream>
#include <list>
int main() {
    std::list<int> lst = {1,2,3};
    auto it = std::next(lst.begin());  // points to 2
    lst.insert(it, 99);                 // insert 99 before 2
    lst.erase(lst.begin());             // remove first element (1)

    for(int x : lst)
        std::cout << x << " ";         // 99 2 3
    std::cout << "\n";
}
```

---

### 7. `std::array` (Fixed‑Size Wrapper)  
```cpp
#include <iostream>
#include <array>
int main() {
    std::array<double, 4> a = {0.1, 0.2, 0.3, 0.4};
    for(double x : a)
        std::cout << x << " ";       // 0.1 0.2 0.3 0.4
    std::cout << "\n";
}
```

**Part 2 – Associative & Unordered Containers, Container Adapters, and Utility Classes**  

---

## 1. Associative Containers  
Automatically sorted by key, with logarithmic-time lookups (`O(log n)`).

### 1.1 `std::map<Key, T>`  
A sorted key→value store with **unique** keys.  
```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    // Count word frequencies
    std::map<std::string, int> freq;
    for (const char* w : {"apple", "banana", "apple", "cherry", "banana", "apple"}) {
        ++freq[w];
    }

    // Iterate in sorted key order
    for (auto& [word, count] : freq) {
        std::cout << word << ": " << count << "\n";
    }
    // Output:
    // apple: 3
    // banana: 2
    // cherry: 1
}
```

### 1.2 `std::set<T>`  
A sorted **unique** collection of keys.  
```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> s = {4, 1, 7, 3, 4, 1};
    s.insert(5);
    s.erase(7);

    // Prints 1 3 4 5
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    // Check existence
    if (s.count(3)) std::cout << "3 is in the set\n";
}
```

---

## 2. Unordered Containers  
Hash‑based, average **O(1)** lookups (no ordering).

### 2.1 `std::unordered_map<Key, T>`  
Unsorted key→value store with **unique** keys.  
```cpp
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    // Same frequency count but hashed
    std::unordered_map<std::string,int> freq;
    for (auto w : {"dog","cat","dog","bird","cat"}) {
        ++freq[w];
    }

    // Iteration order is unspecified
    for (auto& p : freq) {
        std::cout << p.first << ": " << p.second << "\n";
    }
}
```

### 2.2 `std::unordered_set<T>`  
Unsorted **unique** collection of keys.  
```cpp
#include <iostream>
#include <unordered_set>

int main() {
    std::unordered_set<int> us = {10,20,20,30};
    us.insert(40);
    us.erase(20);

    // Unspecified order; just membership
    for (int x : us) std::cout << x << " ";
    std::cout << "\n";
}
```

---

## 3. Container Adapters  
Provide specialized interfaces on top of other containers.

### 3.1 `std::stack<T>` (LIFO)  
```cpp
#include <iostream>
#include <stack>
#include <string>

bool isBalanced(const std::string& s) {
    std::stack<char> st;
    for (char c : s) {
        if (c=='(') st.push(c);
        else if (c==')') {
            if (st.empty()) return false;
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    std::cout << std::boolalpha
              << isBalanced("((()))") << "\n"   // true
              << isBalanced("(()")    << "\n";  // false
}
```

### 3.2 `std::queue<T>` (FIFO)  
```cpp
#include <iostream>
#include <queue>
#include <vector>

void breadthFirst(const std::vector<std::vector<int>>& adj, int start) {
    std::vector<bool> visited(adj.size(), false);
    std::queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        std::cout << u << " ";
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {
    // Simple graph: 0–1, 0–2, 1–3
    std::vector<std::vector<int>> adj = {
        {1,2}, {0,3}, {0}, {1}
    };
    breadthFirst(adj, 0);  // prints: 0 1 2 3
}
```

### 3.3 `std::priority_queue<T>` (Max‑heap by default)  
```cpp
#include <iostream>
#include <queue>
#include <vector>

int main() {
    std::priority_queue<int> pq;
    pq.push(5);
    pq.push(1);
    pq.push(7);

    // Pops largest first: 7, 5, 1
    while (!pq.empty()) {
        std::cout << pq.top() << " ";
        pq.pop();
    }
    std::cout << "\n";
}
```

---

## 4. Utility Classes  

### 4.1 `std::pair<A,B>`  
A simple two‑element struct.  
```cpp
#include <iostream>
#include <utility>

std::pair<int,int> divmod(int a, int b) {
    return {a/b, a%b};
}

int main() {
    auto [quot, rem] = divmod(13, 5);
    std::cout << "13 / 5 = " << quot 
              << ", remainder = " << rem << "\n";
}
```

### 4.2 `std::tuple<Ts…>`  
Heterogeneous fixed‑length collection.  
```cpp
#include <iostream>
#include <tuple>
#include <string>

std::tuple<std::string,int,double> getPerson() {
    return {"Alice", 30, 65.5};
}

int main() {
    auto [name, age, weight] = getPerson();
    std::cout << name << " is " << age 
              << " years old, " << weight << "kg\n";
}
```

### 4.3 `std::bitset<N>`  
Compile-time fixed-size sequence of bits.  
```cpp
#include <iostream>
#include <bitset>

int main() {
    std::bitset<8> flags;
    flags.set(1);    // turn on bit 1
    flags[3] = 1;    // turn on bit 3

    std::cout << "Flags: " << flags << "\n";       // 00001010
    std::cout << "Any set? " << flags.any() << "\n"; // true
}
```

---



# Side Notes

# How to use std properly

In C++ the `std` namespace holds all the standard‑library names (like `string`, `cout`, `vector`, etc.). You have two main ways to make those names available:

---

## 1. Fully‑qualified names (what you’ve seen here)

You write:
```cpp
std::string name;
std::cout << "Hello\n";
```
**Pros**  
- It’s always crystal‑clear where each symbol comes from.  
- No risk of accidentally clashing with your own functions or third‑party libraries.

**Cons**  
- A bit more typing—especially if you’re doing a lot of I/O.

---

## 2. `using namespace std;`

At the top of your file you write:
```cpp
using namespace std;

int main() {
    string name;        // OK: std::string
    cout << "Hello\n";  // OK: std::cout
}
```
This brings *every* name from `std` into the global namespace, so you don’t need `std::` everywhere.

**Pros**  
- Less typing, maybe cleaner looking in small examples or short snippets.

**Cons**  
- **Name collisions.** If you or another library define a symbol called `map`, `sort`, `string`, etc., the compiler can’t tell which one you mean.  
- **Pollutes** the global namespace, making code harder to read and maintain as projects grow.  
- **Especially dangerous in header files**, because it forces anyone including your header to also have all of `std` in their global namespace.

---

### Best Practice Guidelines

1. **Do _not_** put `using namespace std;` in header files.  
2. In small example programs or easy-to-read teaching code, it’s fine in a single `.cpp` for brevity.  
3. In larger projects, prefer either:  
   ```cpp
   using std::string;
   using std::cout;
   using std::vector;
   ```
   or just keep the `std::` prefix for clarity.

---

In short: people use `using namespace std;` for convenience in small demos, but in real‑world code it’s safer and clearer to stick with `std::…` (or selective `using` declarations) to avoid surprises down the road.



# Differences between head.next and head->next

In C++, the `.` and `->` operators are two ways of accessing members of a class or struct, but you use them in different situations:

1. **The dot (`.`) operator** is for when you have an actual _object_:
   ```cpp
   ListNode node;     // node is an object, not a pointer
   node.val  = 5;
   node.next = nullptr;  // fine: node is a ListNode, so use `.`
   ```

2. **The arrow (`->`) operator** is for when you have a _pointer_ to an object:
   ```cpp
   ListNode* p = &node;  // p is a pointer to a ListNode
   p->val  = 6;          // same as (*p).val  = 6;
   p->next = nullptr;    // same as (*p).next = nullptr;
   ```

---

### Why `head->next` in your code?

```cpp
bool hasCycle(ListNode* head) {
    // head is declared as a pointer: ListNode*
    // so to get the `next` field, you must write head->next
    head = head->next;  
    // head.next would be a compile‑time error, because `head` is not an object
    // (it’s a pointer), so it has no member named `next` to access with `.`
    …
}
```

Under the hood:
```cpp
head->next 
// is exactly equivalent to
(*head).next
```
– you first dereference the pointer (`*head`), yielding a `ListNode` lvalue, and then access its `.next` member.

---

### Quick Cheat‑Sheet

| You have…                 | Use this to access member `foo`  |
|---------------------------|----------------------------------|
| A `ListNode` object       | `object.foo`                     |
| A `ListNode*` pointer     | `pointer->foo`  (i.e. `(*pointer).foo`) |

So in your `hasCycle` function, since `head` is of type `ListNode*`, you must write:
```cpp
head = head->next;
```
and **not**:
```cpp
head = head.next;  // error: `head` is not an object, it’s a pointer
```

---
# lvalue and rvalue, std::move()

### 1. `std::move(n)`  
- **What it is**: `std::move` is not a “real” move—it’s a cast that turns its argument into an _rvalue reference_ (`T&&`).  
- **What happens**: In your ctor  
  ```cpp
  Person(std::string n, int a)
    : name(std::move(n)), age(a) {}
  ```  
  you’ve taken the local `n` (an lvalue) and told the compiler “treat `n` as an rvalue(T&&) and something I won’t use again,” so `std::string`’s _move‑constructor_ can steal `n`’s internal buffer into `name`.  
- **After the move**: `n` is left in a valid but unspecified (often empty) state.  

```cpp
std::string s = "hello";
std::string t = std::move(s);
// now t=="hello", and s==""  (or some valid but empty state)
```

---

### 2. lvalue vs. rvalue  
- **lvalue** (“locator value”): anything that has a stable address in memory and can appear on the **left** of `=`.  
  ```cpp
  int x = 5;    // x is an lvalue
  x = 10;       // OK
  ```  
- **rvalue**: a temporary or “pure” value that you can’t assign into.  
  ```cpp
  int y = x + 3;   // (x+3) is an rvalue
  (x+3) = 7;       // error: you can’t assign to an rvalue
  ```  
- **Why it matters**: move ctors and overloads distinguish `T&` (binds only to lvalues) from `T&&` (binds only to rvalues) so you can write efficient “steal” semantics.

---

### 3. `std::ostream` & `operator<<`  
- **`std::ostream`**: the base type for all output streams (e.g. `std::cout`).  
- **`operator<<`**: the insertion operator—overloaded so you can write things like  
  ```cpp
  std::cout << "Hello " << 123 << "\n";
  ```  
- **Why friend?**  
  ```cpp
  friend std::ostream& operator<<(std::ostream &out, const Person &p);
  ```  
  lets your `operator<<` access `Person`’s private members, then return the same `out` so calls can be chained.

---

### 4. Brace vs. Parenthesis Initialization  
- **Braces** (`{…}`) are C++11’s _uniform initialization_, which:  
  - Works for aggregates, single‑argument ctors, and prevents narrowing.  
  - Avoids the “most vexing parse” (ambiguous function declarations).  
- You **could** write  
  ```cpp
  Person alice("Alice", 30);
  ```  
  exactly the same—brace‑init is just the newer, more consistent idiom:

```cpp
Person alice{"Alice", 30};
```

---

**In summary**:  
- `std::move` casts to rvalue so you can “steal” resources.  
- lvalues have identity/addressable; rvalues are temps.  
- `std::ostream` + `operator<<` let you print your types.  
- Brace‑init is the modern, unambiguous way to call ctors (though parens still work).



# When to use this in class

Here are several real‑world situations in C++ where you **must** explicitly use `this->` (or at least `this`) to get correct code:

---

### 1. Disambiguating a member from a parameter or local variable  
When a member and a local name collide, you need `this->` to say “the one on the object,” not the local:

```cpp
struct Foo {
    int value;
    void setValue(int value) {
        // Without this->, “value = value;” just assigns the parameter to itself
        this->value = value;  
    }
};
```

---

### 2. Referring to dependent base‑class members in a template  
Inside a class template that inherits from another template, unqualified names aren’t looked up in the base without `this->` (or a `using`):

```cpp
template<typename T>
struct Base {
    void greet() { /*…*/ }
};

template<typename T>
struct Derived : Base<T> {
    void hello() {
        // error: greet is dependent, compiler won’t find it
        // greet();        

        // OK: tells the compiler “look for greet in this object’s bases”
        this->greet();  
    }
};
```

---

### 3. Capturing the current object in a lambda  
If you want a lambda inside a member function to refer back to `this`, you must capture it explicitly:

```cpp
struct Button {
    void onClick() {
        // [this] makes 'this' available inside the lambda
        auto cb = [this]() {
            this->doAction();   // or just doAction(), but you needed the capture
        };
        registerCallback(cb);
    }
    void doAction();
};
```

---

### 4. Pointer‑to‑member operations  
When you have a pointer‑to‑member (e.g. `int Foo::*pm`), you use `this->*pm` to apply it:

```cpp
struct Foo {
    int x, y;
    void print(int Foo::*pm) {
        std::cout << this->*pm << "\n";  
    }
};
```

---

### 5. Method chaining by returning `*this` or `this`  
If you return the object itself to chain calls, you explicitly return `*this` (or `this` for pointers):

```cpp
struct Builder {
    Builder& setA(int a)   { this->a = a;   return *this; }
    Builder& setB(int b)   { this->b = b;   return *this; }
    Foo     build() const  { return Foo(a,b); }
private:
    int a, b;
};
```

---

### 6. Overloaded operators where both parameters are implicit  
Inside a member `operator+=`, you might still refer to `*this`:

```cpp
struct Vec {
    int x,y;
    Vec& operator+=(const Vec& o) {
        this->x += o.x;
        this->y += o.y;
        return *this;
    }
};
```

---

### 7. Returning the raw pointer to the current object  
Sometimes APIs expect you to hand out `this` directly:

```cpp
struct Node {
    Node* getPtr() { return this; }
};
```

---

> **Key takeaway:**  
> - **`this->member`** is required when the compiler can’t unambiguously find a member (shadowing or dependent base).  
> - **Capturing `this`** in lambdas requires `[this]`.  
> - Everywhere else `this->` is optional—`foo()` and `this->foo()` are equivalent if `foo` is unambiguous.




# Structured Binding
Sure! Structured bindings are super useful in C++17 and above. They make your code cleaner by unpacking pairs, tuples, arrays, or even structs directly into named variables. Here's a list of common and practical **use cases**:

---

### ✅ 1. **Unpacking `std::pair` (e.g., `std::map` iteration)**

```cpp
std::map<std::string, int> scores = {{"Alice", 90}, {"Bob", 85}};

for (auto [name, score] : scores) {
    std::cout << name << " scored " << score << "\n";
}
```

🔹 Before C++17: you'd have to use `.first` and `.second`.

---

### ✅ 2. **Unpacking return values from `std::pair` or `std::tuple`**

```cpp
std::tuple<int, int, int> getRGB() {
    return {255, 128, 64};
}

auto [r, g, b] = getRGB();
std::cout << "Red: " << r << ", Green: " << g << ", Blue: " << b << "\n";
```

---

### ✅ 3. **Decomposing `std::array`**

```cpp
std::array<int, 3> coords = {10, 20, 30};

auto [x, y, z] = coords;
std::cout << "X=" << x << ", Y=" << y << ", Z=" << z << "\n";
```

---

### ✅ 4. **Custom Struct Decomposition**

If your struct has public members and is aggregate-initializable:

```cpp
struct Point {
    int x;
    int y;
};

Point p{4, 7};
auto [a, b] = p;
std::cout << "x = " << a << ", y = " << b << "\n";
```

---

### ✅ 5. **Simplifying `if` with `std::map::find`**

```cpp
std::map<int, std::string> m = {{1, "one"}, {2, "two"}};

if (auto [it, found] = m.find(2); it != m.end()) {
    std::cout << "Found: " << it->second << "\n";
}
```

This avoids declaring the iterator beforehand — it's scoped just to the `if`.

---

### ✅ 6. **Efficient destructuring in algorithms**

```cpp
std::vector<std::pair<std::string, int>> items = {{"apple", 3}, {"banana", 5}};

std::for_each(items.begin(), items.end(), [](const auto& [name, count]) {
    std::cout << name << ": " << count << "\n";
});
```

---

# Binary Search
In C++’s `<algorithm>` (and in C++20’s `<ranges>`), the “binary-search family” that works on **sorted ranges** consists of four main routines:

```cpp
std::binary_search(begin, end, value);        // returns bool
std::lower_bound(begin, end, value);          // first ≥ value
std::upper_bound(begin, end, value);          // first >  value
std::equal_range(begin, end, value);          // pair {lower_bound, upper_bound}
```

and two more helpers in C++20:

```cpp
std::partition_point(begin, end, pred);       // first for which pred(elem)==false
std::ranges::* versions with projections, comparators, etc.
```

Below is a quick cheat-sheet for each, with signatures, semantics, and tiny examples.

---

## 1. `binary_search`

```cpp
bool binary_search( ForwardIt first, ForwardIt last,
                    const T& value,
                    Compare comp = Compare{} );
```

- **What it does**: tells you if `value` **exists** in the sorted range `[first,last)`.  
- **Note**: internally does a lower_bound + check.  
- **Example**:
  ```cpp
  vector<int> v = {1,3,5,7,9};
  bool has5 = binary_search(v.begin(), v.end(), 5);  // true
  bool has2 = binary_search(v.begin(), v.end(), 2);  // false
  ```

---

## 2. `lower_bound`

```cpp
ForwardIt lower_bound( ForwardIt first, ForwardIt last,
                       const T& value,
                       Compare comp = Compare{} );
```

- **Returns** the **first iterator** `it` in `[first,last)` such that  
  `!comp(*it, value)` → i.e. `*it >= value`.  
- If all elements are `< value`, returns `last`.  
- **Use** when you need the insertion point for `value` without discarding equal elements.  
- **Example**:
  ```cpp
  vector<int> v = {2,4,4,4,6,8};
  auto it = lower_bound(v.begin(), v.end(), 4);
  // it points to the first 4 (index 1)
  int idx = it - v.begin();  // 1
  ```

---

## 3. `upper_bound`

```cpp
ForwardIt upper_bound( ForwardIt first, ForwardIt last,
                       const T& value,
                       Compare comp = Compare{} );
```

- **Returns** the **first iterator** `it` in `[first,last)` such that  
  `comp(value, *it)` → i.e. `*it > value`.  
- If no element is `> value`, returns `last`.  
- **Use** when you want the end of the “equal range”—i.e. the insert position **after** any existing `value`s.  
- **Example**:
  ```cpp
  vector<int> v = {2,4,4,4,6,8};
  auto it = upper_bound(v.begin(), v.end(), 4);
  // it points to the element 6 (index 4)
  int idx = it - v.begin();  // 4
  ```

---

## 4. `equal_range`

```cpp
pair<ForwardIt,ForwardIt>
equal_range( ForwardIt first, ForwardIt last,
             const T& value,
             Compare comp = Compare{} );
```

- **Returns** `{ lower_bound(...), upper_bound(...) }`.  
- Represents the **sub‐range** of elements equal to `value`.  
- **Example**:
  ```cpp
  vector<int> v = {2,4,4,4,6,8};
  auto [lo, hi] = equal_range(v.begin(), v.end(), 4);
  // lo points at index 1, hi at index 4
  int count = hi - lo;  // 3 copies of 4
  ```

---

## 5. `partition_point` (C++11)

```cpp
ForwardIt partition_point( ForwardIt first, ForwardIt last,
                           UnaryPredicate p );
```

- **Precondition**: The range `[first,last)` is partitioned by `p`—i.e. all `x` with `p(x)==true` come **before** all with `p(x)==false`.  
- **Returns** the first `it` where `p(*it)` is `false`.  
- **Use** this to find the boundary of a sorted/partitioned range under an arbitrary predicate (not necessarily comparing to a single `value`).  
- **Example**:
  ```cpp
  vector<int> v = {1,2,3,4,5,6,7,8};
  // Split at 5: everything <5 is true, >=5 is false
  auto it = partition_point(v.begin(), v.end(),
                            [](int x){ return x < 5; });
  // it points to the first element >= 5 (i.e. 5)
  ```

---

## 6. C++20 `<ranges>` overloads

In C++20 you get **ranges** versions that accept:

- Views (`std::views::filter`, `std::views::transform`, etc.)  
- **Projections** and **custom comparators** more cleanly:  
  ```cpp
  using std::ranges::lower_bound;
  // example: sort people by age, then search by person.age
  struct Person { string name; int age; };
  vector<Person> team = {...};
  ranges::sort(team, {}, &Person::age);
  Person target{"",30};
  auto it = lower_bound(team, target, {},
                        &Person::age);
  ```

---

### When to use each

| Need                                           | Algorithm             |
|------------------------------------------------|-----------------------|
| Test if `value` exists in sorted range         | `binary_search`       |
| First position to insert **before** any ≥ val  | `lower_bound`         |
| First position to insert **after** all == val  | `upper_bound`         |
| Get both lower+upper in one call               | `equal_range`         |
| Split a partitioned range on predicate         | `partition_point`     |

All of these run in **O(log N)** on random-access iterators (and **O(N)** if only forward iterators), so they’re very efficient on large sorted arrays or vectors.


---

# Heap in <algorithm> library
Here are some concrete examples of using the `<algorithm>` heap APIs—`make_heap`, `push_heap`, `pop_heap`, and `sort_heap`—with different comparators:



## 1. Default “max-heap” (uses `less<>`)

By default, `make_heap` and its friends use `std::less` (i.e. `operator<`) so that the **largest** element is at `front()`:

```cpp
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {5, 1, 7, 3, 9, 2};
    
    // Build a max-heap in v
    make_heap(v.begin(), v.end());  
    // Now v.front() == 9
    cout << "Top of max-heap: " << v.front() << "\n";

    // Pop the top
    pop_heap(v.begin(), v.end());   // swaps 9 to the back, re-heapifies [begin,end-1)
    cout << "Popped value: " << v.back() << "\n";  // prints 9
    v.pop_back();                   // actually remove it

    // Push a new value
    v.push_back(8);
    push_heap(v.begin(), v.end());  // re-heapifies to include 8
    cout << "New top: " << v.front() << "\n";       // now 8

    // Sort the heap (destroys the heap property, yields ascending sort)
    sort_heap(v.begin(), v.end());
    cout << "Sorted: ";
    for (int x : v) cout << x << " ";  // 1 2 3 5 7 8
    cout << "\n";
}
```

---

## 2. Min-heap via `greater<>`

If you want the **smallest** element at `front()`, pass `greater<>` everywhere:

```cpp
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

int main() {
    vector<int> v = {5, 1, 7, 3, 9, 2};

    // Build a min-heap
    make_heap(v.begin(), v.end(), greater<>());  
    // Now v.front() == 1
    cout << "Top of min-heap: " << v.front() << "\n";

    // Pop the top
    pop_heap(v.begin(), v.end(), greater<>());  
    cout << "Popped value: " << v.back() << "\n";  // prints 1
    v.pop_back();

    // Push new
    v.push_back(0);
    push_heap(v.begin(), v.end(), greater<>());  
    cout << "New top: " << v.front() << "\n";     // now 0

    sort_heap(v.begin(), v.end(), greater<>());   // sorts descending
    cout << "Sorted descending: ";
    for (int x : v) cout << x << " ";  // 9 7 5 3 2 0
    cout << "\n";
}
```

---

## 3. Heap of `pair<int,string>`, lexicographic by frequency then word

Say you want a “max-heap” of `(frequency, word)` so that highest frequency comes first, and for ties lexicographically smaller word comes first. You can use a custom comparator:

```cpp
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// Compare so that:
//   higher freq → comes first
//   if freq equal, lexicographically smaller word → comes first
bool myComp(const pair<int,string>& a,
            const pair<int,string>& b) {
    if (a.first != b.first)
        return a.first < b.first;            // max-heap on freq
    return a.second > b.second;              // min-heap on word
}

int main() {
    vector<pair<int,string>> v = {
        {3,"apple"}, {5,"orange"}, {5,"banana"}, {2,"pear"}
    };

    // Build our custom max-heap
    make_heap(v.begin(), v.end(), myComp);
    // Top is (5,"banana")? or (5,"apple")? We want (5,"banana")? Let's see:
    // Since for equal freq=5, we do a.second > b.second → "banana" > "orange"? yes
    // So the larger string is treated as “smaller” in our heap-comparison → ends up at front
    cout << "Top: (" 
         << v.front().first << "," 
         << v.front().second << ")\n";  

    // Pop it
    pop_heap(v.begin(), v.end(), myComp);
    auto best = v.back();
    cout << "Popped: (" << best.first << "," << best.second << ")\n";
}
```

---

## 4. Partial heapify / subrange

You can heapify only part of a vector.  For example, say you want the 10 largest items out of a big vector `data`:

```cpp
vector<int> data = /* ... lots of data ... */;

// Create a max-heap of the first 10 items
make_heap(data.begin(), data.begin()+10);

// For each remaining element, if it’s larger than heap‐top, replace & re‐heapify
for (auto it = data.begin()+10; it != data.end(); ++it) {
    if (*it > data.front()) {
        pop_heap(data.begin(), data.begin()+10);  // move old smallest of top-10 to position 9
        data[9] = *it;                            // overwrite it
        push_heap(data.begin(), data.begin()+10);// re‐heapify top-10
    }
}
// Now data[0..9] contains the 10 largest elements, unordered
sort_heap(data.begin(), data.begin()+10);       // sort them if you want
```

---

### Recap of function signatures

```cpp
make_heap(    RandomIt first, RandomIt last,
              Compare comp = Compare() );

push_heap(    RandomIt first, RandomIt last,
              Compare comp = Compare() );

pop_heap(     RandomIt first, RandomIt last,
              Compare comp = Compare() );

sort_heap(    RandomIt first, RandomIt last,
              Compare comp = Compare() );
```

- `make_heap` builds a heap in-place.  
- `push_heap` assumes `[first,last-1)` is a heap, and “pushes” the new element at `last-1` into the heap.  
- `pop_heap` moves the heap‐top to `last-1`, and re‐heapifies `[first,last-1)`.  
- `sort_heap` repeatedly does `pop_heap`, yielding a sorted range.

By choosing `std::less<>` (the default) you get a **max-heap**, and by using `std::greater<>` (or your own comparator) you can invert or customize the ordering.

---

# Initilize containers with predefined capacities or initial elements

**Explaining vectors, arrays, and containers**

The user wants a full breakdown of containers with predefined capacities or initial values. I’ll cover std::vector, std::array, C arrays, std::deque, std::list, etc., and detail how to declare them with specific sizes and values.

For vectors, scenarios like `vector<int> v(size)` for default values, `v.reserve(N)` for capacity, and initializers like `vector{1,2,3}` using `initializer_list` are important to mention.

Next, I'll explain how std::array and C arrays work with initialization and list other relevant containers like deques and strings.


Thought for 5 seconds


Below is a survey of the most common ways to create fixed‐size or pre‐allocated containers in C++, with code examples and notes on when to use each.  We’ll cover:

1. C‑style arrays
2. `std::array`
3. `std::vector`
4. Other sequence containers (`deque`, `list`, `forward_list`)
5. `std::string`
6. Raw dynamic arrays & smart pointers

---

## 1. C‑style arrays

* **Compile‑time fixed size**

  ```cpp
  int a[5];             // size = 5, elements uninitialized (if local)
  int b[5] = {0};       // size = 5, all elements zeroed
  int c[5] = {1,2,3};   // c = {1,2,3,0,0}
  ```
* **Pros:** simple, no dynamic allocation.
* **Cons:** size must be a compile‑time constant; no bounds checking; decays to pointer.

---

## 2. `std::array<T,N>` (fixed‐size wrapper)

* **Compile‑time size, behaves like a first‑class container**

  ```cpp
  #include <array>

  std::array<int,5> a;                      // elements default initialized (0 for int)
  std::array<int,5> b = {1,2,3,4,5};        // list‐init
  std::array<int,5> c;                      
  c.fill(42);                               // set all 5 elements to 42
  ```
* **Pros:** size known at compile time, supports iterators, copyable, no heap.

---

## 3. `std::vector<T>` (dynamic array)

### a) Size + default values

```cpp
#include <vector>
// size = 10, all elements == T() (0 for ints)
std::vector<int> v1(10);    
```

### b) Size + fill value

```cpp
// size = 10, all elements == 7
std::vector<int> v2(10, 7);
```

### c) Initializer‑list

```cpp
std::vector<int> v3 = {1,2,3,4};
```

### d) Reserve capacity (without constructing elements)

```cpp
std::vector<int> v4;
v4.reserve(100);   // capacity ≥100, but size == 0
// push_back/emplace_back will not reallocate until size > 100
```

### e) Resize an existing vector

```cpp
v4.resize(5);      // now size == 5, elements default‑constructed
v4.resize(8, 42);  // size == 8, new elements == 42
```

### f) Assign from another range or fill

```cpp
std::vector<int> v5;
v5.assign(3, 9);   // size = 3, all elements == 9

std::vector<int> src{1,2,3};
v5.assign(src.begin()+1, src.end()); // v5 = {2,3}
```

---

## 4. Other sequence containers

Most STL containers that hold elements can be pre‑filled via a “fill constructor” or `.assign()`:

| Container              | Fill constructor               | Notes              |
| ---------------------- | ------------------------------ | ------------------ |
| `std::deque<T>`        | `deque( N, val )`              | double‑ended queue |
| `std::list<T>`         | `list( N, val )`               | doubly linked list |
| `std::forward_list<T>` | default ctor + `assign(N,val)` | singly linked list |

Example:

```cpp
std::deque<double> dq(4, 3.14);    // {3.14,3.14,3.14,3.14}
std::list<char> lst(3, 'x');       // {'x','x','x'}
std::forward_list<int> fl;
fl.assign(5, 1);                   // {1,1,1,1,1}
```

---

## 5. `std::string`

Strings are just dynamic arrays of `char`:

```cpp
#include <string>

// size N, filled with character c
std::string s1(10, 'a');       // "aaaaaaaaaa"

// reserve capacity
std::string s2;
s2.reserve(20);                // capacity ≥20, size = 0

// initializer list
std::string s3 = "hello";

// resize
s3.resize(8, '!');             // s3 == "hello!!!"
```

---

## 6. Raw dynamic arrays & smart pointers

If you truly need a raw buffer whose size is only known at runtime:

```cpp
// classic new/delete
int* buf = new int[N];         // uninitialized
delete[] buf;

// smart pointer for RAII
#include <memory>
std::unique_ptr<double[]> buf2(new double[N]); 
// automatically delete[] when buf2 goes out of scope
```

---

### Size vs. Capacity

* **Size** (`.size()`): how many elements are constructed (and logically in the container).
* **Capacity** (`.capacity()`): how many elements can fit before a reallocation occurs (only for vector/string/deque).
* **`reserve(n)`** sets capacity, doesn’t change size.
* **`resize(n)`** changes size (constructs or destroys elements), and may change capacity.

---

### When to use each strategy

* **Fixed, small size known at compile time** → C‑array or `std::array`.
* **Dynamic size but want contiguous memory** → `std::vector`.

  * If you know final size up front, use the size‐constructor (`vector<T> v(n);`) or `reserve(n)`.
  * If you need a uniform initial value, use the two‑arg constructor (`vector<T> v(n, val);`) or `.assign()`.
* **Need O(1) push/pop front** → `std::deque`.
* **Need O(1) insertion anywhere** → `std::list`/`forward_list`.
* **String data** → `std::string` with the same patterns.
* **Low‑level buffer** → `new T[n]` wrapped in a smart pointer, or `std::vector<T>` if you can accept a constructed default.

By choosing the right constructor or member function—`reserve`, `resize`, `assign`, or fill constructors—you can control **both** the logical contents **and** the memory footprint of your container before you start using it.
