/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:09:51 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/10 11:13:25 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// ceci est une fonction destinée a supprimer les "" ou les ''

char* remove_empty_quotes(char* str)
{
    int len = strlen(str);
    char* new_str = (char*)malloc(len+1);
	int single_quote;
	int dubble_quote;
    int j = 0;

    for (int i = 0; i < len; i++)
	{
        if (str[i] == '"' && str[i+1] == '"')
		{
            i++;
        }
		else if (str[i] == '\'' && str[i+1] == '\'')
		{
            i++;
        }
		else
		{
            new_str[j] = str[i];
            j++;
        }
    }
    new_str[j] = '\0';
	free(str);
	j = 0;
	single_quote = 0;
	dubble_quote = 0;
	while (new_str[j] != '\0')
	{
		if (new_str[j] == '\'' && dubble_quote != 1)
		{
			if (single_quote == 0)
				single_quote = 1;
			else
				single_quote = 0;
		}
		if (new_str[j] == '\"' && single_quote != 1)
		{
			if (dubble_quote == 0)
				dubble_quote = 1;
			else
				dubble_quote = 0;
		}
		j++;
	}
	if (dubble_quote == 1 || single_quote == 1)
	{
		ft_putstr_fd("parser error : alone standing quote\n", 2);
		free(new_str);
		return (NULL);
	}
    return new_str;
}

// parsing de la substitution 

char	*parse_line(char *line, t_shell *data, int i)
{
	(void)i;
	char	*ret;

	ret = substitute_variables(line, data->exit_code, data->envp_list);
	free(line);
	return (ret);
}
