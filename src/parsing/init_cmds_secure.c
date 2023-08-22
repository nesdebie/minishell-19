/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_secure.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mebourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 19:00:56 by mebourge          #+#    #+#             */
/*   Updated: 2023/08/22 19:01:08 by mebourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_supp_null_args(t_shell *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->count_cmd && data->cmd[i].cmd)
	{
		j = 0;
		while (data->cmd[i].args[j])
		{
			if (!ft_strlen(data->cmd[i].args[j]))
			{
				while (data->cmd[i].args[j])
				{
					data->cmd[i].args[j] = data->cmd[i].args[j + 1];
					j++;
				}
				continue ;
			}
			j++;
		}
		i++;
	}
}
