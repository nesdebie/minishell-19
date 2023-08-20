/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:09:51 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/20 16:57:28 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void removeQuotes(char *input)
{
	int length = ft_strlen(input);
	int i, j;
	for (i = 0, j = 0; i < length; i++)
	{
		if (input[i] && (input[i] == '\'' || input[i] == '\"'))
		{
			int quoteType = input[i];
			int endQuoteIndex = -1;
			for (int k = i + 1; k < length; k++)
			{
				if (input[k] == quoteType)
				{
					endQuoteIndex = k;
					break;
				}
			}
			if (endQuoteIndex != -1)
			{
				for (int k = i + 1; k < endQuoteIndex; k++)
				{
					input[j++] = input[k];
				}
				i = endQuoteIndex;
			}
			else
			{
				input[j++] = input[i];
			}
		}
		else
		{
			input[j++] = input[i];
		}
	}
	input[j] = '\0';
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
