/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_manager_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:56:57 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 10:39:19 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	heredoc_excep(t_list *lst, int i)
{
	t_redir	*redir;
	int		j;

	j = 1;
	while (lst)
	{
		redir = lst->content;
		if (j == i && redir->mode == MODE_HEREDOC)
			return (1);
		lst = lst->next;
		j++;
	}
	return (0);
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
		dup2(data->cmd[i].out_file, STDOUT_FILENO);
		close(data->cmd[i].out_file);
	}
	else if (i < data->count_cmd - 1)
		dup2(fd[i][1], STDOUT_FILENO);
	if (data->cmd[i].in_file)
	{
		dup2(data->cmd[i].in_file, STDIN_FILENO);
		close(data->cmd[i].in_file);
	}
	else if (i)
	{
		if (heredoc_excep(data->cmd->redir, i))
			return ;
		dup2(fd[i - 1][0], STDIN_FILENO);
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
