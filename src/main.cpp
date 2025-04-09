#include <func.h>
#include <iostream>
#include <limits>

int main() {
    BookNode* head = nullptr;
    BookNode* tail = nullptr;

    getFileNameFromUser(head, tail);  // Зчитуємо назву файлу і перевіряємо його існування

    std::string command;

    while (true) {
        // Виводимо меню
        std::cout << "\nОберіть дію:\n";
        std::cout << "1. Додати нову книгу\n";
        std::cout << "2. Вивести список книг\n";
        std::cout << "3. Змінити місцями книги\n";
        std::cout << "4. Відсортувати книги за автором\n";
        std::cout << "5. Видалити книги з ціною менше 5 грн\n";
        std::cout << "6. Зберегти зміни в файл\n";
        std::cout << "Введіть 'exit' для виходу.\n";

        std::cout << "Ваш вибір: ";
        std::getline(std::cin, command);

        // Перевірка на вихід
        if (command == "exit") {
            std::cout << "Вихід з програми.\n";
            break;
        }

        // Виконання вибраної операції
        switch (std::stoi(command)) {
            case 1:
                addBookToEnd(head, tail);  // Додаємо нову книгу
                break;
            case 2:
                displayBooks(head);  // Виводимо список книг
                break;
            case 3:
                swapBooksFromUser(head);  // Змінюємо книжки місцями
                break;
            case 4:
                bubbleSortBooks(head);  // Сортуємо книги
                break;
            case 5:
                deleteBooksUnder5(head);  // Видаляємо книги з ціною менше 5 грн
                break;
            case 6:
                saveChangesToFile(head);  // Зберігаємо зміни в файл
                break;
            default:
                std::cout << "Невірний вибір. Спробуйте ще раз.\n";
                break;
        }
    }

    return 0;
}