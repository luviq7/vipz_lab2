#include "func.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>

using namespace std;
//--------------------------------------------------------------------------------

/* Функція завантажує книги з файлу та додає їх в список

   Функція приймає:
   - filename: шлях до файлу, з якого будуть завантажені книги;
   - head та tail: вказівники на голову та кінець списку книг.
   
   Під час виконання функція відкриває файл, читає дані про кожну книгу, 
   створює новий вузол для книги, заповнює його даними та додає до списку.
   Якщо файл не відкривається, виводиться повідомлення про помилку. */

void loadBooksFromFile(const string& strFilename, BookNode*& pHead, BookNode*& pTail) {
    ifstream ifsFile(strFilename);

    if (!ifsFile.is_open()) {
        displayFileError();  // Виведення повідомлення про помилку при відкритті файлу
        return;
    }

    string strAuthor, strTitle, strYear, strPages, strPrice;

    while (ifsFile) {
        BookNode* pNewBookNode = new BookNode;

        // Читання даних з файлу
        getline(ifsFile, strAuthor, '"');
        getline(ifsFile, strAuthor, '"');  

        getline(ifsFile, strTitle, '"');
        getline(ifsFile, strTitle, '"');  

        getline(ifsFile, strYear, '"');
        getline(ifsFile, strYear, '"');  

        getline(ifsFile, strPages, '"');
        getline(ifsFile, strPages, '"');  

        getline(ifsFile, strPrice, '"');
        getline(ifsFile, strPrice, '"');  

        // Перевірка на порожні значення
        if (strAuthor.empty() || strTitle.empty() || strYear.empty() || strPages.empty() || strPrice.empty()) {
            delete pNewBookNode;
            continue;
        }

        // Присвоєння значень
        pNewBookNode->m_sBook.bookAuthorTitle.m_strBookAuthor = strAuthor;
        pNewBookNode->m_sBook.bookAuthorTitle.m_strBookTitle = strTitle;
        pNewBookNode->m_sBook.bookYearPagesPrice.m_iBookYear = stoi(strYear);
        pNewBookNode->m_sBook.bookYearPagesPrice.m_iBookPages = stoi(strPages);
        pNewBookNode->m_sBook.bookYearPagesPrice.m_dBookPrice = stod(strPrice);

        pNewBookNode->m_pNext = nullptr;

        if (!pHead) {
            pHead = pNewBookNode;  // Якщо список порожній, новий елемент стає головою
            pTail = pHead;         // Кінець списку також вказує на цей елемент
        } else {
            pTail->m_pNext = pNewBookNode;  // Додаємо нову книгу в кінець списку
            pTail = pNewBookNode;           // Оновлюємо вказівник на кінець
        }
    }

    ifsFile.close();
    displayBooks(pHead);  // Виведення всіх книг
}

//--------------------------------------------------------------------------------

/* Функція запитує у користувача назву файлу та намагається його відкрити

   Функція приймає:
   - head та tail: вказівники на голову та кінець списку книг.

   Якщо файл відкривається, завантажує книги з цього файлу. Якщо неможливо відкрити файл, 
   виводиться повідомлення про помилку. */

void getFileNameFromUser(BookNode*& pHead, BookNode*& pTail) {
    string strFilename;
    cout << "Введіть назву файлу: ";
    getline(cin, strFilename);

    string strFullPath = "../data/" + strFilename;

    ifstream ifsFile(strFullPath);
    if (ifsFile.is_open()) {
        loadBooksFromFile(strFullPath, pHead, pTail);  // Завантаження книг з файлу
        ifsFile.close();
    } else {
        displayFileError();  // Виведення помилки при неможливості відкрити файл
    }
}

//--------------------------------------------------------------------------------

/* Функція додає нову книгу в кінець списку

   Функція приймає:
   - head та tail: вказівники на голову та кінець списку книг.
   
   Під час виконання користувач вводить всі необхідні дані для нової книги, 
   яка потім додається в кінець списку. */

void addBookToEnd(BookNode*& pHead, BookNode*& pTail) {
    BookNode* pNewBookNode = new BookNode;
    cout << "Додайте нову книгу в кінець списку" << endl;

    cout << "Введіть прізвище автора: ";
    getline(cin, pNewBookNode->m_sBook.bookAuthorTitle.m_strBookAuthor);

    cout << "Введіть назву книги: ";
    getline(cin, pNewBookNode->m_sBook.bookAuthorTitle.m_strBookTitle);

    cout << "Введіть рік видання: ";
    cin >> pNewBookNode->m_sBook.bookYearPagesPrice.m_iBookYear;

    cout << "Введіть кількість сторінок: ";
    cin >> pNewBookNode->m_sBook.bookYearPagesPrice.m_iBookPages;

    cout << "Введіть ціну книги (грн): ";
    cin >> pNewBookNode->m_sBook.bookYearPagesPrice.m_dBookPrice;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // очищення буфера

    pNewBookNode->m_pNext = nullptr;

    if (pHead == nullptr) {
        pHead = pNewBookNode;
        pTail = pNewBookNode;
    } else {
        BookNode* pTemp = pHead;
        while (pTemp->m_pNext != nullptr) {
            pTemp = pTemp->m_pNext;
        }
        pTemp->m_pNext = pNewBookNode;
        pTail = pNewBookNode; // оновлюємо tail 
    }

    cout << "Книга успішно додана!\n";
}

