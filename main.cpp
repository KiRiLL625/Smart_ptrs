#include <iostream>
#include "Unique_ptr.h"
#include "Shared_ptr.h"
#include "MemorySpan.h"

const size_t capacity = 5; // Вместимость MemorySpan

// Функция, реализующая меню
bool menu(MemorySpan<int, capacity>& span) {
    static bool unique_ptr_in_use = false; // Флаг, показывающий, используется ли unique_ptr (static, чтобы сохранить значение между вызовами), чтобы не было segfault
    while (true) {
        std::cout << "1. Add element\n";
        std::cout << "2. Remove element\n";
        std::cout << "3. Get ptr\n";
        std::cout << "4. Exit\n";
        int choice; // Выбор пользователя
        std::cin >> choice;
        switch (choice) {
            case 1: { // Добавление элемента
                std::cout << "Enter the value to add: ";
                int value;
                std::cin >> value;
                span.add(value); // Добавление элемента
                std::cout << "Now span is: ";
                for (size_t i = 0; i < span.get_size(); ++i) {
                    MsPtr<int> ptr = span.get_ptr(i); // Получение указателя на элемент
                    std::cout << *ptr << " "; // Вывод элементов
                }
                std::cout << std::endl;
                return true; // Продолжение работы
            }
            case 2: {
                std::cout << "Enter the index to remove: ";
                int index;
                std::cin >> index;
                span.remove(index); // Удаление элемента
                std::cout << "Now span is: ";
                for (size_t i = 0; i < span.get_size(); ++i) {
                    MsPtr<int> ptr = span.get_ptr(i); // Получение указателя на элемент
                    std::cout << *ptr << " "; // Вывод элементов
                }
                std::cout << std::endl;
                return true;
            }
            case 3: {
                std::cout << "Enter the index to get ptr: ";
                int index;
                std::cin >> index;
                std::cout << *span.get_ptr(index) << std::endl; // Получение указателя
                return true;
            }
            case 4: // Выход из программы
                return false;
            default: // Некорректный ввод
                std::cout << "Invalid choice\n" << std::endl;
                return true;
        }
    }
}

int main() {
    MemorySpan<int, capacity> span; // Создание MemorySpan
    while (menu(span)); // Вызов меню с MemorySpan
    return 0;
}