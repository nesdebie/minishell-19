/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:53:52 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 13:59:13 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_quote_args(t_shell *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (i < data->count_cmd && data->cmd[i].cmd)
	{
		j = 0;
		while (data->cmd[i].args[j])
		{
			remove_quotes(data->cmd[i].args[j]);
			j++;
		}
		i++;
	}
	ft_supp_null_args(data);
}

int	args_counter(t_list *lst)
{
	int		count;
	char	*token;

	count = 0;
	while (lst)
	{
		token = lst->content;
		if (*token == '<' || *token == '>')
			count = count - 1;
		if (*token == '|')
			break ;
		lst = lst->next;
		count++;
	}
	return (count);
}

void	free_content(void *content)
{
	if (content)
		free (content);
}

static int	set_redir_mode(void *content)
{
	if (!ft_strncmp(content, "<<", 3))
		return (MODE_HEREDOC);
	else if (!ft_strncmp(content, ">>", 3))
		return (MODE_APPEND);
	else if (!ft_strncmp(content, ">", 2))
		return (MODE_WRITE);
	else if (!ft_strncmp(content, "<", 2))
		return (MODE_READ);
	return (0);
}

void	ft_init_file(t_list *lst, t_cmnd *cmd, t_shell *data, int idx)
{
	t_redir	*redir;

	if (!lst)
		return ;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return ;
	lst->next->content = parse_line(lst->next->content, data);
	if (!lst->next->content)
		return ;
	redir->mode = set_redir_mode(lst->content);
	redir->name = ft_strdup(lst->next->content);
	if (!redir->name)
		return (free_content(lst->next->content));
	redir->idx = -1;
	if (redir->mode > 0)
		redir->idx = idx;
	if (redir->mode == MODE_HEREDOC && data->flag_heredoc == -1)
		data->flag_heredoc = idx;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
}
