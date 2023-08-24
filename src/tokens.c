/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:07:22 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/24 13:54:30 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_quotes(int i, char *line, int is_quote)
{
	if (line[i] == '\'' && line[i] != '\"')
	{
		if (is_quote == 0)
			is_quote = '\'';
		else
			is_quote = 0;
	}
	if (line[i] == '\"' && line[i] != '\'')
	{
		if (is_quote == 0)
			is_quote = '\"';
		else
			is_quote = 0;
	}
	return (is_quote);
}

static int	skip_quotes(char *s, int i)
{
	char	quote;

	quote = s[i];
	i++;
	while (s[i])
	{
		if (s[i] == quote)
			return (i);
		i++;
	}
	return (i);
}

static int	len_token(char *s, int i)
{
	if (s[i] == '|')
		return (i + 1);
	if (s[i] == '<' || s[i] == '>')
	{
		i++;
		if (s[i] == '<' || s[i] == '>')
			return (i + 1);
		return (i);
	}
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = skip_quotes(s, i);
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '|')
			return (i);
		if ((s[i] == '<' || s[i] == '>') && s[i] != s[i + 1])
			return (i);
		if ((s[i] == '<' && s[i + 1] == '<')
			|| (s[i] == '>' && s[i + 1] == '>'))
			return (i);
		i++;
	}
	return (i);
}

t_list	*get_tokens(char *line, t_list *token)
{
	int		len;
	int		i;
	char	*tmp;

	len = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		len = len_token(line, i);
		tmp = ft_substr(line, i, len - i);
		if (!tmp)
			return (token);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		i = len;
	}
	free (line);
	return (token);
}
