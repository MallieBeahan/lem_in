C = clang

NAME = libftprintf.a

FLAGS = -Wall -Wextra -Werror -c -O2

DIR_S = sources

DIR_O = temporary

HEADER = include

TEST = main.c

SOURCES = ft_parse_long_float.c ft_parse_float.c ft_default_float.c ft_bzero.c ft_parse_nbr.c ft_parse_size.c ft_parse_string.c ft_print_char_string.c ft_print_other.c ft_printf.c ft_printnbr.c ft_printnbr_logic.c ft_strlen.c help_functions.c

OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	@mkdir -p temporary
	@$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

re: fclean all

test:
	gcc -ggdb $(TEST) $(NAME)	-I $(HEADER)