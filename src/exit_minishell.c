/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 16:07:25 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/16 11:53:52 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit_minishell(t_shell *data)
{
	if (data->count_cmd == 1)
		ft_putendl_fd("exit", 1);
	if (data->envp_list)
		ft_free_env(&data->envp_list);
	if (data->cmd && data->count_cmd > 0)
		free_shell(data);
	exit(data->exit_code);
}
