#ifndef DATABASE_H
#define DATABASE_H
# include <mysql/mysql.h>
# include <stdio.h>
# define HOST "http://0.0.0.0:3333"
# define HOSTDB "us-cdbr-east-05.cleardb.net"
# define USER "b48af622edd96b"
# define PASSWORD "da039320"
# define DB "heroku_174cdb875597074"

void create_database_books(void);
void create_database_category(void);
void add_foreign_key(void);

void populate_books(void);
void populate_categories(void);

#endif