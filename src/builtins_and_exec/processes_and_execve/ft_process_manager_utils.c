/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_manager_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:56:57 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 14:58:53 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exec_error(t_shell *data, int i)
{
	if (errno == EACCES)
	{
		ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
		ft_putstr_fd(data->cmd[i].cmd, 2);
		if (ft_isinset('/', data->cmd[i].cmd))
		{
			ft_putendl_fd(": is a directory", 2);
			data->exit_code = 126;
		}
		else
		{
			ft_putendl_fd(": command not found", 2);
			data->exit_code = 127;
		}
	}
}

void	set_heredocflag(t_shell *data, t_list *lst, pid_t *id, int i)
{
	t_redir	*rd;

	rd = lst->content;
	while (lst)
	{
		rd = lst->content;
		if (rd->idx > i)
		{
			if (rd->mode == MODE_HEREDOC)
			{
				data->flag_heredoc = rd->idx;
				break ;
			}
		}
		lst = lst->next;
	}
	if (lst)
		data->flag_heredoc = rd->idx;
	else
		data->flag_heredoc = -1;
	waitpid(id[i], &g_exit_code, 0);
}

void	ft_close_fd(int *fd[2], t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	i = 0;
	while (i < data->count_cmd - 1)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}

void	ft_dup_fd(int i, int **fd, t_shell *data)
{
	if (data->cmd[i].out_file)
	{
		if (dup2(data->cmd[i].out_file, STDOUT_FILENO) == -1)
			exit (EXIT_FAILURE);
		close(data->cmd[i].out_file);
	}
	else if (i < data->count_cmd - 1)
		if (dup2(fd[i][1], STDOUT_FILENO) == -1)
			exit (EXIT_FAILURE);
	if (data->cmd[i].in_file)
	{
		if (dup2(data->cmd[i].in_file, STDIN_FILENO) == -1)
			exit (EXIT_FAILURE);
		close(data->cmd[i].in_file);
	}
	else if (i)
	{
		if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
			exit (EXIT_FAILURE);
	}
	ft_close_fd(fd, data);
}

int	set_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		exit_status = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
	{
		if (WTERMSIG(exit_status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
		exit_status = 128 + WTERMSIG(exit_status);
	}
	return (exit_status);
}
