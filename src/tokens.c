/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:07:22 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/10 15:11:05 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_quotes(char *line, int i)
{
	char	quotes;
	int		len;

	len = 0;
	quotes = line[i];
	len++;
	while (line[i + len] != quotes)
	{
		len++;
	}
	return (len + 1);
}

int ft_is_quotes(int i, char *line, int is_quote)
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

/* check the len of tokens (< or <<, len of words between quotes) */
static int	len_token(char *line, int i)
{
	int	len;
	int is_quote;

	len = 0;
	if (line[i] == '<' || line[i] == '>')
	{
		i++;
		if (line[i] == '<' || line[i] == '>')
			return (2);
		return (1);
	}
	if (line[i] == '|')
		return (1);
	if (line[i] == '\"' || line[i] == '\'')
	{	
		return (len_quotes(line, i));
	}
	while (line[i + len])
	{
		is_quote = ft_is_quotes(i + len, line, is_quote);
		if (!is_quote)
			len++;
		if ((line[i + len] == ' ' || line[i + len] == '\t') && is_quote)
			return (len);
		if (line[i + len] == '<' || line[i + len] == '>')
			return (len);
		if (line[i + len] == '|')
			return (len);
		len++;
	}
	return (len);
}

t_list	*get_tokens(char *line, t_list *token)
{
	int		len;
	int		i;
	char	*tmp;
	int		quote;

	len = 0;
	quote = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
		len = len_token(line, i);
		tmp = ft_substr(line, i, len);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		i += len;
	}
	free (line);
	return (token);
}