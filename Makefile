NAME = minishell

SRCS =	./src/main.c \
		./src/frees.c \
		./src/errors.c \
		./src/signal.c \
		./src/builtins_and_executables/builtins/ft_builtins.c \
		./src/builtins_and_executables/builtins/ft_cd.c \
		./src/builtins_and_executables/builtins/ft_echo.c \
		./src/builtins_and_executables/builtins/ft_env.c \
		./src/builtins_and_executables/builtins/ft_exit.c \
		./src/builtins_and_executables/builtins/ft_export.c \
		./src/builtins_and_executables/builtins/ft_pwd.c \
		./src/builtins_and_executables/builtins/ft_unset.c \
		./src/builtins_and_executables/processes_and_execve/ft_execute_utils.c \
		./src/builtins_and_executables/processes_and_execve/ft_execute.c \
		./src/builtins_and_executables/processes_and_execve/ft_process_manager.c \		
		./src/env_list_manager/ft_env_list_create.c \
		./src/env_list_manager/ft_env_list_sort.c \
		./src/parsing/init_cmds.c \
		./src/parsing/line_parsing.c \
		./src/parsing/parsing.c \
		./src/parsing/quotes_pipes_redir.c \
		./src/parsing/redirections.c


CC = cc

CFLAGS = -Werror -Wall -Wextra -g

RDL_PATH = -L/Users/$(USER)/.brew/opt/readline/lib/

RDL_HISTORY_PATH = -L/Users/$(USER)/.brew/opt/readline/lib/

RDL = -lreadline.8.1 $(RDL_PATH)

RDL_HISTORY = -lhistory.8.1 $(RDL_HISTORY_PATH)

READLINE = $(RDL) $(RDL_HISTORY)

RM = rm -rf

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		make re -C ./libft
		$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

clean:
	make clean -C ./libft
	rm -f $(OBJS)


fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)


re: fclean all

.PHONY:	all clean fclean re
