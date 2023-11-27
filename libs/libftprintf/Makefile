CC = cc
CFLAGS = -Wextra -Werror -Wall
INCLUDES = -I.
DEPS = ft_printf.h
FILES = ft_printf \
					ft_putnbr_base \
					ft_print_char \
					ft_print_str \
					ft_print_decimal \
					ft_print_u \
					ft_print_hex_l \
					ft_print_hex_u \
					ft_print_p \
					ft_print_format \
					ft_putchar_fd \
					ft_putstr_fd \
					ft_strlen

OBJ = $(FILES:%=%.o)

NAME = libftprintf.a

$(NAME): $(OBJ)
	ar -rc $@ $^

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: all clean fclean re
