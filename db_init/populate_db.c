#include "database.h"

void populate_books(void)
{
    MYSQL conn;
	char	  query[2000];

	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		printf("Adding books\n");
		sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","Harry Potter e a pedra filosofal", "2017-08-19 00:00:00", "J.K. Rowling", "Rocco", "8532530788", 4);
		mysql_query(&conn, query);

        sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","Harry Potter e a Câmara Secreta", "2017-08-19 00:00:00", "J.K. Rowling", "Rocco", "8532530796", 4);
		mysql_query(&conn, query);

        sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","Harry Potter e o prisioneiro de Azkaban", "2017-08-19 00:00:00", "J.K. Rowling", "Rocco", "853253080X", 4);
		mysql_query(&conn, query);

        sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","Harry Potter e a ordem da fênix", "2017-08-19 00:00:00", "J.K. Rowling", "Rocco", "8532530826", 4);
		mysql_query(&conn, query);

		sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","Daqui a cinco anos", "2020-07-20 00:00:00", "Rebecca Serle", "Paralela", "8584391738", 24);
		mysql_query(&conn, query);

		sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","A paciente silenciosa", "2019-05-20 00:00:00", "Alex Michaelides", "Record", "8501116432", 34);
		mysql_query(&conn, query);

		sprintf(query, "INSERT INTO books(name, publish_date, author, publisher, ISBN, category_code, created_at)VALUES('%s', '%s', '%s', '%s', '%s', %d, NOW())","A rainha vermelha", "2015-06-09 00:00:00", "Victoria Aveyard", "Seguinte", "8565765695", 14);
		mysql_query(&conn, query);

		mysql_close(&conn);
		printf("Done\n");
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}

void populate_categories(void)
{
	MYSQL conn;
	char	  query[2000];
	mysql_init(&conn);
	if (mysql_real_connect(&conn, HOSTDB, USER, PASSWORD, DB, 0, NULL, 0))
	{
		printf("Adding Categories\n");
		sprintf(query, "INSERT INTO categories(name, created_at)VALUES('%s', NOW())", "Sci-fi");
		mysql_query(&conn, query);

        sprintf(query, "INSERT INTO categories(name, created_at)VALUES('%s', NOW())", "Action");
		mysql_query(&conn, query);

        sprintf(query, "INSERT INTO categories(name, created_at)VALUES('%s', NOW())", "Drama");
		mysql_query(&conn, query);

        sprintf(query, "INSERT INTO categories(name, created_at)VALUES('%s', NOW())", "thriller");
		mysql_query(&conn, query);
		mysql_close(&conn);
		printf("Done\n");
	}
	else
	{
		printf("Failed to connect to database\n");
		printf("Error %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}