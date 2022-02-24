#include "server.h"

MYSQL_RES *get_books(void)
{
	MYSQL_RES *results;
	MYSQL conn;
	char	  *query;

	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
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

void	store_book(new_book *book)
{
	MYSQL_RES *results;
	int		   status;
	MYSQL conn;
	char	  query[2000];
	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())",book->name, book->publish_date, book->author, book->publisher, book->ISBN, atoi(book->category_code));
		mysql_query(&conn, query);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}

void	delete_book(int id)
{
	MYSQL_RES	*results;
	MYSQL		conn;
	char	 	query[2000];

	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query, "DELETE FROM books where id=%d", id);
		mysql_query(&conn, query);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}