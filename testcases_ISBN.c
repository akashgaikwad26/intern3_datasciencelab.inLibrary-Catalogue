#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "catalogue.c"

void ISBN() 
{
    struct LibraryCatalogue *catalogue = malloc(sizeof(struct LibraryCatalogue));
    struct Book temp;

    struct LibraryCatalogue *current = catalogue;
    while (current != NULL) {
        assert(strcmp(current->books.ISBN_number, temp.ISBN_number));
        int cmp = strcmp(current->books.ISBN_number, temp.ISBN_number);
        printf("Comparison result: %d\n", cmp);
        printf("%d %d", current->books.ISBN_number, temp.ISBN_number);
        current = current->NEXT; // Move to the next node
    }

    // Free the linked list
    free(catalogue->NEXT);
    free(catalogue);
}

void test_add_book()
{
    int count = 0, Book_cnt;
    printf("Enter the number to add new books : ");
    scanf("%d", &Book_cnt);

    for(int i = 0; i < Book_cnt; i++)
    {
        add_book();
        count++;
    }

    assert(count == Book_cnt);
    printf("Assertion passed : %d out of %d are added\n", count, Book_cnt);
}

int main()
{
    test_add_book();
    ISBN();
    return 0;
}

