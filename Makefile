NAME		= bookApi

CC			= clang
CFLAGS		= 

RM			= rm -rf

MAKEFLAGS += -silent

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

INCLUDE 	= -I ./includes/
LIBFLAGS	= `mysql_config --cflags --libs` -ljson-c
PATH_OBJ	= ./objs/
PATH_SRC	= ./src/
PATH_CONTROLLERS = $(PATH_SRC)controllers/
PATH_MODELS = $(PATH_SRC)models/
PATH_LIBS = $(PATH_SRC)libs/
PATH_APP = $(PATH_SRC)app/
SRCS		=	$(PATH_APP)main.c $(PATH_LIBS)mongoose.c $(PATH_LIBS)mjson.c

OBJS		= $(patsubst $(PATH_SRC)%.c, $(PATH_OBJ)%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	@echo "$(GRE)Book Api compiled!\n$(D)"

$(PATH_OBJ)%.o: $(PATH_SRC)%.c
	@mkdir -p $(PATH_OBJ)
	@mkdir -p $(PATH_OBJ)controllers/
	@mkdir -p $(PATH_OBJ)models/
	@mkdir -p $(PATH_OBJ)libs/
	@mkdir -p $(PATH_OBJ)app/
	@$(CC) $(CFLAGS) $(LIBFLAGS) $(INCLUDE) -c $< -o $@

clean: 
	@$(RM) $(PATH_OBJ)
	@echo "$(RED)Cleaning Book Api objects.$(D)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removing Book Api binary.$(D)"

re: fclean all