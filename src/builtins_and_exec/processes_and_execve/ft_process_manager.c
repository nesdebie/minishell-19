/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_manager.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:58:32 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/27 14:25:45 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	process(t_shell *data, char **envp, int i, int **fd)
{
	signal(SIGQUIT, SIG_DFL);
	if (ft_redir(data, &data->cmd[i], data->cmd->redir, i) || g_exit_code == 1)
		exit(data->exit_code);
	ft_dup_fd(i, fd, data);
	if (i < data->flag_heredoc)
		exit(EXIT_SUCCESS);
	if (is_builtin(data, i))
		execute_builtin(data, i);
	else if (execve(data->cmd[i].cmd, data->cmd[i].args, envp) == -1)
		exec_error(data, i);
	exit(data->exit_code);
}

static int	ft_create_pipe(int **fd, t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			ft_putendl_fd("error in pipe", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	ft_wait_process(pid_t	*id, t_shell *data)
{
	int		i;
	int		ret;
	int		prev;

	prev = 0;
	i = 0;
	while (i < data->count_cmd)
	{
		waitpid(id[i], &ret, 0);
		data->exit_code = set_exit_status(ret);
		if (data->exit_code == 2 && i > 0 && prev > 0)
			data->exit_code = 1;
		if (i == 0 || data->exit_code)
			prev = data->exit_code;
		i++;
	}
}

static int	**ft_malloc_fd(t_shell *data, int i)
{
	int	**fd;

	fd = malloc(sizeof(int *) * (data->count_cmd - 1));
	if (!fd)
		return (0);
	while (++i < data->count_cmd - 1)
	{
		fd[i] = malloc(sizeof(int ) * 2);
		if (!fd[i])
		{
			while (--i >= 0)
				free(fd[i]);
			free(fd);
			return (0);
		}
	}
	if ((ft_create_pipe(fd, data)) || !fd)
		return (0);
	return (fd);
}

int	ft_process_manager(pid_t	*id, t_shell *data, char **envp, int i)
{
	int		**fd;

	if (is_builtin(data, 0) == NO_FORKS && data->count_cmd == 1)
		return (execute_builtin(data, 0));
	fd = ft_malloc_fd(data, i);
	if (!fd)
		return (1);
	i = -1;
	while (++i < data->count_cmd)
	{
		id[i] = fork();
		if (id[i] == -1)
			exit(EXIT_FAILURE);
		if (!id[i])
			process(data, envp, i, fd);
	}
	ft_close_fd(fd, data);
	ft_wait_process(id, data);
	return (0);
}
