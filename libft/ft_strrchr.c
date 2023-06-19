/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 23:05:01 by nesdebie          #+#    #+#             */
/*   Updated: 2023/03/28 23:05:08 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int c)
{
	int				i;
	unsigned char	my_c;

	my_c = (unsigned char)c;
	i = ft_strlen(str);
	while (i != -1)
	{
		if (str[i] == my_c)
			return ((char *)(&str[i]));
		i--;
	}
	return (NULL);
}
