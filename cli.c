#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_count {
	int	get_books;
	int	get_book;
	int	post_book;
	int	put_book;
	int	delete_book;
	int	get_category;
	int	get_categories;
	int	post_category;
	int	put_category;
	int	delete_category;
} t_counters;

void init_counters(t_counters *counter)
{
	counter->get_books = 0;
	counter->get_book = 0;
	counter->post_book = 0;
	counter->put_book = 0;
	counter->delete_book = 0;
	counter->get_category = 0;
	counter->get_categories = 0;
	counter->post_category = 0;
	counter->put_category = 0;
	counter->delete_category = 0;
}

int count_requests(t_counters *counters, char *line)
{
	if(!strncmp(line, "GET /books/?id=", 15))
		return(counters->get_book++);
	else if(!strncmp(line, "GET /books", 10))
		return(counters->get_books++);
	else if(!strncmp(line, "POST /books", 11))
		return(counters->post_book++);
	else if(!strncmp(line, "PUT /books/?id=", 15))
		return(counters->put_book++);
	else if(!strncmp(line, "DELETE /books/?id=", 15))
		return(counters->delete_book++);

	if(!strncmp(line, "GET /categories/?id=", 20))
		return(counters->get_category++);
	else if(!strncmp(line, "GET /categories", 15))
		return(counters->get_categories++);
	else if(!strncmp(line, "POST /categories", 16))
		return(counters->post_category++);
	else if(!strncmp(line, "PUT /categories/?id=", 20))
		return(counters->put_category++);
	else if(!strncmp(line, "DELETE /categories/?id=", 23))
		return(counters->delete_category++);
}

void print_books(t_counters *counter)
{
	printf("\tBooks section\n");
	printf("*****************************************************************\n");
	printf("*\tURL\t\t*\tMETHOD\t*\tTOTAL REQUESTS\t*\n");
	printf("*****************************************************************\n");
	printf("*\t/books\t\t*\tGET\t*\t\t%d\t*\n", counter->get_books);
	printf("*\t/books\t\t*\tPOST\t*\t\t%d\t*\n", counter->post_book);
	printf("*\t/books/\t\t*\tGET\t*\t\t%d\t*\n", counter->get_book);
	printf("*\t/books/\t\t*\tPUT\t*\t\t%d\t*\n", counter->put_book);
	printf("*\t/books/\t\t*\tDELETE\t*\t\t%d\t*\n", counter->delete_book);
	printf("*****************************************************************\n");
}

void print_categories(t_counters *counter)
{
	printf("\tCategory section\n");
	printf("*****************************************************************\n");
	printf("*\tURL\t\t*\tMETHOD\t*\tTOTAL REQUESTS\t*\n");
	printf("*****************************************************************\n");
	printf("*\t/categories\t*\tGET\t*\t\t%d\t*\n", counter->get_categories);
	printf("*\t/categories\t*\tPOST\t*\t\t%d\t*\n", counter->post_category);
	printf("*\t/categories/\t*\tGET\t*\t\t%d\t*\n", counter->get_category);
	printf("*\t/categories/\t*\tPUT\t*\t\t%d\t*\n", counter->put_category);
	printf("*\t/categories/\t*\tDELETE\t*\t\t%d\t*\n", counter->delete_category);
	printf("*****************************************************************\n");
}

void print_help()
{
	printf("Usage: ./bookcli [OPTIONS]\n");
	printf("-a, --all\t\t\t Print request logs from books and categories.\n");
	printf("-b, --books\t\t\t Print request logs from books.\n");
	printf("-c, --categories\t\t Print request logs from categories.\n");
}

void print_all(t_counters *counter)
{
	print_books(counter);
	print_categories(counter);
}
int main(int argc, char *argv[])
{
	FILE * fp = fopen("log.txt", "r");
	t_counters counter;
    char * line = NULL;
    size_t len = 0;
    size_t read;
	read = getline(&line, &len, fp);
	init_counters(&counter);
	while(read != -1)
	{
		count_requests(&counter, line);
		read = getline(&line, &len, fp);
	}
	if(line)
		free(line);
	fclose(fp);
	if(!strncmp(argv[1], "-a\0", 3) || !strncmp(argv[1], "--all\0", 6))
		print_all(&counter);
	else if(!strncmp(argv[1], "-b\0", 3) || !strncmp(argv[1], "--books\0", 8))
		print_books(&counter);
	else if(!strncmp(argv[1], "-c\0", 3) || !strncmp(argv[1], "--categories\0", 13))
		print_categories(&counter);
	else if (!strncmp(argv[1], "-h\0", 3) || !strncmp(argv[1], "--help\0", 7))
		print_help();
	else
		printf("bookcli: invalid option %s", argv[1]);
	return (0);
}