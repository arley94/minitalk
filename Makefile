# NAMES
NAME_S = server
NAME_C = client
NAME_S_BONUS = server_bonus
NAME_C_BONUS = client_bonus

# LIBS
LIBS_DIR = libs/
FT_DIR = libft/libft.a
FTPRINTF_DIR = libftprintf/libftprintf.a
LIBFT = $(addprefix $(LIBS_DIR), $(FT_DIR))
LIBFTPRINTF = $(addprefix $(LIBS_DIR), $(FTPRINTF_DIR))

# SOURCE FILES
SRC_DIR = src/
SRC_S_FILES = server.c utils.c
SRC_C_FILES = client.c utils.c
SRC_S_FILES_BONUS = server_bonus.c utils_bonus.c
SRC_C_FILES_BONUS = client_bonus.c utils_bonus.c
SRC_S = $(addprefix $(SRC_DIR), $(SRC_S_FILES))
SRC_C = $(addprefix $(SRC_DIR), $(SRC_C_FILES))
SRC_S_BONUS = $(addprefix $(SRC_DIR), $(SRC_S_FILES_BONUS))
SRC_C_BONUS = $(addprefix $(SRC_DIR), $(SRC_C_FILES_BONUS))

# OBJECT FILES
OBJ_S = ${SRC_S:.c=.o}
OBJ_C = ${SRC_C:.c=.o}
OBJ_S_BONUS = ${SRC_S_BONUS:.c=.o}
OBJ_C_BONUS = ${SRC_C_BONUS:.c=.o}

# COMPILER OPTIONS
CC		= gcc
FLAGS	= -Wall -Werror -Wextra
INCLUDE = -I include
RM		= rm -f

# COLORS
RED		=	\033[91;1m
GREEN	=	\033[92;1m
YELLOW	=	\033[93;1m
BLUE	=	\033[94;1m
PINK	=	\033[95;1m
CLEAR	=	\033[0m

# MAKEFILE RULES
all:	$(NAME_S) $(NAME_C)

$(NAME_S):	$(OBJ_S)
	@make -C libs/libft
	@make -C libs/libftprintf
	@echo "$(PINK)Compiling the Server.$(CLEAR)"
	$(CC) $(FLAGS) $(OBJ_S) $(INCLUDE) $(LIBFT) $(LIBFTPRINTF) -o $(NAME_S) 
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"


$(NAME_C):	$(OBJ_C)
	@make -C libs/libft
	@make -C libs/libftprintf
	@echo "$(PINK)Compiling the Client.$(CLEAR)"
	$(CC) $(FLAGS) $(OBJ_C) $(INCLUDE) $(LIBFT) $(LIBFTPRINTF) -o $(NAME_C)
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

bonus:	$(NAME_S_BONUS) $(NAME_C_BONUS)

$(NAME_S_BONUS):	$(OBJ_S_BONUS)
	@make -C libs/libft
	@make -C libs/libftprintf
	@echo "$(PINK)Compiling the Server.$(CLEAR)"
	$(CC) $(FLAGS) $(OBJ_S_BONUS) $(INCLUDE) $(LIBFT) $(LIBFTPRINTF) -o $(NAME_S_BONUS)
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"


$(NAME_C_BONUS):	$(OBJ_C_BONUS)
	@make -C libs/libft
	@make -C libs/libftprintf
	@echo "$(PINK)Compiling the Client.$(CLEAR)"
	$(CC) $(FLAGS) $(OBJ_C_BONUS) $(INCLUDE) $(LIBFT) $(LIBFTPRINTF) -o $(NAME_C_BONUS)
	@echo "$(GREEN)[OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	@echo "$(PINK)Removing compiled files.$(CLEAR)"
	@make clean -C libs/libft
	@make clean -C libs/libftprintf
	$(RM) $(OBJ_S)
	$(RM) $(OBJ_C)
	$(RM) $(OBJ_S_BONUS)
	$(RM) $(OBJ_C_BONUS)
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@make fclean -C libs/libft
	@make fclean -C libs/libftprintf
	$(RM) $(NAME_S)
	$(RM) $(NAME_C)
	$(RM) $(NAME_S_BONUS)
	$(RM) $(NAME_C_BONUS)
	@echo "$(GREEN)Exec. files removed correctly\nSuccess!$(CLEAR)"

re: fclean all

.PHONY:		all bonus clean fclean re