/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:07:22 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/20 15:17:09 by nesdebie         ###   ########.fr       */
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

/* check the len of tokens (< or <<, len of words between quotes) */
static int	len_token(char *s, int i, int len, int is_quote)
{
	if (s[i] == '<' || s[i] == '>')
	{
		i++;
		if (s[i] == '<' || s[i] == '>')
			return (2);
		return (1);
	}
	if (s[i] == '|')
		return (1);
	if (s[i] == '\"' || s[i] == '\'')
	{
		return (len_quotes(s, i));
	}
	while (s[i + ++len])
	{
		is_quote = ft_is_quotes(i + len, s, is_quote);
		if (!is_quote)
			len++;
		if ((s[i + len] == ' ' || s[i + len] == '\t') && is_quote)
			return (len);
		if (s[i + len] == '<' || s[i + len] == '>' || s[i + len] == '|')
			return (len);
	}
	return (len);
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
		len = len_token(line, i, -1, 1);
		tmp = ft_substr(line, i, len);
		ft_lstadd_back(&token, ft_lstnew(tmp));
		i += len;
	}
	free (line);
	return (token);
}
