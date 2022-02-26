# ifndef SERVER_H
# define SERVER_H
# define HOST "http://0.0.0.0:3333"
# define HOSTDB "localhost"
# define USER "moacir"
# define PASSWORD "12091997"
# define DB "labs"

# include <stdio.h>
# include "mongoose.h"
# include "mjson.h"
# include <mysql/mysql.h>
# include <json-c/json.h>
# include <string.h>

typedef struct book {
	char	name[255];
	char	publish_date[255];
	char	author[255];
	char	publisher[255];
	char	ISBN[255];
	char	category_code[255];
}	new_book;



void		routes(struct mg_connection *c,struct mg_http_message *hm);


MYSQL_RES	*get_books(void);
MYSQL_ROW 	get_book(int id);
void		store_book(new_book *book);
void		delete_book(int id);
void 		update_book_db(new_book *updated_book, int id);

char 		*show_books();
char		*create_book(struct mg_http_message *hm);
char		*remove_book(struct mg_http_message *hm);
char		*show_book(struct mg_http_message *hm);
char		*update_book(struct mg_http_message *hm);

MYSQL_RES 	*get_categories(void);
MYSQL_ROW 	get_category(int id);
void		store_category(char *category_name);
void		delete_category(int id);
void 		update_category_db(char *category_name, int id);

char		*show_categories();
char		*show_category(struct mg_http_message *hm);
char		*create_category(struct mg_http_message *hm);
char		*remove_category(struct mg_http_message *hm);
char		*update_category(struct mg_http_message *hm);

int			get_id(char *str);
char		*send_json_error(char *msg);
int			has_query(char *query);

# endif