// ArrayList_TEST.cpp
#include "ArrayList.hpp"
#include <iostream>
#include <string>
using namespace std;


static int g_passed = 0;
static int g_failed = 0;

void check(bool cond, const string& msg) {
    if (cond) {
        ++g_passed;
    }
    else {
        ++g_failed;
        cerr << "[FAIL] " << msg << endl;
    }
}

template <typename T>
void printList(const ArrayList<T>& a, const string& label) {
    cout << label << " (size = " << a.getSize()
        << " cap = " << a.getCapacity() << "): ";
    for (int i = 0; i < a.getSize(); ++i) {
        cout << a.getItem(i);
        if (i + 1 < a.getSize()) cout << " ";
    }
    cout << endl;
}


void runIntTests() {
    cout << endl << " Int tests" << endl;
    ArrayList<int> a;

    check(a.isEmpty(), "New list should be empty");
    check(a.getSize() == 0, "New list size should be 0");
    check(a.getCapacity() >= 10, "Default capacity should be >= 10");

    int initialCap = a.getCapacity();
    for (int i = 1; i <= initialCap; ++i) a.pushBack(i);
    check(a.getSize() == initialCap, "Size should equal initial capacity after pushes");
    check(a.getBack() == initialCap, "getBack should return last pushed value");

    a.pushBack(initialCap + 1);
    check(a.getSize() == initialCap + 1, "Size should increase after growth");
    check(a.getCapacity() > initialCap, "Capacity should grow when full");
    check(a.getBack() == initialCap + 1, "getBack after growth");

    a.popBack();
    check(a.getSize() == initialCap, "popBack should decrement size by 1");
    check(a.getBack() == initialCap, "getBack after popBack");

    a.pushFront(999);
    check(a.getFront() == 999, "getFront returns new front");
    check(a.getSize() == initialCap + 1, "pushFront increases size");
    a.popFront();
    check(a.getFront() == 1, "popFront removes front element");
    check(a.getSize() == initialCap, "popFront decreases size");

    check(a.getItem(0) == 1, "getItem(0) should be 1");
    a.setItem(0, 111);
    check(a.getItem(0) == 111, "setItem should update value");

    a.insert(0, 7);
    check(a.getItem(0) == 7, "insert at index 0 places item at front");
    check(a.getItem(1) == 111, "items shift right after insert");
    check(a.getSize() == initialCap + 1, "size increases after insert");

    int mid = a.getSize() / 2;
    a.insert(mid, 555);
    check(a.getItem(mid) == 555, "insert in middle places item correctly");
    check(a.getSize() == initialCap + 2, "size increases after middle insert");

    int oldSize = a.getSize();
    a.insert(a.getSize(), 42);
    check(a.getBack() == 42, "insert at end behaves like pushBack");
    check(a.getSize() == oldSize + 1, "size increases after insert at end");

    int before = a.getItem(mid + 1);
    a.remove(mid);
    check(a.getItem(mid) == before, "remove shifts items left");
    check(a.getSize() == oldSize, "size decreases after remove");

    printList(a, "After int tests");
}


void runStringTests() {
    cout << endl << "=== String tests ===" << endl;
    ArrayList<string> s(2);
    check(s.isEmpty(), "String list initially empty");

    s.pushBack("a");
    s.pushBack("b");
    check(s.getSize() == 2, "Size should be 2 after pushBacks");
    check(s.getBack() == "b", "getBack should be 'b'");

    int cap0 = s.getCapacity();
    s.pushBack("c");
    check(s.getCapacity() > cap0, "Capacity should grow for strings too");
    check(s.getSize() == 3, "Size == 3 after pushing 'c'");

    s.pushFront("z");
    check(s.getFront() == "z", "getFront should be 'z'");
    s.popFront();
    check(s.getFront() == "a", "popFront removes 'z'");

    check(s.getItem(0) == "a", "Index 0 should be 'a'");
    s.setItem(1, "B");
    check(s.getItem(1) == "B", "Index 1 now 'B'");

    s.insert(1, "X"); // a, X, B, c
    check(s.getItem(1) == "X", "Insert string in middle");
    s.remove(2);      // a, X, c
    check(s.getItem(2) == "c", "Remove shifts left for strings");

    printList(s, "After string tests");
}

int main() {
    cout << "Running ArrayList tests..." << endl;
    runIntTests();
    runStringTests();

    cout << "Passed: " << g_passed << " Failed: " << g_failed << endl;
    if (g_failed == 0) {
        cout << "All tests passed" << endl;
        return 0;
    }
    else {
        cout << "Some tests failed" << endl;
        return 1;
    }
}
