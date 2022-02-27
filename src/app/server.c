#include "server.h"

static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	if (ev == MG_EV_HTTP_MSG)
	{
		struct mg_http_message *hm = (struct mg_http_message *)ev_data;

		routes(c, hm);
	}
}


void log_request(char *str)
{
  char *buf;
  buf = strtok(str, "\n");
  sprintf(buf, "%s\n", str);
  FILE *fp = fopen("log.txt", "a");
  if (fp != NULL) {
    fprintf(fp, "%s", buf);
    fclose(fp);
  }
}

int main()
{
	struct mg_mgr mgr;
	mg_log_set("2");
	mg_mgr_init(&mgr);
	mg_http_listen(&mgr, HOST, fn, NULL);
	printf("Server running on: %s\n", HOST);
	for (;;) mg_mgr_poll(&mgr, 1000);
	mg_mgr_free(&mgr);
	return 0;
}