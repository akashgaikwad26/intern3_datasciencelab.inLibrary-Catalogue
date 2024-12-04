#include "book.h"

struct LibraryCatalogue{
    struct Book books;
    struct LibraryCatalogue *NEXT;
};
