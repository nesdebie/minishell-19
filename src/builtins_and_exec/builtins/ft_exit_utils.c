/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:44:38 by mebourge          #+#    #+#             */
/*   Updated: 2023/08/27 18:47:49 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_is_digict_arg_place(t_shell *data, int num_cmd)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	while (data->cmd[num_cmd].args[2] && data->cmd[num_cmd].args[1][j])
	{
		if (!ft_isdigit(data->cmd[num_cmd].args[1][j]))
			ret = 1;
		j++;
	}
	if (ret == 1)
		ft_return_error_isnum(data, num_cmd, 1);
}

void	ft_return_error_isnum(t_shell *data, int num_cmd, int i)
{
	ft_putendl_fd("exit", 1);
	ft_putstr_fd("W3LC0M3-1N-sH3LL: exit: ", 2);
	ft_putstr_fd(data->cmd[num_cmd].args[i], 2);
	ft_putendl_fd(" : numeric argument required", 2);
	data->exit_code = 255;
	exit (255);
}
