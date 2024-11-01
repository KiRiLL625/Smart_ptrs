#ifndef MEMORY_SPAN_H
#define MEMORY_SPAN_H

#include "MsPtr.h"
#include <stdexcept>

template <typename T, size_t Capacity>
class MemorySpan {
private:
    T data[Capacity]; // Массив данных фиксированного размера
    size_t size; // Текущий размер MemorySpan

public:
    MemorySpan() : size(0) {}

    void add(T value) {
        if (size >= Capacity) {
            throw std::out_of_range("MemorySpan capacity exceeded");
        }
        data[size++] = value; // Добавление элемента в массив
    }

    void remove(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1]; // Сдвиг элементов влево
        }
        --size;
    }

    MsPtr<T> get_ptr(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return MsPtr<T>(data, size, index); // возвращаем MsPtr
    }

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return Capacity;
    }
};

#endif // MEMORY_SPAN_H