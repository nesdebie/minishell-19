/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:09:51 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/22 16:23:41 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes2(char *input, int i[3], int length, int quote_type[2])
{
	quote_type[0] = input[i[0]];
	quote_type[1] = -1;
	i[2] = i[0] + 1;
	while (i[2] < length)
	{
		if (input[i[2]] == quote_type[0])
		{
			quote_type[1] = i[2];
			break ;
		}
		i[2]++;
	}
	if (quote_type[1] != -1)
	{
		i[2] = i[0] + 1;
		while (i[2] < quote_type[1])
		{
			input[i[1]++] = input[i[2]];
			i[2]++;
		}
		i[0] = quote_type[1];
	}
	else
		input[i[1]++] = input[i[1]];
}

void	remove_quotes(char *input)
{
	int	length;
	int	i[3];
	int	quote_type[2];

	quote_type[0] = 0;
	length = ft_strlen(input);
	ft_bzero(i, 8);
	while (i[0] < length)
	{
		if (input[i[0]] && (input[i[0]] == '\'' || input[i[0]] == '\"'))
			remove_quotes2(input, i, length, quote_type);
		else
			input[i[1]++] = input[i[0]];
		i[0]++;
	}
	input[i[1]] = '\0';
}

char	*parse_line(char *line, t_shell *data)
{
	char	*ret;

	if (!line)
		return (0);
	ret = substitute_variables(line, data->exit_code, data->envp_list);
	if (line)
		free(line);
	return (ret);
}
