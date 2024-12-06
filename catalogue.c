#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.c"

void add_book()
{
    struct LibraryCatalogue *new_entry = (struct LibraryCatalogue *)malloc(sizeof(struct LibraryCatalogue));
    if (!new_entry) {
        perror("Failed to allocate memory for new book entry");
        return;
    }

    create_book();

    new_entry->books = *temp;
    new_entry->NEXT = NULL; 
    if (catalogue == NULL) {
        catalogue = malloc(sizeof(struct LibraryCatalogue *));
        catalogue = NULL;
    }
    new_entry->NEXT = catalogue;
    catalogue = new_entry;
}

void delete_book() {
    printf("\n***** Delete a Book from catalogue *****\n");

    char isbn_to_delete[20];
    printf("\nEnter ISBN to delete book details : ");
    scanf("%s", isbn_to_delete);

    // Check if the list is empty
    if (head == NULL) {
        printf("\nThe catalogue is empty. No books to delete.\n");
        return;
    }

    struct Book *current = head;
    struct Book *previous = NULL;
    while (current != NULL) {
        if (strcmp(current->ISBN_number, isbn_to_delete) == 0) 
        {
            printf("\nBook with ISBN '%s' is present. Deleting...\n", isbn_to_delete);
            if (previous == NULL) 
            {
                head = current->next;
            } 
            else 
            {
                previous->next = current->next;
            }
            if (current == tail) {
                tail = previous;
            }
            free(current);
            printf("Book successfully deleted.\n");
            return;
        }

        previous = current;
        current = current->next;
    }

    printf("\nBook with ISBN '%s' not present in the catalogue.\n", isbn_to_delete);
}

void update_book() {
    printf("\n***** Update the details for a Book *****\n");

    char isbn_to_update[20]; 
    printf("\nEnter ISBN to update book details : ");
    scanf("%s", isbn_to_update);

    struct Book *current = head;

    while (current != NULL) {
        if (strcmp(current->ISBN_number, isbn_to_update) == 0) {
            printf("\nBook with ISBN '%s' is present. nEnter new details : \n", isbn_to_update);

            printf("Enter the New Title (Current - %s): ", current->book_title);
            scanf("%s", current->book_title);

            printf("Enter the New Author (Current - %s): ", current->author);
            scanf("%s", current->author);

            printf("Enter the New Publisher (Current - %s): ", current->publisher);
            scanf("%s", current->publisher);

            printf("Enter the New Publication Year (Current - %s): ", current->publication_year);
            scanf("%s", &current->publication_year);

            printf("Enter the New Genre (Current - %s): ", current->genre);
            scanf("%s", current->genre);

            printf("\nBook details updated successfully.\n");
            return;
        }
        current = current->next;
    }

    printf("\nBook with ISBN '%s' is not present in the catalogue.\n", isbn_to_update);
}

void search_book() {
    int choice;
    char query[100];
    struct Book *current = head;

    printf("\n***** Search for a Book *****\n");
    printf("Search by:\n1. Title\n2. Author\n3. ISBN Number\nEnter your choice : ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Please enter 1, 2, or 3.\n");
        return;
    }

    printf("Enter your search element : ");
    scanf("%s", query);

    while (current != NULL) {
        if ((choice == 1 && strcasecmp(current->book_title, query) == 0) ||
            (choice == 2 && strcasecmp(current->author, query) == 0) ||
            (choice == 3 && strcmp(current->ISBN_number, query) == 0)) {
            printf("\nBook is present, Book's details :\n");
            printf("Title : %s\n", current->book_title);
            printf("Author : %s\n", current->author);
            printf("ISBN Number : %s\n", current->ISBN_number);
            printf("Publisher : %s\n", current->publisher);
            printf("Publication Year : %d\n", current->publication_year);
            printf("Genre : %s\n", current->genre);
            return;
        }
        current = current->next;
    }

    printf("\nBook is not matching with the element.\n");
}

