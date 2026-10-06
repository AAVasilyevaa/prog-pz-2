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
    bool set(size_t index, int value) noexcept;
    bool get(size_t index, int& value) const noexcept;
    bool pushBack(int value);
    bool add(const DynamicArray& other) noexcept;
    bool sub(const DynamicArray& other) noexcept;
    void print(ostream& output) const;

private:
    int* data_;
    size_t size_;

    static bool validValue(int value) noexcept;
    bool combine(const DynamicArray& other, int sign) noexcept;
};

#endif
