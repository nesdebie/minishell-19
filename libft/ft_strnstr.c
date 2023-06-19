/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:50 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/06 12:49:40 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char const *str, char const *tofind, size_t n)
{
	size_t	i;
	size_t	j;

	if (!str && n == 0)
		return (0);
	i = 0;
	j = ft_strlen(tofind);
	if (!j)
		return ((char *)str);
	if (!ft_strlen(str))
		return (0);
	while (i < n)
	{
		if (!ft_strncmp((char *)&str[i], tofind, j))
		{
			if (i + j > n)
				return (0);
			return ((char *)&str[i]);
		}
		i++;
	}
	return (0);
}
