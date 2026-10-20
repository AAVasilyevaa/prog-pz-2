#include "../include/DynamicArray.h"

#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

int main() {
    DynamicArray a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);

    cout << "a = ";
    a.print(cout);
    cout << '\n';
    cout << "a[1] = " << a.get(1) << '\n';

    DynamicArray copy(a);
    copy.set(0, 50);
    copy.pushBack(40);
    cout << "a after copying = ";
    a.print(cout);
    cout << "\ncopy after changing and adding an element = ";
    copy.print(cout);
    cout << '\n';

    DynamicArray b(2);
    b.set(0, 1);
    b.set(1, 2);
    a.add(b);
    cout << "a after add(b) = ";
    a.print(cout);
    cout << ", size: " << a.size() << '\n';

    a.sub(b);
    cout << "a after sub(b) = ";
    a.print(cout);
    cout << ", size: " << a.size() << '\n';

    try {
        a.get(a.size());
    } catch (const out_of_range& error) {
        cout << "Caught out_of_range: " << error.what() << '\n';
    }

    try {
        a.set(0, 101);
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument: " << error.what() << '\n';
    }

    try {
        DynamicArray impossible(numeric_limits<size_t>::max());
    } catch (const bad_alloc& error) {
        cout << "Caught bad_alloc: " << error.what() << '\n';
    }
}
