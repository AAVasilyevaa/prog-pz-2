#include "../include/DynamicArray.h"

#include <limits>
#include <new>
#include <ostream>
#include <stdexcept>

DynamicArray::DynamicArray(size_t size)
    : data_(nullptr), size_(size) {
    if (size > numeric_limits<size_t>::max() / sizeof(int)) {
        throw bad_alloc();
    }
    data_ = size == 0 ? nullptr : new int[size]{};
}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(other.size_ == 0 ? nullptr : new int[other.size_]), size_(other.size_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];A
    }
}

DynamicArray::~DynamicArray() {
    delete[] data_;
}

size_t DynamicArray::size() const noexcept {
    return size_;
}

bool DynamicArray::validValue(int value) noexcept {
    return value >= -100 && value <= 100;
}

void DynamicArray::set(size_t index, int value) {
    if (index >= size_) {
        throw out_of_range("Index is out of range");
    }
    if (!validValue(value)) {
        throw invalid_argument("Value must be in range [-100, 100]");
    }
    data_[index] = value;
}

int DynamicArray::get(size_t index) const {
    if (index >= size_) {
        throw out_of_range("Index is out of range");
    }
    return data_[index];
}

void DynamicArray::pushBack(int value) {
    if (!validValue(value)) {
        throw invalid_argument("Value must be in range [-100, 100]");
    }
    if (size_ >= numeric_limits<size_t>::max() / sizeof(int)) {
        throw bad_alloc();
    }

    int* next = new int[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        next[i] = data_[i];
    }
    next[size_] = value;

    delete[] data_;
    data_ = next;
    ++size_;
}

void DynamicArray::combine(const DynamicArray& other, int sign) {
    for (size_t i = 0; i < size_; ++i) {
        const long long right = i < other.size_ ? other.data_[i] : 0;
        const long long result = static_cast<long long>(data_[i]) + sign * right;
        if (result < numeric_limits<int>::min() || result > numeric_limits<int>::max()) {
            throw overflow_error("Arithmetic result is out of int range");
        }
    }

    for (size_t i = 0; i < size_; ++i) {
        const long long right = i < other.size_ ? other.data_[i] : 0;
        data_[i] = static_cast<int>(static_cast<long long>(data_[i]) + sign * right);
    }
}

void DynamicArray::add(const DynamicArray& other) {
    combine(other, 1);
}

void DynamicArray::sub(const DynamicArray& other) {
    combine(other, -1);
}

void DynamicArray::print(ostream& output) const {
    output << '[';
    for (size_t i = 0; i < size_; ++i) {
        if (i != 0) {
            output << ", ";
        }
        output << data_[i];
    }
    output << ']';
}
