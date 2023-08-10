/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nedebies <nedebies@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:09:51 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/10 20:42:31 by nedebies         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void removeQuotes(char *input)
{
    int length = strlen(input);
    int i, j;

    for (i = 0, j = 0; i < length; i++)
	{
        if (input[i] == '\'' || input[i] == '\"')
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
	//printf("INPUT VALUE [%s]\n", input);
}


// ceci est une fonction destinée a supprimer les "" ou les ''


// char	*remove_empty_quotes(char	*str)
// {
// 	char	*new_str;
// 	int		single_quote;
// 	int		dubble_quote;
// 	int		j;
// 	int		i;

// 	new_str = (char *)malloc(ft_strlen(str) + 1);
// 	j = 0;
// 	i = 0;
// 	while ((size_t)i < ft_strlen(str))
// 	{
// 		if (str[i] == '"' && str[i + 1] == '"')
// 		{
// 			i++;
// 		}
// 		else if (str[i] == '\'' && str[i + 1] == '\'')
// 		{
// 			i++;
// 		}
// 		else
// 		{
// 			new_str[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	new_str[j] = '\0';
// 	free(str);
// 	j = 0;
// 	single_quote = 0;
// 	dubble_quote = 0;
// 	while (new_str[j] != '\0')
// 	{
// 		if (new_str[j] == '\'' && dubble_quote != 1)
// 		{
// 			if (single_quote == 0)
// 				single_quote = 1;
// 			else
// 				single_quote = 0;
// 		}
// 		if (new_str[j] == '\"' && single_quote != 1)
// 		{
// 			if (dubble_quote == 0)
// 				dubble_quote = 1;
// 			else
// 				dubble_quote = 0;
// 		}
// 		j++;
// 	}
// 	if (dubble_quote == 1 || single_quote == 1)
// 	{
// 		ft_putstr_fd("parser error : alone standing quote\n", 2);
// 		free(new_str);
// 		return (NULL);
// 	}
// 	return (new_str);
// }

// parsing de la substitution 

char	*parse_line(char *line, t_shell *data, int i)
{
	(void)i;
	char	*ret;

	ret = substitute_variables(line, data->exit_code, data->envp_list);
	free(line);
	return (ret);
}
