#include "server.h"

MYSQL_RES *get_books(void)
{
	MYSQL_RES *results;
	MYSQL conn;
	char	  *query;

	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, "localhost", "moacir", "12091997", "labs", 0, NULL, 0))
	{
		query = "SELECT books.name, publish_date, author, publisher,categories.name as Category FROM books"
				" JOIN categories on books.category_code = categories.id";
		mysql_query(&conn, query);
		results = mysql_store_result(&conn);
		mysql_close(&conn);
	}

	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
	
	return (results);
}