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
		query = "SELECT * FROM categories";
		mysql_query(&conn, query);
		results = mysql_store_result(&conn);
		mysql_close(&conn);
	}

	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
	mysql_library_end();
	return (results);
}

void	store_category(char *category_name)
{
	MYSQL_RES *results;
	int		   status;
	MYSQL conn;
	char	  query[2000];
	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query, "INSERT INTO categories(name, created_at)VALUES('%s', NOW())", category_name);
		mysql_query(&conn, query);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
	mysql_library_end();
}

void	delete_category(int id)
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
	mysql_library_end();
}

MYSQL_ROW get_category(int id)
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
		sprintf(query,	"SELECT * FROM categories "
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
	mysql_library_end();
	return (row);
}

void update_category_db(char *category_name, int id)
{
	MYSQL_RES *results;
	int		   status;
	MYSQL conn;
	char	  query[2000];
	results = NULL;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		sprintf(query, "UPDATE categories SET name='%s' WHERE id=%d AND '%s'<> ''", category_name, id, category_name);
		
		mysql_query(&conn, query);
		mysql_close(&conn);
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
	mysql_library_end();
} 