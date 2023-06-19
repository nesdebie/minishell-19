/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:42:34 by nesdebie          #+#    #+#             */
/*   Updated: 2023/04/06 17:42:36 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*dest;

	dest = NULL;
	while (lst)
	{
		new = ft_lstnew((*f)(lst->content));
		if (new)
			ft_lstadd_back(&dest, new);
		else
		{
			ft_lstclear(&dest, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (dest);
}
