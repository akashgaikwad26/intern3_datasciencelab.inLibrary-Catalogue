#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "catalogue.c"
#include "sort_book.c"
#include "import_export.c"
// #include "database.c"

// Test function implementations
void test_create_book() 
{
    add_book("Test_Book", "Test_Author", "1234567890123", "Test_Publisher", "2022", "Fiction"); // Add a book

    assert(head != NULL); // Check if a book was added to the list
    assert(strcmp(head->book_title, "Test_Book") == 0); // Check book title
    assert(strcmp(head->author, "Test_Author") == 0); // Check author
    assert(strcmp(head->ISBN_number, "1234567890123") == 0); // Check ISBN
    assert(strcmp(head->publisher, "Test_Publisher") == 0); // Check publisher
    assert(strcmp(head->publication_year, "2022")); // Check publication year
    assert(strcmp(head->genre, "Fiction") == 0); // Check genre
}

void test_display_book() 
{
    display_book(); // This would normally print to stdout
}

void test_delete_book()
{
    char isbnToDelete[] = "1234567890123"; // Replace with the ISBN of your added book

    delete_book(isbnToDelete); // Delete the book

    assert(head == NULL); // Should be NULL since the book was deleted
}

void test_update_book() 
{
    char isbnToUpdate[] = "1234567890123"; // Replace with the ISBN of your added book

    update_book(isbnToUpdate); // Update the book

    assert(strcmp(head->book_title, "Updated_Book") == 0); // Check updated book title
    assert(strcmp(head->author, "Updated_Author") == 0); // Check updated author
    assert(strcmp(head->publisher, "Updated_Publisher") == 0); // Check updated publisher
    assert(strcmp(head->publication_year, "2023") == 0); // Check updated publication year
    assert(strcmp(head->genre, "Updated_Genre") == 0); // Check updated genre
}

void test_search_book() 
{
    // free_catalogue();
    // add_book();
    display_book();
    char isbnToSearch[] = "1234567890123"; // Replace with the ISBN of your added book

    search_book(); // Search for the book

    assert(strcmp(head->book_title, "Updated_Book") == 0); // Check book title
    assert(strcmp(head->author, "Updated_Author") == 0); // Check author
    assert(strcmp(head->ISBN_number, "1234567890123") == 0); // Check ISBN
    assert(strcmp(head->publisher, "Updated_Publisher") == 0); // Check publisher
    // assert(strcmp(head->publication_year, "2023")); // Check updated publication year
    assert(strcmp(head->genre, "Updated_Genre") == 0); // Check genre
}

void test_sort_books() 
{
    free_catalogue();
    for(int i = 0; i < 3; i++)
    {
        add_book(); // Add multiple books
    }

    sort_books(); // Sort the books

    assert(strcmp(head->book_title, "A") == 0); // Check first book title
    assert(strcmp(head->next->book_title, "B") == 0); // Check second book title
    assert(strcmp(head->next->next->book_title, "C") == 0); // Check third book title
}

int main() {
    // Run all tests
    test_create_book();
    test_display_book();
    test_update_book();
    test_search_book();
    test_delete_book();
    test_sort_books();
    test_display_book();

    printf("All tests passed successfully!\n");
    return 0;
}