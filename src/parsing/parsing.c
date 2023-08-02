/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:10:28 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/02 10:56:35 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_cmd(t_list *lst, t_shell *mini)
{
	int		i;
	char	*token;

	i = 0;
	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (*token == '|')
		{
			i++;
			lst = lst->next;
		}
		else
			init_each_command(&lst, mini, i);
	}
	return (0);
}

static int	check_tokens(t_list *lst)
{
	char	*token;

	while (lst)
	{
		token = lst->content;
		if (!token)
			return (1);
		if (!ft_strncmp(token, ">>", 2) || !ft_strncmp(token, "<<", 2))
		{
			lst = lst->next;
			token = lst->content;
			if (*token == '|')
				return (0);
		}
		else if (*token == '>' | *token == '<')
		{
			lst = lst->next;
			token = lst->content;
			if (*token == '|')
				return (0);
		}
		else
			lst = lst -> next;
	}
	return (1);
}

static char	*open_pipe(char *line)
{	
	char	*tmp;
	char	*nl;

	tmp = NULL;
	nl = readline("> ");
	while (!ft_strlen(nl))
	{
		free(nl);
		nl = readline("> ");
	}
	tmp = ft_strdup(line);
	if (line)
		free (line);
	if (ft_strlen(nl))
		line = ft_strjoin(tmp, nl);
	if (tmp)
		free (tmp);
	if (nl)
		free (nl);
	if (ft_strlen(line) > 1 && line[ft_strlen(line) - 1] == '|')
		line = open_pipe(line);
	return (line);
}

int	parser(char *line, t_shell *shell)
{
	t_list	*tokens;

	tokens = NULL;
	if (ft_strlen(line) > 1 && line[ft_strlen(line) - 1] == '|')
		line = open_pipe(line);
	add_history(line);
	shell->count_cmd = pre_parse(line, shell);
	if (shell->count_cmd == -1)
		return (1);
	tokens = get_tokens(line, tokens);
	if (!check_tokens(tokens))
	{
		ft_lstclear(&tokens, free);
		return (1);
	}
	shell->cmd = malloc(sizeof(t_cmnd) * shell->count_cmd);
	if (!shell->count_cmd)
		return (1);
	ft_memset(shell->cmd, '\0', sizeof(t_cmnd) * shell->count_cmd);
	init_cmd(tokens, shell);
	ft_lstclear(&tokens, free);
	return (0);
}
