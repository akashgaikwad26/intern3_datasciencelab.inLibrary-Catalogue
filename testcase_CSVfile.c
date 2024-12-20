#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Structure to represent a book record
typedef struct {
    char title[100];
    char author[100];
    char isbn[20];
    char publisher[100];
    int year;
    char genre[50];
} Book;

// Function to parse a CSV line into a Book structure
Book parseBookRecord(const char *line) {
    Book book;
    char buffer[300];
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ",");
    strcpy(book.title, token);

    token = strtok(NULL, ",");
    strcpy(book.author, token);

    token = strtok(NULL, ",");
    strcpy(book.isbn, token);

    token = strtok(NULL, ",");
    strcpy(book.publisher, token);

    token = strtok(NULL, ",");
    book.year = atoi(token);

    token = strtok(NULL, ",");
    strcpy(book.genre, token);

    return book;
}

// Function to test if a year is valid
void testValidYear(int year) {
    if (year <= 0 || year > 2024) {
        fprintf(stderr, "Error: Invalid publication year (%d)!\n", year);
        assert(0 || "Invalid publication year!");
    }
}

// Function to test if an ISBN is valid (length between 10 and 13)
void testValidISBN(const char *isbn) {
    int len = strlen(isbn);
    assert((len == 10 || len == 13) && "Invalid ISBN length!");
}

// Function to test if a book title and author are non-empty
void testNonEmptyFields(const char *field, const char *fieldName) {
    assert(strlen(field) > 0 && "Field cannot be empty!");
}

// Test automation for the CSV file
void runTests(const char *csvFile) {
    FILE *file = fopen(csvFile, "r");
    if (!file) {
        perror("Failed to open the file");
        exit(EXIT_FAILURE);
    }

    char line[300];
    int lineNumber = 0;

    // Read each line and test
    while (fgets(line, sizeof(line), file)) {
        lineNumber++;

        // Skip the header line
        if (lineNumber == 1) continue;

        // Parse the book record
        Book book = parseBookRecord(line);

        // Run assertions
        printf("Testing line %d: %s\n", lineNumber, book.title);
        testNonEmptyFields(book.title, "Title");
        testNonEmptyFields(book.author, "Author");
        testNonEmptyFields(book.isbn, "ISBN");
        testValidISBN(book.isbn);
        testValidYear(book.year);
    }

    fclose(file);
    printf("All tests passed!\n");
}

int main() {
    // Path to the CSV file
    const char *csvFilePath = "book_data.csv";

    // Run automated tests
    runTests(csvFilePath);

    return 0;
}
