/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:01:23 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/04 16:22:06 by nesdebie         ###   ########.fr       */
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
/*
static void	ft_echo_print(char *s, int flag)
{
	if (!flag)
	{
		ft_putstr_fd(s, STDOUT_FILENO);
		if (ft_strncmp(s, "$", 1))
			write(STDOUT_FILENO, " ", 1);
	}
	else
	{
		ft_putstr_fd(s, STDOUT_FILENO);
		write(STDOUT_FILENO, " ", 1);
	}
}*/

static void ft_print(t_shell *d, char *s)
{
	int	i;
	int j;
	char *tmp;

	i = 0;
	while(s[i])
	{
		if (s[i] == '$')
		{
			i++;
			if (s[i] == '?')
				ft_putnbr_fd(d->exit_code, STDOUT_FILENO);
			else
			{
				j = i + 1;
				while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
					j++;
				tmp = ft_substr(s, i, j);
				if (ft_getenv(d->envp_list, tmp))
					ft_putstr_fd(ft_getenv(d->envp_list, tmp), STDOUT_FILENO);
				free (tmp);
				i = j;
			}
		}
		else
			ft_putchar_fd(s[i], STDOUT_FILENO);
		i++;
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
			/**if (!ft_strncmp(d->cmd[num_cmd].args[i], "$?", 3))
				ft_putnbr_fd(d->exit_code, 1);
			else if (!d->cmd[num_cmd].args[i + 1])
				ft_putstr_fd(d->cmd[num_cmd].args[i], STDOUT_FILENO);
			else if ((!flag && i > 1) || (flag && i > flag + 1))
				ft_echo_print(d->cmd[num_cmd].args[i], 1);
			else
				ft_echo_print(d->cmd[num_cmd].args[i], 0);**/
			ft_print(d, d->cmd[num_cmd].args[i]); // PAS AU POINT
		}
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	d->exit_code = 0;
}
