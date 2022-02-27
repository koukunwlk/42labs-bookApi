#include "database.h"

void create_database_books(void)
{
	MYSQL conn;
	char	  *query;

	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		query = "CREATE TABLE IF NOT EXISTS `books`("
                "`id` int AUTO_INCREMENT,"
                "`name` varchar(255),"
                "`category_code` int,"
                "`publish_date` varchar(255),"
                "`author` varchar(255),"
                "`publisher` varchar(255),"
                "`ISBN` varchar(255),"
                "`created_at` timestamp,"
                "PRIMARY KEY (id));";
		mysql_query(&conn, query);
		mysql_close(&conn);
	}

	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}

void create_database_category(void)
{
    MYSQL conn;
	char	  *query;

	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		query = "CREATE TABLE IF NOT EXISTS `categories` ("
                "`id` int AUTO_INCREMENT,"
                "`name` varchar(255),"
                "`created_at` timestamp,"
                "PRIMARY KEY (id));";

        mysql_query(&conn, query);
		mysql_close(&conn);
    }
    else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}

void add_foreign_key(void)
{
    MYSQL conn;
	char	  *query;

	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		query = "ALTER TABLE `books` ADD FOREIGN KEY"
                "(`category_code`) REFERENCES `categories` (`id`);";
        mysql_query(&conn, query);
		mysql_close(&conn);
    }
    else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}