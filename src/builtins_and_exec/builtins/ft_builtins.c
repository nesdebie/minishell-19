/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:54:20 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/02 14:13:11 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	is_builtin(t_shell *data, int num_cmd)
{
	if (data->cmd[num_cmd].cmd == NULL)
		return (0);
	if (!ft_strncmp(data->cmd[num_cmd].cmd, "cd", 2))
		return (NO_FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "pwd", 3))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "PWD", 3))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "echo", 4))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "env", 3))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "ENV", 3))
		return (FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "exit", 4))
		return (NO_FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "unset", 5))
		return (NO_FORKS);
	else if (!ft_strncmp(data->cmd[num_cmd].cmd, "export", 6))
		return (NO_FORKS);
	return (0);
}

int	execute_builtin(t_shell *data, int num_cmd)
{
	if (!ft_strncmp(data->cmd[num_cmd].args[0], "pwd", 3))
		ft_pwd(data);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "PWD", 3))
		ft_pwd(data);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "echo", 4))
		ft_echo(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "cd", 2))
		ft_cd(data, num_cmd, NULL);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "env", 3))
		ft_env(&data->envp_list);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "ENV", 3))
		ft_env(&data->envp_list);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "export", 6))
		ft_export(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "unset", 5))
		ft_unset(data, num_cmd);
	else if (!ft_strncmp(data->cmd[num_cmd].args[0], "exit", 4))
		ft_exit(data, num_cmd);
	return (EXIT_SUCCESS);
}
