/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/29 09:58:20 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	set_in_out(t_shell *data, t_redir *rd, t_cmnd *cmd)
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
	{
		heredoc(cmd, tmp);
		data->flag_heredoc = -1;
	}
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
			set_in_out(data, rd, cmd);
			if (ft_no_file_dir(data, cmd->in_file, rd->name, 1))
				return (1);
			else if (ft_no_file_dir(data, cmd->out_file, rd->name, 1))
				return (1);
			if (g_exit_code >= 0)
			{
				data->exit_code = g_exit_code;
				return (1);
			}
		}
		lst = lst->next;
	}
	return (0);
}
