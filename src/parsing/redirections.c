/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <nesdebie@marvin.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/25 17:10:40 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	read_heredoc(const char *end, int *fd)
{
	char	*line;
	char	*str;
	char	*tmp;

	close(fd[0]);
	str = calloc(1,1);
	while (1)
	{
		line = readline("> ");
		if (!strncmp(line, end, ft_strlen(line) + 1) && *line)
		{	
			g_exit_code = -1;
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		str = ft_strjoin(str, tmp);
		free(tmp);
		free(line);
	}
	free(line);
	if (g_exit_code == -1)
	{
		str[ft_strlen(str) - 1] = '\0';
		ft_putendl_fd(str, fd[1]);
	}
	free (str);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}
/*
static void	heredoc(t_cmnd *cmd, const char *stop,
	struct termios *attr_out, struct termios *attr_in)
{
	int				fd[2];
	pid_t			id;

	attr_out = (struct termios *)malloc(sizeof(struct termios));
	if (!attr_out)
		return ;
	attr_in = (struct termios *)malloc(sizeof(struct termios));
	if (!attr_in)
		return (free_content(attr_out));
	pipe(fd);
	tcgetattr(STDOUT_FILENO, attr_out);
	tcgetattr(STDIN_FILENO, attr_in);
	id = fork();
	signal(SIGINT, SIG_IGN);
	if (!id)
		read_heredoc(stop, fd);
	close(fd[1]);
	waitpid(id, NULL, 0);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, attr_out);
	tcsetattr(STDIN_FILENO, TCSANOW, attr_in);
	free(attr_out);
	free(attr_in);
	dup2(fd[0], cmd->in_file);
	close(fd[0]);
}*/

static void	suppress_output(void)
{
	struct termios	termios_p;

	if (tcgetattr(0, &termios_p) != 0)
		perror("Minishell: tcgetattr");
	termios_p.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios_p) != 0)
		perror("Minishell: tcsetattr");
}


void	handle_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		//ft_putendl_fd("ctrl-C", 2);
		//rl_redisplay();
	//write(1, "\n", 1);
	exit(1);
	}
}

static void	child_heredoc(char *stop, int *id)
{
	signal(SIGINT, handle_sigint_heredoc);
	close(id[0]);
	read_heredoc(stop, id);
	close(id[1]);
	exit(0);
}

static void	handle_sigint(int sig)
{
	(void)sig;
	//write(1, "\n", 1);
	//rl_on_new_line();
	//rl_replace_line("", 0);
	g_exit_code = 1;
	rl_redisplay();
	exit (1);
}

static void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		//ft_putendl_fd("ctrl-V", 2);
	//rl_redisplay();
	g_exit_code = 0;
	exit(0);
	}
}

void	signals_init(void)
{
	suppress_output();
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

static int	parent_heredoc(t_cmnd *command, int *id)
{
	signal(SIGINT, SIG_IGN);
	wait(&g_exit_code);
	close(id[1]);
	if (WIFEXITED(g_exit_code))
	{
		g_exit_code = WEXITSTATUS(g_exit_code);
		if (g_exit_code > 0)
			return (g_exit_code);
		else
			command->in_file = dup(id[0]);
		close(id[0]);
	}
	signals_init();
	g_exit_code = 0;
	return (g_exit_code);
}

int	heredoc(t_cmnd *command, char *stop)
{
	int	pid;
	int	id[2];
	int	i;

	g_exit_code = -1;
	i = pipe(id);
	if (i == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
		child_heredoc(stop, id);
	else
		return (parent_heredoc(command, id));
	return (0);
}

static void	ft_check_fd(t_cmnd *cmd, t_redir **rd, t_list *lst)
{
	*rd = lst->content;
	if ((*rd)->mode == MODE_READ || (*rd)->mode == MODE_HEREDOC)
	{
		if (cmd->in_file)
			close(cmd->in_file);
	}
	else if ((*rd)->mode == MODE_APPEND || (*rd)->mode == MODE_WRITE)
	{
		if (cmd->out_file)
			close(cmd->out_file);
	}
}

static void	set_in_out(t_redir *rd, t_cmnd *cmd)
{
	char	*tmp;

	tmp = ft_strtrim(rd->name, "\"");
	if (!tmp)
		tmp = rd->name;
	remove_quotes(tmp);
	if (rd->mode == MODE_READ)
		cmd->in_file = open(tmp, O_RDONLY);
	else if (rd->mode == MODE_WRITE)
		cmd->out_file = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (rd->mode == MODE_APPEND)
		cmd->out_file = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (rd->mode == MODE_HEREDOC)
		heredoc(cmd, tmp);
	if (tmp)
		free(tmp);
}

int	ft_redir(t_shell *data, t_cmnd *cmd, t_list *lst, int i)
{
	t_redir	*rd;

	while (lst)
	{
		if (data->count_cmd == 1)
			ft_check_fd(cmd, &rd, lst);
		else
			rd = lst->content;
		if (i == rd->idx)
		{
			set_in_out(rd, cmd);
			if (ft_no_file_dir(data, cmd->in_file, rd->name))
				return (1);
			else if (ft_no_file_dir(data, cmd->out_file, rd->name))
				return (1);
			//printf ("|%d|", g_exit_code);
			if (g_exit_code > 0)
				return (1);
		}
		lst = lst->next;
	}
	return (0);
}
