NAME = minishell

SRCS =	./src/main.c \
		./src/frees.c \
		./src/errors.c \
		./src/tokens.c \
		./src/exit_minishell.c \
		./src/builtins_and_exec/builtins/ft_builtins.c \
		./src/builtins_and_exec/builtins/ft_cd.c \
		./src/builtins_and_exec/builtins/ft_echo.c \
		./src/builtins_and_exec/builtins/ft_env.c \
		./src/builtins_and_exec/builtins/ft_exit.c \
		./src/builtins_and_exec/builtins/ft_export.c \
		./src/builtins_and_exec/builtins/ft_export_utils.c \
		./src/builtins_and_exec/builtins/ft_pwd.c \
		./src/builtins_and_exec/builtins/ft_unset.c \
		./src/builtins_and_exec/processes_and_execve/ft_execute_utils.c \
		./src/builtins_and_exec/processes_and_execve/ft_execute.c \
		./src/builtins_and_exec/processes_and_execve/ft_process_manager.c \
		./src/builtins_and_exec/processes_and_execve/ft_process_manager_utils.c \
		./src/env_list_manager/ft_env_list.c \
		./src/env_list_manager/ft_env_list_utils.c \
		./src/env_list_manager/ft_mini_split.c \
		./src/parsing/init_cmds.c \
		./src/parsing/init_cmds_utils.c \
		./src/parsing/line_parsing.c \
		./src/parsing/line_parsing_utils.c \
		./src/parsing/parsing.c \
		./src/parsing/quotes_pipes_redir.c \
		./src/parsing/redirections.c \
		./src/parsing/substitute.c \
		./src/parsing/substitute_utils.c \
		./src/parsing/init_cmds_secure.c \
		./src/parsing/heredoc.c \
		./src/parsing/heredoc_utils.c

CC = cc

CFLAGS = -Werror -Wall -Wextra

READLINE = -lreadline -lhistory -L/Users/$(USER)/.brew/opt/readline/lib/

RM = rm -rf

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		make bonus -C ./libft
		$(CC) $(CFLAGS) $(READLINE) $(OBJS) -Llibft -lft -o $(NAME)

clean:
	make clean -C ./libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
