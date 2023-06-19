/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:45:11 by nesdebie          #+#    #+#             */
/*   Updated: 2023/06/19 12:08:10 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*permission_error(char *cmd, t_shell *dt)
{
	printf("not-bash: %s: permission denied\n", cmd);
	dt->exit_code = 126;
	return (NULL);
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
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

int	ft_no_file_dir(int fd, char *name)
{
	if (fd == -1)
	{
		ft_putstr_fd("not-bash: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}