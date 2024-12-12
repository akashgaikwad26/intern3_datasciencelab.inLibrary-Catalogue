#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"
#include <libpq-fe.h>

// Declare the head and tail for the linked list
struct Book *head = NULL, *tail = NULL;

// Prototypes
void test_connect_to_database();
void test_initialize_database();
void test_save_to_database();
void test_load_from_database();
void free_catalogue();

int main() {
    printf("Running test cases for PostgreSQL integration...\n\n");

    test_connect_to_database();
    test_initialize_database();
    test_save_to_database();
    test_load_from_database();

    printf("\nAll tests for PostgreSQL integration completed.\n");
    return 0;
}

void test_connect_to_database() {
    printf("Testing connect_to_database...\n");

    PGconn *conn = connect_to_database();
    assert(conn != NULL);
    assert(PQstatus(conn) == CONNECTION_OK);

    PQfinish(conn);
    printf("\t[PASS] Database connection successful.\n");
}

void test_initialize_database() {
    printf("Testing initialize_database...\n");

    initialize_database();

    // Connect to the database to verify the table exists
    PGconn *conn = connect_to_database();
    const char *check_table_sql = "SELECT EXISTS ("
                                  "SELECT FROM information_schema.tables "
                                  "WHERE table_name = 'books');";
    PGresult *res = PQexec(conn, check_table_sql);
    assert(PQresultStatus(res) == PGRES_TUPLES_OK);
    assert(strcmp(PQgetvalue(res, 0, 0), "t") == 0); // "t" means true in PostgreSQL

    PQclear(res);
    PQfinish(conn);
    printf("\t[PASS] Database schema initialized successfully.\n");
}

void test_save_to_database() {
    printf("Testing save_to_database...\n");

    // Create sample data in the linked list
    struct Book *book1 = (struct Book *)malloc(sizeof(struct Book));
    strcpy(book1->book_title, "Book1");
    strcpy(book1->author, "Author1");
    strcpy(book1->ISBN_number, "123-4567890123");
    strcpy(book1->publisher, "Publisher1");
    book1->publication_year = 2023;
    strcpy(book1->genre, "Fiction");
    book1->next = NULL;

    struct Book *book2 = (struct Book *)malloc(sizeof(struct Book));
    strcpy(book2->book_title, "Book2");
    strcpy(book2->author, "Author2");
    strcpy(book2->ISBN_number, "987-6543210987");
    strcpy(book2->publisher, "Publisher2");
    book2->publication_year = 2022;
    strcpy(book2->genre, "Non-Fiction");
    book2->next = NULL;

    head = book1;
    book1->next = book2;
    tail = book2;

    // Save the data to the database
    save_to_database();

    // Connect to the database and verify the data
    PGconn *conn = connect_to_database();
    const char *check_data_sql = "SELECT COUNT(*) FROM Books;";
    PGresult *res = PQexec(conn, check_data_sql);
    assert(PQresultStatus(res) == PGRES_TUPLES_OK);
    assert(atoi(PQgetvalue(res, 0, 0)) == 2);

    PQclear(res);
    PQfinish(conn);
    printf("\t[PASS] Data saved to database successfully.\n");
}

void test_load_from_database() {
    printf("Testing load_from_database...\n");

    // Load data from the database into the linked list
    load_from_database();

    // Validate the data in the linked list
    assert(head != NULL);
    assert(strcmp(head->book_title, "Book1") == 0);
    assert(strcmp(head->author, "Author1") == 0);
    assert(strcmp(head->ISBN_number, "123-4567890123") == 0);
    assert(strcmp(head->publisher, "Publisher1") == 0);
    assert(head->publication_year == 2023);
    assert(strcmp(head->genre, "Fiction") == 0);

    assert(head->next != NULL);
    assert(strcmp(head->next->book_title, "Book2") == 0);
    assert(strcmp(head->next->author, "Author2") == 0);
    assert(strcmp(head->next->ISBN_number, "987-6543210987") == 0);
    assert(strcmp(head->next->publisher, "Publisher2") == 0);
    assert(head->next->publication_year == 2022);
    assert(strcmp(head->next->genre, "Non-Fiction") == 0);

    printf("\t[PASS] Data loaded from database successfully.\n");
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
