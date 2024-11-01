#ifndef SMART_PTRS_SHARED_PTR_H
#define SMART_PTRS_SHARED_PTR_H

template <typename T>
class Shared_ptr { //Класс умного указателя, который удаляет память при выходе из области видимости всех указателей (аналог std::shared_ptr)
private:
    T* ptr; //Указатель на объект (сырой указатель)
    unsigned* ref_count; //Указатель на счётчик ссылок (количество указателей на объект), unsigned - беззнаковое целое

public:
    explicit Shared_ptr(T* p = nullptr) : ptr(p), ref_count(new unsigned(1)) {} //Конструктор с параметрами (переданный указатель и счётчик ссылок, по умолчанию nullptr и 1 - один указатель)

    Shared_ptr(const Shared_ptr& other) : ptr(other.ptr), ref_count(other.ref_count) { //Конструктор копирования (копирует указатель и счётчик ссылок, увеличивает счётчик ссылок)
        ++(*ref_count);
    }

    Shared_ptr(Shared_ptr&& other) noexcept : ptr(other.ptr), ref_count(other.ref_count) { //Конструктор перемещения (перемещает указатель и счётчик ссылок, обнуляет указатель и счётчик ссылок в переданном объекте, счётчик ссылок не увеличивается)
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }

    Shared_ptr& operator=(const Shared_ptr& other) { //Оператор копирования (как конструктор копирования, но для уже существующего объекта)
        if (this != &other) { //Проверка на самоприсваивание
            if (ref_count && --(*ref_count) == 0) { //Если счётчик ссылок равен 0, удаляем указатель и счётчик ссылок
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count); //Увеличиваем счётчик ссылок
        }
        return *this;
    }

    Shared_ptr& operator=(Shared_ptr&& other) noexcept { //Оператор перемещения (как конструктор перемещения, но для уже существующего объекта)
        if (this != &other) {
            if (ref_count && --(*ref_count) == 0) { //Если счётчик ссылок равен 0, удаляем указатель и счётчик ссылок
                delete ptr;
                delete ref_count;
            }
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }
        return *this;
    }

    ~Shared_ptr() { //Деструктор
        if (ref_count && --(*ref_count) == 0) { //Только если счётчик ссылок равен 0, удаляем указатель и счётчик ссылок
            delete ptr;
            delete ref_count;
        }
    }

    const T& operator*() const { //Оператор разыменования (получение значения по указателю)
        return *ptr;
    }
    const T* operator->() const { //Оператор доступа к члену класса (получение указателя)
        return ptr;
    }
    const T* get() const { //Метод получения сырого указателя из умного
        return ptr;
    }
    unsigned use_count() const { //Метод получения количества указателей на объект
        return *ref_count;
    }
    void reset(T* p = nullptr) { //Метод, который заменяет текущий указатель на новый (или nullptr при отсутствии нового указателя) и меняет счётчик ссылок
        if (ref_count && --(*ref_count) == 0) { //Если счётчик ссылок равен 0, удаляем указатель и счётчик ссылок
            delete ptr;
            delete ref_count;
        }
        ptr = p; //Заменяем указатель
        ref_count = new unsigned(1); //Создаём новый счётчик ссылок
    }

    T* release() { //Метод, который возвращает сырой указатель и обнуляет указатель и счётчик ссылок
        T* old_ptr = ptr;
        ptr = nullptr;
        if (ref_count && --(*ref_count) == 0) { //Если счётчик ссылок равен 0, удаляем счётчик ссылок
            delete ref_count;
        }
        ref_count = nullptr; //Обнуляем счётчик ссылок
        return old_ptr; //Возвращаем старый указатель\divideontimes\ltimes\amalg
    }
};

#endif // SMART_PTRS_SHARED_PTR_H