.PHONY: clean, fclean, re

.SUFFIXES:

NAME = ft_ls

CC = gcc

SRCC = ft_ls.c ft_file.c ft_data.c ft_data_2.c ft_dir.c ft_error.c ft_flag.c ft_print.c ft_sort.c ft_tab.c

SRCO = ft_ls.o ft_file.o ft_data.o ft_data_2.o ft_dir.o ft_error.o ft_flag.o ft_print.o ft_sort.o ft_tab.o

LIB_SRC = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

lib:
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $(SRCC)

$(NAME): $(SRCO)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCO) $(LIB_SRC)

clean:
	make -C ./libft clean
	rm -f $(SRCO)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
