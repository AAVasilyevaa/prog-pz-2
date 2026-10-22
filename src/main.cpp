#include "../include/DynamicArray.h"

#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <typeinfo>

int main() {
    DynamicArray<int> a(3);
    a.set(0, 10);
    a.set(1, 20);
    a.set(2, 30);

    cout << "a = ";
    a.print(cout);
    cout << '\n';
    cout << "a[1] = " << a.get(1) << '\n';

    DynamicArray<int> copy(a);
    copy.set(0, 50);
    copy.pushBack(40);
    cout << "a after copying = ";
    a.print(cout);
    cout << "\ncopy after changing and adding an element = ";
    copy.print(cout);
    cout << '\n';

    DynamicArray<int> b(2);
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
        DynamicArray<int> impossible(numeric_limits<size_t>::max());
    } catch (const bad_alloc& error) {
        cout << "Caught bad_alloc: " << error.what() << '\n';
    }

    DynamicArray<int> c(3);
    c.set(0, 13);
    c.set(1, 24);
    c.set(2, 30);
    cout << "a = " << a << '\n';
    cout << "c = " << c << '\n';
    cout << "distance(a, c) = " << a.distance(c) << '\n';

    try {
        a.distance(b);
    } catch (const invalid_argument& error) {
        cout << "Caught invalid_argument for different sizes: " << error.what() << '\n';
    }

    DynamicArray<double> decimals(2);
    decimals.set(0, 125.5);
    decimals.set(1, -2.5);
    cout << "decimals = " << decimals << '\n';

    DynamicArray<string> words(2);
    words.set(0, "hello");
    words.set(1, "cpp");
    cout << "words = " << words << '\n';

    try {
        words.distance(words);
    } catch (const bad_typeid& error) {
        cout << "Caught bad_typeid for non-numeric distance: " << error.what() << '\n';
    }
}
