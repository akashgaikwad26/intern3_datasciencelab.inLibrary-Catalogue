#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "catalogue.c"
#include "sort_book.c"
#include "import_export.c"
// #include "database.c"

// Function prototypes for the tests
void test_create_book();
void test_display_book();
void test_delete_book();
void test_update_book();
void test_search_book();
void test_sort_books();

int main() {
    // Run all tests
    test_create_book();
    test_display_book();
    test_delete_book();
    test_update_book();
    test_search_book();
    test_sort_books();

    printf("All tests passed successfully!\n");
    return 0;
}

// Test function implementations
void test_create_book() {
    free_catalogue(); // Clear any existing data
    add_book("Test Book", "Test Author", "1234567890123", "Test Publisher", 2022, "Fiction"); // Add a book

    assert(head != NULL); // Check if a book was added to the list
    assert(strcmp(head->book_title, "Test Book") == 0); // Check book title
    assert(strcmp(head->author, "Test Author") == 0); // Check author
    assert(strcmp(head->ISBN_number, "1234567890123") == 0); // Check ISBN
    assert(strcmp(head->publisher, "Test Publisher") == 0); // Check publisher
    assert(strcmp(head->publication_year, "2022") == 0); // Check publication year
    assert(strcmp(head->genre, "Fiction") == 0); // Check genre
}

void test_display_book() {
    // Difficult to test without capturing stdout - see previous response for suggestions on how to handle this.
    free_catalogue();
    add_book(); // Add a book

    display_book(); // This would normally print to stdout
}

void test_delete_book() {
    free_catalogue();
    add_book(); // Add a book with a known ISBN
    char isbnToDelete[] = "1234567890123"; // Replace with the ISBN of your added book

    delete_book(isbnToDelete); // Delete the book

    assert(head == NULL); // Should be NULL since the book was deleted
}

void test_update_book() {
    free_catalogue();
    add_book(); // Add a book with a known ISBN
    char isbnToUpdate[] = "1234567890123"; // Replace with the ISBN of your added book

    update_book(isbnToUpdate); // Update the book

    assert(strcmp(head->book_title, "Updated Book") == 0); // Check updated book title
    assert(strcmp(head->author, "Updated Author") == 0); // Check updated author
    assert(strcmp(head->publisher, "Updated Publisher") == 0); // Check updated publisher
    assert(strcmp(head->publication_year, "2023") == 0); // Check updated publication year
    assert(strcmp(head->genre, "Updated Genre") == 0); // Check updated genre
}

void test_search_book() {
    free_catalogue();
    add_book(); // Add a book with a known ISBN
    char isbnToSearch[] = "1234567890123"; // Replace with the ISBN of your added book

    search_book(); // Search for the book

    assert(strcmp(head->book_title, "Test Book") == 0); // Check book title
    assert(strcmp(head->author, "Test Author") == 0); // Check author
    assert(strcmp(head->ISBN_number, "1234567890123") == 0); // Check ISBN
    assert(strcmp(head->publisher, "Test Publisher") == 0); // Check publisher
    assert(strcmp(head->publication_year, "2022") == 0); // Check updated publication year
    assert(strcmp(head->genre, "Fiction") == 0); // Check genre
}

void test_sort_books() {
    // This test requires a predictable way to add books and a defined sorting criteria
    free_catalogue();
    add_book(); // Add multiple books

    sort_books(); // Sort the books

    assert(strcmp(head->book_title, "Book A") == 0); // Check first book title
    assert(strcmp(head->next->book_title, "Book B") == 0); // Check second book title
    assert(strcmp(head->next->next->book_title, "Book C") == 0); // Check third book title
}