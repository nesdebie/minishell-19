/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 14:01:20 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/27 15:18:47 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_heredoc(const char *end, int *fd, char *str)
{
	char	*line;
	char	*tmp;

	close(fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			g_exit_code = 0;
			break ;
		}
		if (!strncmp(line, end, ft_strlen(line) + 1))
		{
			free(line);
			g_exit_code = -1;
			break ;
		}
		tmp = ft_strjoin(line, "\n");
		str = ft_strjoin(str, tmp);
		free(tmp);
		free(line);
	}
	free(line);
	return (str);
}

static void	child_heredoc(char *stop, int *id)
{
	char	*str;

	signal(SIGINT, handle_sigint_heredoc);
	close(id[0]);
	str = ft_calloc(1, 1);
	str = read_heredoc(stop, id, str);
	if (g_exit_code == -1 || g_exit_code == 0)
	{
		str[ft_strlen(str) - 1] = '\0';
		ft_putendl_fd(str, id[1]);
	}
	if (str)
		free (str);
	close(id[1]);
	exit(0);
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
