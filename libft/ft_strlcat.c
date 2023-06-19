/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:03:52 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/06 12:49:25 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char const *src, size_t n)
{
	size_t	dest_len;
	size_t	i;
	size_t	tmp;

	if (!dest && n == 0)
		return (ft_strlen(src));
	dest_len = ft_strlen(dest);
	i = 0;
	while (src[i] && (i + dest_len + 1) < n)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (!src[i])
		dest[dest_len + i] = 0;
	tmp = i;
	i = ft_strlen(src);
	if (n == 0)
		return (i);
	if (dest_len < n)
	{
		dest[tmp + dest_len] = 0;
		return (dest_len + i);
	}
	return (n + i);
}
