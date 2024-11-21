#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "book.h"

// Array-based implementation of LibraryCatalogue
typedef struct {
    struct Book* books;         // Dynamic array of books
    int size;            // Current number of books
    int capacity;        // Maximum capacity of the array
} LibraryCatalogue;

// Function prototypes
LibraryCatalogue* initializeCatalogue(int initial_capacity);
void addBook(LibraryCatalogue* catalogue, struct Book book);
void displayCatalogue(const LibraryCatalogue* catalogue);
void freeCatalogue(LibraryCatalogue* catalogue);

#endif // CATALOGUE_H
