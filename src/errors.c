/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:45:11 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/20 09:23:06 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*permission_error(char *cmd, t_shell *dt)
{
	printf("prompt: %s: permission denied\n", cmd);
	dt->exit_code = 126;
	return (0);
}

int	ft_print_error(t_shell *data, const char *str, int nbr)
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

int	ft_no_file_dir(int fd, char *name)
{
	if (fd == -1)
	{
		ft_putstr_fd("prompt: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(": No such file or directory", 2);
		return (1);
	}
	return (0);
}
