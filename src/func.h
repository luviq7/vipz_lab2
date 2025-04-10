#pragma once
#include <string>

// Структура для зберігання інформації про книгу.
// Включає автора та назву книги, а також рік видання, кількість сторінок і ціну.
// Приклад створення об'єкта та використання:
//
// Book myBook;
// myBook.bookAuthorTitle.m_strBookAuthor = "Автор книги";
// myBook.bookAuthorTitle.m_strBookTitle = "Назва книги";
// myBook.bookYearPagesPrice.m_iBookYear = 2025;
// myBook.bookYearPagesPrice.m_iBookPages = 200;
// myBook.bookYearPagesPrice.m_dBookPrice = 250.0;
//
// В результаті об'єкт myBook міститиме інформацію про книгу.
struct Book {
    // Структура для зберігання автора та назви книги.
    // Містить поля для збереження імені автора та назви книги.
    struct AuthorTitle {
        std::string m_strBookAuthor;  // Автор книги
        std::string m_strBookTitle;   // Назва книги
    } bookAuthorTitle;

    // Структура для зберігання року видання, кількості сторінок і ціни книги.
    // Містить поля для зберігання року видання, кількості сторінок і ціни книги.
    struct YearPagesPrice {
        int m_iBookYear;    // Рік видання книги
        int m_iBookPages;   // Кількість сторінок у книзі
        double m_dBookPrice; // Ціна книги
    } bookYearPagesPrice;
};

// Структура для елемента списку книжок.
// Кожен елемент містить книгу та вказівник на наступний елемент списку.
// Приклад використання:
// BookNode* head = new BookNode;  // Створюємо новий елемент списку
// head->m_sBook.bookAuthorTitle.m_strBookAuthor = "Автор 1";
// head->m_sBook.bookAuthorTitle.m_strBookTitle = "Книга 1";
// head->m_pNext = nullptr;  // Ініціалізуємо наступний елемент як nullptr
struct BookNode {
    Book m_sBook;       // Книга
    BookNode* m_pNext; // Вказівник на наступний елемент списку
};

// функція для зчитування даних з файлу та додавання книг до списку
void loadBooksFromFile(const std::string& filename, BookNode*& head, BookNode*& tail);

// функція для запиту назви файлу у користувача та зчитування книг
void getFileNameFromUser(BookNode*& head, BookNode*& tail);

// функція для додавання нової книги в кінець списку
void addBookToEnd(BookNode*& head, BookNode*& tail);

// функція для виведення списку книг на екран
void displayBooks(BookNode* head);

// функція для виведення повідомлення про помилку при відкритті файлу
void displayFileError();

// функція для зміни місцями двох книжок за їх індексами
void swapBooks(BookNode* head, int index1, int index2);

// функція для запиту у користувача індексів двох книг та їх зміни місцями
void swapBooksFromUser(BookNode* head);

// функція для сортування списку книг за алфавітним порядком авторів
void bubbleSortBooks(BookNode*& head);

// функція для видалення книг з ціною нижче 5 грн
void deleteBooksUnder5(BookNode*& head);

// функція для збереження змін у файлі
void saveChangesToFile(BookNode* head);