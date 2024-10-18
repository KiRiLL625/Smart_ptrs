#include <iostream>
#include "Unique_ptr.h"
#include "Shared_ptr.h"
#include "MemorySpan.h"

//Функция, реализующая меню
bool menu(MemorySpan<int>& span){
    static bool unique_ptr_in_use = false; //Флаг, показывающий, используется ли unique_ptr (static, чтобы сохранить значение между вызовами), чтобы не было segfault
    while(true){
        std::cout << "1. Add element\n";
        std::cout << "2. Remove element\n";
        std::cout << "3. Get unique\n";
        std::cout << "4. Get shared\n";
        std::cout << "5. Exit\n";
        int choice; //Выбор пользователя
        std::cin >> choice;
        switch(choice){
            case 1: //Добавление элемента
                std::cout << "Enter the value to add: ";
                int value;
                std::cin >> value;
                span.add(value); //Добавление элемента
                return true; //Продолжение работы
            case 2: {
                std::cout << "Enter the index to remove: ";
                int index;
                std::cin >> index;
                span.remove(index); //Удаление элемента
                return true;
            }
            case 3: {
                std::cout << "Enter the index to get unique: ";
                int index;
                std::cin >> index; //Ввод индекса элемента из span
                if(unique_ptr_in_use){ //Если unique_ptr уже используется
                    std::cout << "Unique_ptr is already in use\n";
                    return true;
                }
                //Получение unique_ptr (если не используется)
                Unique_ptr<int> ptr = span.get_unique(index);
                std::cout << "Value is: " << *ptr << std::endl;
                unique_ptr_in_use = true; //Установка флага на true, т.к. unique_ptr уже используется
                return true;
            }
            case 4: {
                std::cout << "Enter the index to get shared: ";
                int index;
                std::cin >> index;
                Shared_ptr<int> ptr = span.get_shared(index); //Получение shared_ptr
                std::cout << "Value is: " << *ptr << std::endl; //Вывод значения
                return true;
            }
            case 5: //Выход из программы
                return false;
            default: //Некорректный ввод
                std::cout << "Invalid choice\n" << std::endl;
                return true;
        }
    }
}

int main() {
    int capacity; //Вместимость MemorySpan
    std::cout << "Enter the capacity of the MemorySpan: ";
    std::cin >> capacity;
    MemorySpan<int> span(capacity); //Создание MemorySpan
    while(menu(span)); //Вызов меню с MemorySpan
    return 0;
}
