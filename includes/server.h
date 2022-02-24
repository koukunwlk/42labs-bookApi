# ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include "mongoose.h"
# include "mjson.h"
# include <mysql/mysql.h>
# include <json-c/json.h>
# include <string.h>

#define HOST "http://0.0.0.0:3333"

void	routes(struct mg_connection *c,struct mg_http_message *hm);


# endif