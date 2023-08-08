/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:09:51 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/08 14:34:21 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* remove quotes & join before & after quotes
** make *line points to the newly joined line
*/
static int	remove_quotes(char **line, char *mid, int start, int end)
{
	char	*head;
	char	*tail;
	char	*tmp;

	head = ft_substr(*line, 0, start);
	if (!ft_strncmp(*line, "$\"$", 3))
		tail = ft_substr(*line, end + 2, ft_strlen(*line) - end - 1);
	else
		tail = ft_substr(*line, end + 1, ft_strlen(*line) - end - 1);
	free(*line);
	*line = ft_strjoin(head, mid);
	tmp = ft_strdup(*line);
	free(*line);
	*line = ft_strjoin(tmp, tail);
	free(tmp);
	free(head);
	free(tail);
	return (0);
}

/* check if $ followed by char & if is_end is FALSE
** expand the env var. or return -1
*/
static int	dollar(char **line, int start, t_shell *data, int flag)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	while ((*line)[start + i + 1] && !(is_end((*line)[start + i + 1])))
		i++;
	tmp = ft_substr(*line, start + 1, i);
	str = ft_getenv(data->envp_list, tmp);
	if (!str)
	{
		free(tmp);
		return (-1);
	}
	free(tmp);
	if (flag)
		*line -= 1;
	remove_quotes(line, str, start, start + i);
	return (1);
}

/* loop over line, break if find closing quote
** if add $ within quotes, dollar(), if $ is not expanded,
move to next char, ignore $
 */
static	int	del_quotes(char **line, int start, t_shell *data, int flag)
{
	char	quotes;
	char	*mid;
	int		end;

	end = start + 1;
	quotes = (*line)[start];
	while ((*line)[end])
	{
		if ((*line)[end] == '$' && quotes == '\"')
		{
			if (dollar(line, end, data, flag) == -1)
				end++;
			flag = 0;
		}
		else if ((*line)[end] == quotes)
			break ;
		else
			end++;
	}
	mid = ft_substr(*line, start + 1, end - start - 1);
	if (flag)
		*line -= 1;
	remove_quotes(line, mid, start, end);
	free(mid);
	return (end - 2);
}

/* move *line after $ */
static int	dollar_quotes(char **line, int start, t_shell *data)
{
	int	i;

	i = 0;
	*line += 1;
	i = del_quotes(line, start, data, 1);
	return (i);
}


/*	
**	fonction sevant a faire la substitution du exit_code de la bonne facon
**
*/

char *get_dollar_exit_code(char *line, int i, t_shell *data)
{
	char *exit_cod2;
	char *ret;
	int j;
	int tmp;

	exit_cod2 = ft_itoa(data->exit_code);
	j = (ft_strlen(line)) + ft_strlen(exit_cod2);
	ret = calloc((j + 1), sizeof(char));
	j = 0;
	while (j != i)
	{
		ret[j] = line[j];
		j++;
	}
	tmp = 0;
	while ((size_t)tmp != ft_strlen(exit_cod2))
	{
		ret[j + tmp] = exit_cod2[tmp];
		tmp++;
	}
	j += tmp;
	tmp = 0;
	while (line[i + 2 + tmp])
	{
		ret[j] = line[i + 2 + tmp];
		tmp++;
		j++;
	}
	free(exit_cod2);
	return (ret);
}

/* param line is (*lst)->content
** parse $"" & $''
** parse "" & ''
** parse $
 */
char	*parse_line(char *line, t_shell *data, int i)
{
	(void)i;
	/*if (!line)
		return (0);
	while (line[++i])
	{
		if (line[i] == '$' && (line[i + 1] == '\'' || line[i + 1] == '\"'))
		{
			i = dollar_quotes(&line, i, data);
			if (i == -1)
				break ;
		}
		else if (line[i] == '\'' || line[i] == '\"')
		{
			i = del_quotes(&line, i, data, 0);
			if (i == -1)
				break ;
		}
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line = get_dollar_exit_code(line, i, data);
		}
		else if (line[i] == '$')
		{
			i = dollar(&line, i, data, 0);
			if (i == -1)
				break ;
		}
		printf("i : %d\nlen : %zu\nline : %s\n\n", i, ft_strlen(line), line);
	}*/
	line = substitute_variables(line, convertListToArray(data->envp_list), data->exit_code, data->envp_list);
	return (line);
}
