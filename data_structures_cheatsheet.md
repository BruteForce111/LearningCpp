# Summary of Basic Data Structures in C++
> If you need to know in details about each Data Structure, pull up to the right below part

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
- **Arrays**: `int a[10];` —​contiguous fixed‑size collection  
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

### Getting Started  
1. **Play with `std::vector` and `std::string`**—they’re the workhorses of C++.  
2. **Try a `std::map` vs. `std::unordered_map`** to see differences in lookup speed.  
3. **Use `std::list` or `std::forward_list`** when you need constant‑time insertion/deletion in the middle.

As you write more code, you’ll naturally reach for the right container. Each one has trade‑offs in performance (time and memory) and interface—so checking the reference (e.g. cppreference.com) becomes second nature. Good luck on your C++ journey!



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
```cpp
#include <iostream>
#include <vector>
int main() {
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    // random access and iteration
    for(size_t i = 0; i < v.size(); ++i)
        std::cout << v[i] << " ";    // 10 20 30
    std::cout << "\n";
}
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