#ifndef SMART_PTRS_UNIQUE_PTR_H
#define SMART_PTRS_UNIQUE_PTR_H

template <typename T>
class Unique_ptr { //Класс умного указателя, который удаляет память при выходе из области видимости (аналог std::unique_ptr)
private:
    T* ptr; //Указатель на объект (сырой указатель)
    bool owns_memory; //Флаг, показывающий, владеет ли указатель памятью
public:
    explicit Unique_ptr(T* ptr, bool owns_memory = true) : ptr(ptr), owns_memory(owns_memory) {} //Конструктор с параметрами (переданный указатель и флаг владения памятью, по умолчанию владеет памятью)

    Unique_ptr(const Unique_ptr& other) = delete; //Запрет копирования
    Unique_ptr& operator=(const Unique_ptr& other) = delete; //Запрет копирования

    //Конструктор перемещения (перемещает указатель и флаг владения памятью, обнуляет указатель и флаг владения памятью в переданном объекте)
    Unique_ptr(Unique_ptr&& other) noexcept : ptr(other.ptr), owns_memory(other.owns_memory) {
        other.ptr = nullptr;
        other.owns_memory = false;
    }

    //Оператор перемещения (как конструктор, но для уже существующего объекта)
    Unique_ptr& operator=(Unique_ptr&& other) noexcept {
        if (this != &other) { //Проверка на самоприсваивание
            if (owns_memory) { //Если владеет памятью, только тогда удаляем сырой указатель
                delete ptr;
            }
            ptr = other.ptr;
            owns_memory = other.owns_memory;
            other.ptr = nullptr;
            other.owns_memory = false;
        }
        return *this;
    }

    ~Unique_ptr() { //Деструктор
        if (owns_memory) { //Только если владеет памятью, удаляем сырой указатель
            delete ptr;
        }
    }

    T& operator*() { //Оператор разыменования (получение значения по указателю)
        return *ptr;
    }

    T* operator->() { //Оператор доступа к члену класса (получение указателя)
        return ptr;
    }

    T* get() { //Метод получения сырого указателя из умного
        return ptr;
    }

    //Метод, который текущий указатель заменяет на новый (или nullptr) и меняет флаг владения памятью (опять же по умолчанию владеет памятью)
    void reset(T* new_ptr, bool new_owns_memory = true) {
        if (owns_memory) {
            delete ptr;
        }
        ptr = new_ptr;
        owns_memory = new_owns_memory;
    }

    //Метод, который возвращает сырой указатель и обнуляет указатель и флаг владения памятью
    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        owns_memory = false;
        return temp;
    }
};


#endif //SMART_PTRS_UNIQUE_PTR_H
