#include "book.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function Implementations
Book* createBook(const char* bookTitle, const char* bookAuthor, const char* bookId, bool isBorrowed){
    Book* newBook = (Book*)malloc(sizeof(Book));
    if (newBook == NULL){
        printf("Failed to allocate memory for new book.");
        return NULL;
    }

    snprintf(newBook->bookTitle, MAX_TITLE_LENGTH, "%s", bookTitle);
    snprintf(newBook->bookAuthor, MAX_AUTHOR_LENGTH, "%s", bookAuthor);
    snprintf(newBook->bookId, MAX_BOOK_ID_LENGTH, "%s", bookId);
    newBook->isBorrowed = isBorrowed;

    return newBook;
}

void printBook(const Book* book){
    if (book == NULL){
        printf("Error: Cannot print NULL book.\n");
        return;
    }
    printf("--- Book Details ---\n");
    printf("ID: %s\n", book->bookId);
    printf("Title: %s\n", book->bookTitle);
    printf("Author: %s\n", book->bookAuthor);
    printf("Status: %s\n", book->isBorrowed ? "Borrowed" : "Available");
    printf("--------------------\n");
}

void destroyBook(Book* book){
    if (book != NULL){
        free(book);
    }
}