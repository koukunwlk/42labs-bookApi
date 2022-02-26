#include "server.h"

int	has_field(char *query)
{
	if(!strncmp(query, "id=", 3))
		return 1;
	
	if(!strncmp(query, "name=", 5))
		return 1;
	
	return 0;
}