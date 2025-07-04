#ifndef LIBRARY_H
#define LIBRARY_H
#include "book.h"

#define INITIAL_CAPACITY 10

// Library structure
typedef struct {
    Book** books;
    int countBook;
    int capacity;
} Library;

// Function declarations
Library* createLibrary();

bool addBookToLibrary(Library* library, Book* newBook);

Book* findBookById(const Library* library, const char* bookId);

bool updateBook(Library* library, const char* bookId, const char* newTitle, const char* newAuthor, bool newIsBorrowed);

bool removeBookFromLibrary(Library* library, const char* bookId);

void listAllBooks(const Library* library);

void destroyLibrary(Library* library);

#endif  // LIBRARY_H