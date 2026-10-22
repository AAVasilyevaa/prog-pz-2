#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cmath>
#include <cstddef>
#include <limits>
#include <memory>
#include <new>
#include <ostream>
#include <stdexcept>
#include <type_traits>
#include <typeinfo>

using namespace std;

template <typename T>
class DynamicArray {
public:
    explicit DynamicArray(size_t size) : data_(nullptr), size_(size) {
        if (size > numeric_limits<size_t>::max() / sizeof(T)) {
            throw bad_alloc();
        }
        data_ = size == 0 ? nullptr : new T[size]{};
    }

    DynamicArray(const DynamicArray& other) : data_(nullptr), size_(other.size_) {
        unique_ptr<T[]> next(other.size_ == 0 ? nullptr : new T[other.size_]{});
        for (size_t i = 0; i < size_; ++i) {
            next[i] = other.data_[i];
        }
        data_ = next.release();
    }

    DynamicArray& operator=(const DynamicArray& other) = delete;

    ~DynamicArray() {
        delete[] data_;
    }

    size_t size() const noexcept {
        return size_;
    }

    void set(size_t index, const T& value) {
        if (index >= size_) {
            throw out_of_range("Index is out of range");
        }
        validateValue(value);
        data_[index] = value;
    }

    const T& get(size_t index) const {
        if (index >= size_) {
            throw out_of_range("Index is out of range");
        }
        return data_[index];
    }

    void pushBack(const T& value) {
        validateValue(value);
        if (size_ >= numeric_limits<size_t>::max() / sizeof(T)) {
            throw bad_alloc();
        }

        unique_ptr<T[]> next(new T[size_ + 1]{});
        for (size_t i = 0; i < size_; ++i) {
            next[i] = data_[i];
        }
        next[size_] = value;

        delete[] data_;
        data_ = next.release();
        ++size_;
    }

    void add(const DynamicArray& other) {
        combine(other, false);
    }

    void sub(const DynamicArray& other) {
        combine(other, true);
    }

    double distance(const DynamicArray& other) const {
        if (size_ != other.size_) {
            throw invalid_argument("Arrays must have the same size");
        }
        if constexpr (is_arithmetic_v<T>) {
            long double sum = 0;
            for (size_t i = 0; i < size_; ++i) {
                const long double difference = static_cast<long double>(data_[i])
                    - static_cast<long double>(other.data_[i]);
                sum += difference * difference;
            }
            return static_cast<double>(sqrt(sum));
        } else {
            throw bad_typeid();
        }
    }

    void print(ostream& output) const {
        output << *this;
    }

    friend ostream& operator<<(ostream& output, const DynamicArray& array) {
        output << '[';
        for (size_t i = 0; i < array.size_; ++i) {
            if (i != 0) {
                output << ", ";
            }
            output << array.data_[i];
        }
        return output << ']';
    }

private:
    T* data_;
    size_t size_;

    static void validateValue(const T& value) {
        if constexpr (is_integral_v<T>) {
            if constexpr (is_signed_v<T>) {
                if (value < static_cast<T>(-100) || value > static_cast<T>(100)) {
                    throw invalid_argument("Integral values must be in range [-100, 100]");
                }
            } else if (value > static_cast<T>(100)) {
                throw invalid_argument("Integral values must be in range [-100, 100]");
            }
        } else {
            static_cast<void>(value);
        }
    }

    static void checkArithmetic(T left, T right, bool subtract) {
        if constexpr (is_integral_v<T> && !is_same_v<T, bool>) {
            if constexpr (is_unsigned_v<T>) {
                if (subtract ? left < right : left > numeric_limits<T>::max() - right) {
                    throw overflow_error("Arithmetic result is out of range");
                }
            } else if (subtract) {
                if ((right < 0 && left > numeric_limits<T>::max() + right)
                    || (right > 0 && left < numeric_limits<T>::min() + right)) {
                    throw overflow_error("Arithmetic result is out of range");
                }
            } else if ((right > 0 && left > numeric_limits<T>::max() - right)
                || (right < 0 && left < numeric_limits<T>::min() - right)) {
                throw overflow_error("Arithmetic result is out of range");
            }
        } else {
            static_cast<void>(left);
            static_cast<void>(right);
            static_cast<void>(subtract);
        }
    }

    void combine(const DynamicArray& other, bool subtract) {
        if constexpr (is_arithmetic_v<T>) {
            for (size_t i = 0; i < size_; ++i) {
                const T right = i < other.size_ ? other.data_[i] : T{};
                checkArithmetic(data_[i], right, subtract);
            }
            for (size_t i = 0; i < size_; ++i) {
                const T right = i < other.size_ ? other.data_[i] : T{};
                data_[i] = subtract ? data_[i] - right : data_[i] + right;
            }
        } else {
            throw bad_typeid();
        }
    }
};

#endif
