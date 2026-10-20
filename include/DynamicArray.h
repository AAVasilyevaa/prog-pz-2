#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>
#include <iosfwd>

using namespace std;

class DynamicArray {
public:
    explicit DynamicArray(size_t size);
    DynamicArray(const DynamicArray& other);
    DynamicArray& operator=(const DynamicArray& other) = delete;
    ~DynamicArray();

    size_t size() const noexcept;
    void set(size_t index, int value);
    int get(size_t index) const;
    void pushBack(int value);
    void add(const DynamicArray& other);
    void sub(const DynamicArray& other);
    void print(ostream& output) const;

private:
    int* data_;
    size_t size_;

    static bool validValue(int value) noexcept;
    void combine(const DynamicArray& other, int sign);
};

#endif
