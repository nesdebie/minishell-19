/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:17:54 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/23 16:00:02 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_end(int c)
{
	if (c == '_')
		return (0);
	if (ft_isalpha(c))
		return (0);
	if (ft_isdigit(c))
		return (0);
	if (c == '?')
		return (0);
	return (1);
}

int	is_non_builtin(char *str, t_shell *data, char *tmp, size_t i)
{
	char	**paths;
	char	*s;

	if (access(str, F_OK))
		return (1);
	paths = ft_get_path(data);
	if (!paths)
		return (0);
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		s = ft_strjoin(tmp, str);
		free (tmp);
		if (s && !access(s, F_OK))
		{
			ft_free_arr_content(paths, -1, s);
			return (1);
		}
		if (s)
			free(s);
	}
	ft_free_arr_content(paths, -1, NULL);
	return (0);
}
