// #include <stdio.h>
// #include "book.h"
// // #include "catalogue.h"

// void book_details()
// {
//     struct Book b1 = {"Shyamachi Aai", "Sane Guruji", "978-3-16-148410-0", "XYZ", 2024, "Novel"};
//     printf("Book's Title : %s\n", b1.book_title);
//     printf("Author Name : %s\n", b1.author);
//     printf("ISBN Number : %s\n", b1.ISBN_number);
//     printf("Publisher Name : %s\n", b1.publisher);
//     printf("Publication Year : %d\n", b1.publication_year);
//     printf("Genre : %s\n", b1.genre);
// }

// void main()
// {
//     // new_book();
//     book_details();
// }

#include "catalogue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to initialize the library catalogue
void initializeCatalogue(LibraryCatalogue *catalogue) {
    catalogue->head = NULL;
    catalogue->size = 0;
}

// Function to create a new book
Book *createBook(int id, const char *title, const char *author, const char *isbn,
                 const char *publisher, int publicationYear, const char *genre) {
    Book *newBook = (Book *)malloc(sizeof(Book));
    if (!newBook) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }
    newBook->id = id;
    strncpy(newBook->title, title, MAX_TITLE_LENGTH - 1);
    newBook->title[MAX_TITLE_LENGTH - 1] = '\0';
    strncpy(newBook->author, author, MAX_AUTHOR_LENGTH - 1);
    newBook->author[MAX_AUTHOR_LENGTH - 1] = '\0';
    strncpy(newBook->isbn, isbn, MAX_ISBN_LENGTH - 1);
    newBook->isbn[MAX_ISBN_LENGTH - 1] = '\0';
    strncpy(newBook->publisher, publisher, MAX_PUBLISHER_LENGTH - 1);
    newBook->publisher[MAX_PUBLISHER_LENGTH - 1] = '\0';
    newBook->publicationYear = publicationYear;
    strncpy(newBook->genre, genre, MAX_GENRE_LENGTH - 1);
    newBook->genre[MAX_GENRE_LENGTH - 1] = '\0';
    newBook->next = NULL;
    return newBook;
}

// Function to add a book to the catalogue
void addBook(LibraryCatalogue *catalogue, Book *book) {
    if (!book) return;
    book->next = catalogue->head;
    catalogue->head = book;
    catalogue->size++;
}

// Function to remove a book from the catalogue by ID
int removeBook(LibraryCatalogue *catalogue, int id) {
    Book *current = catalogue->head;
    Book *prev = NULL;

    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                catalogue->head = current->next;
            }
            free(current);
            catalogue->size--;
            return 1;  // Successfully removed
        }
        prev = current;
        current = current->next;
    }
    return 0;  // Book not found
}

// Function to find a book by title
Book *findBookByTitle(LibraryCatalogue *catalogue, const char *title) {
    Book *current = catalogue->head;
    while (current) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Book not found
}

// Function to display the entire catalogue
void displayCatalogue(LibraryCatalogue *catalogue) {
    if (!catalogue->head) {
        printf("The catalogue is empty.\n");
        return;
    }
    Book *current = catalogue->head;
    printf("Library Catalogue:\n");
    while (current) {
        printf("ID: %d\n", current->id);
        printf("Title: %s\n", current->title);
        printf("Author(s): %s\n", current->author);
        printf("ISBN: %s\n", current->isbn);
        printf("Publisher: %s\n", current->publisher);
        printf("Year: %d\n", current->publicationYear);
        printf("Genre: %s\n\n", current->genre);
        current = current->next;
    }
    printf("Total books: %d\n", catalogue->size);
}

// Function to clean up the library catalogue and free memory
void cleanupCatalogue(LibraryCatalogue *catalogue) {
    Book *current = catalogue->head;
    while (current) {
        Book *temp = current;
        current = current->next;
        free(temp);
    }
    catalogue->head = NULL;
    catalogue->size = 0;
}
