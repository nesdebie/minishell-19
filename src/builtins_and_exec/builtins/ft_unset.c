/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:03:58 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/02 14:45:50 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_namecmp(t_list *lst, char *str)
{
	t_env	*ptr;

	ptr = (t_env *)lst->content;
	if (!ft_strncmp(str, ptr->name, ft_strlen(ptr->name) + 1))
		return (1);
	return (0);
}

void	ft_del_var_env(void *lst)
{
	t_env	*ls_node_env;

	ls_node_env = (t_env *)(lst);
	if (ls_node_env->name)
		free(ls_node_env->name);
	if (ls_node_env->value)
		free(ls_node_env->value);
	free(ls_node_env);
}

void	ft_unset_var_env(t_list **is_envp_list, char *str)
{
	t_list	**ls_current;
	t_list	*ls_next;

	ls_current = is_envp_list;
	while (*ls_current)
	{
		if (ft_namecmp(*ls_current, str))
		{
			ls_next = (*ls_current)->next;
			ft_lstdelone(*ls_current, &ft_del_var_env);
			*ls_current = ls_next;
			break ;
		}
		ls_current = &(*ls_current)->next;
	}
}

static int	ft_is_valid_token_unset(char *s)
{
	while (s && *s)
	{
		if (!ft_isalnum(*s))
			if (*s != '_')
				return (0);
		s++;
	}
	return (1);
}

void	ft_unset(t_shell *d, int nb_cmd)
{
	int	i;

	if (!d->cmd[nb_cmd].args)
		return ;
	i = 1;
	while (d->cmd[nb_cmd].args[i])
	{
		if (ft_is_valid_token_unset(d->cmd[nb_cmd].args[i]))
			ft_unset_var_env(&d->envp_list, d->cmd[nb_cmd].args[i++]);
		else
		{
			printf("WELCOME-IN-sHELL: unset: `%s': ", d->cmd[nb_cmd].args[i++]);
			printf("not a valid identifier\n");
			d->exit_code = 1;
		}
	}
	return ;
}
