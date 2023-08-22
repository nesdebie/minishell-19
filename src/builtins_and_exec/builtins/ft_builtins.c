/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:54:20 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/22 14:51:55 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(t_shell *data, int num_cmd)
{
	if (data->cmd[num_cmd].cmd == NULL)
		return (0);
	if (!ft_strncmp(data->cmd[num_cmd].cmd, "cd", 3))
		return (NO_FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "pwd", 4))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "PWD", 4))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "echo", 5))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "env", 4))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "ENV", 4))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "exit", 5))
		return (NO_FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "unset", 6))
		return (NO_FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "export", 7))
		return (NO_FORKS);
	return (0);
}

int	execute_builtin(t_shell *data, int num_cmd)
{
	if (!ft_strncmp(data->cmd[num_cmd].args[0], "pwd", 4))
		ft_pwd(data);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "PWD", 4))
		ft_pwd(data);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "echo", 5))
		ft_echo(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "cd", 3))
		ft_cd(data, num_cmd, NULL);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "env", 4))
		ft_env(&data->envp_list);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "ENV", 4))
		ft_env(&data->envp_list);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "export", 7))
		ft_export(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "unset", 6))
		ft_unset(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "exit", 5))
		ft_exit(data, num_cmd);
	return (EXIT_SUCCESS);
}
