/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:01:52 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 12:49:29 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_read_lst(void *lst)
{
	t_env	*ls_env_node;

	ls_env_node = (t_env *)(lst);
	if (ls_env_node->name && ls_env_node->equal)
	{
		ft_putstr_fd(ls_env_node->name, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		if (ls_env_node->value && ft_strlen(ls_env_node->value))
			ft_putstr_fd(ls_env_node->value, STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

int	ft_env(t_list **is_envp_list)
{
	if (!is_envp_list)
		return (1);
	ft_lstiter(*is_envp_list, &ft_read_lst);
	return (0);
}
