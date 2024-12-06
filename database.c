#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

// PostgreSQL connection parameters
#define DB_HOST "localhost"
#define DB_PORT "5432"
#define DB_NAME "library"
#define DB_USER "postgres"
#define DB_PASS "password"

// Function to establish a connection to the PostgreSQL database
PGconn *connect_to_database() {
    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo),
             "host=%s port=%s dbname=%s user=%s password=%s",
             DB_HOST, DB_PORT, DB_NAME, DB_USER, DB_PASS);

    PGconn *conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    return conn;
}

// Function to initialize the database schema
void initialize_database() {
    PGconn *conn = connect_to_database();

    const char *sql = "CREATE TABLE IF NOT EXISTS Books ("
                      "id SERIAL PRIMARY KEY,"
                      "title TEXT NOT NULL,"
                      "author TEXT NOT NULL,"
                      "isbn TEXT UNIQUE NOT NULL,"
                      "publisher TEXT,"
                      "year INT,"
                      "genre TEXT);";

    PGresult *res = PQexec(conn, sql);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        fprintf(stderr, "Error creating table: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    PQclear(res);
    PQfinish(conn);
    printf("Database initialized successfully.\n");
}

// Save the linked list to the PostgreSQL database
void save_to_database() {
    PGconn *conn = connect_to_database();

    const char *sql = "INSERT INTO Books (title, author, isbn, publisher, year, genre) "
                      "VALUES ($1, $2, $3, $4, $5, $6) "
                      "ON CONFLICT (isbn) DO UPDATE SET "
                      "title = EXCLUDED.title, "
                      "author = EXCLUDED.author, "
                      "publisher = EXCLUDED.publisher, "
                      "year = EXCLUDED.year, "
                      "genre = EXCLUDED.genre;";

    struct Book *current = head;

    while (current) {
        const char *values[6];
        char year_str[10];
        snprintf(year_str, sizeof(year_str), "%d", current->publication_year);

        values[0] = current->book_title;
        values[1] = current->author;
        values[2] = current->ISBN_number;
        values[3] = current->publisher;
        values[4] = year_str;
        values[5] = current->genre;

        PGresult *res = PQexecParams(conn, sql, 6, NULL, values, NULL, NULL, 0);

        if (PQresultStatus(res) != PGRES_COMMAND_OK) {
            fprintf(stderr, "Error saving book: %s\n", PQerrorMessage(conn));
        }

        PQclear(res);
        current = current->next;
    }

    PQfinish(conn);
    printf("Catalogue saved to the database successfully.\n");
}

// Load books from the PostgreSQL database into the linked list
void load_from_database() {
    PGconn *conn = connect_to_database();

    const char *sql = "SELECT title, author, isbn, publisher, year, genre FROM Books;";
    PGresult *res = PQexec(conn, sql);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error loading books: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    Free_MemoryAllocated(); // Clear current linked list

    int rows = PQntuples(res);

    for (int i = 0; i < rows; i++) {
        struct Book *new_book = malloc(sizeof(struct Book));
        if (!new_book) {
            perror("Memory allocation failed");
            PQclear(res);
            PQfinish(conn);
            exit(1);
        }

        strcpy(new_book->book_title, PQgetvalue(res, i, 0));
        strcpy(new_book->author, PQgetvalue(res, i, 1));
        strcpy(new_book->ISBN_number, PQgetvalue(res, i, 2));
        strcpy(new_book->publisher, PQgetvalue(res, i, 3));
        new_book->publication_year = atoi(PQgetvalue(res, i, 4));
        strcpy(new_book->genre, PQgetvalue(res, i, 5));

        new_book->next = NULL;

        if (!head) {
            head = tail = new_book;
        } else {
            tail->next = new_book;
            tail = new_book;
        }
    }

    PQclear(res);
    PQfinish(conn);
    printf("Catalogue loaded from the database successfully.\n");
}
