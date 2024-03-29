/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:45:11 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/29 10:00:09 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	no_home_err(t_shell *sh)
{
	ft_putendl_fd("bash: cd: HOME not set", 2);
	sh->exit_code = 1;
	return (sh->exit_code);
}

char	*permission_error(char *cmd, t_shell *dt)
{
	ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": Permission denied", 2);
	dt->exit_code = 126;
	return (0);
}

int	ft_print_perror(t_shell *data, const char *str, int nbr)
{
	if (str)
		perror(str);
	if (nbr < 0)
		nbr = EXIT_FAILURE;
	data->exit_code = nbr;
	return (nbr);
}

void	ft_print_err_export(char *str)
{
	ft_putstr_fd("export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
}

int	ft_no_file_dir(t_shell *data, int fd, char *name, int exit)
{
	if (fd == -1)
	{
		if (errno == EACCES)
			permission_error(name, data);
		else
		{
			ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
			ft_putstr_fd(name, 2);
			ft_putendl_fd(": No such file or directory", 2);
		}
		data->exit_code = exit;
		return (1);
	}
	return (0);
}
