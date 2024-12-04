#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogue.h"
// #include "book.h"

struct Book *tail = NULL, *head = NULL, *temp;
struct LibraryCatalogue *catalogue;

void create_NewBook()
{
    printf("\n ***** Enter the Book Details ***** \n");
    temp = malloc(sizeof(struct Book));

    printf("Enter the Book Title : ");
    scanf("%s", temp->book_title);

    printf("Enter the Author Name : ");
    scanf("%s", temp->author);

    printf("Enter the ISBN Number : ");
    scanf("%s", temp->ISBN_number);

    printf("Enter the Publisher Name : ");
    scanf("%s", temp->publisher);

    printf("Enter the Publication Year : ");
    scanf("%d", temp->publication_year);

    printf("Enter the Genre : ");
    scanf("%s", temp->genre);

    temp->next = NULL;
      
    if(head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
}

void Add_NewBook()
{
    struct LibraryCatalogue *new_entry = (struct LibraryCatalogue *)malloc(sizeof(struct LibraryCatalogue));
    if (!new_entry) {
        perror("Failed to allocate memory for new book entry");
        return;
    }

    create_NewBook();
  
    new_entry->books = *temp;
    new_entry->NEXT = NULL; 
    if (catalogue == NULL) {
        catalogue = malloc(sizeof(struct LibraryCatalogue *));
        catalogue = NULL;
    }
    new_entry->NEXT = catalogue;
    catalogue = new_entry;
}

void Display_BookDetails()
{
    struct LibraryCatalogue *current = catalogue;
    struct Book *temp = head;
    int count = 1;
    if(head == NULL)
    {
        printf("Records are not present");
    }
    else
    {
        while (temp != NULL)
        {
            printf("\n ***** Display the Book Details - Book : %d ***** \n", count);
            printf("Book's Title : %s\n", temp->book_title);
            printf("Author Name : %s\n", temp->author);
            printf("ISBN Number : %s\n", temp->ISBN_number);
            printf("Publisher Name : %s\n", temp->publisher);
            printf("Publication Year : %d\n", temp->publication_year);
            printf("Genre : %s\n", temp->genre);
            temp = temp->next;
            if(temp != NULL)
            {
                count++;
            }
        } 
    }
    current = current->NEXT;
}

void Free_MemoryAllocated() 
{
    // Free the linked list of books
    struct Book *currentBook = head;
    while (currentBook != NULL) {
        struct Book *tempBook = currentBook;
        currentBook = currentBook->next;
        free(tempBook);
    }
    head = NULL;
    tail = NULL;

    // Free the linked list of LibraryCatalogue entries
    struct LibraryCatalogue *currentCatalogue = catalogue;
    while (currentCatalogue != NULL) {
        struct LibraryCatalogue *tempCatalogue = currentCatalogue;
        currentCatalogue = currentCatalogue->NEXT;
        free(tempCatalogue);
    }
    catalogue = NULL;

    printf("\nMemory for catalogue and books has been freed.\n");
}

int main()
{
    int Book_cnt;
    printf("Enter the number to add new books : ");
    scanf("%d", &Book_cnt);

    for(int i = 0; i < Book_cnt; i++)
    {
        Add_NewBook();
    }
    
    Display_BookDetails();
    Free_MemoryAllocated();
    Display_BookDetails();
    return 0;
}

