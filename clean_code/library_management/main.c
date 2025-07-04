#include "inc/library.h"
#include "inc/book.h"
#include <stdio.h>

int main() {
    // Create a new library
    Library* myLibrary = createLibrary();
    if (myLibrary == NULL) {
        return 1;
    }

    // Create some books
    Book* book1 = createBook("The Great Gatsby", "F. Scott Fitzgerald", "ISBN001", false);
    Book* book2 = createBook("1984", "George Orwell", "ISBN002", false);
    Book* book3 = createBook("To Kill a Mockingbird", "Harper Lee", "ISBN003", false);
    Book* book4 = createBook("Pride and Prejudice", "Jane Austen", "ISBN004", true); // Already borrowed

    // Check if book creation failed and clean up if necessary
    if (!book1 || !book2 || !book3 || !book4) {
        fprintf(stderr, "One or more books could not be created. Exiting.\n");
        destroyBook(book1); destroyBook(book2); destroyBook(book3); destroyBook(book4);
        destroyLibrary(myLibrary);
        return 1;
    }

    printf("\n--- Adding Books ---\n");
    addBookToLibrary(myLibrary, book1);
    addBookToLibrary(myLibrary, book2);
    addBookToLibrary(myLibrary, book3);
    addBookToLibrary(myLibrary, book4);

    // Try adding an existing book (should fail)
    Book* duplicateBook = createBook("1984", "George Orwell", "ISBN002", false);
    if (!addBookToLibrary(myLibrary, duplicateBook)) {
        destroyBook(duplicateBook);
    }

    listAllBooks(myLibrary);

    // Find a book
    printf("\n--- Finding Book by ID ---\n");
    Book* foundBook = findBookById(myLibrary, "ISBN002");
    if (foundBook != NULL) {
        printf("Found book with ID ISBN002:\n");
        printBook(foundBook);
    } else {
        printf("Book with ID ISBN002 not found.\n");
    }

    printf("\n--- Updating Book Status ---\n");
    if (updateBook(myLibrary, "ISBN001", NULL, NULL, true)) {
        printf("Successfully borrowed ISBN001.\n");
    } else {
        printf("Failed to update ISBN001.\n");
    }

    if (updateBook(myLibrary, "ISBN004", "New Title for Pride", "New Author for Pride", false)) {
        printf("Successfully returned ISBN004 and updated details.\n");
    } else {
        printf("Failed to update ISBN004.\n");
    }

    // Try updating a non-existent book (should fail)
    if (!updateBook(myLibrary, "ISBN999", "Fake Title", "Fake Author", false)) {
        printf("Attempted to update non-existent book ISBN999 (as expected).\n");
    }

    listAllBooks(myLibrary);

    printf("\n--- Removing Book ---\n");
    if (removeBookFromLibrary(myLibrary, "ISBN003")) {
        printf("ISBN003 removed successfully.\n");
    } else {
        printf("Failed to remove ISBN003.\n");
    }

    // Try removing a non-existent book (should fail)
    if (!removeBookFromLibrary(myLibrary, "ISBN999")) {
        printf("Attempted to remove non-existent book ISBN999 (as expected).\n");
    }

    listAllBooks(myLibrary);

    destroyLibrary(myLibrary);
 
    return 0;
}