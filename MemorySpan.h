#ifndef MEMORY_SPAN_H
#define MEMORY_SPAN_H

#include "Shared_ptr.h"
#include "Unique_ptr.h"
#include <vector>
#include <stdexcept>

template <typename T>
class MemorySpan { //Класс, который хранит указатели на объекты и удаляет их при выходе из области видимости
private:
    std::vector<Shared_ptr<T>> data; //Вектор указателей на объекты
    size_t capacity; //Вместимость MemorySpan
public:
    explicit MemorySpan(size_t capacity) : capacity(capacity) {} //Конструктор с параметрами (вместимость MemorySpan)

    void add(T value) { //Метод добавления элемента
        if (data.size() >= capacity) { //Если вектор указателей на объекты превышает вместимость, бросаем исключение
            throw std::out_of_range("MemorySpan capacity exceeded");
        }
        data.push_back(Shared_ptr<T>(new T(value))); //Добавляем указатель на объект в вектор
    }

    void remove(size_t index) { //Метод удаления элемента
        if (index >= data.size()) { //Если индекс превышает размер вектора, бросаем исключение
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index); //Удаляем указатель на объект из вектора (begin() - итератор/указатель на начало вектора)
    }

    Unique_ptr<T> get_unique(size_t index) { //Метод получения элемента по индексу в виде unique_ptr
        if (index >= data.size()) { //Если индекс превышает размер вектора, бросаем исключение
            throw std::out_of_range("Index out of range");
        }
        return Unique_ptr<T>(data[index].release()); //Возвращаем unique_ptr, который владеет указателем на объект
    }

    Shared_ptr<T> get_shared(size_t index) { //Метод получения элемента по индексу в виде shared_ptr
        if (index >= data.size()) { //Если индекс превышает размер вектора, бросаем исключение
            throw std::out_of_range("Index out of range");
        }
        return data[index]; //Возвращаем shared_ptr
    }
};

#endif // MEMORY_SPAN_H