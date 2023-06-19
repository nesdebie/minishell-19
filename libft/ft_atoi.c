/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:44:26 by nesdebie          #+#    #+#             */
/*   Updated: 2023/03/28 22:45:19 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isovermaxmin(int sign)
{
	if (sign == 1)
		return (-1);
	return (0);
}

int	ft_atoi(char const *str)
{
	int		i;
	int		sign;
	long	result;
	int		cpt;

	result = 0;
	i = 0;
	sign = 1;
	cpt = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		result = result * 10 + str[i] - 48;
		if (result < 0 || ++cpt > 19)
			return (ft_isovermaxmin(sign));
		i++;
	}
	return ((int)(sign * result));
}
