/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:59:17 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/03 10:51:17 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	char	nbr;

	if (nb == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	if (nb < 0 && nb > -2147483648)
	{
		ft_putchar_fd('-', fd);
		nb = nb * (-1);
	}
	if (nb < 10 && nb >= 0)
	{
		nbr = nb + '0';
		ft_putchar_fd(nbr, fd);
	}
	else if (nb > 9)
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putnbr_fd((nb % 10), fd);
	}
}
