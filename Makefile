NAME		= bookApi

CC			= gcc
CFLAGS		= -g

RM			= rm -rf

# MAKEFLAGS += --silent

B			=		$(shell tput bold)
BLA 		=	$(shell tput setaf 0)
RED 		=	$(shell tput setaf 1)
GRE 		=	$(shell tput setaf 2)
YEL 		=	$(shell tput setaf 3)
BLU 		=	$(shell tput setaf 4)
MAG 		=	$(shell tput setaf 5)
CYA 		=	$(shell tput setaf 6)
WHI 		=	$(shell tput setaf 7)
D 			=	$(shell tput sgr0)
BEL 		=	$(shell tput bel)
CLR 		=	$(shell tput el 1)

INCLUDES	= -I ./includes/
LIBFLAGS	= `mysql_config --libs` -ljson-c
PATH_OBJ	= ./objs/
PATH_SRC	= ./src/
PATH_CONTROLLERS = $(PATH_SRC)controllers/
PATH_MODELS = $(PATH_SRC)models/
PATH_LIBS = $(PATH_SRC)libs/
PATH_APP = $(PATH_SRC)app/
PATH_UTILS = $(PATH_SRC)utils/
SRCS		=	$(PATH_APP)server.c $(PATH_APP)routes.c  $(PATH_LIBS)mongoose.c $(PATH_LIBS)mjson.c $(PATH_CONTROLLERS)book_controller.c $(PATH_MODELS)book.c $(PATH_UTILS)get_id.c $(PATH_UTILS)send_json_error.c

OBJS		= $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS)  $(LIBFLAGS)  -o $(NAME)
	@echo "$(GRE)Book Api compiled!\n$(D)"

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	@mkdir -p $(PATH_OBJ)controllers/
	@mkdir -p $(PATH_OBJ)models/
	@mkdir -p $(PATH_OBJ)libs/
	@mkdir -p $(PATH_OBJ)app/
	@mkdir -p $(PATH_OBJ)utils/
	@$(CC) $(CFLAGS) $(INCLUDES) $(LIBFLAGS) -c $< -o $@

clean: 
	@$(RM) $(PATH_OBJ)
	@echo "$(RED)Cleaning Book Api objects.$(D)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removing Book Api binary.$(D)"

re: fclean all

run: re
	./bookApi