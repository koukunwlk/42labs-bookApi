#include "server.h"

void	routes(struct mg_connection *c,struct mg_http_message *hm)
{
	/* Doc endpoit */
	if(mg_http_match_uri(hm, "/"))
		mg_http_reply(c, 302, "Location: https://documenter.getpostman.com/view/19780281/UVkqrEiK#9472dc3a-88dd-4cf8-828d-9fd1e35acf4f\r\n", "");
	
	/* Book endpoits */

	if(mg_http_match_uri(hm, "/books"))
	{
		if(strncmp(hm->method.ptr, "POST", 4) == 0)
			return (mg_http_reply(c, 201, "", create_book(hm)));

		else if (strncmp(hm->method.ptr, "GET", 3) == 0)
			return (mg_http_reply(c, 200, "", show_books(hm)));

		else
			return (mg_http_reply(c, 405, "", "Metodo nao permitido"));
	}

	else if (mg_http_match_uri(hm, "/books/*"))
	{
		if(strncmp(hm->uri.ptr, "/books/?", 8))
			mg_http_reply(c, 404, "", "Endpoit not found");
		else if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
			return (mg_http_reply(c, 202, "", remove_book(hm)));

		else if(strncmp(hm->method.ptr, "GET", 3) == 0)
			return (mg_http_reply(c, 200, "", show_book(hm)));
		
		else if(strncmp(hm->method.ptr, "PUT", 3) == 0)
			return (mg_http_reply(c, 200, "", update_book(hm)));

		else
			return (mg_http_reply(c, 405, "", "Metodo nao permitido"));
	}

	/* Categorys endpoits */

	if(mg_http_match_uri(hm, "/categories"))
	{
		if(strncmp(hm->method.ptr, "POST", 4) == 0)
			mg_http_reply(c, 201, "", create_category(hm));

		else if (strncmp(hm->method.ptr, "GET", 3) == 0)
			mg_http_reply(c, 200, "", show_categories(hm));

		else
			mg_http_reply(c, 405, "", "Metodo nao permitido");
	}

	else if (mg_http_match_uri(hm, "/categories/*"))
	{
		if(strncmp(hm->uri.ptr, "/categories/?", 13))
			mg_http_reply(c, 404, "", "Endpoit not found");
		else if(strncmp(hm->method.ptr, "DELETE", 6) == 0)
			mg_http_reply(c, 202, "", remove_category(hm));

		else if(strncmp(hm->method.ptr, "GET", 3) == 0)
			mg_http_reply(c, 200, "", show_category(hm));
		
		else if(strncmp(hm->method.ptr, "PUT", 3) == 0)
			mg_http_reply(c, 200, "", update_category(hm));
		else
			mg_http_reply(c, 405, "", "Metodo nao permitido");
	}
	else
		mg_http_reply(c, 404, "", "Endpoit not found");
}