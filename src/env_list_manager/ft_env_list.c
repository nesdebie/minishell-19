/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:49:23 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/23 12:05:31 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_add2list(t_list *is_envp_list, char *i_str)
{
	t_env	*ls_content;
	char	**ls_val_env;

	if (!i_str)
		return (0);
	ls_content = malloc(sizeof(t_env));
	if (!ls_content)
		return (0);
	ls_val_env = ft_minisplit(i_str);
	if (!ls_val_env)
	{
		free(ls_content);
		return (0);
	}
	ls_content->name = ls_val_env[0];
	ls_content->value = ls_val_env[1];
	ft_lstadd_back(&is_envp_list, ft_lstnew(ls_content));
	free(ls_val_env);
	return (is_envp_list);
}

static int	ft_insnewlst(t_list **is_head, char *name, char *val)
{
	t_env	*content;

	content = malloc(sizeof(t_env));
	if (!is_head || !name || !val || !content)
		return (1);
	content->name = ft_calloc(ft_strlen(name) + 1, sizeof(char));
	if (!content->name)
		return (1);
	content->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
	if (!content->value)
	{
		free(content->name);
		return (1);
	}
	content->name = ft_memcpy(content->name, name, ft_strlen(name));
	content->value = ft_memcpy(content->value, val, ft_strlen(val) + 1);
	ft_lstadd_back(is_head, ft_lstnew(content));
	return (0);
}

int	ft_putenv(t_list **is_head, char *name, char *val)
{
	t_env	*ls_ptr;
	t_list	*ls_tmp_head;

	ls_tmp_head = ft_search_dubname(is_head, name);
	if (ls_tmp_head)
	{
		ls_ptr = (t_env *)(ls_tmp_head->content);
		free(ls_ptr->value);
		ls_ptr->value = ft_calloc(ft_strlen(val) + 1, sizeof(char));
		if (ls_ptr->value)
			ls_ptr->value = ft_memcpy(ls_ptr->value, val, ft_strlen(val));
	}
	else
		return (ft_insnewlst(is_head, name, val));
	if (ls_ptr->value)
		return (0);
	else
		return (1);
}

char	*ft_getenv(t_list *is_head, char *i_str)
{
	t_env	*val;

	if (!is_head || !i_str)
		return (0);
	while (is_head)
	{
		val = (t_env *)(is_head->content);
		if (!ft_strncmp(val->name, i_str, ft_strlen(i_str) + 1))
			return (val->value);
		is_head = is_head->next;
	}
	return (0);
}

t_list	*ft_init_env(t_shell *data, char **env)
{
	int		i;
	t_list	*ls_envp_list;

	i = 0;
	ls_envp_list = NULL;
	while (env && env[i])
		ls_envp_list = ft_add2list(ls_envp_list, env[i++]);
	if (!ls_envp_list || !i)
	{
		ft_print_perror(data, "env list failed", 1);
		ft_free_env(&ls_envp_list);
		return (0);
	}
	return (ls_envp_list);
}
