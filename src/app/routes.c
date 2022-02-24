#include "server.h"

void	routes(struct mg_connection *c,struct mg_http_message *hm)
{

	/* Book endpoits */

	if(mg_http_match_uri(hm, "/books"))
	{
		if(strncmp(hm->method.ptr, "POST", 4) == 0)
			return (mg_http_reply(c, 200, "", create_book(hm)));

		else if (strncmp(hm->method.ptr, "GET", 3) == 0)
			return (mg_http_reply(c, 200, "", show_books()));

		else
			return (mg_http_reply(c, 405, "", "Metodo nao permitido"));
	}

	else if (mg_http_match_uri(hm, "/books/*"))
	{
		if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
			return (mg_http_reply(c, 200, "", remove_book(hm)));

		else if(strncmp(hm->method.ptr, "GET", 3) == 0)
			return (mg_http_reply(c, 200, "", "Endpoit books/* metodo GET"));
		
		else if(strncmp(hm->method.ptr, "PUT", 3) == 0)
			return (mg_http_reply(c, 200, "", "Endpoit books/* metodo PUT"));

		else
			return (mg_http_reply(c, 405, "", "Metodo nao permitido"));
	}

	/* Categorys endpoits */

	if(mg_http_match_uri(hm, "/categories"))
	{
		if(strncmp(hm->method.ptr, "POST", 4) == 0)
			mg_http_reply(c, 200, "", "Endpoit categories/ metodo post");

		else if (strncmp(hm->method.ptr, "GET", 3) == 0)
			mg_http_reply(c, 200, "", "Endpoit categories/ metodo get");

		else
			mg_http_reply(c, 405, "", "Metodo nao permitido");
	}

	else if (mg_http_match_uri(hm, "/categories/*"))
	{
		if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
			mg_http_reply(c, 200, "", "Endpoit categories/* metodo delete");

		else if(strncmp(hm->method.ptr, "GET", 3) == 0)
			mg_http_reply(c, 200, "", "Endpoit categories/* metodo GET");
		
		else if(strncmp(hm->method.ptr, "PUT", 3) == 0)
			mg_http_reply(c, 200, "", "Endpoit categories/* metodo PUT");
		else
			mg_http_reply(c, 405, "", "Metodo nao permitido");
	}
	else
		mg_http_reply(c, 404, "", "Endpoit not found");
}