#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "catalogue.h"

// Helper functions for testing
struct Book* create_book(const char* title, const char* author, const char* isbn, const char* publisher, const char* year, const char* genre) {
    struct Book* new_book = (struct Book*)malloc(sizeof(struct Book));
    assert(new_book != NULL);

    strncpy(new_book->book_title, title, MAX_TITLE_LENGTH);
    strncpy(new_book->author, author, MAX_AUTHOR_LENGTH);
    strncpy(new_book->ISBN_number, isbn, 17);
    strncpy(new_book->publisher, publisher, MAX_PUBLISHER_LENGTH);
    strncpy(new_book->publication_year, year, 6);
    strncpy(new_book->genre, genre, MAX_GENRE_LENGTH);

    new_book->next = NULL;
    return new_book;
}

struct LibraryCatalogue* create_catalogue() {
    struct LibraryCatalogue* catalogue = (struct LibraryCatalogue*)malloc(sizeof(struct LibraryCatalogue));
    assert(catalogue != NULL);
    catalogue->NEXT = NULL;
    return catalogue;
}

void add_book_to_catalogue(struct LibraryCatalogue* catalogue, struct Book* book) {
    assert(catalogue != NULL && book != NULL);

    struct LibraryCatalogue* current = catalogue;
    while (current->NEXT != NULL) {
        current = current->NEXT;
    }

    struct LibraryCatalogue* new_entry = (struct LibraryCatalogue*)malloc(sizeof(struct LibraryCatalogue));
    assert(new_entry != NULL);

    new_entry->books = *book;
    new_entry->NEXT = NULL;
    current->NEXT = new_entry;
}

int count_books_in_catalogue(struct LibraryCatalogue* catalogue) {
    assert(catalogue != NULL);

    int count = 0;
    struct LibraryCatalogue* current = catalogue->NEXT;
    while (current != NULL) {
        count++;
        current = current->NEXT;
    }
    return count;
}

// Test cases
int main() {
    struct LibraryCatalogue* catalogue = create_catalogue();

    // Test 1: Catalogue is initially empty
    assert(count_books_in_catalogue(catalogue) == 0);

    // Test 2: Add a book to the catalogue
    struct Book* book1 = create_book("Book One", "Author A", "123-4567890123", "Publisher X", "2023", "Fiction");
    add_book_to_catalogue(catalogue, book1);
    assert(count_books_in_catalogue(catalogue) == 1);

    // Test 3: Add another book to the catalogue
    struct Book* book2 = create_book("Book Two", "Author B", "987-6543210987", "Publisher Y", "2022", "Non-Fiction");
    add_book_to_catalogue(catalogue, book2);
    assert(count_books_in_catalogue(catalogue) == 2);

    // Test 4: Validate book data in the catalogue
    struct LibraryCatalogue* current = catalogue->NEXT;
    assert(strcmp(current->books.book_title, "Book One") == 0);
    assert(strcmp(current->books.author, "Author A") == 0);
    assert(strcmp(current->books.ISBN_number, "123-4567890123") == 0);
    assert(strcmp(current->books.publisher, "Publisher X") == 0);
    assert(strcmp(current->books.publication_year, "2023") == 0);
    assert(strcmp(current->books.genre, "Fiction") == 0);

    current = current->NEXT;
    assert(strcmp(current->books.book_title, "Book Two") == 0);
    assert(strcmp(current->books.author, "Author B") == 0);
    assert(strcmp(current->books.ISBN_number, "987-6543210987") == 0);
    assert(strcmp(current->books.publisher, "Publisher Y") == 0);
    assert(strcmp(current->books.publication_year, "2022") == 0);
    assert(strcmp(current->books.genre, "Non-Fiction") == 0);

    // Test 5: Adding duplicate or invalid data (skipping implementation)

    // Cleanup
    free(book1);
    free(book2);
    struct LibraryCatalogue* temp;
    while (catalogue != NULL) {
        temp = catalogue;
        catalogue = catalogue->NEXT;
        free(temp);
    }

    printf("***** Testcases for Create and books are working *****\n");

    return 0;
}
