#ifndef SMART_PTRS_MSPTR_H
#define SMART_PTRS_MSPTR_H

#include <stdexcept>

template <typename T>
class MsPtr {
private:
    T* ptr;
    size_t size;
    size_t index;

public:
    MsPtr(T* ptr, size_t size, size_t index = 0) : ptr(ptr), size(size), index(index) {}

    // Оператор разыменования
    T& operator*() {
        if (index >= size) {
            throw std::out_of_range("Разыменование за пределами диапазона");
        }
        return ptr[index];
    }

    // Оператор стрелки
    T* operator->() {
        if (index >= size) {
            throw std::out_of_range("Разыменование за пределамии диапазона");
        }
        return &ptr[index];
    }

    // Оператор префиксного инкремента
    MsPtr& operator++() {
        if (index + 1 >= size) {
            throw std::out_of_range("Арифметика указателей вышла за пределы диапазона");
        }
        ++index;
        return *this;
    }

    // Оператор постфиксного инкремента
    MsPtr operator++(int) {
        MsPtr temp = *this;
        ++(*this);
        return temp;
    }

    // Оператор префиксного декремента
    MsPtr& operator--() {
        if (index == 0) {
            throw std::out_of_range("Арифметика указателей вышла за пределы диапазона");
        }
        --index;
        return *this;
    }

    // Оператор постфиксного декремента
    MsPtr operator--(int) {
        MsPtr temp = *this;
        --(*this);
        return temp;
    }

    // Оператор сложения
    MsPtr operator+(size_t n) const {
        if (index + n >= size) {
            throw std::out_of_range("Арифметика указателей вышла за пределы диапазона");
        }
        return MsPtr(ptr, size, index + n);
    }

    // Оператор вычитания
    MsPtr operator-(size_t n) const {
        if (index < n) {
            throw std::out_of_range("Арифметика указателей вышла за пределы диапазона");
        }
        return MsPtr(ptr, size, index - n);
    }

    // Оператор равенства
    bool operator==(const MsPtr& other) const {
        return ptr == other.ptr && index == other.index;
    }

    // Оператор неравенства
    bool operator!=(const MsPtr& other) const {
        return *this != other;
    }
};

#endif // SMART_PTRS_MSPTR_H