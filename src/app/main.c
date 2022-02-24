#include <stdio.h>
#include "mongoose.h"
#include "mjson.h"
#include <mysql/mysql.h>
#include <json-c/json.h>
#include <string.h>
#include <stdlib.h>

static const char *host = "http://0.0.0.0:3333";
char	*get_books(void);
void	create_book(struct mg_http_message *hm);
void	delete_book(int id);

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	

	if(ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *) ev_data;

		if(mg_http_match_uri(hm, "/books"))
		{
			if(strncmp(hm->method.ptr, "POST", 4) == 0)
			{
				create_book(hm);
				mg_http_reply(c, 200, "", "Livro inserido");
			}
			else
				mg_http_reply(c, 200, "", get_books());
		}
		if(mg_http_match_uri(hm, "/book/*"))
		{
			if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
			{
				char id[13];
				int i = -1;
				while(hm->query.ptr[++i] > '0' && hm->query.ptr[i] < '9')
					id[i] = hm->query.ptr[i];
				printf("query = %s\n", id);
				delete_book(atoi(id));
				mg_http_reply(c, 200, "", "");
			}
		}
	}
}

int main()
{
struct mg_mgr mgr;                        
  mg_log_set("2");                             
  mg_mgr_init(&mgr);                            
  mg_http_listen(&mgr, host, fn, NULL);
  for (;;) mg_mgr_poll(&mgr, 1000);             
  mg_mgr_free(&mgr);
  return 0;
}

char *get_books(void)
{
	MYSQL conn;
	MYSQL_RES *results;
	MYSQL_ROW row;
	json_object *obj;
	json_object *arr = json_object_new_array();
	json_object *res = json_object_new_object();
	json_object *value;
	mysql_init(&conn);
	if (mysql_real_connect(&conn, "localhost", "moacir", "12091997", "testC", 0, NULL, 0))
	{
		//printf("Conectado ao banco");
		mysql_query(&conn, "SELECT * from books");
		results = mysql_store_result(&conn);
		row = mysql_fetch_row(results);
		while(row != 0)
		{
			obj = json_object_new_object();
			value = json_object_new_string(row[1]); 
			json_object_object_add(obj, "name", value);
			json_object_array_add(arr, obj);
			row = mysql_fetch_row(results);
		}
		json_object_object_add(res, "books", arr);
		//printf("%s\n", json_object_to_json_string(res));
		mysql_close(&conn);
		return ((char *)json_object_to_json_string(res));
	}
	else
	{
		printf("Falha ao conectar ao banco");
		printf("Erro %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
	return ("");
}

void	create_book(struct mg_http_message *hm)
{
	MYSQL conn;
	char	query[2000];
	char	book[256];
	char	buffer[256];
	int		result;

	
	result = mjson_get_string(hm->body.ptr, hm->body.len, "$.name", book, sizeof(book));
	
	mysql_init(&conn);
	if (mysql_real_connect(&conn, "localhost", "moacir", "12091997", "testC", 0, NULL, 0))
	{
		sprintf(query, "INSERT INTO books(name)VALUES('%s')", book);
		mysql_query(&conn, query);
		printf("Query = %s\n", query);
		mysql_close(&conn);
	}
	else
	{
		printf("Falha ao conectar ao banco");
		 printf("Erro %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}

void delete_book(int id)
{
	MYSQL conn;
	char	query[2000];

	mysql_init(&conn);
	if (mysql_real_connect(&conn, "localhost", "moacir", "12091997", "testC", 0, NULL, 0))
	{
		sprintf(query, "DELETE FROM books where id=%d", id);
		mysql_query(&conn, query);
		printf("Query = %s\n", query);
		mysql_close(&conn);
	}
	else
	{
		printf("Falha ao conectar ao banco");
		 printf("Erro %d: %s\n", mysql_errno(&conn), mysql_error(&conn));
	}
}