#include "server.h"

MYSQL_RES *get_categories(void)
{
	MYSQL_RES *results;
	MYSQL conn;
	char	  *query;

	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		query = "SELECT categories.name FROM categories";
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

/* void	store_book(new_book *category)
{
	MYSQL_RES *results;
	int		   status;
	MYSQL conn;
	char	  query[2000];
	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query, "INSERT INTO categories(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())",category->name, category->publish_date, category->author, category->publisher, category->ISBN, atoi(category->category_code));
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
		sprintf(query, "DELETE FROM categories where id=%d", id);
		mysql_query(&conn, query);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}

MYSQL_ROW get_book(int id)
{
	MYSQL_RES	*results;
	MYSQL_ROW	row;
	MYSQL		conn;
	char	 	query[2000];

	results = NULL;
	row = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query,	"SELECT categories.name, publish_date, author, publisher,categories.name as Category FROM categories "
						"JOIN categories on categories.category_code = categories.id "
						"WHERE categories.id=%d", id);
		mysql_query(&conn, query);
		results = mysql_store_result(&conn);
		row = mysql_fetch_row(results);
		mysql_close(&conn);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
	return (row);
}

void update_book_db(new_book *updated_book, int id)
{
	MYSQL_RES *results;
	int		   status;
	MYSQL conn;
	char	  query[2000];
	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query, "UPDATE categories SET name='%s' WHERE id=%d AND '%s'<> ''", updated_book->name, id, updated_book->name);
		mysql_query(&conn, query);

		sprintf(query, "UPDATE categories SET author='%s' WHERE id=%d AND '%s'<> ''", updated_book->author, id, updated_book->author);
		mysql_query(&conn, query);

		sprintf(query, "UPDATE categories SET publisher='%s' WHERE id=%d AND '%s'<> ''", updated_book->publisher, id, updated_book->publisher);
		mysql_query(&conn, query);

		sprintf(query, "UPDATE categories SET publish_date='%s' WHERE id=%d AND '%s'<> ''", updated_book->publish_date, id, updated_book->publish_date);
		mysql_query(&conn, query);

		sprintf(query, "UPDATE categories SET ISBN='%s' WHERE id=%d AND '%s'<> ''", updated_book->ISBN, id, updated_book->ISBN);
		mysql_query(&conn, query);

		sprintf(query, "UPDATE categories SET name='%s' WHERE id=%d AND '%s'<> ''", updated_book->name, id, updated_book->name);
		mysql_query(&conn, query);

		sprintf(query, "UPDATE categories SET category_code=%d WHERE id=%d AND '%s'<> ''", atoi(updated_book->category_code), id, updated_book->category_code);
		mysql_query(&conn, query);
		
		mysql_close(&conn);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
} */