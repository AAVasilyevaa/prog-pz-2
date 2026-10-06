#include "../include/DynamicArray.h"

#include <iostream>

int main() {
    DynamicArray a(3);
    if (!a.set(0, 10) || !a.set(1, 20) || !a.set(2, 30)) {
        cerr << "Could not initialize the array\n";
        return 1;
    }

    cout << "a = ";
    a.print(cout);
    cout << '\n';

    int value = 0;
    if (!a.get(1, value)) {
        cerr << "Could not read the array element\n";
        return 1;
    }
    cout << "a[1] = " << value << '\n';

    DynamicArray copy(a);
    if (!copy.set(0, 50) || !copy.pushBack(40)) {
        cerr << "Could not change the copy\n";
        return 1;
    }
    cout << "a after copying = ";
    a.print(cout);
    cout << "\ncopy after changing and adding an element = ";
    copy.print(cout);
    cout << '\n';

    DynamicArray b(2);
    if (!b.set(0, 1) || !b.set(1, 2)) {
        cerr << "Could not initialize the second array\n";
        return 1;
    }
    if (!a.add(b)) {
        cerr << "Could not add the arrays\n";
        return 1;
    }
    cout << "a after add(b) = ";
    a.print(cout);
    cout << ", size: " << a.size() << '\n';

    if (!a.sub(b)) {
        cerr << "Could not subtract the arrays\n";
        return 1;
    }
    cout << "a after sub(b) = ";
    a.print(cout);
    cout << ", size: " << a.size() << '\n';
}
