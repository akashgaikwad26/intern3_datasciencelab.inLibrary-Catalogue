#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Export books to a CSV file
void export_catalogue() 
{
    char filename[20];
    printf("\nEnter filename to export : ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for export");
        return;
    }

    struct Book *current = head;
    fprintf(file, "Title,Author,ISBN,Publisher,Year,Genre\n"); // Header row
    while (current) {
        fprintf(file, "%s,%s,%s,%s,%s,%s\n",
                current->book_title,
                current->author,
                current->ISBN_number,
                current->publisher,
                current->publication_year,
                current->genre);
        current = current->next;
    }

    fclose(file);
    printf("Catalogue exported to '%s' successfully.\n", filename);
}

// Import books from a CSV file
void import_catalogue()
{
    char filename[20];
    printf("\nEnter filename to import : ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file for import");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), file); // Skip header row

    while (fgets(line, sizeof(line), file)) {
        struct Book *new_book = malloc(sizeof(struct Book));
        if (!new_book) {
            perror("Memory allocation failed");
            fclose(file);
            return;
        }

        sscanf(line, "%s,%s,%s,%s,%s,%s\n]",
               new_book->book_title,
               new_book->author,
               new_book->ISBN_number,
               new_book->publisher,
               &new_book->publication_year,
               new_book->genre);

        new_book->next = NULL;
        if (!head) {
            head = tail = new_book;
        } else {
            tail->next = new_book;
            tail = new_book;
        }
    }

    fclose(file);
    printf("Catalogue imported from '%s' successfully.\n", filename);
}
