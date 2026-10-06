#include "../include/DynamicArray.h"

#include <limits>
#include <ostream>

DynamicArray::DynamicArray(size_t size)
    : data_(size == 0 ? nullptr : new int[size]{}), size_(size) {}

DynamicArray::DynamicArray(const DynamicArray& other)
    : data_(other.size_ == 0 ? nullptr : new int[other.size_]), size_(other.size_) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
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

bool DynamicArray::set(size_t index, int value) noexcept {
    if (index >= size_ || !validValue(value)) {
        return false;
    }
    data_[index] = value;
    return true;
}

bool DynamicArray::get(size_t index, int& value) const noexcept {
    if (index >= size_) {
        return false;
    }
    value = data_[index];
    return true;
}

bool DynamicArray::pushBack(int value) {
    if (!validValue(value) || size_ >= numeric_limits<size_t>::max() / sizeof(int)) {
        return false;
    }

    int* next = new int[size_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        next[i] = data_[i];
    }
    next[size_] = value;

    delete[] data_;
    data_ = next;
    ++size_;
    return true;
}

bool DynamicArray::combine(const DynamicArray& other, int sign) noexcept {
    for (size_t i = 0; i < size_; ++i) {
        const long long right = i < other.size_ ? other.data_[i] : 0;
        const long long result = static_cast<long long>(data_[i]) + sign * right;
        if (result < numeric_limits<int>::min() || result > numeric_limits<int>::max()) {
            return false;
        }
    }

    for (size_t i = 0; i < size_; ++i) {
        const long long right = i < other.size_ ? other.data_[i] : 0;
        data_[i] = static_cast<int>(static_cast<long long>(data_[i]) + sign * right);
    }
    return true;
}

bool DynamicArray::add(const DynamicArray& other) noexcept {
    return combine(other, 1);
}

bool DynamicArray::sub(const DynamicArray& other) noexcept {
    return combine(other, -1);
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
