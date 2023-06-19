/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:10:45 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/03 10:52:01 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*setret(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	if (src < dest)
	{
		i = n;
		while (i > 0 && (dest || src))
		{
			i--;
			d[i] = s[i];
		}
	}
	else if (src > dest)
	{
		while (i < n && (dest || src))
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (src == dest)
		return (dest);
	return ((char *)setret(dest, src, n));
}
