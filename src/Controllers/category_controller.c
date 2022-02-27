#include "server.h"

char	*create_category(struct mg_http_message *hm)
{
	char category_name[255];
	json_object *status = json_object_new_object();
	log_request((char *)hm->head.ptr);
	mjson_get_string(hm->body.ptr, hm->body.len, "$.name", category_name, sizeof(category_name));
	store_category(category_name);
	json_object_object_add(status, "status", json_object_new_string("ok"));
	return ((char *)json_object_to_json_string(status));
}

char	*show_categories(struct mg_http_message *hm)
{
	MYSQL_RES *results;
	MYSQL_ROW row;
	json_object *category;
	json_object *categories;

	log_request((char *)hm->head.ptr);
	results = get_categories();
	row = mysql_fetch_row(results);
	categories = json_object_new_array();
	while(row != 0)
	{
		category = json_object_new_object();
		json_object_object_add(category, "id", json_object_new_string(row[0]));
		json_object_object_add(category, "name", json_object_new_string(row[1]));
		json_object_array_add(categories, category);
		row = mysql_fetch_row(results);
	}
	return ((char *)json_object_to_json_string(categories));
}

char	*remove_category(struct mg_http_message *hm)
{
	int 	id;
	json_object *status = json_object_new_object();
	log_request((char *)hm->head.ptr);

	id = get_id((char *)hm->query.ptr);
	if(get_category(id) == NULL)
		return (send_json_error("category not found"));
	delete_category(id);
	json_object_object_add(status, "status", json_object_new_string("ok"));
	return ((char *)json_object_to_json_string(status));
}

char	*show_category(struct mg_http_message *hm)
{
	json_object *category = json_object_new_object();

	log_request((char *)hm->head.ptr);
	if(hm->query.ptr == NULL)
		return (send_json_error("Query not provided"));
	
	if(!has_field((char *)hm->query.ptr))
		return (send_json_error("Field not found"));

	if(strncmp(hm->query.ptr, "id=", 3) == 0)
	{
		int id = get_id((char *)hm->query.ptr);
		MYSQL_ROW row = get_category(id);
		if(!row)
			return(send_json_error("category not found"));
		json_object_object_add(category, "id", json_object_new_string(row[0]));
		json_object_object_add(category, "name", json_object_new_string(row[1]));
	}
	return((char *)json_object_to_json_string(category));
}

char	*update_category(struct mg_http_message *hm)
{
	const char	*tmp;
	char		category[255];
	int			n;
	int			id;
	json_object *status = json_object_new_object();

	log_request((char *)hm->head.ptr);
	if(hm->query.ptr == NULL)
		return (send_json_error("Query not provided"));
	
	if(!has_field((char *)hm->query.ptr))
		return (send_json_error("Field not found"));
	
	id = get_id((char *)hm->query.ptr);
	if(get_category(id) == NULL)
		return (send_json_error("category not found"));
	
	if(mjson_find(hm->body.ptr, hm->body.len, "$.name", &tmp, &n)!= MJSON_TOK_INVALID)
		mjson_get_string(hm->body.ptr, hm->body.len, "$.name", category, sizeof(category));
	
	update_category_db(category, id);

	json_object_object_add(status, "status", json_object_new_string("ok"));
	return ((char *)json_object_to_json_string(status));
}