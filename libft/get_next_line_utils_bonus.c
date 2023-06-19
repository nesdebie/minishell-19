/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:53:06 by nesdebie          #+#    #+#             */
/*   Updated: 2023/05/19 13:01:11 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoingnl(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;

	j = 0;
	i = ft_strlen(s1);
	result = (char *)malloc((i + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (ft_free(s1, 0));
	while (s1[j])
	{
		result[j] = s1[j];
		j++;
	}
	i = 0;
	while (s2[i])
	{
		result[j] = s2[i];
		i++;
		j++;
	}
	result[j] = 0;
	free(s1);
	return (result);
}
