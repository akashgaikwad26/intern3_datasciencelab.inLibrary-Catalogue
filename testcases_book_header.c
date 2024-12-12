#include <stdio.h>
#include <string.h> 
#include <assert.h>
#include "book.h"

void test_create_book() 
{
    struct Book book;

    // Initialize book fields
    strncpy(book.book_title, "The Great Gatsby", MAX_TITLE_LENGTH - 1);
    book.book_title[MAX_TITLE_LENGTH - 1] = '\0'; // Ensure null termination

    strncpy(book.author, "F. Scott Fitzgerald", MAX_AUTHOR_LENGTH - 1);
    book.author[MAX_AUTHOR_LENGTH - 1] = '\0'; // Ensure null termination

    strncpy(book.ISBN_number, "9783161484100", 16);
    book.ISBN_number[16] = '\0'; // Ensure null termination

    strncpy(book.publisher, "Scribner", MAX_PUBLISHER_LENGTH - 1);
    book.publisher[MAX_PUBLISHER_LENGTH - 1] = '\0'; // Ensure null termination

    // Correctly initialize publication_year
    strncpy(book.publication_year, "1925", 4);
    book.publication_year[4] = '\0'; // Ensure null termination

    strncpy(book.genre, "Fiction", MAX_GENRE_LENGTH - 1);
    book.genre[MAX_GENRE_LENGTH - 1] = '\0'; // Ensure null termination

    book.next = NULL;

    // Assertions to verify correctness
    assert(strcmp(book.book_title, "The Great Gatsby") == 0);
    assert(strcmp(book.author, "F. Scott Fitzgerald") == 0);
    assert(strcmp(book.ISBN_number, "9783161484100") == 0);
    assert(strcmp(book.publisher, "Scribner") == 0);
    assert(strcmp(book.publication_year, "1925") == 0); // Matches expected
    assert(strcmp(book.genre, "Fiction") == 0);
    assert(book.next == NULL);

    printf("Test create_book passed.\n");
}

void test_truncation() 
{
    struct Book book;

    strncpy(book.book_title, "A very long book title that exceeds the maximum length of the title buffer", MAX_TITLE_LENGTH);
    book.book_title[MAX_TITLE_LENGTH - 1] = '\0'; // Ensure null termination
    assert(strlen(book.book_title) <= MAX_TITLE_LENGTH - 1);

    printf("Test truncation passed.\n");
}

void test_null_values() 
{
    struct Book book = { "", "", "", "", "", "", NULL };

    assert(strcmp(book.book_title, "") == 0);
    assert(strcmp(book.author, "") == 0);
    assert(strcmp(book.ISBN_number, "") == 0);
    assert(strcmp(book.publisher, "") == 0);
    assert(strcmp(book.publication_year, "") == 0);
    assert(strcmp(book.genre, "") == 0);
    assert(book.next == NULL);

    printf("Test null_values passed.\n");
}

void test_link_books() 
{
    struct Book book1, book2;

    strncpy(book1.book_title, "Book 1", MAX_TITLE_LENGTH);
    book1.next = &book2;

    strncpy(book2.book_title, "Book 2", MAX_TITLE_LENGTH);
    book2.next = NULL;

    assert(book1.next == &book2);
    assert(strcmp(book1.next->book_title, "Book 2") == 0);

    printf("Test link_books passed.\n");
}

void test_isbn_format() 
{
    struct Book book;
    
    // Valid ISBN
    strncpy(book.ISBN_number, "978-3-16-148410-0", 17);
    assert(strlen(book.ISBN_number) == 17);

    // Invalid ISBN (too short)
    strncpy(book.ISBN_number, "123456", 17);
    assert(strlen(book.ISBN_number) != 13 && strlen(book.ISBN_number) != 16);

    printf("Test isbn_format passed.\n");
}

void test_genre_and_year() 
{
    struct Book book;

    // Genre length test
    strncpy(book.genre, "Science Fiction", MAX_GENRE_LENGTH);
    assert(strlen(book.genre) < MAX_GENRE_LENGTH);

    // Publication year test
    strncpy(book.publication_year, "2021", 4);
    book.publication_year[4] = '\0'; // Ensure null termination
    assert(strlen(book.publication_year) == 4);

    printf("Test genre_and_year passed.\n");
}

int main()
{
    printf("***** Testcases for Phase 1 Task 1 *****\n");
    test_create_book();
    test_truncation();
    test_null_values();
    test_link_books();
    test_isbn_format();
    test_genre_and_year();
    printf("All tests passed.\n");
}