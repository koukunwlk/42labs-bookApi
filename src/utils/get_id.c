#include "server.h"


int	get_id(char *str)
{
	int		index = 0;
	if(strncmp(str, "id=", 3))
		return (-1);

	str += 3;
	while(str[index] != 32)
		index++;

	str[index] = '\0';

	return (atoi(str));
}