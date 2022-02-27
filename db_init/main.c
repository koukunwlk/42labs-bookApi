#include "database.h"

int main(void)
{
    create_database_books();
    create_database_category();
    add_foreign_key();
    populate_categories();
    populate_books();
    return 0;
}