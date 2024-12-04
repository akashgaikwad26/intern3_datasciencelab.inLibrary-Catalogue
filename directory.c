#include "book.h"

add_book()
{
    insert into public.book_data values ('Shyamachi Aai', 'Sane Guruji', 
    '9788188773022', 'Sadhana', '1948', 'Classic');
}

delete_book()
{
    delete from public.book_data where isbn_number = '9788188773022'
}

update_book()
{
    
}

search_book()
{
    select * from public.book_data;
}