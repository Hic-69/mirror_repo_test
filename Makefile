##
## EPITECH PROJECT, 2026
## minishell1
## File description:
## Makefile
##

CC	=	clang

MAIN	=	src/main.c

SRC_FILES	=	src/prompt.c \
			src/prompt_render.c \
			src/my_str_to_array.c \
			src/parse_arg.c \
			src/str_utils.c \
			src/find_path.c \
			src/func_execute.c \
			src/env.c \
			src/easy_builtin.c \
			src/my_getnbr.c \
			src/my_strcmp.c \
			src/hardbuitin_utils.c \
			src/unsetenv_builtin.c \
			src/setenv_buitin.c \
			src/space_tabs.c \
			src/my_printf.c \
			src/separator.c \
			src/pipe.c \
			src/redirection.c \
			src/write_utils.c \
			src/git_branch.c \
			src/bad_style_test.c \

OBJ_MAIN	=	$(MAIN:.c=.o)

OBJ_SRC_FILES	=	$(SRC_FILES:.c=.o)

NAME	=	mysh

all:	$(NAME)

$(NAME):	$(OBJ_MAIN) $(OBJ_SRC_FILES)
	$(CC) -o $(NAME) $(OBJ_MAIN) $(OBJ_SRC_FILES)

clean:
	find . -type f \( \
		-name "*.o" -o \
		-name "*~" -o \
		-name "a.out" -o \
		-name "#*#" -o \
		-name "vgcore.*" -o \
		-name "*.gcda" -o \
		-name "*.gcno" \
		\) \
	-delete

tests_run:
	$(CC) --coverage -o unit_tests $(SRC_FILES) \
		tests/test_my_exec.c -lcriterion
	./unit_tests

fclean:	clean
	rm -f $(NAME)
	rm -f unit_tests

re: fclean all