//--------------------------------------------------------------------------------

/* Функція відображає всі книги в списку

   Функція приймає:
   - head: вказівник на голову списку книг.
   
   Під час виконання функція виводить інформацію про всі книги в списку. 
   Якщо список порожній, виводиться відповідне повідомлення. */

void displayBooks(BookNode* pHead) {
    if (!pHead) {
        cout << "Немає книг для відображення.\n";
        return;
    }

    BookNode* pCurrent = pHead;
    int iIndex = 0;  // Змінна для індексації книг
    while (pCurrent) {
        cout << "Індекс: " << iIndex + 1 << "\n";
        cout << "Автор: " << pCurrent->m_sBook.bookAuthorTitle.m_strBookAuthor << "\n";
        cout << "Назва книги: " << pCurrent->m_sBook.bookAuthorTitle.m_strBookTitle << "\n";
        cout << "Рік: " << pCurrent->m_sBook.bookYearPagesPrice.m_iBookYear << "\n";
        cout << "Сторінки: " << pCurrent->m_sBook.bookYearPagesPrice.m_iBookPages << "\n";
        cout << "Ціна: " << pCurrent->m_sBook.bookYearPagesPrice.m_dBookPrice << " грн\n";
        cout << "----------------------------\n";

        // Переходимо до наступного елементу
        pCurrent = pCurrent->m_pNext;
        iIndex++;  // Збільшуємо індекс
    }
}

//--------------------------------------------------------------------------------

/* Функція відображає повідомлення про помилку при відкритті файлу */

void displayFileError() {
    cout << "Помилка: не вдалося відкрити файл.\n";
}
/* Функція запитує у користувача індекси двох книг і викликає функцію для їх обміну місцями

   Функція приймає параметр:
   head - голова списку книг

   Під час виконання, функція запитує у користувача два індекси і передає їх функції swapBooks
   для здійснення обміну між книгами за вказаними індексами */

   void swapBooksFromUser(BookNode* pHead) {
    int index1, index2;

    // Запитуємо у користувача індекси
    cout << "Введіть індекс першої книги для зміни місцями: ";
    cin >> index1;
    cout << "Введіть індекс другої книги для зміни місцями: ";
    cin >> index2;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // очищаємо буфер вводу

    // Викликаємо функцію для зміни місцями
    swapBooks(pHead, index1 - 1, index2 - 1);
}

/* Функція здійснює обмін двох книг у списку за заданими індексами

   Функція приймає параметри:
   pHead - голова списку книг
   index1 - індекс першої книги для обміну
   index2 - індекс другої книги для обміну

   Під час виконання, функція знаходить книги за вказаними індексами і міняє їх місцями */

void swapBooks(BookNode* pHead, int index1, int index2) {
    if (index1 == index2) return; // Якщо індекси однакові, нічого не робимо.

    BookNode* pFirst = nullptr;
    BookNode* pSecond = nullptr;
    BookNode* pTemp = pHead;
    int currentIndex = 0;

    // Шукаємо елементи з відповідними індексами
    while (pTemp != nullptr) {
        if (currentIndex == index1) pFirst = pTemp;
        if (currentIndex == index2) pSecond = pTemp;
        pTemp = pTemp->m_pNext;
        currentIndex++;
    }

    // Якщо хоча б один з елементів не знайдений
    if (!pFirst || !pSecond) {
        cout << "Невірні індекси.\n";
        return;
    }

    // Міняємо місцями книжки
    Book tempBook = pFirst->m_sBook;
    pFirst->m_sBook = pSecond->m_sBook;
    pSecond->m_sBook = tempBook;

    cout << "Книжки успішно поміняні місцями!\n";
}

/* Функція сортує список книг за автором в алфавітному порядку (метод бульбашки)

   Функція приймає параметр:
   pHead - голова списку книг

   Під час виконання, функція порівнює авторів книг і здійснює їх перестановку при необхідності */
   
