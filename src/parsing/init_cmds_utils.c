/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:53:52 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/20 16:57:33 by nesdebie         ###   ########.fr       */
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
			removeQuotes(data->cmd[i].args[j]);
			j++;
		}
		i++;
	}
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

static void	free_content(void *content)
{
	if (content)
		free (content);
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
	if (!ft_strncmp(lst->content, "<<", 3))
		redir->mode = MODE_HEREDOC;
	else if (!ft_strncmp(lst->content, ">>", 3))
		redir->mode = MODE_APPEND;
	else if (!ft_strncmp(lst->content, ">", 2))
		redir->mode = MODE_WRITE;
	else if (!ft_strncmp(lst->content, "<", 2))
		redir->mode = MODE_READ;
	redir->name = ft_strdup(lst->next->content);
	if (!redir->name)
		return (free_content(lst->next->content));
	redir->idx = -1;
	if (redir->mode > 0)
		redir->idx = idx;
	ft_lstadd_back(&cmd->redir, ft_lstnew(redir));
}
