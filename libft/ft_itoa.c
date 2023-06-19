/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:53:56 by nesdebie          #+#    #+#             */
/*   Updated: 2023/03/28 22:54:08 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intsize(int n)
{
	int		size;

	if (n == 0)
		return (1);
	size = 0;
	if (n == -2147483648)
		n = n + 1;
	if (n < 0)
	{
		n = n * (-1);
		size++;
	}
	while (n > 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static int	ft_setnegative(int n)
{
	if (n == -2147483648)
		n = n + 1;
	if (n < 0)
		n = n * (-1);
	return (n);
}

char	*ft_itoa(int n)
{
	char	*nb;
	int		len;
	char	tmp;
	int		t;

	t = n;
	len = ft_intsize(n);
	nb = malloc(sizeof(char) * (len + 1));
	if (!nb)
		return (0);
	nb[len] = 0;
	n = ft_setnegative(n);
	while (len-- > 0)
	{
		tmp = n % 10 + '0';
		n = n / 10;
		nb[len] = tmp;
	}
	if (t < 0)
		nb[0] = '-';
	if (t == -2147483648)
		nb[ft_intsize(t) - 1] = nb[ft_intsize(t) - 1] + 1;
	return (nb);
}
