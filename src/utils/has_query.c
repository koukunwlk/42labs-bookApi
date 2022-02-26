#include "server.h"

int	has_query(char *query)
{
	if(strncmp(query, "id=", 3))
		return 0;
	
	if(strncmp(query, "name=", 5))
		return 0;
	
	return 1;
}