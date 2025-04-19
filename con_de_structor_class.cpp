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
    Widget(Widget &&other) noexcept
      : id(other.id), name(std::move(other.name))
    {
        ++count;
        other.id = 0;             // leave 'other' in a valid state
        cout << "[Widget#"<< id <<"] move-constructed. Other reset to #"<< other.id
             <<". Total count="<< count <<"\n";
    }

    // -------------------------
    // 5) Copy assignment
    // -------------------------
    // Called when you write: w2 = w1;
    Widget& operator=(const Widget &other) {
        if (this != &other) {    // protect against self‑assignment
            id   = other.id;
            name = other.name;
        }
        cout << "[Widget#"<< id <<"] copy-assigned from Widget#"<< other.id <<"\n";
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
