#include "server.h"

char	*send_json_error(char *msg)
{
	json_object *obj_error = json_object_new_object();
	
	json_object_object_add(obj_error, "Error", json_object_new_string(msg));
	return ((char *)json_object_to_json_string(obj_error));
}