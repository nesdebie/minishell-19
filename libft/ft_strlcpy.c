/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:04:02 by nesdebie          #+#    #+#             */
/*   Updated: 2023/03/28 23:04:08 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n - 1 && n != 0)
	{
		dest[i] = src[i];
		i++;
	}
	if (n != 0)
		dest[i] = 0;
	return (ft_strlen(src));
}
