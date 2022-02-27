#ifndef DATABASE_H
#define DATABASE_H
# include <mysql/mysql.h>
# include <stdio.h>

# define HOST "http://0.0.0.0:3333"
# define HOSTDB "localhost"
# define USER "moacir"
# define PASSWORD "12091997"
# define DB "labs"

void create_database_books(void);
void create_database_category(void);
void add_foreign_key(void);

void populate_books(void);
void populate_categories(void);

#endif