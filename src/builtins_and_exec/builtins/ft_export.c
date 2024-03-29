/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:02:53 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/28 16:23:13 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_isinset(char c, char *set)
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

static int	ft_check_name(t_shell *d, char *s, int i)
{
	while (s[++i])
	{
		if (ft_isnum(s[0]))
		{
			ft_print_err_export(s);
			d->exit_code = 1;
			return (0);
		}
		if (!ft_isalnum(s[i]))
		{
			if (s[i] != '_')
			{
				ft_print_err_export(s);
				d->exit_code = 1;
				return (0);
			}
		}
	}
	return (1);
}

static int	add_value2(t_shell *d, char *s, char *brut, char *name)
{
	char	*str;
	int		ret;

	ret = 0;
	str = NULL;
	if (!s)
		return (-1);
	str = ft_strdup(s);
	if (!str)
	{
		free(s);
		return (-1);
	}
	if (!ft_isinset('=', brut))
		ft_putenv(&d->envp_list, name, str, 0);
	else
		ft_putenv(&d->envp_list, name, str, 1);
	if (!ft_strlen(str))
		ret = -1;
	free(s);
	free(str);
	return (ret);
}

int	add_value(char *name, t_shell *d, int num_cmd, int ret)
{
	char	*s;
	char	*tmp;

	s = NULL;
	if (!ft_check_name(d, name, -1))
		return (-1);
	if (ft_strnstr(d->cmd[num_cmd].args[ret], "+=", ft_strlen(name) + 2))
	{
		tmp = get_value_env(d->cmd[num_cmd].args[ret]);
		if (!tmp)
			return (-1);
		if (!ft_getenv(d->envp_list, name))
			s = ft_strdup(tmp);
		else
			s = ft_strjoin_export(ft_getenv(d->envp_list, name), tmp, 0);
		free(tmp);
	}
	else if (ft_isinset('=', d->cmd[num_cmd].args[ret]))
		s = get_value_env(d->cmd[num_cmd].args[ret]);
	else
		s = ft_calloc(1, 1);
	return (add_value2(d, s, d->cmd[num_cmd].args[ret], name));
}

void	ft_export(t_shell *data, int num_cmd)
{
	int		i;
	char	*name;

	data->exit_code = 0;
	if (!data->cmd[num_cmd].args[1])
		return (ft_print_env(&data->envp_list));
	i = 1;
	while (data->cmd[num_cmd].args[i] && ft_strlen(data->cmd[num_cmd].args[i]))
	{
		name = get_name_env(data->cmd[num_cmd].args[i]);
		if (!name || !ft_strlen(name))
		{
			ft_print_err_export(name);
			data->exit_code = 1;
			return ;
		}
		add_value(name, data, num_cmd, i);
		free(name);
		i++;
	}
}
