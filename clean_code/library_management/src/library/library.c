#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Function Implementations
Library* createLibrary(){
    Library* newLibrary = (Library*)malloc(sizeof(Library));
    if (newLibrary == NULL){
        printf("Failed to allocate memory for new library.\n");
        return NULL;
    }
    newLibrary->books = (Book**)malloc(INITIAL_CAPACITY * sizeof(Book*));
    if (newLibrary->books == NULL){
        printf("Failed to allocate memory for library books.\n");
        return NULL;
    }
    newLibrary->countBook = 0;
    newLibrary->capacity = INITIAL_CAPACITY;
    printf("Library created with initial capacity of %d. \n", newLibrary->capacity);

    return newLibrary;
}

bool addBookToLibrary(Library* library, Book* newBook){
    if (library ==  NULL || newBook == NULL){
        fprintf(stderr, "Error: Library or book cannot be NULL for adding. \n");
        return false;
    }

    if (findBookById(library, newBook->bookId) != NULL){
        fprintf(stderr, "Error: Book with ID '%s' already exists in the library.\n", newBook->bookId);
        return false;
    }

    library->books[library->countBook] = newBook;
    library->countBook++;
    printf("Book '%s' (ID: %s) added to library.\n", newBook->bookTitle, newBook->bookId);
    return true;
}

Book* findBookById(const Library* library, const char* bookId){
    if (library == NULL || bookId == NULL) {
        fprintf(stderr, "Error: Library or Book ID cannot be NULL for finding.\n");
        return NULL;
    }
    for (int i = 0; i < library->countBook; i++){
        if (strcmp(library->books[i]->bookId, bookId) == 0){
            return library->books[i];
        }
    }
    return NULL;
}

bool updateBook(Library* library, const char* bookId, const char* newTitle, const char* newAuthor, bool newIsBorrowed){
    if (library == NULL || bookId == NULL){
        fprintf(stderr, "Error: Library or Book ID cannot be NULL for updating. \n");
        return false;
    }

    Book* bookToUpdate = findBookById(library, bookId);
    if (bookToUpdate == NULL){
        fprintf(stderr, "Error: Book with ID %s not found for update.\n", bookId);
        return false;
    }

    // Update title if newTitle is provided and different
    if (newTitle != NULL && strcmp(bookToUpdate->bookTitle, newTitle) != 0){
        snprintf(bookToUpdate->bookTitle, MAX_TITLE_LENGTH, "%s", newTitle);
        printf("Updated title for book ID %s to '%s'.\n", bookId, newTitle);
    }

    // Update author if newAuthor is provided and different
    if (newAuthor != NULL && strcmp(bookToUpdate->bookAuthor, newAuthor) != 0){
        snprintf(bookToUpdate->bookAuthor, MAX_AUTHOR_LENGTH, "%s", newAuthor);
        printf("Updated author for book ID %s to '%s'.\n", bookId, newAuthor);
    }

    // Update borrowed status if different
    if (bookToUpdate->isBorrowed != newIsBorrowed){
        bookToUpdate->isBorrowed = newIsBorrowed;
        printf("Updated status for book ID %s to '%s'.\n", bookId, newIsBorrowed ? "Borrowed" : "Available");
    }
    
    return true;
}

bool removeBookFromLibrary(Library* library, const char* bookId){
    if (library == NULL || bookId == NULL){
        fprintf(stderr, "Error: Library or Book ID cannot be NULL for removal. \n");
        return false;
    }

    int foundIndex = -1;

    for (int i = 0; i < library->countBook; i++){
        if (strcmp(library->books[i]->bookId, bookId) == 0){
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1){
        fprintf(stderr, "Error: Book with ID '%s' not found for removal.\n", bookId);
        return false;
    }

    // Free the memory of the book being removed
    printf("Book '%s' (ID: %s) removed and freed. \n", library->books[foundIndex]->bookTitle, library->books[foundIndex]->bookId);
    destroyBook(library->books[foundIndex]);

    // Shift remaining books to fill the gap
    for (int i = foundIndex; i < library->countBook - 1; i++){
        library->books[i] = library->books[i+1];
    }
    library->countBook--;

    return true;
}

void listAllBooks(const Library* library){
    if (library == NULL){
        fprintf(stderr, "Error: Library cannot be NULL for listing books. \n");
        return;
    }

    printf("\n ----- All Books in Library (%d/%d) ----- \n", library->countBook, library->capacity);
    if (library->countBook == 0){
        printf("The library is currently empty. \n");
        return;
    }

    for (int i = 0; i < library->countBook; i++){
        printBook(library->books[i]);
    }
    printf("------ End of Book List -----\n\n");
}

void destroyLibrary(Library* library){
    if (library != NULL){
        // Free memory for each individual book in the library
        for (int i = 0; i < library->countBook; i++){
            destroyBook(library->books[i]);
        }
        free(library->books);
        free(library);
        printf("Library and all its books destroyed. \n");
    }
}


