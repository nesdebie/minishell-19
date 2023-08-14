/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nesdebie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 12:00:49 by nesdebie          #+#    #+#             */
/*   Updated: 2023/08/14 14:03:16 by nesdebie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_free_cmds(t_shell *data)
{
	int	i;

	i = 0;
	while (i < data->count_cmd)
	{
		if (!is_builtin(data, i) && ft_getenv(data->envp_list, "PATH"))
			free (data->cmd[i].cmd);
		i++;
	}
}

static char	*error_path(t_shell *dt, char *command, char *tmp, char *cmd)
{
	dt->exit_code = 127;
	ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	free(command);
	free(tmp);
	free(cmd);
	return (0);
}

static char	*pre_join_path(char *cmd, t_shell *dt)
{
	if (cmd)
	{
		if (access(cmd, X_OK) && !access(cmd, F_OK) && ft_strchr(cmd, '/'))
			return (permission_error(cmd, dt));
		if (access(cmd, F_OK) && ft_strchr(cmd, '/'))
		{
			ft_no_file_dir(dt, -1, cmd);
			dt->exit_code = 127;
			return (0);
		}
	}
	else
	{
		dt->exit_code = 127;
		ft_putstr_fd("W3LC0M3-1N-sH3LL: ", 2);
		ft_putendl_fd("command not found", 2);
		return (0);
	}
	return (cmd);
}

char	*join_path(char *cmd, char **path, t_shell *dt)
{
	int		i;
	char	*tmp;
	char	*command;

	i = 0;
	if (!access(cmd, X_OK))
		return (cmd);
	if (!pre_join_path(cmd, dt))
		return (0);
	command = ft_strdup(cmd);
	tmp = ft_strjoin("/", cmd);
	cmd = ft_strjoin(path[i], tmp);
	while (path[i] && access(cmd, X_OK) != 0)
	{
		free(cmd);
		cmd = ft_strjoin(path[i++], tmp);
	}
	if (path[i] == NULL)
		return (error_path(dt, command, tmp, cmd));
	free(command);
	free(tmp);
	return (cmd);
}
