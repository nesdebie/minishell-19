/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:46:26 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/03 13:32:13 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	range;

	range = count * size;
	if (size != 0 && (count != range / size))
		return (0);
	if (range == 0)
		range = 1;
	ptr = malloc(range);
	if (!ptr)
		return (0);
	ft_bzero(ptr, range);
	return (ptr);
}
