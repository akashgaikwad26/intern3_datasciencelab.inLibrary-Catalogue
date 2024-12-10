#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "phase1_task1.c"

void test_create_catalogue_node() {
    struct LibraryCatalogue *node = create_catalogue_node(
        "The Great Gatsby",
        "F. Scott Fitzgerald",
        "9783161484100",
        "Scribner",
        "1925",
        "Fiction"
    );

    assert(strcmp(node->books.book_title, "The Great Gatsby") == 0);
    assert(strcmp(node->books.author, "F. Scott Fitzgerald") == 0);
    assert(strcmp(node->books.ISBN_number, "9783161484100") == 0);
    assert(strcmp(node->books.publisher, "Scribner") == 0);
    assert(strcmp(node->books.publication_year, "1925") == 0);
    assert(strcmp(node->books.genre, "Fiction") == 0);
    assert(node->NEXT == NULL);

    printf("Test create_catalogue_node passed.\n");

    free(node);
}

void test_add_book_to_catalogue() {
    struct LibraryCatalogue *catalogue = NULL;

    struct Book book1 = {
        "The Great Gatsby", "F. Scott Fitzgerald", "9783161484100",
        "Scribner", "1925", "Fiction", NULL
    };
    struct Book book2 = {
        "1984", "George Orwell", "9780451524935",
        "Secker & Warburg", "1949", "Dystopian", NULL
    };

    add_book_to_catalogue(&catalogue, &book1);
    add_book_to_catalogue(&catalogue, &book2);

    assert(catalogue != NULL);  // Check catalogue is not empty
    assert(strcmp(catalogue->books.book_title, "1984") == 0);  // New book should be added first
    assert(strcmp(catalogue->NEXT->books.book_title, "The Great Gatsby") == 0);

    printf("Test add_book_to_catalogue passed.\n");

    free_catalogue(catalogue);
}

void test_print_catalogue() {
    struct LibraryCatalogue *catalogue = NULL;

    struct Book book1 = {
        "The Great Gatsby", "F. Scott Fitzgerald", "9783161484100",
        "Scribner", "1925", "Fiction", NULL
    };
    struct Book book2 = {
        "1984", "George Orwell", "9780451524935",
        "Secker & Warburg", "1949", "Dystopian", NULL
    };

    add_book_to_catalogue(&catalogue, &book1);
    add_book_to_catalogue(&catalogue, &book2);

    // Test that the catalogue prints correctly
    printf("Catalogue:\n");
    print_catalogue(catalogue);

    free_catalogue(catalogue);
}

void test_free_catalogue() {
    struct LibraryCatalogue *catalogue = NULL;

    struct Book book1 = {
        "The Great Gatsby", "F. Scott Fitzgerald", "9783161484100",
        "Scribner", "1925", "Fiction", NULL
    };

    add_book_to_catalogue(&catalogue, &book1);

    // Freeing the catalogue should not crash the program
    free_catalogue(catalogue);

    printf("Test free_catalogue passed.\n");
}

int main() 
{
    printf("***** Testcases for Phase 1 Task 2 *****");
    test_create_catalogue_node();
    test_add_book_to_catalogue();
    test_print_catalogue();
    test_free_catalogue();
    printf("All tests passed.\n");

    return 0;
}