void bubbleSortBooks(BookNode*& pHead) {
    if (!pHead || !pHead->m_pNext) {
        return;  // Якщо список порожній або містить лише один елемент
    }

    bool swapped;
    do {
        swapped = false;
        BookNode* pCurrent = pHead;
        while (pCurrent && pCurrent->m_pNext) {
            if (pCurrent->m_sBook.bookAuthorTitle.m_strBookAuthor > pCurrent->m_pNext->m_sBook.bookAuthorTitle.m_strBookAuthor) {
                // Міняємо місцями книги, якщо автор наступної книги має менше значення
                Book temp = pCurrent->m_sBook;
                pCurrent->m_sBook = pCurrent->m_pNext->m_sBook;
                pCurrent->m_pNext->m_sBook = temp;

                swapped = true;
            }
            pCurrent = pCurrent->m_pNext;
        }
    } while (swapped);  // Якщо було зроблено обмін, повторюємо
}

/* Функція видаляє книги, ціна яких менше 5 грн, з запитом у користувача на підтвердження

   Функція приймає параметр:
   pHead - голова списку книг

   Під час виконання, функція перевіряє ціну кожної книги і запитує у користувача
   чи хоче він її видалити, якщо ціна менша за 5 грн */

void deleteBooksUnder5(BookNode*& pHead) {
    if (!pHead) {
        cout << "Список порожній.\n";
        return;
    }

    BookNode* pCurrent = pHead;
    BookNode* pPrev = nullptr;
    bool anyDeleted = false;

    while (pCurrent) {
        if (pCurrent->m_sBook.bookYearPagesPrice.m_dBookPrice < 5) {
            cout << "Книга \"" << pCurrent->m_sBook.bookAuthorTitle.m_strBookTitle << "\" автор: "
                      << pCurrent->m_sBook.bookAuthorTitle.m_strBookAuthor << " має ціну "
                      << pCurrent->m_sBook.bookYearPagesPrice.m_dBookPrice << " грн.\n";
            cout << "Чи хочете ви її видалити? (1 - так, 0 - ні): ";
            int choice;
            cin >> choice;

            // Очищаємо буфер вводу після cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 1) {
                // Видалення книги з початку списку або з середини/кінця
                if (pPrev) {
                    pPrev->m_pNext = pCurrent->m_pNext;
                } else {
                    pHead = pCurrent->m_pNext;  // Якщо це перший елемент, змінюємо head
                }
                BookNode* pTemp = pCurrent;
                pCurrent = pCurrent->m_pNext;
                delete pTemp;
                anyDeleted = true;
            } else {
                pPrev = pCurrent;
                pCurrent = pCurrent->m_pNext;
            }
        } else {
            pPrev = pCurrent;
            pCurrent = pCurrent->m_pNext;
        }
    }

    if (!anyDeleted) {
        cout << "Немає книг з ціною менше 5 грн.\n";
    } else {
        cout << "Видалено книги з ціною менше 5 грн.\n";
    }
}

/* Функція зберігає зміни списку книг у файл

   Функція приймає параметр:
   pHead - голова списку книг

   Під час виконання, функція запитує у користувача назву файлу для збереження
   і зберігає інформацію про всі книги у файл */
   
void saveChangesToFile(BookNode* pHead) {
    // Запитуємо назву файлу для збереження
    string filename;
    cout << "Введіть назву файлу для збереження: ";
    getline(cin, filename);

    // Додаємо шлях до папки data
    string fullPath = "../data/" + filename;

    // Запитуємо чи хоче користувач зберегти зміни
    cout << "Чи хочете ви зберегти зміни в файл? (1 - так, 0 - ні): ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Очищаємо буфер вводу

    // Якщо вибір "1", записуємо зміни у файл
    if (choice == 1) {
        ofstream file(fullPath);
        
        if (!file.is_open()) {
            cout << "Не вдалося відкрити файл для запису.\n";
            return;
        }

        BookNode* pCurrent = pHead;
        while (pCurrent) {
            file << "\"" << pCurrent->m_sBook.bookAuthorTitle.m_strBookAuthor << "\" "
                 << "\"" << pCurrent->m_sBook.bookAuthorTitle.m_strBookTitle << "\" "
                 << "\"" << pCurrent->m_sBook.bookYearPagesPrice.m_iBookYear << "\" "
                 << "\"" << pCurrent->m_sBook.bookYearPagesPrice.m_iBookPages << "\" "
                 << "\"" << pCurrent->m_sBook.bookYearPagesPrice.m_dBookPrice << "\"\n";
            pCurrent = pCurrent->m_pNext;
        }

        file.close();
        cout << "Зміни успішно збережено у файл: " << fullPath << "\n";
    } else {
        cout << "Зміни не були збережені.\n";
    }
}