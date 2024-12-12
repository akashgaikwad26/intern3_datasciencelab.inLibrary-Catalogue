#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declare the head and tail for the linked list
struct Book *head = NULL, *tail = NULL;

void test_export_catalogue();
void test_import_catalogue();

int main() {
    printf("Running test cases for export_catalogue and import_catalogue...\n\n");

    test_export_catalogue();
    test_import_catalogue();

    printf("\nAll tests completed.\n");
    return 0;
}

void test_export_catalogue() {
    printf("Testing export_catalogue...\n");

    // Setup: Add a few books to the catalogue
    struct Book *book1 = (struct Book *)malloc(sizeof(struct Book));
    strcpy(book1->book_title, "Book1");
    strcpy(book1->author, "Author1");
    strcpy(book1->ISBN_number, "123-4567890123");
    strcpy(book1->publisher, "Publisher1");
    strcpy(book1->publication_year, "2023");
    strcpy(book1->genre, "Fiction");
    book1->next = NULL;

    struct Book *book2 = (struct Book *)malloc(sizeof(struct Book));
    strcpy(book2->book_title, "Book2");
    strcpy(book2->author, "Author2");
    strcpy(book2->ISBN_number, "987-6543210987");
    strcpy(book2->publisher, "Publisher2");
    strcpy(book2->publication_year, "2022");
    strcpy(book2->genre, "Non-Fiction");
    book2->next = NULL;

    head = book1;
    book1->next = book2;
    tail = book2;

    // Redirect stdin to simulate filename input
    FILE *input = fopen("test_export_input.txt", "w");
    fprintf(input, "test_catalogue.csv\n");
    fclose(input);
    freopen("test_export_input.txt", "r", stdin);

    // Call the export_catalogue function
    export_catalogue();

    // Check if the file is created and contains the correct data
    FILE *exported_file = fopen("test_catalogue.csv", "r");
    assert(exported_file != NULL);

    char buffer[256];
    fgets(buffer, sizeof(buffer), exported_file); // Read header
    assert(strcmp(buffer, "Title,Author,ISBN,Publisher,Year,Genre\n") == 0);

    fgets(buffer, sizeof(buffer), exported_file); // Read first book
    assert(strcmp(buffer, "Book1,Author1,123-4567890123,Publisher1,2023,Fiction\n") == 0);

    fgets(buffer, sizeof(buffer), exported_file); // Read second book
    assert(strcmp(buffer, "Book2,Author2,987-6543210987,Publisher2,2022,Non-Fiction\n") == 0);

    fclose(exported_file);

    printf("\t[PASS] export_catalogue works correctly.\n");
}

void test_import_catalogue() {
    printf("Testing import_catalogue...\n");

    // Cleanup the current list
    free_catalogue();

    // Create a CSV file to simulate import
    FILE *import_file = fopen("test_import.csv", "w");
    fprintf(import_file, "Title,Author,ISBN,Publisher,Year,Genre\n");
    fprintf(import_file, "Book1,Author1,123-4567890123,Publisher1,2023,Fiction\n");
    fprintf(import_file, "Book2,Author2,987-6543210987,Publisher2,2022,Non-Fiction\n");
    fclose(import_file);

    // Redirect stdin to simulate filename input
    FILE *input = fopen("test_import_input.txt", "w");
    fprintf(input, "test_import.csv\n");
    fclose(input);
    freopen("test_import_input.txt", "r", stdin);

    // Call the import_catalogue function
    import_catalogue();

    // Validate the imported data
    assert(head != NULL);
    assert(strcmp(head->book_title, "Book1") == 0);
    assert(strcmp(head->author, "Author1") == 0);
    assert(strcmp(head->ISBN_number, "123-4567890123") == 0);
    assert(strcmp(head->publisher, "Publisher1") == 0);
    assert(strcmp(head->publication_year, "2023") == 0);
    assert(strcmp(head->genre, "Fiction") == 0);

    assert(head->next != NULL);
    assert(strcmp(head->next->book_title, "Book2") == 0);
    assert(strcmp(head->next->author, "Author2") == 0);
    assert(strcmp(head->next->ISBN_number, "987-6543210987") == 0);
    assert(strcmp(head->next->publisher, "Publisher2") == 0);
    assert(strcmp(head->next->publication_year, "2022") == 0);
    assert(strcmp(head->next->genre, "Non-Fiction") == 0);

    printf("\t[PASS] import_catalogue works correctly.\n");
}

void free_catalogue() {
    struct Book *current = head;
    while (current) {
        struct Book *temp = current;
        current = current->next;
        free(temp);
    }
    head = tail = NULL;
}
