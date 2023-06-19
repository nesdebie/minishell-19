/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:05:10 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/03 10:49:12 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_in_set(char c, char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!s1 || !set)
		return ((char *)s1);
	while (char_in_set(s1[i], (char *)set) && s1[i])
		i++;
	start = i;
	i = ft_strlen(s1) - 1;
	while (char_in_set(s1[i], (char *)set) && i > start)
		i--;
	end = i;
	i = 0;
	str = malloc(sizeof(char) * (end - start + 2));
	if (!str)
		return (str);
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
