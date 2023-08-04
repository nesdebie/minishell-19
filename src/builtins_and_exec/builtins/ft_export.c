/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:02:53 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/04 14:28:08 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_isinset(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static void	ft_print_env(t_list **is_envp_list)
{
	t_env	**env_lst;
	int		i;
	char	*s;

	s = NULL;
	i = 0;
	env_lst = ft_sortenv(is_envp_list);
	while (env_lst && env_lst[i])
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, env_lst[i]->name, ft_strlen(env_lst[i]->name));
		write(STDOUT_FILENO, "=\"", 2);
		if (ft_getenv(*is_envp_list, env_lst[i]->name))
		{
			s = ft_getenv(*is_envp_list, env_lst[i]->name);
			write(STDOUT_FILENO, s, ft_strlen(s));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
			write(STDOUT_FILENO, "\"\n", 2);
		i++;
	}
	free(env_lst);
}

static int	ft_check_name(t_shell *d, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isnum(s[0]))
		{
			printf("W3LC0M3-1N-sH3LL: export: `%s': ", s);
			printf("not a valid identifier\n");
			d->exit_code = 1;
			return (0);
		}
		if (!ft_isalnum(s[i]))
		{
			if (s[i] != '_')
			{
				printf("W3LC0M3-1N-sH3LL: export: `%s': ", s);
				printf("not a valid identifier\n");
				d->exit_code = 1;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	add_value(char *name, t_shell *d, int num_cmd, int ret)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if (!ft_check_name(d, name))
		return (-1);
	if (ft_strnstr(d->cmd[num_cmd].args[ret], "+=", ft_strlen(name) + 2))
	{
		tmp = get_value_env(d->cmd[num_cmd].args[ret]);
		if (!ft_getenv(d->envp_list, name))
			s = ft_strdup(tmp);
		else
			s = ft_strjoin(ft_getenv(d->envp_list, name), tmp);
		free(tmp);
	}
	else if (ft_isinset('=', d->cmd[num_cmd].args[ret]))
		s = get_value_env(d->cmd[num_cmd].args[ret]);
	else
		s = ft_calloc(1, 1);
	ft_putenv(&d->envp_list, name, s);
	if (!ft_strlen(s))
		ret = -1;
	free(s);
	return (ret);
}

void	ft_export(t_shell *data, int num_cmd)
{
	int		i;
	char	*name;

	if (!data->cmd[num_cmd].args[1])
		return (ft_print_env(&data->envp_list));
	i = 1;
	while (data->cmd[num_cmd].args[i] && ft_strlen(data->cmd[num_cmd].args[i]))
	{
		name = get_name_env(data->cmd[num_cmd].args[i]);
		i = add_value(name, data, num_cmd, i);
		free(name);
		if (i == -1)
			return ;
		i++;
	}
	ft_print_perror(data, NULL, 0);
}
