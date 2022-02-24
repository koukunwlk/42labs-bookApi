#include "server.h"

char *create_book(struct mg_http_message *hm)
{
	new_book book;
	json_object *status = json_object_new_object();

	mjson_get_string(hm->body.ptr, hm->body.len, "$.name", book.name, sizeof(book.name));
	mjson_get_string(hm->body.ptr, hm->body.len, "$.publish_date", book.publish_date, sizeof(book.publish_date));
	mjson_get_string(hm->body.ptr, hm->body.len, "$.author", book.author, sizeof(book.author));
	mjson_get_string(hm->body.ptr, hm->body.len, "$.publisher", book.publisher, sizeof(book.publisher));
	mjson_get_string(hm->body.ptr, hm->body.len, "$.ISBN", book.ISBN, sizeof(book.ISBN));
	mjson_get_string(hm->body.ptr, hm->body.len, "$.category_code", book.category_code, sizeof(book.category_code));
	store_book(&book);
	json_object_object_add(status, "status", json_object_new_string("ok"));
	return ((char *)json_object_to_json_string(status));
}

char *show_books()
{
	MYSQL_RES *results;
	MYSQL_ROW row;
	json_object *book;
	json_object *books;

	results = get_books();
	row = mysql_fetch_row(results);
	books = json_object_new_array();
	while(row != 0)
	{
		book = json_object_new_object();
		json_object_object_add(book, "name", json_object_new_string(row[0]));
		json_object_object_add(book, "publish_date", json_object_new_string(row[1]));
		json_object_object_add(book, "author", json_object_new_string(row[2]));
		json_object_object_add(book, "publisher", json_object_new_string(row[3]));
		json_object_object_add(book, "category", json_object_new_string(row[4]));
		printf("json obj = %s\n", json_object_to_json_string(book));
		json_object_array_add(books, book);
		row = mysql_fetch_row(results);
	}
	return ((char *)json_object_to_json_string(books));
}