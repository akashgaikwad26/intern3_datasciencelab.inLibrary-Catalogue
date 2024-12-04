#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_PUBLISHER_LENGTH 100
#define MAX_GENRE_LENGTH 50

struct Book{
    char book_title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char ISBN_number[17];  // ISBN-13 or ISBN-10 with a hyphen
    char publisher[MAX_PUBLISHER_LENGTH];
    char publication_year[4];
    char genre[MAX_GENRE_LENGTH];
    struct Book *next;
};




 