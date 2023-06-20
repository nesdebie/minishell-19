/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_pipes_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:11:06 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/20 11:22:37 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*print_quotes_er(char quotes)
{
	if (quotes == '\'')
		ft_putendl_fd("prompt: unclosed single quote error", 2);
	else
		ft_putendl_fd("prompt: unclosed double quote error", 2);
	return (0);
}

static char	*print_er(char *error)
{
	ft_putstr_fd("prompt: syntax error near unexpected token ", 2);
	ft_putendl_fd(error, 2);
	return (0);
}

/* check if line is empty or if line is only made up of spaces */
static	int	check_empty_line(char *line)
{
	if (!line)
	{
		free(line);
		return (1);
	}
	while ((*line == ' ' || *line == '\t') && *line)
		line++;
	if (*line == '|')
	{
		print_er("`|'");
		return (259);
	}
	if (!line)
		return (1);
	return (0);
}

static char	*ft_check_sign(char *line, char quotes,	int *cnt, t_shell *shell)
{
	if (*line == '\'' || *line == '\"')
	{
		quotes = *line;
		line++;
		while (*line != quotes && *line)
			line++;
		if (*line != quotes)
			return (print_quotes_er(quotes));
	}
	if (*line == '|')
	{
		(*cnt)++;
		line++;
		while (*line == ' ')
			line++;
		if (*line == '|')
		{
			print_er("`|'");
			shell->exit_code = 258;
			return (0);
		}
	}
	else
		line++;
	return (line);
}

int	pre_parse(char *line, t_shell *shell)
{
	char	quotes;
	int		count_cmd;
	int		err;

	count_cmd = 1;
	err = check_empty_line(line);
	if (err)
	{
		shell->exit_code = err - 1;
		return (-1);
	}
	while (*line)
	{
		quotes = '0';
		line = ft_check_sign(line, quotes, &count_cmd, shell);
		if (!line)
			return (-1);
	}
	if (*(line - 1) == '<' || *(line - 1) == '>')
	{
		print_er("`newline'");
		shell->exit_code = 258;
		return (-1);
	}
	return (count_cmd);
}
