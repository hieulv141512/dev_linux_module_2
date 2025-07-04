#ifndef BOOK_H
#define BOOK_H

#include <stdio.h>
#include <stdbool.h>

// Define constants
#define MAX_TITLE_LENGTH    100
#define MAX_AUTHOR_LENGTH   50
#define MAX_BOOK_ID_LENGTH  15

// Book structure
typedef struct {
    char bookTitle[MAX_TITLE_LENGTH];
    char bookAuthor[MAX_AUTHOR_LENGTH];
    char bookId[MAX_BOOK_ID_LENGTH];
    bool isBorrowed;
} Book;

// Function declarations
Book* createBook(const char* bookTitle, const char* bookAuthor, const char* bookId, bool isBorrowed);

void printBook(const Book* book);

void destroyBook(Book* book);

#endif  // BOOK_H