#include "server.h"

void init_book(new_book *book)
{
	strcpy(book->name, "");
	strcpy(book->author, "");
	strcpy(book->category_code, "");
	strcpy(book->ISBN, "");
	strcpy(book->publish_date, "");
	strcpy(book->publisher, "");
}

char	*create_book(struct mg_http_message *hm)
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

char	*show_books()
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
		json_object_array_add(books, book);
		row = mysql_fetch_row(results);
	}
	return ((char *)json_object_to_json_string(books));
}

char	*remove_book(struct mg_http_message *hm)
{
	int 	id;
	json_object *status = json_object_new_object();

	id = get_id((char *)hm->query.ptr);
	if(get_book(id) == NULL)
		return (send_json_error("Book not found"));
	delete_book(id);
	json_object_object_add(status, "status", json_object_new_string("ok"));
	return ((char *)json_object_to_json_string(status));
}

char	*show_book(struct mg_http_message *hm)
{
	json_object *book = json_object_new_object();

	if(strncmp(hm->query.ptr, "id=", 3) == 0)
	{
		int id = get_id((char *)hm->query.ptr);
		MYSQL_ROW row = get_book(id);
		printf("book = %s\n",send_json_error("Book not found"));
		if(!row)
			return(send_json_error("Book not found"));
		json_object_object_add(book, "name", json_object_new_string(row[0]));
		json_object_object_add(book, "publish_date", json_object_new_string(row[1]));
		json_object_object_add(book, "author", json_object_new_string(row[2]));
		json_object_object_add(book, "publisher", json_object_new_string(row[3]));
		json_object_object_add(book, "category", json_object_new_string(row[4]));
	}
	return((char *)json_object_to_json_string(book));
}

char	*update_book(struct mg_http_message *hm)
{
	new_book book;
	init_book(&book);
	const char	*tmp;
	int		n;

	if(mjson_find(hm->body.ptr, hm->body.len, "$.name", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.name", book.name, sizeof(book.name));
	if(mjson_find(hm->body.ptr, hm->body.len, "$.publish_date", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.publish_date", book.publish_date, sizeof(book.publish_date));
	if(mjson_find(hm->body.ptr, hm->body.len, "$.author", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.author", book.author, sizeof(book.author));
	if(mjson_find(hm->body.ptr, hm->body.len, "$.publisher", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.publisher", book.publisher, sizeof(book.publisher));
	if(mjson_find(hm->body.ptr, hm->body.len, "$.ISBN", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.ISBN", book.ISBN, sizeof(book.ISBN));
	if(mjson_find(hm->body.ptr, hm->body.len, "$.category_code", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.category_code", book.category_code, sizeof(book.category_code));
	printf("Book fild 1 = %s\n",book.name);
	printf("Book fild 2 = %s\n",book.publish_date);
	printf("Book fild 3 = %s\n",book.author);
	printf("Book fild 4 = %s\n",book.publisher);
	printf("Book fild 5 = %s\n",book.ISBN);
	printf("Book fild 6 = %s\n",book.category_code);
}

