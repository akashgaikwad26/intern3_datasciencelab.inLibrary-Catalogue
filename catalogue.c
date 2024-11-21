// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "catalogue.h"
// // #include "book.h"

// // void book_details()
// // {
// //     struct Book b1 = {"Shyamachi Aai", "Sane Guruji", "978-3-16-148410-0", "XYZ", 2024, "Novel"};
// //     printf("Book's Title : %s\n", b1.book_title);
// //     printf("Author Name : %s\n", b1.author);
// //     printf("ISBN Number : %s\n", b1.ISBN_number);
// //     printf("Publisher Name : %s\n", b1.publisher);
// //     printf("Publication Year : %d\n", b1.publication_year);
// //     printf("Genre : %s\n", b1.genre);
// // }

// // struct LibraryCatalogue *next;
// struct Book *tail = NULL;
// struct Book *head = NULL;

// void Add_NewBook()
// {
//     struct Book *temp = malloc(sizeof(struct Book));
//     printf("\nEnter the Book Title : ");
//     scanf("%s", temp->book_title);

//     printf("\nEnter the Author Name : ");
//     scanf("%s", temp->author);

//     printf("\nEnter the ISBN Number : ");
//     scanf("%s", temp->ISBN_number);

//     printf("\nEnter the Publisher Name : ");
//     scanf("%s", temp->publisher);

//     printf("\nEnter the Publication Year : ");
//     scanf("%d", temp->publication_year);

//     printf("\nEnter the Genre : ");
//     scanf("%s", temp->genre);

//     temp->next = NULL;

//     if(head == NULL)
//     {
//         head = temp;
//         tail = temp;
//     }
//     else
//     {
//         tail->next = temp;
//         tail = temp;
//     }
// }

// int main()
// {
//     Add_NewBook();
//     //book_details();
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogue.h"

// Initialize the LibraryCatalogue with a specified capacity
LibraryCatalogue* initializeCatalogue(int initial_capacity) {
    LibraryCatalogue* catalogue = (LibraryCatalogue*)malloc(sizeof(LibraryCatalogue));
    if (!catalogue) {
        printf("Memory allocation for catalogue failed.\n");
        return NULL;
    }
    catalogue->books = (struct Book*)malloc(initial_capacity * sizeof(struct Book));
    if (!catalogue->books) {
        printf("Memory allocation for books array failed.\n");
        free(catalogue);
        return NULL;
    }
    catalogue->size = 0;
    catalogue->capacity = initial_capacity;
    return catalogue;
}

// Add a new book to the catalogue
void addBook(LibraryCatalogue* catalogue, struct Book book) {
    if (catalogue->size == catalogue->capacity) {
        // Resize the books array
        int new_capacity = catalogue->capacity * 2;
        struct Book* new_books = (struct Book*)realloc(catalogue->books, new_capacity * sizeof(struct Book));
        if (!new_books) {
            printf("Failed to resize the books array.\n");
            return;
        }
        catalogue->books = new_books;
        catalogue->capacity = new_capacity;
    }
    catalogue->books[catalogue->size++] = book;
}

// Display all books in the catalogue
void displayCatalogue(const LibraryCatalogue* catalogue) {
    if (catalogue->size == 0) {
        printf("The library catalogue is empty.\n");
        return;
    }

    printf("Library Catalogue:\n");
    for (int i = 0; i < catalogue->size; i++) {
        struct Book* book = &catalogue->books[i];
        printf("\nBook %d:\n", i + 1);
        printf("  Title: %s\n", book->book_title);
        printf("  Author: %s\n", book->author);
        printf("  ISBN: %s\n", book->ISBN_number);
        printf("  Publisher: %s\n", book->publisher);
        printf("  Publication Year: %d\n", book->publication_year);
        printf("  Genre: %s\n", book->genre);
    
    }
}

// Free the memory allocated for the catalogue
void freeCatalogue(LibraryCatalogue* catalogue) {
    if (catalogue) {
        free(catalogue->books);
        free(catalogue);
    }
}

#include <stdio.h>
#include "catalogue.h"

int main() {
    // Initialize the library catalogue
    LibraryCatalogue* catalogue = initializeCatalogue(2);
    if (!catalogue) {
        return 1;
    }

    // Create some books
    struct Book book1 = {
        "1984",
        "George Orwell",
        "9780451524935",
        "Secker & Warburg",
        1949,
        "Dystopian Fiction"
    };

    struct Book book2 = {
        "The Catcher in the Rye",
        "J.D. Salinger",
        "9780316769488",
        "Little, Brown and Company",
        1951,
        "Fiction"
    };

    struct Book book3 = {
        "To Kill a Mockingbird",
        "Harper Lee",
        "9780061120084",
        "J.B. Lippincott & Co.",
        1960,
        "Classic"
    };

    // Add books to the catalogue
    addBook(catalogue, book1);
    addBook(catalogue, book2);
    addBook(catalogue, book3);

    // Display the catalogue
    displayCatalogue(catalogue);

    // Free the catalogue
    freeCatalogue(catalogue);

    return 0;
}
