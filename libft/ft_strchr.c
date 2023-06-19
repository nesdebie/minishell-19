/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:03:02 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/03 10:50:46 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char const *str, int c)
{
	char	my_c;

	my_c = (char)c;
	while (*str)
	{
		if (*str == my_c)
			return ((char *)str);
		str++;
	}
	if (!my_c)
		return ((char *)str);
	return (NULL);
}
