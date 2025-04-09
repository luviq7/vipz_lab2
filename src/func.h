#pragma once
#include <string>

// структура для зберігання інформації про книгу
struct Book {
    // структура для зберігання автора та назви книги
    struct AuthorTitle {
        std::string m_strBookAuthor;  // автор книги
        std::string m_strBookTitle;   // назва книги
    } bookAuthorTitle;

    // структура для зберігання року видання, кількості сторінок і ціни книги
    struct YearPagesPrice {
        int m_iBookYear;    // рік видання книги
        int m_iBookPages;   // кількість сторінок
        double m_dBookPrice; // ціна книги
    } bookYearPagesPrice;
};

// структура для елемента списку книжок
struct BookNode {
    Book m_sBook;       // книга
    BookNode* m_pNext; // вказівник на наступний елемент списку
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