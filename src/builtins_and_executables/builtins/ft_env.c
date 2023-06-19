/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:01:52 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/19 12:38:39 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_read_lst(void *lst)
{
	t_env	*ls_env_node;

	ls_env_node = (t_env *)(lst);
	if (ls_env_node->name && ls_env_node->value)
	{
		ft_putendl_fd(ls_env_node->name, STDOUT_FILENO);
		ft_putendl_fd(ls_env_node->value, STDOUT_FILENO);
	}
}

int	ft_env(t_list **is_envp_list)
{
	if (!is_envp_list)
		return (1);
	ft_lstiter(*is_envp_list, &ft_read_lst);
	return (0);
}

char	*get_name_env(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	temp = ft_substr(s, 0, i);
	return (temp);
}

char	*get_value_env(char *s)
{
	int		i;
	char	*temp;

	temp = NULL;
	i = 0;
	if (!s)
	{
		temp = (char *)ft_calloc(1, sizeof(char));
		return (temp);
	}
	while (s[i] != '=' && s[i])
		i++;
	if (s[i] == '=')
		temp = ft_substr(s, i + 1, ft_strlen(s) - i);
	return (temp);
}

t_list	*ft_search_dubname(t_list **is_head, char *name)
{
	t_env	*ls_ptr;
	t_list	*ls_tmp_head;

	ls_tmp_head = *is_head;
	while (ls_tmp_head)
	{
		ls_ptr = (t_env *)(ls_tmp_head->content);
		if (!ft_strncmp(ls_ptr->name, name, ft_strlen(name) + 1))
			break ;
		ls_tmp_head = ls_tmp_head->next;
	}
	return (ls_tmp_head);
}