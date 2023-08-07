/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:01:23 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/07 15:22:45 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	ft_is_flag_echo(char *s)
{
	if (!s || *s != '-')
		return (0);
	s++;
	if (!(*s))
		return (0);
	while (*s)
	{
		if (*s != 'n')
			return (0);
		s++;
	}
	return (1);
}

static int	ft_add_flag(char **args)
{
	int	i;
	int	c;

	i = 2;
	c = 0;
	while (args[i])
	{
		if (ft_is_flag_echo(args[i]))
			c++;
		else
			break ;
		i++;
	}
	return (c);
}

static void	ft_parse_and_write(t_shell *d, char *s)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			j = i + 1;
			while (s[i + j] && s[i + j] != '$')
				j++;
			tmp = ft_substr(s, i + 1, j - 1);
			if (!tmp)
				return ;
			if (tmp[0] == '?')
			{
				ft_putnbr_fd(d->exit_code, STDOUT_FILENO);
				if (tmp[1] == '?')
					tmp = ft_substr(tmp, i + 2, j);
				else 
					tmp = ft_substr(tmp, i + 1, j);
			}
			if (ft_getenv(d->envp_list, tmp))
				ft_putstr_fd(ft_getenv(d->envp_list, tmp), STDOUT_FILENO);
			else
				ft_putstr_fd(tmp, STDOUT_FILENO);
			i = j;
			free(tmp);
		}
		else
		{
			ft_putchar_fd(s[i], STDOUT_FILENO);
			i++;
		}
	}
}

void	ft_echo(t_shell *d, int num_cmd)
{
	int	i;
	int	flag;

	i = 1;
	flag = ft_is_flag_echo(d->cmd[num_cmd].args[i]);
	if (flag)
		i += ft_add_flag(d->cmd[num_cmd].args) + 1;
	while (d->cmd[num_cmd].args[i])
	{
		if (ft_strlen(d->cmd[num_cmd].args[i]))
		{
			if (ft_strnstr(d->cmd[num_cmd].args[i], "$?", ft_strlen(d->cmd[num_cmd].args[i])))
				ft_parse_and_write(d, d->cmd[num_cmd].args[i]);
			else
				ft_putstr_fd(d->cmd[num_cmd].args[i], STDOUT_FILENO);
			if (d->cmd[num_cmd].args[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	d->exit_code = 0;
}
