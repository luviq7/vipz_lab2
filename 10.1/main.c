#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct books {
    char author[50];
    char book_name[50];
    int year;
    int pages;
    double price;
    struct books* next;
};

int main(void) {
    struct books* head = NULL;
    FILE* in = fopen("/Users/taraskabacok/Documents/oplabs/10_xcode/10.1/in.txt", "r");

    char author[50], book_name[50];
    int year, pages;
    double price;

    while (fscanf(in, " \"%[^\"]\" \"%[^\"]\" \"%d\" \"%d\" \"%lf\"", author, book_name, &year, &pages, &price) == 5) {
        struct books* newNode = (struct books*)malloc(sizeof(struct books));
        strcpy(newNode->author, author);
        strcpy(newNode->book_name, book_name);
        newNode->year = year;
        newNode->pages = pages;
        newNode->price = price;
        newNode->next = NULL;

        if (head == NULL || strcmp(newNode->author, head->author) < 0) {
            newNode->next = head;
            head = newNode;
        } else {
            struct books* current = head;
            while (current->next != NULL && strcmp(newNode->author, current->next->author) > 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    fclose(in);

    printf("сортування:\n");
    struct books* current = head;
    while (current != NULL) {
        printf("\"%s\" \"%s\" \"%d\" \"%d\" \"%.2lf\"\n", current->author, current->book_name, current->year, current->pages, current->price);
        current = current->next;
    }
    struct books* newBook = (struct books*)malloc(sizeof(struct books));
    strcpy(newBook->author, "NEW_AUTHOR");
    strcpy(newBook->book_name, "NEW_BOOK");
    newBook->year = 9999;
    newBook->pages = 999;
    newBook->price = 999.0;
    newBook->next = NULL;

    if (head == NULL || strcmp(newBook->author, head->author) < 0) {
        newBook->next = head;
        head = newBook;
    } else {
        current = head;
        while (current->next != NULL && strcmp(newBook->author, current->next->author) > 0) {
            current = current->next;
        }
        newBook->next = current->next;
        current->next = newBook;
    }
    printf("\n");

    printf("список з новою книгою:\n");
    current = head;
    while (current != NULL) {
        printf("\"%s\" \"%s\" \"%d\" \"%d\" \"%.2lf\"\n", current->author, current->book_name, current->year, current->pages, current->price);
        current = current->next;
    }
    
    printf("\n");
    printf("видаляємо книги з ціною менше 5 грн:\n");
    current = head;
    struct books* prev = NULL;
    while (current != NULL) {
        if (current->price < 5.0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            struct books* temp = current;
            current = current->next;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }

    current = head;
    while (current != NULL) {
        printf("\"%s\" \"%s\" \"%d\" \"%d\" \"%.2lf\"\n", current->author, current->book_name, current->year, current->pages, current->price);
        current = current->next;
    }

    FILE* out = fopen("/Users/taraskabacok/Documents/oplabs/10_xcode/10.1/out.txt", "w");
    current = head;
    while (current != NULL) {
        fprintf(out, "\"%s\" \"%s\" \"%d\" \"%d\" \"%.2lf\"\n", current->author, current->book_name, current->year, current->pages, current->price);
        current = current->next;
    }
    fclose(out);
}
