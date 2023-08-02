/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 12:12:47 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/02 12:12:53 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char		**ft_minisplit(char *str)
{
	int i;
	char **arr;

	arr = malloc(sizeof(char *) * 3);
	if (!arr)
		return (0);
	arr[0] = ft_strdup("LS_COLORS");
	if (!arr[0])
	{
		free (arr);
		return (0);
	}
	i = 0;
	while (str[i + 10])
		i++;
	arr[1] = ft_substr(str, 10, i);
	if (!arr[1])
	{
		free(arr[0]);
		free(arr);
		return (0);
	}
	arr[2] = 0;
	return (arr);
}