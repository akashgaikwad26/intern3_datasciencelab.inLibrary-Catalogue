#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "catalogue.c"
#include "sort_book.c"
#include "import_export.c"
// #include "database.c"

void print_menu() {
    printf("\n=== Library Catalogue CLI ===\n");
    printf("1. Add a New Book\n");
    printf("2. Display All Books\n");
    printf("3. Search for a Book\n");
    printf("4. Update Book Information\n");
    printf("5. Delete a Book\n");
    printf("6. Sort Books\n");
    printf("7. Import Books from File\n");
    printf("8. Export Books to File\n");
    printf("9. Save Catalogue to Database\n");
    printf("10. Load Catalogue from Database\n");
    printf("11. Free memory allocated for the catalogue\n");
    printf("Enter your choice : ");
}

int main() {
    int choice; int Book_cnt; 
    // initialize_database(); // Ensure the database schema exists

    while (1) {
        print_menu();
        scanf("%d", &choice);
        getchar(); // Consume newline left in the input buffer

        switch (choice) {
            case 1:
                printf("Enter the number to add new books : ");
                scanf("%d", &Book_cnt);

                for(int i = 0; i < Book_cnt; i++)
                {
                    add_book();
                }
                break;

            case 2:
                display_book();
                break;

            case 3: {
                search_book();
                break;
            }

            case 4:
                update_book();
                break;

            case 5:
                delete_book();
                break;

            case 6: {
                sort_books();
                break;
            }

            case 7: {
                import_catalogue();
                break;
            }

            case 8: {
                export_catalogue();
                break;
            }

            // case 9:
            //     save_to_database();
            //     break;

            // case 10:
            //     load_from_database();
            //     break;

            case 11:
                free_catalogue();
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}


// int main()
// {
//     int Book_cnt; 

//     // Insert a book by ISBN
//     printf("Enter the number to add new books : ");
//     scanf("%d", &Book_cnt);

//     for(int i = 0; i < Book_cnt; i++)
//     {
//         add_book();
//     }

//     // Display book
//     display_book();

//     // // Delete a book by ISBN
//     // delete_book();
//     // display_book();

//     // // Delete a book by ISBN
//     // update_book();
//     // display_book();

//     // // Search book by entered details
//     // search_book();

//     // Sort the books by entered element
//     // sort_books();
//     // display_book();

//     // export_catalogue();
    
//     // import_catalogue();
//     // display_book();

//     save_to_database();

//     load_from_database();

//     // Free catalogue
//     // free_catalogue();
//     return 0;
// }