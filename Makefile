.PHONY: clean, fclean, re

.SUFFIXES:

#~~~~~~~~~~~~~~~~COLORS~~~~~~~~~~~~~~

FONT_NOIR = \033[40m
BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
PINK = \033[35m
CYAN = \033[36m
GREY = \033[37m

NORMAL = \033[0m

#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

NAME = ft_ls

LIB_PATH = libft/

CC = gcc

SRCC =	ft_ls.c ft_file.c ft_dir.c ft_error.c ft_flag.c ft_print.c ft_sort.c ft_tab.c	\
		ft_data_rights.c ft_data_type.c ft_data_size.c ft_data_time.c ft_data_id.c		\
		ft_padding.c

SRCO =	ft_ls.o ft_file.o ft_dir.o ft_error.o ft_flag.o ft_print.o ft_sort.o ft_tab.o	\
		ft_data_rights.o ft_data_type.o ft_data_size.o ft_data_time.o ft_data_id.o		\
		ft_padding.o

LIB_SRC = libft/libft.a

CFLAGS = -Wall -Wextra -Werror

all: lib $(NAME)

#Display rules~~~~~~~~~~~~

cleared:
	@ echo "$(YELLOW)$(FONT_NOIR)$(NAME) : $(RED).o files destruction\t\t[$(GREEN)\xe2\x9c\x94$(RED)]$(NORMAL)"

full_clear:
	@ echo "$(YELLOW)$(FONT_NOIR)$(NAME) : $(RED)executable file destruction\t[$(GREEN)\xe2\x9c\x94$(RED)]$(NORMAL)"

re_init:
	@ echo "$(BLUE)$(FONT_NOIR)Reseting $(NAME) }~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(NORMAL)"

re_done:
	@ echo "$(BLUE)$(FONT_NOIR)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{ Reset Complete[$(GREEN)\xe2\x9c\x94$(BLUE)]$(NORMAL)"

#~~~~~RULES FOR GIT~~~~~~~~

gadd:
	@ echo "$(BLUE)$(FONT_NOIR)Adding modified files }~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~$(NORMAL)"
	@ git add $(shell git status | grep modified | rev | cut -d' ' -f1 | rev | tr '\n' ' ' | rev | cut -d' ' -f2- | rev)
	@ echo "$(PINK)$(FONT_NOIR)$(shell git status | grep modified | tr -s ' ' | cut -d' ' -f2 | tr ' ' '\n')\t$(PINK)[$(GREEN)\xe2\x9c\x94$(PINK)]$(NORMAL)"
	@ echo "$(BLUE)$(FONT_NOIR)~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{ Adding Complete[$(GREEN)\xe2\x9c\x94$(BLUE)]$(NORMAL)"

commit:
	@ echo "$(PINK)$(FONT_NOIR)commit changes \t\t[$(GREEN)\xe2\x9c\x94$(PINK)]$(NORMAL)"
	@ echo "$(PINK)$(FONT_NOIR)$(shell git commit -m "automatic commit from Makefile" | grep files)$(NORMAL)"

#~~~~~~~~~~~~~~~~~~~~~~~~~

lib:
	@ make -C $(LIB_PATH)

lib_re:
	@ make -C $(LIB_PATH) re

%.o: %.c
	@ $(CC) $(CFLAGS) -c $<

$(NAME): $(SRCO) ft_ls.h
	@ echo "$(PINK)$(FONT_NOIR).o successfully created\t\t\t[$(GREEN)\xe2\x9c\x94$(PINK)]$(NORMAL)"
	@ $(CC) $(CFLAGS) -o $(NAME) $(SRCO) $(LIB_SRC)
	@ echo "$(PINK)$(FONT_NOIR)Compilation of $(NAME)\t\t\t[$(GREEN)\xe2\x9c\x94$(PINK)]$(NORMAL)"

clean: cleared
	@ make -C $(LIB_PATH) clean
	@ rm -f $(SRCO)

fclean: full_clear clean
	@ make -C $(LIB_PATH) fclean
	@ rm -f $(NAME)

re: re_init fclean lib_re $(NAME) re_done
