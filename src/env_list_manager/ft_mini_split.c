/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/04 11:10:09 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**ft_minifree(char **arr, int i)
{
	while (--i >= 0)
		free(arr[i]);
	free(arr);
	return (0);
}

char	**ft_minisplit(char *str)
{
	int		i;
	int		j;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (0);
	while (str[i] && str[i] != '=')
		i++;
	arr[0] = ft_substr(str, 0, i);
	if (!arr[0])
		return (ft_minifree(arr, 0));
	i++;
	while (str[i + j])
		j++;
	arr[1] = ft_substr(str, i, j);
	if (!arr[1])
		return (ft_minifree(arr, 1));
	arr[2] = 0;
	return (arr);
}
