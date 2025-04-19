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


#